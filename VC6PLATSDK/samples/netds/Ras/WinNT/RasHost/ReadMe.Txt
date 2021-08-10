*******************************  RASHOST  *************************************

(Revised : SamirM@microsoft.com )
 Date : 10/19/1999
 Tested On Win2k 2154 )

PURPOSE:  verifying basic functionality sample security DLL.


BUILD REQUIREMENTS: headers (.h) and .lib's from the build.  Then run NMAKE.


TEST REQUIREMENTS:  1 NT RAS server, 1 NT RAS client, 
                    both with modem and phone line.


STEPS TO RUN TEST: 

- Edit the registry on the server:

  - Go to  HKLM\SOFTWARE\Microsoft\RAS.  
  - Add a key SecurityHost
  - To that key, add a value named DLLPath of type REG_SZ and give full path
    to the security dll.  (example:  d:\rashost\rashost.dll)

    Example regini script:

    \Registry\Machine
        Software
           Microsoft
              RAS
                 SecurityHost
                    DLLPath = REG_SZ d:\rashost\rashost.dll

- Restart the RAS server 
  ( i.e net stop remoteaccess 
       and then net start remoteaccess )

- Attach NTSD to svchost that runs remoteaccess to see debug output from the security DLL.
  ( To find which svchost is running the remote access do tlist -s 
    and then select the pid of the appropriate svchost )

- From RAS client, configure phonebook entry for post-dial terminal window
  (Edit -> Script -> "After dialing login" -> Pop up a terminal window)
  and dial into the RAS server with appropriate credentials and verify result.
  ( This works only with Modem Connection, because post-script dial is not
    available for dcc devices).

  Currently the security DLL is set to grant access to users whose name 
  starts with 'e'.  This is case-sensitive.  Anyone else attempting to connect 
  will get dropped by the security DLL, regardless of whether their credentials
  are otherwise valid to the server.



SAMPLE TEST CASES:

- username starting with 'e' is granted access (successful RAS connection).

- username not starting with 'e' is denied access (expect RAS error 618).

- credentials (username) used for security dll access must match those used for 
  RAS authentication, or else the connection will be rejected.  (Expect RAS 
  error 629 and the security dll's output will indicate access was granted).


Below is sample debug output for the first two cases.

=========== SAMPLE NTSD OUTPUT FOR VALID ACCESS (username = "eric") ===========

RasSecurityDialogBegin
Returning ERROR_SUCCESS from RasSecurityDialogBegin
CallWorkerThread.
Event 568 created.
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= e
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= r
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= i
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= c
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
Returning Buffer: eric
Returning size: 4
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
ricurning Buffer:
Returning size: 0

UserName: eric

DomainName: (RASHOST - Unknown)
Access granted.


========== SAMPLE NTSD OUTPUT FOR INVALID ACCESS (username = "scott") =========

RasSecurityDialogBegin
Returning ERROR_SUCCESS from RasSecurityDialogBegin
CallWorkerThread.
Event 620 created.
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= s
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= c
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= o
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= t
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= t
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
Returning Buffer: scott
Returning size: 5
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
cottrning Buffer:
Returning size: 0

UserName: scott

DomainName: (RASHOST - Unknown)
Access denied.
RasSecurityDialogEnd

===============================================================================
