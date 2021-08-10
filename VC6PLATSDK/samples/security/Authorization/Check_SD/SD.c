/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1997 - 2000.  Microsoft Corporation.  All rights reserved

Module Name:

    sd.c

Abstract:

    This module contains functions to obtain a variety of different components contained in a
    Security Descriptor.  This includes an owner (SID), a primary group (SID), a discretionary
    ACL (DACL), and a system ACL (SACL).

    DumpAclInfo()    - obtains a variety of information on an ACL applies to
                       both DACLs and SACLs
    DumpControl()    - returns control information which describes the format
                       of the security descriptor, absolute or relative, whether a
                       DACL and/or SACL is present and whether they were set using
                       a default mechanism
    DumpDacl()       - returns information associated with the DACL or SACL and
                       all ACEs.  NOTE: in order to obtain a SACL for an object, you need
                       ACCESS_SYSTEM_SECURITY access to the securable object plus the process
                       obtaining the SACL needs to have the SE_SECURITY_NAME ("manager auditing
                       and security log") privilege which also needs to be enabled.
    DumpOwnerGroup() - returns information on either the owner or primary group
    DumpSD()         - bundles up all the other security descriptor calls to one function
                       call
    DumpSDInfo()     - returns whether the security descriptor is valid and it's
                       length

--*/

#include "check_sd.h"
#include <tchar.h>
#include <stdio.h>
#include <lmcons.h>

DWORD DumpAclInfo(PACL pacl, BOOL bDacl)
{
     ACL_INFORMATION_CLASS    aic;
     BYTE                     pByte[2][12];

     //
     // is the acl valid
     //
     _tprintf(TEXT("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"));
     if (bDacl)
          _tprintf(TEXT(">>                 DACL INFORMATION                    >>\n"));
     else
          _tprintf(TEXT(">>                 SACL INFORMATION                    >>\n"));

     _tprintf(TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"));
     _tprintf(TEXT("valid .............. "));

     if (!IsValidAcl(pacl)){
          _tprintf(TEXT("no\n"));
          return 0;
     }
     else
          _tprintf(TEXT("yes\n"));

     for (aic=1; aic<3; aic++){
          if (!GetAclInformation(pacl, (LPVOID)pByte[aic-1], sizeof(ACL_SIZE_INFORMATION), aic))
               DisplayError(GetLastError(), TEXT("GetAclInformation"));
     }

     _tprintf(TEXT("revision ........... %u\n\n"), *((PACL_REVISION_INFORMATION)pByte[0]));
     _tprintf(TEXT("ace count .......... %u\n"), ((PACL_SIZE_INFORMATION)pByte[1])->AceCount);
     _tprintf(TEXT("acl bytes in use ... %u byte(s)\n"), ((PACL_SIZE_INFORMATION)pByte[1])->AclBytesInUse);
     _tprintf(TEXT("acl bytes free ..... %u byte(s)\n"), ((PACL_SIZE_INFORMATION)pByte[1])->AclBytesFree);

     return ((PACL_SIZE_INFORMATION)pByte[1])->AceCount;
}

void DumpControl(PSECURITY_DESCRIPTOR psd)
{
     DWORD                       dwRevision;
     SECURITY_DESCRIPTOR_CONTROL sdc;

     if (!GetSecurityDescriptorControl(psd, &sdc, &dwRevision))
          DisplayError(GetLastError(), TEXT("GetSecurityDescriptorControl"));

     _tprintf(TEXT("revision ........... %u\n"), dwRevision);
     _tprintf(TEXT("control bits ....... 0x%X\n"), sdc);

     if ((sdc & SE_DACL_DEFAULTED) == SE_DACL_DEFAULTED)
          _tprintf(TEXT(".................... SE_DACL_DEFAULTED\n"));
     if ((sdc & SE_DACL_PRESENT) == SE_DACL_PRESENT)
          _tprintf(TEXT(".................... SE_DACL_PRESENT\n"));
     if ((sdc & SE_GROUP_DEFAULTED) == SE_GROUP_DEFAULTED)
          _tprintf(TEXT(".................... SE_GROUP_DEFAULTED\n"));
     if ((sdc & SE_OWNER_DEFAULTED) == SE_OWNER_DEFAULTED)
          _tprintf(TEXT(".................... SE_OWNER_DEFAULTED\n"));
     if ((sdc & SE_SACL_DEFAULTED) == SE_SACL_DEFAULTED)
          _tprintf(TEXT(".................... SE_SACL_DEFAULTED\n"));
     if ((sdc & SE_SACL_PRESENT) == SE_SACL_PRESENT)
          _tprintf(TEXT(".................... SE_SACL_PRESENT\n"));
     if ((sdc & SE_SELF_RELATIVE) == SE_SELF_RELATIVE)
          _tprintf(TEXT(".................... SE_SELF_RELATIVE\n"));
     if ((sdc & SE_DACL_AUTO_INHERITED) == SE_DACL_AUTO_INHERITED) // NT5.0
          _tprintf(TEXT(".................... SE_DACL_AUTO_INHERITED\n"));
     if ((sdc & SE_SACL_AUTO_INHERITED) == SE_SACL_AUTO_INHERITED) // NT5.0
          _tprintf(TEXT(".................... SE_SACL_AUTO_INHERITED\n"));
     if ((sdc & SE_SACL_PROTECTED) == SE_SACL_PROTECTED) // NT5.0
          _tprintf(TEXT(".................... SE_SACL_PROTECTED\n"));
     if ((sdc & SE_DACL_PROTECTED) == SE_DACL_PROTECTED) // NT5.0
          _tprintf(TEXT(".................... SE_DACL_PROTECTED\n"));
}

void DumpDacl(PSECURITY_DESCRIPTOR psd, TCHAR c, BOOL bDacl)
{
     ACCESS_ALLOWED_ACE *pace;
     BOOL                bDaclPresent;
     BOOL                bDaclDefaulted;
     DWORD               dwAceCount;
     DWORD               cbName;
     DWORD               cbReferencedDomainName;
     DWORD               dwSize;
     int                 i;
     PACL                pacl;
     PSID                psid = NULL;
     SID_NAME_USE        snu;
     TCHAR               szName[UNLEN];
     TCHAR               szReferencedDomainName[DNLEN];
     TCHAR               szSidText[256];
     TCHAR               szSidType[][17] = {TEXT("User"), TEXT("Group"), TEXT("Domain"), TEXT("Alias"), TEXT("Well Known Group"), TEXT("Deleted Account"), TEXT("Invalid"), TEXT("Unknown")};

     if (bDacl){
          if (!GetSecurityDescriptorDacl(psd, &bDaclPresent, &pacl, &bDaclDefaulted))
               DisplayError(GetLastError(), TEXT("GetSecurityDescriptorDacTEXT("));
     }
     else{
          if (!GetSecurityDescriptorSacl(psd, &bDaclPresent, &pacl, &bDaclDefaulted))
               DisplayError(GetLastError(), TEXT("GetSecurityDescriptorSacTEXT("));
     }

     if (bDaclPresent){
          //
          // dump the dacl
          //
          if (pacl == NULL){
               if (bDacl)
                    _tprintf(TEXT("\ndacl ............... NULL\n"));
               else
                    _tprintf(TEXT("\nsacl ............... NULL\n"));
          }
          else{
               dwAceCount = DumpAclInfo(pacl, bDacl);

               for (i = 0; i < (int)dwAceCount; i++){
                    if (!GetAce(pacl, i, (LPVOID)&pace))
                         DisplayError(GetLastError(), TEXT("GetAce"));

                    _tprintf(TEXT("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"));
                    _tprintf(TEXT(">>                  ACE #%u                             >>\n"), i+1);
                    _tprintf(TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"));
                    _tprintf(TEXT("type ............... "));

                    switch(pace->Header.AceType){
                         case ACCESS_ALLOWED_ACE_TYPE:
                              _tprintf(TEXT("ACCESS_ALLOWED_ACE\n"));
                              break;
                         case ACCESS_DENIED_ACE_TYPE:
                              _tprintf(TEXT("ACCESS_DENIED_ACE\n"));
                              break;
                         case SYSTEM_AUDIT_ACE_TYPE:
                              _tprintf(TEXT("SYSTEM_AUDIT_ACE\n"));
                              break;
                         case ACCESS_ALLOWED_OBJECT_ACE_TYPE: // NT5.0
                              _tprintf(TEXT("ACCESS_ALLOWED_OBJECT_ACE_TYPE\n"));
                              break;
                         case ACCESS_DENIED_OBJECT_ACE_TYPE: // NT5.0
                              _tprintf(TEXT("ACCESS_DENIED_OBJECT_ACE_TYPE\n"));
                              break;
                         case SYSTEM_AUDIT_OBJECT_ACE_TYPE: // NT5.0
                              _tprintf(TEXT("SYSTEM_AUDIT_OBJECT_ACE_TYPE\n"));
                              break;
                    }

                    _tprintf(TEXT("flags .............. 0x%X\n"), pace->Header.AceFlags);

                    if ((pace->Header.AceFlags & CONTAINER_INHERIT_ACE) == CONTAINER_INHERIT_ACE)
                         _tprintf(TEXT(".................... CONTAINER_INHERIT_ACE\n"));

                    if ((pace->Header.AceFlags & INHERIT_ONLY_ACE) == INHERIT_ONLY_ACE)
                         _tprintf(TEXT(".................... INHERIT_ONLY_ACE\n"));

                    if ((pace->Header.AceFlags & NO_PROPAGATE_INHERIT_ACE) == NO_PROPAGATE_INHERIT_ACE)
                         _tprintf(TEXT(".................... NO_PROPAGATE_INHERIT_ACE\n"));

                    if ((pace->Header.AceFlags & OBJECT_INHERIT_ACE) == OBJECT_INHERIT_ACE)
                         _tprintf(TEXT(".................... OBJECT_INHERIT_ACE\n"));

                    if ((pace->Header.AceFlags & FAILED_ACCESS_ACE_FLAG) == FAILED_ACCESS_ACE_FLAG)
                         _tprintf(TEXT(".................... FAILED_ACCESS_ACE_FLAG\n"));

                    if ((pace->Header.AceFlags & SUCCESSFUL_ACCESS_ACE_FLAG) == SUCCESSFUL_ACCESS_ACE_FLAG)
                         _tprintf(TEXT(".................... SUCCESSFUL_ACCESS_ACE_FLAG\n"));

                    if ((pace->Header.AceFlags & INHERITED_ACE) == INHERITED_ACE) // NT5.0
                         _tprintf(TEXT(".................... INHERITED_ACE\n"));

                    _tprintf(TEXT("size ............... %u byte(s)\n"), pace->Header.AceSize);
                    _tprintf(TEXT("mask ............... 0x%X\n"), pace->Mask);

                    switch (c){
                         case 'r':
                              //
                              // registry SPECIFIC access rights
                              //
                              if ((pace->Mask & KEY_CREATE_LINK) == KEY_CREATE_LINK)
                                   _tprintf(TEXT(".................... KEY_CREATE_LINK\n"));
                              if ((pace->Mask & KEY_CREATE_SUB_KEY) == KEY_CREATE_SUB_KEY)
                                   _tprintf(TEXT(".................... KEY_CREATE_SUB_KEY\n"));
                              if ((pace->Mask & KEY_ENUMERATE_SUB_KEYS) == KEY_ENUMERATE_SUB_KEYS)
                                   _tprintf(TEXT(".................... KEY_ENUMERATE_SUB_KEYS\n"));
                              if ((pace->Mask & KEY_EXECUTE) == KEY_EXECUTE)
                                   _tprintf(TEXT(".................... KEY_EXECUTE\n"));
                              if ((pace->Mask & KEY_NOTIFY) == KEY_NOTIFY)
                                   _tprintf(TEXT(".................... KEY_NOTIFY\n"));
                              if ((pace->Mask & KEY_QUERY_VALUE) == KEY_QUERY_VALUE)
                                   _tprintf(TEXT(".................... KEY_QUERY_VALUE\n"));
                              if ((pace->Mask & KEY_READ) == KEY_READ)
                                   _tprintf(TEXT(".................... KEY_READ\n"));
                              if ((pace->Mask & KEY_SET_VALUE) == KEY_SET_VALUE)
                                   _tprintf(TEXT(".................... KEY_SET_VALUE\n"));
                              if ((pace->Mask & KEY_WRITE) == KEY_WRITE)
                                   _tprintf(TEXT(".................... KEY_WRITE\n"));
                              break;
                         case 'f':
                              if ((pace->Mask & FILE_READ_DATA) == FILE_READ_DATA)
                                   _tprintf(TEXT(".................... FILE_READ_DATA\n"));
                              if ((pace->Mask & FILE_WRITE_DATA) == FILE_WRITE_DATA)
                                   _tprintf(TEXT(".................... FILE_WRITE_DATA\n"));
                              if ((pace->Mask & FILE_APPEND_DATA) == FILE_APPEND_DATA)
                                   _tprintf(TEXT(".................... FILE_APPEND_DATA\n"));
                              if ((pace->Mask & FILE_READ_EA) == FILE_READ_EA)
                                   _tprintf(TEXT(".................... FILE_READ_EA\n"));
                              if ((pace->Mask & FILE_WRITE_EA) == FILE_WRITE_EA)
                                   _tprintf(TEXT(".................... FILE_WRITE_EA\n"));
                              if ((pace->Mask & FILE_EXECUTE) == FILE_EXECUTE)
                                   _tprintf(TEXT(".................... FILE_EXECUTE\n"));
                              if ((pace->Mask & FILE_READ_ATTRIBUTES) == FILE_READ_ATTRIBUTES)
                                   _tprintf(TEXT(".................... FILE_READ_ATTRIBUTES\n"));
                              if ((pace->Mask & FILE_WRITE_ATTRIBUTES) == FILE_WRITE_ATTRIBUTES)
                                   _tprintf(TEXT(".................... FILE_WRITE_ATTRIBUTES\n"));
                              break;
                         case 'd':
                              if ((pace->Mask & FILE_LIST_DIRECTORY) == FILE_LIST_DIRECTORY)
                                   _tprintf(TEXT(".................... FILE_LIST_DIRECTORY\n"));
                              if ((pace->Mask & FILE_ADD_FILE) == FILE_ADD_FILE)
                                   _tprintf(TEXT(".................... FILE_ADD_FILE\n"));
                              if ((pace->Mask & FILE_ADD_SUBDIRECTORY) == FILE_ADD_SUBDIRECTORY)
                                   _tprintf(TEXT(".................... FILE_ADD_SUBDIRECTORY\n"));
                              if ((pace->Mask & FILE_READ_EA) == FILE_READ_EA)
                                   _tprintf(TEXT(".................... FILE_READ_EA\n"));
                              if ((pace->Mask & FILE_WRITE_EA) == FILE_WRITE_EA)
                                   _tprintf(TEXT(".................... FILE_WRITE_EA\n"));
                              if ((pace->Mask & FILE_TRAVERSE) == FILE_TRAVERSE)
                                   _tprintf(TEXT(".................... FILE_TRAVERSE\n"));
                              if ((pace->Mask & FILE_DELETE_CHILD) == FILE_DELETE_CHILD)
                                   _tprintf(TEXT(".................... FILE_DELETE_CHILD\n"));
                              if ((pace->Mask & FILE_READ_ATTRIBUTES) == FILE_READ_ATTRIBUTES)
                                   _tprintf(TEXT(".................... FILE_READ_ATTRIBUTES\n"));
                              if ((pace->Mask & FILE_WRITE_ATTRIBUTES) == FILE_WRITE_ATTRIBUTES)
                                   _tprintf(TEXT(".................... FILE_WRITE_ATTRIBUTES\n"));
                              break;
                         case 'e':
                              if ((pace->Mask & EVENT_MODIFY_STATE) == EVENT_MODIFY_STATE)
                                   _tprintf(TEXT(".................... EVENT_MODIFY_STATE\n"));
                              break;
                         case 'm':
                              if ((pace->Mask & MUTANT_QUERY_STATE) == MUTANT_QUERY_STATE)
                                   _tprintf(TEXT(".................... MUTANT_QUERY_STATE\n"));
                              break;
                         case 's':
                              if ((pace->Mask & SEMAPHORE_MODIFY_STATE) == SEMAPHORE_MODIFY_STATE)
                                   _tprintf(TEXT(".................... SEMAPHORE_MODIFY_STATE\n"));
                              break;
                         case 'p':
                              if ((pace->Mask & PROCESS_TERMINATE) == PROCESS_TERMINATE)
                                   _tprintf(TEXT(".................... PROCESS_TERMINATE\n"));
                              if ((pace->Mask & PROCESS_CREATE_THREAD) == PROCESS_CREATE_THREAD)
                                   _tprintf(TEXT(".................... PROCESS_CREATE_THREAD\n"));
                              if ((pace->Mask & PROCESS_VM_OPERATION) == PROCESS_VM_OPERATION)
                                   _tprintf(TEXT(".................... PROCESS_VM_OPERATION\n"));
                              if ((pace->Mask & PROCESS_VM_READ) == PROCESS_VM_READ)
                                   _tprintf(TEXT(".................... PROCESS_VM_READ\n"));
                              if ((pace->Mask & PROCESS_VM_WRITE) == PROCESS_VM_WRITE)
                                   _tprintf(TEXT(".................... PROCESS_VM_WRITE\n"));
                              if ((pace->Mask & PROCESS_DUP_HANDLE) == PROCESS_DUP_HANDLE)
                                   _tprintf(TEXT(".................... PROCESS_DUP_HANDLE\n"));
                              if ((pace->Mask & PROCESS_CREATE_PROCESS) == PROCESS_CREATE_PROCESS)
                                   _tprintf(TEXT(".................... PROCESS_CREATE_PROCESS\n"));
                              if ((pace->Mask & PROCESS_SET_QUOTA) == PROCESS_SET_QUOTA)
                                   _tprintf(TEXT(".................... PROCESS_SET_QUOTA\n"));
                              if ((pace->Mask & PROCESS_SET_INFORMATION) == PROCESS_SET_INFORMATION)
                                   _tprintf(TEXT(".................... PROCESS_SET_INFORMATION\n"));
                              if ((pace->Mask & PROCESS_QUERY_INFORMATION) == PROCESS_QUERY_INFORMATION)
                                   _tprintf(TEXT(".................... PROCESS_QUERY_INFORMATION\n"));
                              break;
                         case 'i':
                              if ((pace->Mask & SECTION_QUERY) == SECTION_QUERY)
                                   _tprintf(TEXT(".................... SECTION_QUERY\n"));
                              if ((pace->Mask & SECTION_MAP_WRITE) == SECTION_MAP_WRITE)
                                   _tprintf(TEXT(".................... SECTION_MAP_WRITE\n"));
                              if ((pace->Mask & SECTION_MAP_READ) == SECTION_MAP_READ)
                                   _tprintf(TEXT(".................... SECTION_MAP_READ\n"));
                              if ((pace->Mask & SECTION_MAP_EXECUTE) == SECTION_MAP_EXECUTE)
                                   _tprintf(TEXT(".................... SECTION_MAP_EXECUTE\n"));
                              if ((pace->Mask & SECTION_EXTEND_SIZE) == SECTION_EXTEND_SIZE)
                                   _tprintf(TEXT(".................... SECTION_EXTEND_SIZE\n"));
                              break;
                         case 'v':
                              if ((pace->Mask & SERVICE_CHANGE_CONFIG) == SERVICE_CHANGE_CONFIG)
                                   _tprintf(TEXT(".................... SERVICE_CHANGE_CONFIG\n"));
                              if ((pace->Mask & SERVICE_ENUMERATE_DEPENDENTS) == SERVICE_ENUMERATE_DEPENDENTS)
                                   _tprintf(TEXT(".................... SERVICE_ENUMERATE_DEPENDENTS\n"));
                              if ((pace->Mask & SERVICE_INTERROGATE) == SERVICE_INTERROGATE)
                                   _tprintf(TEXT(".................... SERVICE_INTERROGATE\n"));
                              if ((pace->Mask & SERVICE_PAUSE_CONTINUE) == SERVICE_PAUSE_CONTINUE)
                                   _tprintf(TEXT(".................... SERVICE_PAUSE_CONTINUE\n"));
                              if ((pace->Mask & SERVICE_QUERY_CONFIG) == SERVICE_QUERY_CONFIG)
                                   _tprintf(TEXT(".................... SERVICE_QUERY_CONFIG\n"));
                              if ((pace->Mask & SERVICE_QUERY_STATUS) == SERVICE_QUERY_STATUS)
                                   _tprintf(TEXT(".................... SERVICE_QUERY_STATUS\n"));
                              if ((pace->Mask & SERVICE_START) == SERVICE_START)
                                   _tprintf(TEXT(".................... SERVICE_START\n"));
                              if ((pace->Mask & SERVICE_STOP) == SERVICE_STOP)
                                   _tprintf(TEXT(".................... SERVICE_STOP\n"));
                              if ((pace->Mask & SERVICE_USER_DEFINED_CONTROL) == SERVICE_USER_DEFINED_CONTROL)
                                   _tprintf(TEXT(".................... SERVICE_USER_DEFINED_CONTROL\n"));
                              break;
                         case 'w':
                              if ((pace->Mask & WINSTA_ACCESSCLIPBOARD) == WINSTA_ACCESSCLIPBOARD)
                                   _tprintf(TEXT(".................... WINSTA_ACCESSCLIPBOARD\n"));
                              if ((pace->Mask & WINSTA_ACCESSGLOBALATOMS) == WINSTA_ACCESSGLOBALATOMS)
                                   _tprintf(TEXT(".................... WINSTA_ACCESSGLOBALATOMS\n"));
                              if ((pace->Mask & WINSTA_CREATEDESKTOP) == WINSTA_CREATEDESKTOP)
                                   _tprintf(TEXT(".................... WINSTA_CREATEDESKTOP\n"));
                              if ((pace->Mask & WINSTA_ENUMDESKTOPS) == WINSTA_ENUMDESKTOPS)
                                   _tprintf(TEXT(".................... WINSTA_ENUMDESKTOPS\n"));
                              if ((pace->Mask & WINSTA_ENUMERATE) == WINSTA_ENUMERATE)
                                   _tprintf(TEXT(".................... WINSTA_ENUMERATE\n"));
                              if ((pace->Mask & WINSTA_EXITWINDOWS) == WINSTA_EXITWINDOWS)
                                   _tprintf(TEXT(".................... WINSTA_EXITWINDOWS\n"));
                              if ((pace->Mask & WINSTA_READATTRIBUTES) == WINSTA_READATTRIBUTES)
                                   _tprintf(TEXT(".................... WINSTA_READATTRIBUTES\n"));
                              if ((pace->Mask & WINSTA_READSCREEN) == WINSTA_READSCREEN)
                                   _tprintf(TEXT(".................... WINSTA_READSCREEN\n"));
                              if ((pace->Mask & WINSTA_WRITEATTRIBUTES) == WINSTA_WRITEATTRIBUTES)
                                   _tprintf(TEXT(".................... WINSTA_WRITEATTRIBUTES\n"));
                              break;
                         case 'k':
                              if ((pace->Mask & DESKTOP_CREATEMENU) == DESKTOP_CREATEMENU)
                                   _tprintf(TEXT(".................... DESKTOP_CREATEMENU\n"));
                              if ((pace->Mask & DESKTOP_CREATEWINDOW) == DESKTOP_CREATEWINDOW)
                                   _tprintf(TEXT(".................... DESKTOP_CREATEWINDOW\n"));
                              if ((pace->Mask & DESKTOP_ENUMERATE) == DESKTOP_ENUMERATE)
                                  _tprintf(TEXT(".................... DESKTOP_ENUMERATE\n"));
                              if ((pace->Mask & DESKTOP_HOOKCONTROL) == DESKTOP_HOOKCONTROL)
                                   _tprintf(TEXT(".................... DESKTOP_HOOKCONTROL\n"));
                              if ((pace->Mask & DESKTOP_JOURNALPLAYBACK) == DESKTOP_JOURNALPLAYBACK)
                                   _tprintf(TEXT(".................... DESKTOP_JOURNALPLAYBACK\n"));
                              if ((pace->Mask & DESKTOP_JOURNALRECORD) == DESKTOP_JOURNALRECORD)
                                   _tprintf(TEXT(".................... DESKTOP_JOURNALRECORD\n"));
                              if ((pace->Mask & DESKTOP_READOBJECTS) == DESKTOP_READOBJECTS)
                                   _tprintf(TEXT(".................... DESKTOP_READOBJECTS\n"));
                              if ((pace->Mask & DESKTOP_SWITCHDESKTOP) == DESKTOP_SWITCHDESKTOP)
                                   _tprintf(TEXT(".................... DESKTOP_SWITCHDESKTOP\n"));
                              if ((pace->Mask & DESKTOP_WRITEOBJECTS) == DESKTOP_WRITEOBJECTS)
                                   _tprintf(TEXT(".................... DESKTOP_WRITEOBJECTS\n"));
                              break;
                         case 'l':
                              if ((pace->Mask & SERVER_ACCESS_ADMINISTER) == SERVER_ACCESS_ADMINISTER)
                                   _tprintf(TEXT(".................... SERVER_ACCESS_ADMINISTER\n"));
                              if ((pace->Mask & SERVER_ACCESS_ENUMERATE) == SERVER_ACCESS_ENUMERATE)
                                   _tprintf(TEXT(".................... SERVER_ACCESS_ENUMERATE\n"));
                              if ((pace->Mask & PRINTER_ACCESS_ADMINISTER) == PRINTER_ACCESS_ADMINISTER)
                                   _tprintf(TEXT(".................... PRINTER_ACCESS_ADMINISTER\n"));
                              if ((pace->Mask & PRINTER_ACCESS_USE) == PRINTER_ACCESS_USE)
                                    _tprintf(TEXT(".................... PRINTER_ACCESS_USE\n"));
                              if ((pace->Mask & JOB_ACCESS_ADMINISTER) == JOB_ACCESS_ADMINISTER)
                                   _tprintf(TEXT(".................... JOB_ACCESS_ADMINISTER\n"));
                              break;
                         case 't':
                              if ((pace->Mask & READ) == READ)
                                   _tprintf(TEXT(".................... READ\n"));
                              if ((pace->Mask & CHANGE) == CHANGE)
                                   _tprintf(TEXT(".................... CHANGE\n"));
                              if ((pace->Mask & WRITE) == WRITE)
                                   _tprintf(TEXT(".................... WRITE\n"));
                              break;
                         case 'o':
                              if ((pace->Mask & TOKEN_ADJUST_DEFAULT) == TOKEN_ADJUST_DEFAULT)
                                   _tprintf(TEXT(".................... TOKEN_ADJUST_DEFAULT\n"));
                              if ((pace->Mask & TOKEN_ADJUST_GROUPS) == TOKEN_ADJUST_GROUPS)
                                   _tprintf(TEXT(".................... TOKEN_ADJUST_GROUPSE\n"));
                              if ((pace->Mask & TOKEN_ADJUST_PRIVILEGES) == TOKEN_ADJUST_PRIVILEGES)
                                  _tprintf(TEXT(".................... TOKEN_ADJUST_PRIVILEGES\n"));
                              if ((pace->Mask & TOKEN_ALL_ACCESS) == TOKEN_ALL_ACCESS)
                                  _tprintf(TEXT(".................... TOKEN_ALL_ACCESS\n"));
                              if ((pace->Mask & TOKEN_ASSIGN_PRIMARY) == TOKEN_ASSIGN_PRIMARY)
                                  _tprintf(TEXT(".................... TOKEN_ASSIGN_PRIMARY\n"));
                              if ((pace->Mask & TOKEN_DUPLICATE) == TOKEN_DUPLICATE)
                                  _tprintf(TEXT(".................... TOKEN_DUPLICATE\n"));
                              if ((pace->Mask & TOKEN_EXECUTE) == TOKEN_EXECUTE)
                                  _tprintf(TEXT(".................... TOKEN_EXECUTE\n"));
                              if ((pace->Mask & TOKEN_IMPERSONATE) == TOKEN_IMPERSONATE)
                                  _tprintf(TEXT(".................... TOKEN_IMPERSONATE\n"));
                              if ((pace->Mask & TOKEN_QUERY) == TOKEN_QUERY)
                                  _tprintf(TEXT(".................... TOKEN_QUERY\n"));
                              if ((pace->Mask & TOKEN_QUERY_SOURCE) == TOKEN_QUERY_SOURCE)
                                  _tprintf(TEXT(".................... TOKEN_QUERY_SOURCE\n"));
                              if ((pace->Mask & TOKEN_READ) == TOKEN_READ)
                                  _tprintf(TEXT(".................... TOKEN_READ\n"));
                              if ((pace->Mask & TOKEN_WRITE) == TOKEN_WRITE)
                                  _tprintf(TEXT(".................... TOKEN_WRITE\n"));
                              break;
                         case 'n':
                         case 'a':
                              break;
                         default:
                              break;
                    }

               //
               // object rights
               //
               if ((pace->Mask & READ_CONTROL) == READ_CONTROL)
                    _tprintf(TEXT(".................... READ_CONTROL\n"));
               if ((pace->Mask & WRITE_OWNER) == WRITE_OWNER)
                    _tprintf(TEXT(".................... WRITE_OWNER\n"));
               if ((pace->Mask & WRITE_DAC) == WRITE_DAC)
                    _tprintf(TEXT(".................... WRITE_DAC\n"));
               if ((pace->Mask & DELETE) == DELETE)
                    _tprintf(TEXT(".................... DELETE\n"));
               if ((pace->Mask & SYNCHRONIZE) == SYNCHRONIZE)
                    _tprintf(TEXT(".................... SYNCHRONIZE\n"));
               if ((pace->Mask & ACCESS_SYSTEM_SECURITY) == ACCESS_SYSTEM_SECURITY)
                    _tprintf(TEXT(".................... ACCESS_SYSTEM_SECURITY\n"));

               //
               // GENERIC access rights
               //
               if ((pace->Mask & GENERIC_ALL) == GENERIC_ALL)
                    _tprintf(TEXT(".................... GENERIC_ALL\n"));
               if ((pace->Mask & GENERIC_EXECUTE) == GENERIC_EXECUTE)
                    _tprintf(TEXT(".................... GENERIC_EXECUTE\n"));
               if ((pace->Mask & GENERIC_READ) == GENERIC_READ)
                    _tprintf(TEXT(".................... GENERIC_READ\n"));
               if ((pace->Mask & GENERIC_WRITE) == GENERIC_WRITE)
                    _tprintf(TEXT(".................... GENERIC_WRITE\n"));

               //
               // display sid
               //
               cbName = sizeof(szName);
               cbReferencedDomainName = sizeof(szReferencedDomainName);
               ZeroMemory(szName, cbName);
               ZeroMemory(szReferencedDomainName, cbReferencedDomainName);

               if (!LookupAccountSid(NULL, &(pace->SidStart), szName, &cbName, szReferencedDomainName, &cbReferencedDomainName, &snu)){
                    if (GetLastError() == ERROR_NONE_MAPPED)
                         LookupAccountOtherSid(&(pace->SidStart), szName, &cbName, szReferencedDomainName, &cbReferencedDomainName, &snu);
                    else
                         DisplayError(GetLastError(), TEXT("LookupAccountSid"));
               }

               _tprintf(TEXT("\nuser ............... %s\\%s\n"), szReferencedDomainName, szName);
               dwSize = sizeof(szSidText);
               ZeroMemory(szSidText, dwSize);
               ConvertSid(&(pace->SidStart), szSidText, &dwSize);
               _tprintf(TEXT("sid ................ %s\n"), szSidText);
               _tprintf(TEXT("sid type ........... %s\n"), szSidType[snu-1]);
               _tprintf(TEXT("sid size ........... %u bytes\n"), GetLengthSid(&(pace->SidStart)));
			   }
          }
         }
     else{
          _tprintf(TEXT("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"));
          if (bDacl)
               _tprintf(TEXT(">>                 NO DACL PRESENT                     >>\n"));
          else
               _tprintf(TEXT(">>                 NO SACL PRESENT                     >>\n"));


          _tprintf(TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n"));
     }
}

void DumpOwnerGroup(PSECURITY_DESCRIPTOR psd, BOOL bOwner)
{
     BOOL         bOwnerDefaulted;
     TCHAR        szSidType[][17] = {TEXT("User"), TEXT("Group"), TEXT("Domain"), TEXT("Alias"), TEXT("Well Known Group"), TEXT("Deleted Account"), TEXT("Invalid"), TEXT("Unknown")};
     PSID         psid = NULL;
     SID_NAME_USE snu;
     TCHAR        szName[UNLEN];
     TCHAR        szReferencedDomainName[DNLEN];
     DWORD        cbName = sizeof(szName);
     DWORD        cbReferencedDomainName = sizeof(szReferencedDomainName);
     TCHAR        szSidText[256] = TEXT("");
     DWORD        dwSize = sizeof(szSidText);
     TCHAR        szType[6]      = TEXT("");

     if (bOwner){
          if (!GetSecurityDescriptorOwner(psd, &psid, &bOwnerDefaulted))
               DisplayError(GetLastError(), TEXT("GetSecurityDescriptorOwner"));
               if (!lstrcpy(szType, TEXT("owner")))
                    DisplayError(GetLastError(), TEXT("lstrcpy"));
         }
     else{
          if (!GetSecurityDescriptorGroup(psd, &psid, &bOwnerDefaulted))
               DisplayError(GetLastError(), TEXT("GetSecurityDescriptorGroup"));
               if(!lstrcpy(szType, TEXT("group")))
                    DisplayError(GetLastError(), TEXT("lstrcpy"));
         }

     if (psid == NULL)
          _tprintf(TEXT("%s .............. none\n"), szType);
     else{
          ZeroMemory(szName, cbName);
          ZeroMemory(szReferencedDomainName, cbReferencedDomainName);

          //
          // get the owner of the sid
          //
          if (!LookupAccountSid(NULL, psid, szName, &cbName, szReferencedDomainName, &cbReferencedDomainName, &snu)){
               if (GetLastError() != ERROR_NONE_MAPPED)
                    DisplayError(GetLastError(), TEXT("LookupAccountSid"));
          }

          _tprintf(TEXT("\n%s .............. %s\\%s\n"), szType, szReferencedDomainName, szName);
          ConvertSid(psid, szSidText, &dwSize);
          _tprintf(TEXT("sid ................ %s\n"), szSidText);
          _tprintf(TEXT("sid type ........... %s\n"), szSidType[snu-1]);
     }
}

void DumpSD(PSECURITY_DESCRIPTOR psd, TCHAR c)
{
     //
     // dump security descriptor information
     //
     DumpSDInfo(psd);

     //
     // dump the control bits
     //
     DumpControl(psd);

     //
     // get the owner
     //
     DumpOwnerGroup(psd, TRUE);

     //
     // get the group
     //
     DumpOwnerGroup(psd, FALSE);

     //
     // get the dacl
     //
     DumpDacl(psd, c, TRUE);

     //
     // get the sacl
     //
     DumpDacl(psd, c, FALSE);
}

void DumpSDInfo(PSECURITY_DESCRIPTOR psd)
{
     DWORD dwSDLength;

     //
     // is the security descriptor valid
     //
     _tprintf(TEXT("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"));
     _tprintf(TEXT(">>          SECURITY DESCRIPTOR INFORMATION            >>\n"));
     _tprintf(TEXT(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\nvalid .............. "));

     if (!IsValidSecurityDescriptor(psd)){
          _tprintf(TEXT("no\n"));
          return;
     }
     else
          _tprintf(TEXT("yes\n"));

     //
     // security descriptor size???
     //
     dwSDLength = GetSecurityDescriptorLength(psd);

     _tprintf(TEXT("length ............. %u byte(s)\n"), dwSDLength);
}

