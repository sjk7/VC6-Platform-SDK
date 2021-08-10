Attribute VB_Name = "Group"
Sub Main()

'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       group.bas
'
'  Contents:   Creating Group in a domain or local computer
'
'----------------------------------------------------------------------------

Dim grp As IADsGroup

'-----------------------------------------
'--- CREATING A LOCAL GROUP IN  A DOMAIN
'-----------------------------------------
Set dom = GetObject("WinNT://INDEPENDENCE") '--- Change DomainName accordingly
Set grp = dom.Create("group", "DSys")
grp.Put "groupType", ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP
grp.Description = "Distributed System Group"
grp.SetInfo

'-----------------------------------------
'--- CREATING A GLOBAL GROUP IN  A DOMAIN
'-----------------------------------------
Set dom = GetObject("WinNT://INDEPENDENCE") '--- Change DomainName accordingly
Set grp = dom.Create("group", "PM")
grp.Put "groupType", ADS_GROUP_TYPE_GLOBAL_GROUP
grp.Description = "Program Managers"
grp.SetInfo


'-----------------------------------------
'--- CREATING A LOCAL GROUP IN  A COMPUTER
'-----------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer") '--- Change ComputerName accordingly
Set grp = comp.Create("group", "TheSmiths")
grp.Put "groupType", ADS_GROUP_TYPE_LOCAL_GROUP
grp.Description = "The Smiths Family Member"
grp.SetInfo



'----------------------------------------------------
'--- ADDING A USER IN A DOMAIN LOCAL or GLOBAL GROUP
'----------------------------------------------------
Set grp = GetObject("WinNT://INDEPENDENCE/DSys,group") '--- Change DomainName accordingly
grp.Add ("WinNT://INDEPENDENCE/JSmith")



'-------------------------------------------------
'--- ADDING A USER IN A LOCAL GROUP IN A COMPUTER
'--------------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer") '--- Change ComputerName accordingly
Set grp = comp.GetObject("group", "TheSmiths")
grp.Add ("WinNT://INDEPENDENCE/JSmith")



'----------------------------------------------------
'--- ADDING A GLOBAL GROUP TO LOCAL GROUP IN A DOMAIN
'----------------------------------------------------
Set grp = GetObject("WinNT://INDEPENDENCE/DSys,group") '--- Change DomainName and GroupName accordingly
grp.Add ("WinNT://INDEPENDENCE/PM,group")


'--------------------------------------------------
' ENUMERATING GROUPS IN A DOMAIN
'-------------------------------------------------
Set dom = GetObject("WinNT://INDEPENDENCE")
dom.Filter = Array("Group")

'--- Local Group
Debug.Print "Local Groups---"
For Each grp In dom
  If (grp.GroupType = ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP) Then
    Debug.Print grp.Name
  End If
Next

'-- Global Group
Debug.Print "Global Groups---"
For Each grp In dom
  If (grp.GroupType = ADS_GROUP_TYPE_GLOBAL_GROUP) Then
     Debug.Print grp.Name
  End If
Next

'--------------------------------------------------
' ENUMERATING GROUPS IN A COMPUTER
'-------------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer") '--- Change ComputerName accordingly
comp.Filter = Array("Group")

'All groups in a computer is a local group
Debug.Print "Groups:"
For Each grp In comp
  Debug.Print grp.Name
Next


'--------------------------------------------------
' ENUMERATING GROUPS MEMBERSHIP
'-------------------------------------------------
Set grp = GetObject("WinNT://INDEPENDENCE/DSys,group") '--- Change DomainName and Group accordingly
For Each member In grp.Members
  Debug.Print member.Name & "   (" & member.Class & ")"
  
  'A local group may contain a global group
  'We can enumerate the global group membership as well
  If (member.Class = "Group") Then
      For Each obj In member.Members
         Debug.Print "    " & obj.Name & "   (" & obj.Class & ")"
      Next
  End If
Next

'-----------------------------------------------------
' REMOVING MEMBER FROM A GROUP
'-----------------------------------------------------
Set grp = GetObject("WinNT://INDEPENDENCE/PM,group") '--- Change DomainName/GroupName accordingly
grp.Remove ("WinNT://INDEPENDENCE/ChristyH") '--- Change UserName accordingly

'---------------------------------------------------
' IS MEMBER
'---------------------------------------------------
Set grp = GetObject("WinNT://INDEPENDENCE/DSys,group") '--- Change DomainName and GroupName accordingly
If (grp.IsMember("WinNT://INDEPENDENCE/JSmith")) Then '--- Change DomainName and UserName accordingly
   Debug.Print "Yes"
Else
   Debug.Print "No"
End If



End Sub
