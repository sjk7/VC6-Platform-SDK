<%@ Language=VBScript %>
<%
     'Copyright (c) Microsoft Corporation. All rights reserved.
%>

<OBJECT RUNAT="SERVER" ID="passportManager" PROGID="Passport.Manager.1" >
</OBJECT>
<!-- #INCLUDE File="SCRIPTS/AddHeader.asp" -->
<%
  Response.ContentType="image/gif"
  Response.Expires=-1
  Response.AddHeader "Cache-Control", "no-cache"
  Response.AddHeader "Pragma", "no-cache"

  Response.Cookies("MSPProf") = ""
  Response.Cookies("MSPProf").Expires = #Jan 1,1998#
  Response.Cookies("MSPProf").Path = "/"

  Response.Cookies("MSPAuth") = ""
  Response.Cookies("MSPAuth").Expires = #Jan 1,1998#
  Response.Cookies("MSPAuth").Path = "/"
  
  'For secure sign-in only
  if Request.ServerVariables("HTTPS") = "on" then
	 Response.Cookies("MSPSecAuth") = ""
	 Response.Cookies("MSPSecAuth").Expires = #Jan 1,1998#
	 Response.Cookies("MSPSecAuth").Domain = oMgr.GetCurrentConfig("SecureDomain")
	 Response.Cookies("MSPSecAuth").Path = "/"
  end if
  
  ' To Insert loop to pause on logout screen, uncomment next 2 lines.
  'For i = 0 To 10000000
  'Next  
  
%>
<!--#include File="images/signout_good.gif"-->
