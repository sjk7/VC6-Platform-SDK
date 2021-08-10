Secure File Replication Service Sample

======
SUMMAY
======

The Secure File Replication Service builds on the Simple FileRep Service.
It fixes some of the inadequacies of its design as described in the ReadMe, and demonstrates the following:

  Writing a secure LRPC RPC client and server
  Writing a secure TCP/IP RPC client and server
  Using security-callbacks
  Using mutual authentication
  Using impersonation
  Generating a SID and a name for a known principal
  RpcBindingSetAuthInfoEx
  RpcBindingInqAuthClient

The sample consists of two executables: a client utility and a service.  The service is started by the service control manager.  A distinction should be made between 'local service' and 'remote service'.  Local service is the system service running on the same machine as the client app, while remote service is executing on a remote machine that is a source for the files being replicated.  Terms 'client service' and 'server service' can be used as well, particularly to emphasize the fact that replication can take place within one machine, in case the server is the same as the local computer.  The client utility requests file replication from the local server.  The local server contacts a server on the remote machine, receives the file, and writes it locally.  For the functionality of the system services and a detailed discussion of replication, see ReadMe.txt for the simple file replication service.

The simple service sample did not include any security features.  The client system service and the server system service performed all operations with the privileges of the account that they run as.  Thus, the server service had no information of the identity of the user requesting replication on the client machine, and when ran as a particular user, the service could not gain access to the files or directories of other users, and exposed a single user's data to the world.  Running the service as administrator was insecure and effectively gave full read access to the server machine and full write access to the client machine.

This sample solves the above problems by adding security functionality to the simple service.  The system service should be run as NetworkService.  This can be accomplished by using the service control panel where the privileges can be modified to run as network rather than local service.  This set of lower privileges is more secure.  In particular, the approach limits the damage that can be done to the system in the case of an exploit.  Client and server services perform replication while impersonating the user who issued the request with the client utility.  This handles the problems described above, since the user can read and write only the files permitted on the remote and local systems.

The replication is requested by the FileRep utility.  The functionality is similar to the simple service, but in addition the client sets quality of service parameters and requests authentication for the RPC session.  It requests mutual authentication, because we want to guard against rogue services ran by other users and tricking the client utility into talking to them.  Dynamic identity tracking is used, since it is more efficient for a single LRPC.  Because the client system service needs to impersonate the security context of the client utility on the remote systems where it may replicate files from, the client sets impersonation level to delegate.  This allows server system service to impersonate client system service, which will itself be impersonating the client utility.  The client generates the principal name for the network service that it expects to talk to and uses RpcBindingSetAuthInfoEx to set the security parameters for the call.  The client utility makes sure that it talks to a service running as network service and with the expected principal name.  It calls RequestFile to ask for file replication.

The client service processes the request similarly to the simple file replication service.  In addition, RequestFile verifies that it is being called by a local client.  This involves a check that the protocol sequence is LRPC.  If we allowed remote client to request file replication onto a specific machine, this would make the window for abuse and denial of service (DOS) much wider since a user would not have to be logged in to request replication.  The client service verifies that security level is privacy and impersonates the client utility while opening the file on the remote server and opening the local file.  Impersonation allows the client service to run under the privileges of the user requesting replication with FileRep.  Thus, the user's privileges will be used for opening the local file for write and during the RPC to the remote server and the service itself needs only limited authority to run.  This fixes the problem of the preceding sample where users could not get access to the right subset of the system files, since services ran and performed file IO under a specific account throughout their lifetime.

While calling the server service, the client service uses mutual authentication over Kerberos - a common authentication mechanism.  The client service generates the expected server principal name hoping to talk to the network service on the server machine.  The client service uses static identity tracking since a single client thread issues multiple RPC calls with different identities: the first one to RemoteOpen while impersonating, and the subsequent one to RemoteRead, while not.  The static identity insures that all the calls will go to server under the identity of the user who created the binding handle, which will be the identity of the user running the ClientUtility.  The impersonation type is set to impersonate, since the client system service needs to impersonate the security context of the client utility on the remote systems where it may replicate files from, for example to open the file and obtain a SID,

The server functions similarly to the simple service.  In addition, the server interface is registered with a security callback.  Specifying a security-callback function allows the service to restrict access to its server interface on a per-client basis.  By default the server run time will dispatch unauthenticated calls even if the server has called RpcServerRegisterAuthInfo.  Thus, resources will be consumed and server code invoked even if a client is placing calls without proper authentication.  The, if the server wants to accept only authenticated clients it must call RpcBindingInqAuthClient to retrieve the security level, or attempt to impersonate the client with RpcImpersonateClient.  A security-callback function relieves the server service from doing this.

When a server application specifies a security-callback function for an interface, the RPC run time automatically rejects unauthenticated calls to that interface. Also, the run-time records the interfaces that each client has used. When a client makes an RPC to an interface that it has not used during the current communication session, the RPC run-time library will call the interface's security-callback function.  By using the security-callback the server service is further protected from DOS attacks.

s_RemoteOpen impersonates the client while opening the file to provide a permissions check.  Thus, the clients can only read files that they are supposed to.

The added security in the server system service prevents unauthenticated clients from making RPCs.  For example, the security-callback mechanism insures that only properly authenticated clients using Kerberos can call the interface.  This creates an interoperability problem, where the client system service from the preceding, simple, sample will not be able to replicate files from a secure server service.  The exclusion of insecure clients is a reasonable price to pay for increased service safety.  Also, since the secure and the following multi-user samples use the same authentication model, they should be able to interoperate properly.

To motivate the following example, it is sensible to discuss some restrictions and limitations of this design.  They are the concerns raised by the simple sample and have not been fully answered by the introduction of security features:

- The sample can be easily attacked with denial of service (DOS) or other attacks.  For example, a single user can issue a high number of requests for replication of large files without waiting for their completion.  This can cause the replication traffic to consume the network bandwidth, the disk can be filled up, and CPU may be used very heavily.  The multi-user sample will include provisions to prevent this or to reduce the rate of such exploits, by limiting the number of requests a single user, or a single type of users can have executing concurrently.  The current design also allows a single user to monopolize resources, and this limitation will also be handled in the multi-user sample with the help of quotas, queuing of requests, and rudimentary scheduling.

- The thread management is very primitive and performance is low in the above design.  We create a new thread on the client service for each sufficiently long request, and the thread immediately exits upon completion.  This is inefficient, since under uniform load a constant set of threads should be able to handle the replication tasks, so creation and deletion is unnecessary.  A more advanced thread pool will be introduced in the multi-user sample that will improve performance.

These issues will be addressed in the multi-user file replication sample.  The following design will offer an improvement but will not represent a production high-performance RPC app.


=====
FILES
=====

The directory contains the following files for building
the sample distributed application FileRepSimple:

File                    Description

common.h                Common declarations
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
