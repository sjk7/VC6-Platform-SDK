
SSL WebClient & WebServer

These samples are intended to show one way a developer can implement a 
programmatic solution for secure communication over sockets or other 
transport. These samples make use of the SSL & PCT protocols that are 
implemented by the Security Support Provider (SSP) DLL that ships with 
certain Microsoft Operating Systems. 

Background: SSL & PCT are industry standard protocols and are widely used 
by Web Browsers and Servers to establish secure communication. Products like 
Internet Information Server and Internet Explorer have long made use of the 
SSL & PCT protocols, but the low-level APIs they have used were unavailable 
to the programmer because of Government restrictions on providing uncontrolled
encryption and decryption APIs. Microsoft has solved this problem on Windows 
NT version 4.0 with the release of Service Pack 4, and in all versions of 
Windows 2000, by digitally signing the DLL that implements the SSL & PCT 
protocols (schannel.dll) and forcing all access to schannel.dll to go through 
the "main" security provider DLL, security.dll, which verifies this digital 
signature. Because of this change to the architecture of the SSP interface, 
these samples will not fully work on Windows NT version 4.0 without Service 
Pack 4 or any version of Windows 95/98 with out the Directory Service Client
(dsclient.exe.) add-on from the Windows 2000 server installation CD-ROMs in the
\Clients\Win9x folder.  Dsclient.exe is also available to download from
www.microsoft.com (search on "Directory Service Client")

Additionally the following registry modification must be completed for SSL 
encryption/decryption routines to work on Windows 9x systems after installing
the dsclient:

HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurityProviders
Value: SecurityProviders: REG_SZ 
Add the following to the existing string, "schannel.dll"


The two main samples provided are meant to demonstrate how the developer can 
code an SSL-enabled replacement for a web server or browser and gain complete 
control over the communication protocol. WebClient and WebServer are 
implemented such that the WebClient will initiate a conversation with the 
WebServer for the purpose of performing a standard HTTP "GET" operation after
performing SSL authentication and key exchange through SSPI.

SSL & PCT are not, however, restricted to use in web browsers and servers. 
The developer can use these protocols to establish trusted and secure 
communication across any communication protocol. The SSPI interface is 
generic, robust and transport independent. For instance, the techniques 
demonstrated here can be easily modified to implement a simple secure data 
exchange over some other IPC method.

See the readme.txt in each sample directory for more information.



Additional Documentation and References:

Microsoft Corporation. 1997. Secure Networking Using Microsoft Windows NT 5.0 
   Distributed Security Services. Microsoft Developer Network January 1999.
