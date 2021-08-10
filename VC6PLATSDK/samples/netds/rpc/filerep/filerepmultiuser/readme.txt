Multi User File Replication Service Sample

======
SUMMAY
======

The Secure File Replication Service builds on the Simple and Secure FileRep Service samples.
In addition, it demonstrates the following:

  Writing a secure multi user RPC service
  Managing and prioritizing requests of multiple users
  Using RPC Extended Error Information
  Debugging an RPC application via tracing
  Thread management in an RPC server
  Using the RPC Extended Error Information

NOTE: The sample demonstrates only rudimentary multi user and thread management approaches and should not be used as a guideline for high-performance production RPC servers.

The sample consists of two executables: a client utility and a service.  The service is started by the service control manager.  A distinction should be made between 'local service' and 'remote service'.  Local service is the system service running on the same machine as the client app, while remote service is executing on a remote machine that is a source for the files being replicated.  Terms 'client service' and 'server service' can be used as well, particularly to emphasize the fact that replication can take place within one machine, in case the server is the same as the local computer.  The client utility requests file replication from the local server.  The local server contacts a server on the remote machine, receives the file, and writes it locally.  For the functionality of the system services and a detailed discussion of replication, see ReadMe.txt for the simple file replication service.  The sample includes all of the security features introduced in the secure file replication sample.  For the discussion of the security features consult the ReadMe.txt for the secure sample.

Some of the limitations of the secure service were that it could still be easily attacked with denial of service (DOS) or other attacks.  A single user could issue a high number of requests for replication of large files without waiting for their completion.  In this example we will limit the number of requests a single user or a single type of users can have executing concurrently.  In general, we will add features preventing users from monopolizing resources and avoiding starvation of tasks.  This will be accomplished with quotas, queuing of requests, and rudimentary scheduling.  We will also improve the thread management of the secure service.  The services will be able to maintain a constant set of threads under uniform load, and will create and delete threads considerably less frequently.  The thread management mechanism remains the most complicated piece of the puzzle that we will handle very superficially to give an idea of the issues involved.  A high-performance implementation would need to be much more sophisticated.

The multiuser FileRep utility is identical to the secure service's FileRep.  It issues an RPC RequestFile over LRPC to the local service.  After receiving the client request, the local service handles the requests, issuing several remote procedure calls to retrieve the required data from the server service, which can be local or remote.

The requests of the client utility or the local service can be assigned one of the three priorities on the client service or the server service respectively, based on the identity of the user making the call:

0 - anonymous
1 - normal users
2 - administrators

The above priorities are obtained while impersonating the client.  The identity of the client is tracked using impersonation in the manner described in the ReadMe.txt for the secure service.  The requests are expected to be generally issued by the regular users, and to have priority 1.  Administrators' requests will be handled before normal users' requests, which will be handled before the anonymous users'.

The client service keeps requests in one of two states: new and active.  New requests are put onto one of the three ClientReqQueues corresponding to their priority.  They are then taken off the request queue and put onto the appropriate active queue in ClientActiveReqHashQueues where they are processed and the data is requested from the remote server in batches.

The client system service in the multi user service manages threads differently from the secure service.  When a request from the client utility arrives, it is dispatched on a new thread provided by the RPC runtime.  Structure of the type Req stores all the information pertaining to the request, such as local and remote file names, priority, user SID, etc.  We need to duplicate all of the request data in a separate structure since a single request in the client service can be handled by multiple threads during its lifetime.  This enables higher efficiency in thread management.  For example a thread that has just finished handling a client request can become a worker thread for a new request, avoiding the creation of a new worker.  A procedure ShutdownThread is used to clean up a request structure before the request completes, either normally or due to an error.  This is similar to the way information is provided to worker threads in the preceeding samples.  RequestFile first initializes the request structure, verifies that the client is secure, and records the client's SID and priority.  It then increments pClientReqCounters, the counter that keeps track of the number of pending requests for the clients of each priority level.  If the number of requests exceeds the entry in ClientReqBounds for the priority group, an error is returned.  The request is then added to the pending requests queue in ClientReqQueues that corresponds to the client's priority.  By limiting the number of requests of the users of each priority that are waiting to be handled by the client service, the design prevents some DOS attacks and ensures that users' requests can't be starved by the lower-priority tasks.

