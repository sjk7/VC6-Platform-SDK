<%@ Language = VBScript %>
<%
     'Copyright (c) Microsoft Corporation. All rights reserved.
%>

<%' Option Explicit %>

<%
   '
   ' instantiate Passport Manager
   '
	Set objPassportManager = Server.CreateObject("Passport.Manager.1")

	'
	' get whatever information about the user that we can from Passport
	'
	strCurrentUserEmail = objPassportManager.Profile("PreferredEmail")

	strMemberIDHigh = objPassportManager.Profile("MemberIDHigh")
	strMemberIDLow = objPassportManager.Profile("MemberIDLow")
	strHex = Hex(strMemberIDHigh)
	
	'
	' convert the PUID into the form we need
	'
	strPUID = String(8 - Len(strHex), "0") & strHex
	strHex = Hex(strMemberIDLow)
	strPUID = strPUID & String(8 - Len(strHex), "0") & strHex

   ' If the user has entered information in the form, use it else
   ' display the information from the Passport ticket

   If IsEmpty(Request("tnumber")) Then
      strLastName = objPassportManager.Profile("LastName")
      strFirstName = objPassportManager.Profile("FirstName")
   Else
      strTNumber = Request.form("tnumber")
      strLastName = Request("lname")
      strFirstName = Request("fname")
   End If

%>


<HTML>
    <HEAD>
        <TITLE>Form Posting</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" TOPMARGIN="10" LEFTMARGIN="10">
        
		<!-- Display header. -->

		<FONT SIZE="4" FACE="ARIAL, HELVETICA">
		<B>Passport Provisioning</B></FONT><BR>   

		<HR>

		<P>This page will take the information entered in
		the form fields, and use the information to provision
		an account in this sites Active Directory.

		<FORM NAME=Form1 METHOD=Post ACTION="subscribe.asp">

			First Name: <INPUT TYPE=Text NAME=fname VALUE="<%=strFirstName%>"> <P>
			Last Name: <INPUT TYPE=Text NAME=lname VALUE="<%=strLastName%>"> <P>
			Telephone Number: <INPUT TYPE=Text NAME=tnumber VALUE="<%=strTNumber%>"> <P>
			E-Mail Address: <INPUT TYPE=Text NAME=mail VALUE="<%=strCurrentUserEmail%>"> <P>

			<INPUT TYPE=Submit VALUE="Submit">

		</FORM>

		<HR>

	</BODY>
</HTML>

<% 

if Request.form("tnumber") <> "" then

	Err.Clear

   '
	' connect to AD and find the default naming context for the default domain
   '
	set rootDSE = GetObject("LDAP://RootDSE")

	if Err.Number <> 0 then
		Response.Write "GetObject Error = " & Hex(Err.Number) & " (Source: " & Err.Source & ")"
	end if

	Err.Clear

	strDomainDN = rootDSE.Get("defaultNamingContext")

	if Err.Number <> 0 then
		Response.Write "Get Domain DN Error = " & Hex(Err.Number) & " (Source: " & Err.Source & ")"
	end if

	Err.Clear

	strdnsName = rootDSE.Get("dnsHostName")

   FirstDot = Instr( strdnsName, "." )

   strDomainName = Right( strdnsName, Len( strdnsName ) - FirstDot )

	strContainerDN = "cn=users, " & strDomainDN
	
	' bind to the users container
	set cont = GetObject("LDAP://" & strContainerDN )

	if Err.Number <> 0 then
		Response.Write "GetObject Users Container Error = " & Hex(Err.Number) & " (Source: " & Err.Source & ")"
	end if

	Err.Clear

	' create the user account
	Set user = cont.Create("user", "cn=" & strCurrentUserEmail)
	
	if Err.Number <> 0 then
		Response.Write "Create User Error = " & Hex(Err.Number) & " (Source: " & Err.Source & ")"
	end if

	user.put "samAccountName", strPUID

	strFullAccountName = strPUID & "@" & strDomainName
	
	user.put "altSecurityIdentities", "Kerberos:" & strFullAccountName

   ' set the UPN of the user to equal the PP e-mail address
   user.put "userPrincipalName", strCurrentUserEmail

   user.put "givenName", Request.form("fname")(1)
   user.put "sn", Request.form("lname")(1)
   user.put "telephoneNumber", Request.form("tnumber")(1)

   '   WARNING!!!
   ' Before going live with a site based on this sample code,
   ' the following must be changed so that a random password
   ' is assigned to each account. A recommended way to do this
   ' is to use the CAPICOM Utilities.GetRandom function.
   user.put "userPassword", "89sd53ET!23kL"

	' write the property cache
	user.SetInfo

	' refresh the property cache
	user.GetInfo

	' clear the account disabled flag	
	flags = user.get("userAccountControl")
	flags = flags OR &H00010000
	flags = flags AND &HFFFFFFFD

	user.put "userAccountControl", flags

	user.SetInfo

	Response.Write "Thank you "
	Response.Write Request.form("fname")
	Response.Write " " 
	Response.Write Request.form("lname")
	Response.Write "!<br>"
	Response.Write "You have been enrolled at this Passport-enabled site as: "
	Response.Write strCurrentUserEmail

   Response.Write( "<br><br><A href=../pptest/default.asp> HOME</A>" )
 
end if

%>









