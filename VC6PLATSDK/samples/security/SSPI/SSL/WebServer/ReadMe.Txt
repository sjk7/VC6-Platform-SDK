SSL/WebServer

This sample is intended as a demonstration of the SSPI interface to the SSL/PCT
protocols for secure, authenticated communication provided by secur32.dll and
schannel.dll on Microsoft Windows NT 4.0 w/SP4, Microsoft Windows 2000,
Microsoft Windows Millennium, and Windows 9x. On retail Windows 9x, the SSPI 
interface for SSL will only provide authentication and not encryption services.
If you require full SSL/PCT authentication and encryption services on Windows
9x, then you can update the Windows 9x client interface by installing the 
Directory Service Client (dsclient.exe) on the Windows 9x system. Additionally 
the following registry modification must be completed for SSL 
encryption/decryption routines to work on Windows 9x systems:

HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\SecurityProviders
Value: SecurityProviders: REG_SZ 
Add the following to the existing string, "schannel.dll"

WebServer demonstrates a server side interface while the companion sample
WebClient shows a client side implementation.

WebServer shows how the programmer might conceivably interact directly and
securely with a web browser such as Internet Explorer or a stand-alone, SSL
aware winsock client as demonstrated by the WebClient sample. In this
environment, WebServer would replace a Web Server such as Internet Information
Server and give the programmer full control over the server to client
interaction. The sample shows how to retrieve a server authentication
certificate and present it to the client for validation.

The heart of using the SSL protocols for secure communication is management of
the certificates required for client/server identification and authentication.
On the server side, we must generate and install a X.509 v3 SSL-compatible
server authentication certificate. This server authentication certificate
identifies a server and is used by clients to authenticate a server that the
client wants to access. You may also require that the server to be able to
authenticate the client, in which case, you must generate and install a X.509
v1 and v3 SSL-compatible client authentication certificate.

Generating and installing these certificates correctly is neccessary for proper
functioning of this sample. A possible method for installing the Server
Certificate are detailed below.

Using Microsoft Certificate Server

1) Connect to a machine running Microsoft Certificate Server. On Windows 2000
   Servers, Certificate Server is an installable component from the Add/Remove
   Control Panel applet. For NT4 IIS and Certificate Server is provided with the
   Windows NT Option Pack. For the purposes of this sample, we will assume that
   our certificate server is accessible at http://winbase/certsrv

2) Click on Certificate Enrollment Tools/Request a Certificate

3) Fill out the enrollment form. The Name field must match the name of the
   server machine exactly. Click on the Advanced button and select "Server
   Authentication" from the Usage drop-down list. Click on "Submit Request"
   and then Download from the next page. You can verify that the certificate
   was installed by using the Certificate Manager utility, or 
   the certificate viewer that is found on the 'Content' tab off the 'Internet
   Options' menu item of Internet Explorer.

OS Version Caveats:

NT4 SP4, Windows 9x, Windows ME:
                In the Advanced enrollment dialog, check the box marked "Allow
                Keys to be Exported".

Assuming that you followed the instructions above, you may now run the
webserver application. Assuming that you are running this sample on a machine
named winbase3, and installed a server authentication certificate for the name
winbase3 the following command-line parameters are appropriate:

webserver -Uwinbase3 -v

