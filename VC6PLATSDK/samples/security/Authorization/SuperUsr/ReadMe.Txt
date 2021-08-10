   Module: SUPERUSR.C


   Usage:
   SuperUsr.exe <System PID>

   The system PID can change from OS to OS.  Supply the correct PID for your OS.
   NT4 System PID      -  2
   Win2000 System PID  -  8
   WinXP System PID    -  4

   The following sample code demonstrates how to extract a token from
   a process running in the context of the local system and use it to 
   create a child process running in that same context. The local system
   security context is very powerful because of its far-reaching security 
   access.

   Note: You must be a member of the local administrator group for this
   sample to work. Additionally, note that CreateProcessAsUser requires the 
   SeAssignPrimaryToken (Replace a process level token) and 
   SeIncreaseQuotaPrivilege (Increase Quotas) rights.

   