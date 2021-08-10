This sample dumps system, application, security, and backup eventlogs. It supports 
replaceable parameter strings ("%%xxx" codes), category IDs, and remote logging. The
following APIs are demonstrated:

FormatMessage
OpenEventLog
ReadEventLog
ReportEvent
OpenBackupEventLog
ClearEventLog
RegisterEventSource
DeregisterEventSource
GetEventLogInformation
GetOldestEventLogRecord
GetNumberOfEventLogRecords
NotifyChangeEventLog

To build, just run nmake in your proper build environment window. This sample
works on Windows NT 3.1 and up. It has been tested up through Whistler 32-bit and 
64-bit Beta 2.

Help for this sample can be found by running it with the "/?" parameter. Two
optional parameters are supported, <logname> and <backuplog>. <logname> can be
either "application", "security", or "system", for dumping the application, 
security, or system eventlogs. <backuplog> can be any arbitrary backup eventlog
file.

Known issues: remote event logging works fine, but the local machine needs to
have access to the proper message DLLs in order for this to work. This can be
done one of two ways.

The first method: when setting up the eventlog source keys, put the full UNC
pathname to the message DLL in the registry (which is what I do in this
sample). This has the advantage of not needing to install the message DLLs on
both the local machine and the remote machine. The problem here is with system
apps that use the %systemroot% variable in the pathname in the event logging
source keys. In this case, you need to query the value of systemroot on the
remote machine (from the HKEY_LOCAL_MACHINE\Software\Microsoft\Windows
NT\CurrentVersion key) and construct a UNC path to the DLL on the remote
machine. This is more work, but the advantage of doing this is that you don't
need to have the same identical message DLLs on the local machine, which is
convenient for viewing system messages on a remote machine running a different
version of NT than the local machine.

The other method to get access to the message DLL is to simply have all
necessary message DLLs installed on the local machine. This has the advantage
of being able to view the eventlogs when the remote machine is not running,
which can be very useful for diagnosing a crashed machine; the other method
requires the remote machine to be up and running. For your applications, you
can use an environment variable to hold the path to your message DLLs, which
can then differ from machine to machine, and put this variable into the path
to your message DLL in the event viewer keys. When viewing the eventlog, if you
call ExpandEnvironmentStrings on the path to the message DLL, you'll get the
proper path to the message DLL reguardless if you are doing this locally or
remotely. In this case, system message DLLs using the %systemroot% variable can
be very useful, assuming that you have identical versions of the system running
on both ends - you'll always be able to view the system messages in the
eventlog on the remote machine and use the system message DLLs on the local
machine.

In this sample, I encode the full UNC path to the message DLL into the registry
when doing remote logging, but do not correctly get the value of %systemroot%
on the remote machine when remotely reading system events from the eventlog.
This means that I'm making the assumption that both machines are using
identical message DLLs, and that all necessary message DLLs are also on the
local machine, so make sure that messages.dll is in the same directory on the
local machine as it is on the remote machine, or the sample won't work
correctly.
