SUMMARY
=======

This sample illustrates the new DuplicateTokenEx() API for Windows NT 4.0.
This sample illustrates how to implement a remote cmd client and
server which launches cmd.exe in the security context of the client that
connected to the server.  The input and output from the new process running
on the server in the security context of the client is then redirected to
the client, to allow for remote interaction with the server process.

When a client connects to the named-pipe, the server process impersonates
the client and then saves a copy of the impersonation token.  This token
is then duplicated via DuplicateTokenEx() to a primary level access token.
The primary level token is then supplied to CreateProcessAsUser(), which
launches a process in the security context of the client.  All threads in
the new process inherit the security context of the client.  All processes
created by the new process inherit the security context of the client.  The
input and output of the new process will be redirected to the client over
the named-pipes, which provides a means of interactively executing commands
remotely in a secure manner.

In order to allow processes to run in a different security context than
the server process, it is necessary to adjust the security on the
windowstation and desktop objects associated with the server process.
This is required to allow for proper console initialization.

For simplicity, this sample applies a Null Dacl to the windowstation and
desktop objects, which is generally not appropriate in a production
environment.  The best approach to selectively secure the windowstation and
desktop objects is to extract the Logon Sid from the access token returned
by DuplicateTokenEx().  The Logon Sid can be extracted with
GetTokenInformation() and then added to an access allowed ace which is
supplied in a Dacl which contains the existing access allowed aces in
addition to the new access allowed ace.

Some additional considerations with this sample follow:

* The account which the server process runs in needs the following two
  privileges granted, to allow for the call to CreateProcessAsUser() to
  succeed:

  SeAssignPrimaryTokenPrivilege (Replace a process level token)
  SeIncreateQuotaPrivilege (Increase quotas)

* The security on the initial server side named-pipe allows for Everyone
  to connect.  This may present security problems in the event that the
  server's file system has not be secured appropriately.  In a production
  environment, it may be appropriate to apply a more restrictive Dacl on
  the initial named-pipe.

* This sample only allows one client to be connected at a time.

* Any child processes started by the launched process will not be terminated
  when the initial child process exits.

