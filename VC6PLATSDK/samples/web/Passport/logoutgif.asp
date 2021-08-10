<%@ Language=VBScript %>
<%
     'Copyright (c) Microsoft Corporation. All rights reserved.
%>

<!--#include file="include/globalVars.asp"-->

<%
  Response.Expires = -1

  Response.Cookies(cProfCookie) = ""
  Response.Cookies(cProfCookie).Expires = #Jan 1,1998#

  Response.Cookies(cAuthCookie) = ""
  Response.Cookies(cAuthCookie).Expires = #Jan 1,1998#

  'If you have configured your web site to use a domain other than the default, then
  'uncomment and modify the following lines:
  'Response.Cookies(cProfCookie).Domain = 
  'Response.Cookies(cProfCookie).Path = 
  'Response.Cookies(cAuthCookie).Domain = 
  'Response.Cookies(cAuthCookie).Path = 
  
%>

<!--#include file="signoutcheckmark.gif"-->
