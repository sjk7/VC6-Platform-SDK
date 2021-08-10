PURPOSE
=======

This Check_Sd sample demonstrates how to obtain the security descriptor for a
variety of securable objects on Windows NT.  A security descriptor contains
the following information:

     * owner of the object, SID
     * a primary group, SID
     * Discretionary ACL (DACL)
     * System ACL (SACL)

APIs vary on obtaining an object's security descriptor but the APIs used to
obtain information contained in the security descriptor is the same.  This
sample uses the low level security APIs to obtain security descriptor
information.  In order to get security descriptor information, a handle must
have READ_CONTROL and ACCESS_SYSTEM_SECURITY access.  In addition, the user
running Check_Sd must be granted this access.  In order to obtain the SACL for
an object.  Several additional steps need to be made.  First, the user must
be granted the "manage auditing and security log" privilege.  In addition,
this privilege needs to be enabled in order to obtain a handle with
ACCESS_SYSTEM_SECURITY access.  The following object security descriptors can
be viewed with this sample:

     * desktop
     * directory
     * event
     * file
     * mailslot
     * memory mapped file
     * mutex
     * named pipe
     * network share
     * process
     * printer
     * process access token
     * registry key
     * semaphore
     * service
     * windowstation

HOW TO RUN THE SAMPLE
=====================

Usage displayed by Check_Sd sample:

Usage: check_sd [object] [name]
 -a : mail slot, use \\[server]\mailslot\[mailslotname]
 -d : directory or driver letter, use \\.\[driveletter]
 -e : event
 -f : file
 -i : memory mapped file
 -k : desktop, use [window station\desktop]
 -l : printer, use \\[server]\[printername]
 -m : mutex
 -n : named pipe, use \\[server or .]\pipe\[pipename]
 -o : process access token, use pid instead of name
 -p : process, use pid instead of name
 -r : registry key
 -s : sempahore
 -t : network share, use [server\sharename]
 -v : service
 -w : window station

Examples:

drive letter:
    check_sd -d \\.\a:

desktop:
    check_sd -k winsta0\default

printer:
    check_sd -l \\msprint23\corpi

network share:
    check_sd -t kimchee\public

process access token:
    check_sd -o 328

named pipe:
    check_sd -n \\.\pipe\simple
or
    check_sd -n \\kimchee\pipe\simple

registry key:
    check_sd -r HKEY_USERS\.default

APIS USED IN THE SAMPLE
=======================

The sample only works on Windows NT due to security.

helper.c

     AdjustTokenPrivileges
     AllocateAndInitializeSid
     EqualPrefixSid
     EqualSid
     FormatMessage
     FreeSid
     GetSidIdentifierAuthority
     GetSidSubAuthorityCount
     IsValidSid
     LookupPrivilegeValue
     OpenProcessToken
     OpenThreadToken

sd.c

     GetAclInformation
     GetSecurityDescriptorControl
     GetSecurityDescriptorDacl
     GetSecurityDescriptorLength
     GetSecurityDescriptorOwner
     IsValidSecurityDescriptor
     LookupAccountSid



secobjects.c

     GetFileSecurity
     GetKernelObjectSecurity
     GetPrinter
     GetUserObjectSecurity
     NetShareGetInfo
     QueryServiceObjectSecurity
     RegGetKeySecurity


WHAT THE SAMPLE DOES NOT DEMONSTRATE?
=====================================

It does not demonstrate how to modify a security descriptor.

TIPS
====

One thing to note is that not all objects have security descriptors with
all the components.  For example, printer objects do not have a SACL.

When dumping the security descriptor for a mailslot, you must specify
the server name.

HOW TO BUILD THE SAMPLE
=======================

To build for UNICODE uncomment
#define UNICODE and
#define _UNICODE

from check_sd.h

Debug Version
nmake

Release Version
nmake nodebug=1


To clean up between builds

nmake clean


