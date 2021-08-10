<%
  'Copyright (c) Microsoft Corporation. All rights reserved.

  Response.Expires = -1
  
  Set oMgr = Server.CreateObject("Passport.Manager.1")


  If oMgr.fromNetworkServer Then
    redirURL = "http://"&Request.ServerVariables("SERVER_NAME")&Request.ServerVariables("SCRIPT_NAME")
    Response.Redirect(redirURL)
  End If

Function GetProperDate (strDate)
    getProperDate = Month(strDate) & "/" & Day(strDate) & "/" & Year(strDate)
End Function



%>

<html>
<head>
	<title>Passport/AD Demo Page</title>
</head>
<body BGCOLOR="White" TOPMARGIN="10" LEFTMARGIN="10">

   <!-- Display header. -->

   <FONT SIZE="4" FACE="ARIAL, HELVETICA">
   <B>Passport/AD Integration Demonstration</B></FONT>   


<%




   thisURL = Server.URLEncode("http://" & Request.ServerVariables("SERVER_NAME") & Request.ServerVariables("SCRIPT_NAME") )
   signoutURL = Server.URLEncode("http://" & Request.ServerVariables("SERVER_NAME") & "signout.asp")

   TimeWindow = 3600
   
   If oMgr.IsAuthenticated(TimeWindow,FALSE) Then 
 
      '
      ' Display signout since user is logged in
      '
      Response.Write( "<div align='right'>" & oMgr.LogoTag2( TimeWindow ) & "</div>" )
      Response.Write( "<HR>" ) 
    


   '
   ' Display link to refresh if it's just stale (anonymous has to be enabled in IIS to get here)
   '
   ElseIf oMgr.HasTicket Then

      Response.Write( "<br><br>Your ticket is stale. (" & oMgr.TicketAge & "seconds old)<br>" )
      Response.Write( "<A HREF='"  & oMgr.AuthURL2( thisURL, TimeWindow, TRUE ) & "'>Please Sign In to Passport again</A>" )
      
      

   '
   ' User hasn't done anything, make them sign in 
   '
   Else

      Response.Write( "<br> Please click on the Passport scarab to log in to Passport <br>" )
      Response.Write( oMgr.LogoTag2( thisURL, TimeWindow ) )

   End If


   '
   ' Get the name of the current Windows user that represents this security context
   '
   Response.Write( "<br><br>The current Windows security context for this page is: " ) 

   UserName = Request.ServerVariables("LOGON_USER")

   If StrComp( UserName, "" ) = 0 Then
      Response.Write( " IIS Anonymous User" )
   Else
      Response.Write( " " & UserName )
   End If

   Response.Write( "<br>" )


   '
   ' Make the user refresh tickets every 60 minutes
   '

   If oMgr.IsAuthenticated(TimeWindow,FALSE) Then 


   '
   ' Convert the binary PUID to a hex format for displaying
   '
   strMemberIDHigh = oMgr.Profile("MemberIDHigh")
   strMemberIDLow = oMgr.Profile("MemberIDLow")
   strHex = Hex(strMemberIDHigh)
	
   strPUID = String(8 - Len(strHex), "0") & strHex
   strHex = Hex(strMemberIDLow)
   strPUID = strPUID & String(8 - Len(strHex), "0") & strHex


%>

   <FONT SIZE="2" FACE="ARIAL, HELVETICA">
   <BR><BR><B>You have been authenticated as a Passport user!</B></FONT> <BR><BR>

   <FONT SIZE="2" FACE="ARIAL, HELVETICA">
   <B>The following information about your account has been returned by Passport:</B></FONT> <BR>


<%'
' Construct the form to display the information returned by Passport Manager about the Passport user
'%>

<FORM name="form1" id="form1">
  <CODE><PRE>
      Preferred Email <INPUT id="preferredemail"  name="preferredemail"         value="<% =Server.HTMLEncode(oMgr.Profile("PreferredEmail")) %>"      SIZE="50">
            Last Name <INPUT id="lastname"        name="lastname"               value="<% =oMgr.Profile("LastName") %>"                               SIZE="50">
           First Name <INPUT id="firstname"       name="firstname"              value="<% =oMgr.Profile("FirstName") %>"                              SIZE="50">
             Hex PUID <INPUT id="strPUID"         name="strPUID"                value="<% =strPUID %>"                                                SIZE="50">
            TicketAge <INPUT id="ticketage"       name="ticketage"              value="<% =oMgr.TicketAge %>"                                         SIZE="50">

    <hr>
  </PRE></CODE>
</FORM>

<%

   '
   ' Show the provisioning link if IIS is not impersonating
   ' (this means the mapping did not happen)
   '
   If StrComp( UserName, "" ) = 0 Then
      Response.Write( "You have not been provisioned in Active Directory at this site. Click " )
      Response.Write( "<A href=../subscribe/subscribe.asp> here</A>" )
      Response.Write( " in order to associate your Passport Unique ID with a user account in AD.<br>" )
   End If

   End If

   
 
%>


</body>
</html>
