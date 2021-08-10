PWDFILT

*****Overview*****

This module illustrates how to implement password change notification and
password filtering in Windows NT 4.0.

Password change filtering is useful for enforcing quality or strength of
passwords in an Windows NT account database.

This sample illustrates only one approach to enforcing additional password
quality.

The password change notification can also be used to synchronize foreign
account databases.  Password change notification functionality is available
on Windows NT 3.51 and later.

The password filter can provide strict control over the quality or strength of
new passwords, and the PasswordFilter routine can indicate whether the new
password is appropriate. Password filter functionality is only available on
Windows NT 4.0 systems with Service Pack 2 installed.

CAUTION: Take great care when dealing with passwords in clear text (non-
encrypted text). Sending passwords over the network in clear text could
compromise security on the network because network "sniffers" can watch for
such password traffic. Zeroing memory used to store passwords is recommended
prior to freeing the memory. It is assumed that the reader of this article
knows how to deal with password information in a secure manner.


*****Considerations that Apply to Password Change Events*****

1) All buffers passed into the notification and filter routines should be
treated as read-only. Writing any data to these buffers may cause undefined
behavior.

2) The notification and filter routines should be thread-safe. Use critical
sections or other synchronization techniques to protect data where appropriate.

3) The InitializeChangeNotify function is called when the password notify DLL
is loaded. If this function returns FALSE, the DLL is unloaded. This function
is provided to allow for password notify specific initialization that allows
the password DLL to be used for other purposes.

4) The PasswordFilter function is called when a password change has been
requested. Such password-change events take place during account creation,
administrative password over-ride, and user-specified password changes. If
this function returns TRUE, the password is considered valid and the system
continues to evaluate the password through any other password-change packages
installed on the system. If this function returns FALSE, the password is
considered invalid, and ERROR_ILL_FORMED_PASSWORD (1324) is returned to the
source of the password change request.

5) The PasswordChangeNotify function is called after successful filtering of
the provided passwords and storage of the new password. The return value from
PasswordChangeNotify is currently unused. For the current release of Windows
NT, PasswordChangeNotify should always return STATUS_SUCCESS (0x00000000L).

6) Notification and filtering only take place on the computer that houses the
updated account. Keep this in mind when dealing with domain-user accounts.
Notification on domain accounts only takes place on the Primary domain
controller for the domain. Notification packages should be installed on all
BDCs in a domain, in addition to the PDC, to allow notifications to continue
in the event of server role changes.

7) The following registry entry, of type REG_MULTI_SZ, must be configured
appropriately for this facility to be used:


      HKEY_LOCAL_MACHINE\
       SYSTEM\
       CurrentControlSet\
       Control\
       Lsa\
       Notification Packages (value of type REG_MULTI_SZ)

Notification Packages contains a list of DLLs to be loaded and notified of
password changes and password change requests. If this value does not exist in
the registry, it must be created.


8) The following functions comprise the password change package:
- InitializeChangeNotify ]
- PasswordFilter
- PasswordChangeNotify

Each function is optional and must be declared NTAPI or WINAPI to insure
proper calling convention. Each function used must appear in the .DEF file
used to build the DLL.


9) Unhandled exceptions encountered in these functions cause security related
failures system-wide; structured exception handling should be used when
appropriate.

10) The caller of the password-change function blocks until each function has
completed. When appropriate, move lengthy processing to a separate thread prior
to returning from PasswordChangeNotify or PasswordFilter.

11) The PasswordChangeNotify, PasswordFilter, and InitializeChangeNotify
functions run in the security context of the Local System account.

12) The loading of notification packages is an auditable event through enabling
of AuditCategorySystem "Restart, Shutdown, and System" audit event type.

13) Password change notification and password filters only support password
changes initiated from Windows 95 and Windows NT clients. Password changes
initiated by 16-bit Windows clients do not generate password notification
events because they use a different password change protocol that cannot
support password notification.

*****Microsoft Provided Password Filter DLL*****

System administrators who wish to increase password strength without having
to write their own filter may use the password filter supplied by Microsoft
along with Service Pack 2 for Windows NT 4.0. This filter, PASSFILT.DLL, will
need to be copied to %system root%\SYSTEM32 after Service Pack 2 is installed
on the system. To enable the filter follow steps 6 and 7 above.

PASSFILT.DLL implements the following password policy:

1) Passwords must be at least six (6) characters long.

2) Passwords must contain characters from at least three (3) of the following
four (4) classes:

   Description                            Examples
   English Upper Case Letters             A, B, C, ... Z
   English Lower Case Letters             a, b, c, ... z
   Westernized Arabic Numerals            0, 1, 2, ... 9
   Non-alphanumeric ("Special characters") E.g., punctuation symbols.


3) Passwords may not contain your user name or any part of your full name.



