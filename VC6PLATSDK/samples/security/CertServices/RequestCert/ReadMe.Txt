RequestCert

This sample uses the ICEnroll interface to submit a certificate request to
Microsoft Certificate Server.  The ICEnroll interface is the front end
interface that is used for certificate requests.  Microsoft Certificate Server
also provides other interfaces for communication of certificates.  The sample
uses ICertRequest and ICertConfig in conjuction with ICEnroll to request and
accept client certificates.

This sample must be run on a machine with Certificate Server installed and
running.  Certificate Server runs as a service named "Certificate Authority."
Make sure that the service is running.  Certificate Server also runs from the
command line.  This is used for debugging purposes.  In order to run
Certificate Server from the command line you must stop the "Certficate
Authority" Service and type certsrv -z.  You receive information of what
certificate server is doing.

The usage of RequestCert are as follows:
RequestCert <CommonName> [options]
<CommonName> is the name of the certificate.
The options are:
 /o  <organization>
 /l   <locale>
 /s  <state>
 /c  <country>
 /e  <email address>

Refer to the platform SDK documentation under
\Platform SDK\Windows Base Services\Security\Certificate Server
for further information on Certificate Server.


Sample compile issues: xneroll.h

Xneroll.h is a file necessary for compiling this RequestCert sample. 
To obtain this file, simply install the Internet Development SDK (Version 6.0).
After this SDK has been installed, you will be able to find xneroll.h in the 
\include directory located under the Platform SDK directory created during the SDK installation. 
