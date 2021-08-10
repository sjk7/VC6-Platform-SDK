Copyright (c) Microsoft Corporation. All rights reserved.

SockAuth - Windows 2000 SSPI Sample Application

This sample code shows how to use the Security Support Provider
Interface (SSPI) to implement a secure authentication mechanism
between a client and server application.

This code is closely related to the original Sockauth sample that
has been part of the Platform SDK since NT 3.51. This version is
is targetted at Windows 2000 and later versions of the Windows 
operating system and shows correct usage of the Negotiate Security
Package. The sample also demonstrates how to use the message privacy 
integrity support available with the Kerberos and NTLM Security 
Packages that are abstracted by the Negotiate package.

Unless you are very familiar with SSPI, as well as the Kerberos 
and NTLM authentication packages as implemented in Windows 2000,
you should probably review the documentation in the Platform SDK
before trying to do too much with this sample code.

Like it's predecessor, Sockauth_W2k exchanges security protocol 
messages over a Windows socket opened between the Client and
Server applications. 

The server side of this sample authenticates the client and provides
evidence of this by reporting the client's user name back to the client
via the socket connection.

New things to look for in the Windows 2000 version of Sockauth:

0 Choose the package with "-p". The sample will default to the Negotiate
  package, but you can force the client or server to use either NTLM
  or Kerberos.

0 Use message confidentiality or integrity with "-c" or "-i".

0 In a departure from the original sample, primitive protocol framing 
  was added for sending encrypted/signed message to support the 
  variable sized signature blocks that the packages generate.

0 The sample has also been modified to provide verbose debug output
  which might be useful in troubleshooting authentication problems
  between a client and server. Verbose mode can be enabled by specifying -v
  for both the client and server applications.


A complete list of options can be seen by typing either "server -h" or "client -h".

Notes:

1) Because of the way negotiate works, you can not specify Kerberos or NTLM 
on the server applet and try to connect with a client using Negotiate. You can 
use the Negotiate package on the server, however, and connect from the client using
either NTLM or Kerberos, and of course, Negotiate.

2) If you use the Kerberos package (and for all practical purposes, Negotiate), 
you must specify a targetname parameter that matches the security context 
of the server application. For instance, if you run the server application 
from a command prompt while logged on as the user davemo, you need to specify 
"client -tdavemo". If, however, you ran the server application as a 
service in the local system account on a machine named davemo1, then you
would need to specify "client -tdavemo1". In the latter case you can alternatively 
use the Service Principal Name (SPN) as the targetname if it has been registered.
Also, note that if you are authenticating cross-forests, you will need to provide
a fully qualified netbios target name, i.e., "-tredmond\davemo" or a UPN style name, 
"-tdavemo@redmond.corp.microsoft.com".

3) There is a bug in Kerberos when using message confidentiality. On pre-SP2 Windows
2000 machines, the -c option will result in a server-side failure in 
AcceptSecurityContext. The reported error is SEC_E_INVALID_TOKEN, 0x80090308L. This
bug is fixed in Service Pack 2.