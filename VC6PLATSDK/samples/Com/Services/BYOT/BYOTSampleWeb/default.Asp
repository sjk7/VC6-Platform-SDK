<%@ LANGUAGE = VBScript %>
<%  Option Explicit		
	Response.Buffer = True
	Response.Expires = -1
%>


<html>

<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<meta name="GENERATOR" content="Microsoft FrontPage 3.0">
<title>BYOT Sample Web</title>
</head>

<body bgcolor="#FFFFFF">
<p align="center"><font size="5"><strong>BYOT Sample Web Site</strong></font></p>
<center><strong>This web application is not intended to be executed from within your browser.</strong></center>
<center>Please use the client application located in the ..byot\client\UI directory to launch this application.</center>
<p align="center"><input TYPE="button"
onclick="window.location.href=&quot;byottx.htm&quot;"
VALUE="Click here to add an employee" NAME="cmdAdd"> </p>

<%
	
	On Error Resume next
	
	' Recordset variable	
	Dim adoRs
		
	' Create the recordset
	Set adoRs = CreateObject("ADODB.Recordset")
	if err.number <> 0 then
		Response.Write("Error creating recordset object!")
		Response.End 
	end if 
	
	' Get a list of employees by querying the employee table
	adoRs.Open "Select * from employee", "Provider=SQLOLEDB;server=(local);Database=employee;UID=sa;PWD="
	if err.number <> 0 then
		Response.Write("Error " & err.description & " getting list of employees")
		Response.End 
	end if 
	
	'Build a table of the employees
	if not adoRs.Eof then
		Response.Write ("<center><table border=""5""><tr><td>Employee Number</td><td>First Name</td><td>Last Name</td></tr>")
		while not adoRs.Eof
			Response.Write ("<tr><td>")
			Response.Write (adoRs("id"))
			Response.Write ("</td><td>")
			Response.Write (adoRs("first_name"))
			Response.Write ("</td><td>")
			Response.Write (adoRs("last_name"))
			Response.Write ("</tr>")
			
			' Move to the next record
			adoRs.MoveNext
			if err.number <> 0 then
				Response.Write("Error moving getting next employee.")
				Response.End 
			end if 
		wend
		Response.Write ("</table>")
	end if
	Response.Write ("<BR>")
%>
</body>
</html>
