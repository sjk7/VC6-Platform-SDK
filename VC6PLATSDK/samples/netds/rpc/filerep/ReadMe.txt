=======================
File Replication Sample
=======================

The file replication sample consists of three parts that develop an RPC application from a basic service, allowing file replication, error handling, and profiling, into a secure system supporting authentication, and finally into a milti-user service capable of prioritizing and scheduling multiple users' requests efficiently.

All three parts of the sample share the same common design.  They consist of two main components: a client utility and a service.  The service is started by the service control manager.  File replication takes place in two steps, each of which corresponds to one or more remote procedure calls.  First, the client utility requests file replication from the system service running on the local machine.  The service then contacts the service on the remote machine that is the source of the file to be replicated, receives the file, and writes it locally.

Utility  --RPC-->  Client Service  ----RPC---->  Server Service  <-> Source File
                        |    <---------Data-----------|              
                        |
                        V
                    Target File

Depending on the parameters provided by the client utility, the replication can take place from a different computer, in which case a remote service will be contacted, or from the same machine, in which case the server service defined above will be identical to the client service.  

The three samples explore the following features of RPC:

Simple File Replication Service Sample:

  Writing a basic RPC service
  Using worker threads to process tasks on the server
  Using logging in an RPC service
  Properly handing RPC errors and exceptions
  Profiling the performance of an RPC application

Secure File Replication Service Sample:

  Writing a secure LRPC RPC client and server
  Writing a secure TCP/IP RPC client and server
  Using security-callbacks
  Using mutual authentication
  Using impersonation
  Generating a SID and a name for a known principal
  RpcBindingSetAuthInfoEx
  RpcBindingInqAuthClient


Multi User File Replication Service Sample:

  Writing a secure multi user RPC service
  Managing and prioritizing requests of multiple users
  Using RPC Extended Error Information
  Debugging an RPC application via tracing
  Thread management in an RPC server
  Using the RPC Extended Error Information

The  detailed designs as well as the discussions and the motivation for the features of each sample are available in ReadMe.txt files in the respective folders.
