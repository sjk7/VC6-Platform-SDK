<%@ Language=VBScript %>
<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<SCRIPT ID=clientEventHandlersJS LANGUAGE=javascript>
<!--

function button1_onclick() {
 window.navigate ("default.asp");
}

//-->
</SCRIPT>
</HEAD>
<BODY>
<P>Congratulations! You have 
<%
if  Request.QueryString ("Action") = "Commit"  then
	Response.Write ("<STRONG>Committed</STRONG>")
else
	Response.Write ("<STRONG>Aborted</STRONG>")
end if
%>
 your transaction. &nbsp;</P>
<P 
align=center><INPUT id=button1 name=button1 type=button value=Home LANGUAGE=javascript onclick="return button1_onclick()"></P>

</BODY>
</HTML>
