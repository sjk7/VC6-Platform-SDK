Attribute VB_Name = "Helper"
'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       helper.bas
'
'  Contents:   Helper Functions
'
'----------------------------------------------------------------------------


'--- Given a group, get the group type
Public Function GetGroupType(ByVal grp As IADsGroup)
    sGroupType = "Unknown"
    groupType = grp.Get("groupType")
    If (groupType = ADS_GROUP_TYPE_GLOBAL_GROUP) Then
      sGroupType = "Global Group"
    ElseIf (groupType = ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP) Then
      sGroupType = "Local Group"
    End If
    
    GetGroupType = sGroupType
End Function

