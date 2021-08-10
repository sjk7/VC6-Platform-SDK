<%
     'Copyright (c) Microsoft Corporation. All rights reserved.
%>

<% 
	'Prevent caching
    Response.AddHeader "Pragma", "no-cache"
    Response.CacheControl = "no-cache"
    Response.Expires = -10000

	'Prevent script injection by checking for "<script" in Form & QueryString collections
	For each item in Request.Form
		if Instr(lcase(Request.Form(Item)),"<script") > 0 Then
			Response.Redirect("error.asp")
		end if
	Next

	For each item in Request.QueryString
		if Instr(lcase(Request.QueryString(Item)),"<script") > 0 Then
			Response.Redirect("error.asp")
		end if
	Next
%>




