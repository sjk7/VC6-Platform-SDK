This sample demonstrates how to setup and use the Windows 2000 Kerberos SSP
for interoperability with applications using theKerberos GSS-API. The
equivalent to these samples from running on a non-windows platform can be
found in the MIT Kerberos v5 distribution under src/appl/gss-sample 
(See http://web.mit.edu/kerberos/www/index.html to obtain that distribution).

Interoperability test scenarios depend on where the principal accounts are
created and whether cross-realm authentication is involved. 
See the Kerberos Interoperability Walkthrough at 
http://www.microsoft.com/windows/server/deploy/default.asp for information on
setting up this sample.

MIT Kerberos->Win2000: MIT Kerberos sample client to sample server on Win2000
 Create service account in AD
 Start gssserver on Win2000
  MIT Kerberos gss-client connects to gsserver on Win2000
 Klist from client shows 
  TGT to KDC
  Service ticket to gssserver principal on Win2000

Win2000->MIT Kerberos: Sample client on Win2000 to MIT Kerberos sample server
 Start MIT Kerberos gss-server - requires Kerberos keytab file
   Generate keytab key file by one of methods (see walkthrough document)
 Start gssclient on Win2000, connects to MIT Kerberos gss-server
 Klist from Win2000 shows 
  TGT to KDC
  Service ticket to gss-server principal

Win2000->Win2000: Sample client on Win2000 to sample server on Win2000
 Create service account in AD
 Run both gss sample client and server on Win2000


This sample was originally part of the MIT kerberos distribution and contains
this copyright:
/*
 * Copyright 1993 by OpenVision Technologies, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appears in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of OpenVision not be used
 * in advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission. OpenVision makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
