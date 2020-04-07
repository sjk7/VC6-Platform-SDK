<%@ LANGUAGE = VBScript %>
<%  Option Explicit		
	Response.Buffer = True
%>

<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio">
<META HTTP-EQUIV="Content-Type" content="text/html">
<TITLE>Document Title</TITLE>
</HEAD>
<BODY>

<%
	' TIP Identifier
	Dim sTIP 
	
	' Employee's first name
	Dim sFirstName
	
	' Employee's second name
	Dim sLastName
	
	' Transaction Enlister object
	Dim objTx
	
	' Employee object
	Dim objEmp
	
	' NOTE: To add custom error handling, remove the commented 
	' lines of code below.
	
	'On error resume next
	
	' Retrieve the request parameters
	sTIP = Request.QueryString("TIP")
	sFirstName = Request.QueryString("FirstName")
	sLastName = Request.QueryString("LastName")
	
	' Create an instance of our Transaction Enlister object
	Set objTx = Server.CreateObject ("BYOTSample.EnlistTransaction")
	'if err.number <> 0 then
	'	Response.Redirect ("error.htm")
	'end if
	
	' Store the transaction identifier
	objTx.EnlistTransaction(sTIP)
	'if err.number <> 0 then
	'	Response.Redirect ("error.htm")
	'end if

	' Create an instance of our employee object under the protection
	' of the external transaction.
	Set objEmp = objTx.CreateInstance("BYOTSample.Employee")
	'if err.number <> 0 then
	'	Response.Redirect ("error.htm")
	'end if
	
	' Add the employee
	objEmp.AddEmployee sFirstName,  sLastName
	'if err.number <> 0 then
	'	Response.Redirect ("error.htm")
	'end if
	
%>

<!-- Insert HTML here -->
<form method="POST" id=frmCommitAbort name=frmCommitAbort>
    <p align="center">Your transaction is now pending. Please
    choose one of the commands below.</p>
    <p align="center"><input type="submit" name="cmdCommit"
    value="Commit BYOT Transaction" LANGUAGE=javascript"><input type="submit"
    name="cmdAbort" value="Abort BYOT Transaction" LANGUAGE=javascript"></p>
</form>
</BODY>
</HTML>
