Simple File Replication Service Sample

======
SUMMAY
======

The Simple File Replication Service demonstrates the following:

  Writing a basic RPC service
  Using worker threads to process tasks on the server
  Using logging in an RPC service
  Properly handing RPC errors and exceptions
  Profiling the performance of an RPC application

The sample consists of three executables: a client utility, and two versions of the server.  The server can be run either as a service started by the service control manager, or a stand-alone executable.  The second option is included for convenience and the functionality of the two applications is identical, from the RPC perspective.  The corresponding files are FileRepService.exe and FileRepServer.exe respectively.  In the following discussion both the executable server application and the system service will be referred to as a 'service'.  A distinction should be made between a 'local service' and a 'remote service'.  A local service is either a system service or a server executable running on the same machine as the client app, while a remote service is executing on a remote machine that is a source for the files being replicated.  Terms 'client service' and 'server service' can be used as well, particularly to emphasize the fact that replication can take place within one machine, in case the server is the same as the local computer.

File replication takes place in two steps, each of which corresponds to one or more remote procedure calls.  First, the client utility requests file replication from the local service.  The local service then contacts the service on the remote machine that is the source of the file to be replicated, receives the file, and writes it locally.

Utility  --RPC-->  Client Service  ----RPC---->  Server Service  <-> Source File
                        |    <---------Data-----------|              
                        |
                        V
                    Target File

The client utility requests file replication from the local service by issuing an RPC RequestFile.  After receiving the client request, the client service issues several remote procedure calls to retrieve the required data from the server service.  Depending on the parameters provided by the client utility, the replication can take place from a different computer, in which case a remote service will be contacted, or from the same machine, in which case the server service defined above will be identical to the client service.  The client service first calls RemoteOpen, which opens the source file on the remote machine, reads the first batch of data from it, and returns a context handle corresponding to the source file opened on the service.  The client service then creates a worker thread that repeatedly calls RemoteRead, receiving additional portions of the data, until the whole file is replicated.  When all the data has been read from the remote file, the remote service closes it and returns a NULL context handle to the local service, thus letting the client service know that there will be no more data and that replication is complete.  The client service then closes the target file.

RemoteOpen returns a batch of the data from the server service for performance reasons, saving a single RemoteRead RPC.  For example, if a small file being replicated fits in a single buffer, the client service will finish the job after calling RemoteOpen and will not have to create a worker thread and call RemoteRead.  For connections with high latency (roughly a time for the signal to complete a round-trip) the performance can be two times higher.

If an error occurs at any point during the replication, it is important for the client service to clean up properly.  The procedure ShutdownThread performs cleanup on error or after the completion of replication before the worker thread exits.

The RPC from the client utility to the client service may return before the completion of the replication.  This is because a worker thread is dispatched on the client service after the opening of the remote file to receive data and write it locally, allowing the RPC to return.  Thus, the call from the client utility to the client service is effectively asynchronous, because the processing does not finish with the return of the call.  This approach is convenient, since it lets the client utility exit and allows user to request replication of additional files while the first job is still underway.  The drawback of this design is that the user does not know when the replication is complete and the number of threads in the service can get large as multiple requests are placed before the earlier ones have completed.  Also, error reporting requires special attention.  An exception can be thrown only while the call is still in the context of an RPC thread.  Such errors will be communicated back to the client utility by the runtime.  Errors that occur on the worker thread can't be sent back since the RPC is no longer active and the client may not be executing.  Such events get written into the system log.


To motivate the following examples, it is sensible to discuss some restrictions and limitations of the above design:

- The sample does not include any security features.  The client system service and the server system service perform all operations with the privileges of the account that they run as.  If they run with regular user priveleges, they may not have access to the files or directories of other users, and expose a single user's data to the world.  If they run as administrators, the services will expose sensitive files to be read and overwritten.  In the secure FileRep example we will solve this problem.

- The sample can be easily attacked with denial of service (DOS) or other attacks.  For example, a single user can issue a high number of requests for replication of large files without waiting for their completion.  This can cause the replication traffic to consume the network bandwidth, the disk can be filled up, and CPU may be used very heavily.  The multi-user sample will include provisions to prevent this, by limiting the number of requests a single user, or a single type of users can have executing concurrently.  The current design also allows a single user to monopolize resources, and this will be handled in the multi-user sample with the help of quotas, queuing of requests, and rudimentary scheduling.

- Finally, the thread management is very primitive and performance is low in the above design.  We create a new thread on the client service for each sufficiently long request, and the thread immediately exits upon completion.  This is inefficient, since under uniform load a constant set of threads should be able to handle the replication tasks, so creation and deletion is unnecessary.  A more advanced thread pool will be introduced in the multi-user sample that will improve performance.

Above are the major concerns with the above design.  These and others will be addressed in the secure and multi-user file replication samples.

=====
FILES
=====

The directory contains the following files for building
the sample distributed application FileRepSimple:

File                    Description

common.h                Common declarations
FileRep.cpp             The client utility
FileRepClient.acf       Attribute configuration file for the client service RPC functions
FileRepClient.idl       Interface definition for the client service RPC functions
FileRepClientProc.cpp   Definition of the client service RPC procedures
FileRepServer.acf       Attribute configuration file for the server service RPC functions
FileRepServer.cpp       File replication server, an alternative to system service
FileRepServer.idl       Interface definition for the server service RPC functions
FileRepServerProc.cpp   Definition of the server service RPC procedures
FileRepService.cpp      File replication service
makefile                Nmake file to build for Windows XP
Prof.cpp                Definitions for profiling routines
Prof.h                  Declarations for profiling routines
ReadMe.txt              Readme file for the file replication sample
Service.cpp             Common service function definitions
Service.h               Common service function declarations

=================
PLATFORM SUPORTED
=================

Windows NT 5.1 or later.

To build, type "nmake" at the command line.

The following environment variables should be already set:
  
  set CPU=i386
  set INCLUDE=%SDKROOT%\h
  set LIB=%SDKROOT%\lib
  set PATH=%SDKROOT%\system32;%SDKROOT%\bin

where %SDKROOT% is the root directory for the 32-bit Windows SDK.

Build the sample distributed application:

  nmake cleanall
  nmake

This builds the executable programs FileRepServer.exe (server) FileRepService.exe (service) and FileRep.exe (client).

To build a Debug version add option "DEBUG=1 to nmake

To build a version with profiling options modify the server executable to log to the appropriate location and option "PROFILE=1" to nmake

To build a version that ignores the RPC exceptions resulting from an overloaded server add an option "STRESS=1"


==================
RUNNING THE SAMPLE
==================

On the client and server (if the two are different), enter:

  FileRepServer

or create a service with the executable FileRepSerice.exe


On the client, enter:

  FileRep ServerName RemoteFileName LocalFileName

Note: The client and server applications can run on the same 
Microsoft Windows NT computer.

Several command-line switches are available to change settings for 
this program.  For a listing of the switches available from the client 
program, enter:

  FileRep -?
