-----------------------------------------------------------------
         Windows NetMeeting 3 SDK Team Page Readme File
                         1999-2002
------------------------------------------------------------------

             © 1996-2002, Microsoft Corporation

CONTENTS
========

OVERVIEW OF THE TEAM PAGE SAMPLE
USING THE TEAM PAGE SAMPLE


OVERVIEW OF THE TEAM PAGE SAMPLE
================================
The team page sample, MAIN_TEAM.HTM, illustrates one of the possible uses of the Windows® NetMeeting® UI ActiveX® control. In this case the NetMeeting UI ActiveX control is used in an HTML document that could be a  part of a larger team Web site. The sample HTML document represents an individual profile of a member of the team. Similar pages could be made for other team members, and  users  could read the individual profiles. If users of the team Web site wish to contact a team member, Web site readers can use the NetMeeting UI ActiveX control to initiate a NetMeeting conference.

The sample illustrates how Webmasters can benefit from NetMeeting's functionality and provides an easy way to contact members of a team directly form the team's Web site.


OVERVIEW OF THE TEAM PAGE SAMPLE
================================
To take full advantage of the team Web page sample, you need a NetMeeting 3 build version later than NetMeeting 3.01 (4.4.3373). The NetMeeting version can be checked by running NetMeeting and selecting About Windows NetMeeting from the Help menu.
The team Web page sample does not require the user to upgrade if a NetMeeting build number lower than 4.4.3373 is installed. 
During the ONLOAD event handler in main_team.htm, the NetMeeting version is checked. If the version of the NetMeeting client installed on the local machine is earlier than 4.4.3373, the user is taken to a simplified version of main_team.htm - simple_team.htm. This file resides in the Simple directory included in the sample. 

Webmasters who want to require an upgrade to a later version of NetMeeting can modify the version check ONLOAD event handler in main_team.htm, as described in the following code examples.

Find this code section in MAIN_TEAM.HTM:


<script language="vbscript">

	Sub Window_onload()
		on error resume next
		Version = NetMeeting.Version()
		If err <> 0 Or Version < 67374373 Then 
			window.location.href="simple\simple_team.htm"
		End If
	End Sub
</script>



and substitute it with the following code example:



<script language="vbscript">
Sub Window_onload()
		on error resume next
		Version = NetMeeting.Version()
		If err <> 0 Or Version < 67374373 Then 
			alert ( " You need to install NetMeeting 3.01 in order to use  this page." )
		End If
	End Sub
</script>




Webmasters also need to substitute the NetMeeting object declaration with 


<OBJECT classid=CLSID:3E9BAF2D-7A79-11d2-9334-0000F875AE17
	id=NetMeeting
	width=176
	height=144
	STYLE="position:absolute; top:19; left:49; visibility:hidden;" codebase="file:\\__path_to_\NM30.EXE#Version=4,4,0,A">

	<PARAM NAME="MODE"
	       VALUE="RemoteNoPause">
</OBJECT>


where A = the released or customized build number of NetMeeting 3 desired (3373 and higher).


The following script can be included to handle user error when a user fails to enter anything in the input box: 


<script language="vbscript">

Sub CallToBtn_onclick()
		If CallToAddress.value = "" Then
			alert ("You need to enter a machine name, an e-mail address or an IP address in order to place a NetMeeting call.")
			CallToAddress.focus
		Else	

			on error resume next
			NetMeeting.CallTo(CallToAddress.value)
		
		End If
	End Sub

</script>