The new client requests that have been received but the processing of which has not started yet reside on the queues corresponding to the priority level of the client in the array ClientReqQueues.  The requests that are being processed are kept in ClientActiveReqHashQueues.  This is an array of queues with a queue for each priority level.  These queues, in turn, contain a queue for each user owning requests, kept in a hash implemented as a queue, with SID as a key.  This array of queues of queues is a fairly complex data structure that enables scheduling of multiple requests for multiple users.  All requests of the same user are kept in the same sub-queue of the hash/queue for a given priority.  When an active request is picked up to be handled, the highest priority queue of queues is searched first, followed by the second highest, etc.  If a request for a given user is picked up, the queue of the user's requests is put in the end of the priority group queue.   After the request is processed, it is put into the end of the per-user queue of the appropriate priority group.

The data structure implements the following algorithm: handle request of user with the highest priority when such requests are available and use round robbing scheduling for users within a priority group and round robbing scheduling for requests of a given user.  It serves similar purposes as the ClientReqQueues that holds the pending requests.  In addition, the data structures ensures that a single user can't monopolize the client service, since all of her requests will end up on the same subqueue and the user will be scheduled time in round –robbing.  For example, if 10 pri-1 users are placing identically-sized requests for file replication, and users 1-9 each placed 1 request while user 10 placed 9, all of the users' requests will get about the same time, so each of the first 9 requests will complete in a similar amount of time, while the subsequent 9 will take about 9 times longer.

This system is effective in preventing monopolization of resources, but it has a drawback since the time allocated to a user is not proportional to the user's number of requests, potentially making some of them take much longer.  This is similar with the problem in scheduling user threads, where process as a whole gets allocated a time slice by the system, which may not reflect the number of threads executing in it.

The requests remain on the active request queue until their completion or until an error occurs.  There, they are picked and processed by worker threads.  After putting the clients request onto the pending request queue, a thread becomes a shared worker thread.  It executes ServiceRequests to process the available work.  Since the thread is still a dispatched thread from asynchronous RPC, it is being borrowed from the runtime and blocks a client call.  The thread will be borrowed for at most tServerThread seconds.  After that it will create a new worker thread to take its place and return.  If the thread does not find any job to do it will return as well.

If a pending request is found, the worker calls HandleReq to process it.  Workers call HandleActiveReq to process active requests.  The work done in these functions corresponds to the work done by the worker thread in the secure file replication service to open the remote file, and to read blocks of data from the remote file, respectively.  After a block is read from the server service and written into the target file, the request is returned into the active requests data structure, into the end of the user's queue, where it awaits the next worker.

Since a single thread handles multiple requests while it may or may not be an RPC thread, care must be taken to communicate failures back to the client utility.  The client service will raise exceptions only while the thread is handling the request that it was called with.  Practically, this means that exceptions are raised on error only before the request is put into a pending request queue.  After that point, errors can't be communicated to the client utility which could have exited, and entries are made into the system log.  The failures are handled similarly in the simple and secure file replication samples since the use of worker threads provides for asynchronous request handling.  In addition, the sample uses extneded error information if it is provided by the RPC runtime, allowing better diagnosis of failures.

The server service functions similarly to the secure server service.  In addition, when it receives a request it assigns it one of the above three priorities.  It then adjusts the pServerReqCounters to reflect the number of requests of each priority that it is currently handling.  If the number of such requests exceeds the bound given by ServerReqBounds, an error is returned to the client.  This is a defense against DOS attacks and resource monopolization similar to the one provided by ClientReqQueues in the client service.  Without it, a single user could flood the server service with requests.

Thus, the multi-user functionality fixes some of the inadequacies of the simple and secure samples in the areas of security and performance.


=====
FILES
=====

The directory contains the following files for building
the sample distributed application FileRepSimple:

File                    Description

common.h                Common declarations
DbgMsg.cpp              Definitions for debugging and tracing routines
DbgMsg.h                Declarations for debugging and tracing routines
FileRep.cpp             The client utility
FileRepClient.acf       Attribute configuration file for the client RPC functions
FileRepClient.idl       Interface definition for the client RPC functions
FileRepClientProc.cpp   Client RPC procedures
FileRepServer.acf       Attribute configuration file for the server RPC functions
FileRepServer.cpp       File replication server, an alternative to service
FileRepServer.idl       Interface definition for the server RPC functions
FileRepServerProc.cpp   Server RPC procedures
FileRepService.cpp      File replication service
makefile                Nmake file to build for Windows XP
Prof.cpp                Definitions for profiling routines
Prof.h                  Declarations for profiling routines
ReadMe.txt              Readme file for the file replication sample
Resources.cpp           Definitions for resource-management routines
Resources.h             Declarations for resource-management routines
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

This builds the executable programs FileRepService.exe (service) and FileRep.exe (client).

To build a Debug version add option "DEBUG=1 to nmake.  This will also enable tracing.

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
