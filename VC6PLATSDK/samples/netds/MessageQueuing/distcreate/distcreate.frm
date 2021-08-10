VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "DistCreate"
   ClientHeight    =   1065
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2175
   LinkTopic       =   "Form1"
   ScaleHeight     =   1065
   ScaleWidth      =   2175
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Done"
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   360
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' --------------------------------------------------------------------
'
'  Copyright (c) Microsoft Corporation.  All rights reserved
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' --------------------------------------------------------------------

Private Sub Command1_Click()
    End
End Sub



Private Sub Form_Load()
On Error Resume Next

' The following code creates a distribution list, adds two public
' queues to the distrbution list, and adds one private queue to
' the distribution list via an msMQ-Custom-Recipient object
' (a queue alias) that it creates.


Dim contDS As IADsContainer
Dim groupDist As IADsGroup
Dim qinfo As New MSMQQueueInfo
Dim qinfo1 As New MSMQQueueInfo
Dim qinfo2 As New MSMQQueueInfo
Dim iadsQueueAlias As IADs
Dim contOU As IADsContainer
Dim strQ2 As String
Dim strBind As String
Dim iGroupType As Integer
Dim contRoot As IADsContainer
Dim RootDSE As IADs
Dim strRootDomain As String
Dim sysInfo As New ADSystemInfo
Dim strComputerName As String

'
' Step 1: Creating a group
'
' The group will be created at the root of the local domain.
' For this we need to obtain the local domain name.
' The RootDSE is a unique entry that exists on every directory server. It
' enables you to get information about the server. Here, we use it to
' get the domain name.

' First, get the RootDSE object.
Set RootDSE = GetObject("LDAP://RootDSE")

' Then, get the domain name.
strRootDomain = RootDSE.Get("rootDomainNamingContext")

' Bind the domain name to the DS container.
strBind = "LDAP://" + strRootDomain
Set contDS = GetObject(strBind)

' Create a distribution list (DL) in the form of an Active Directory
' distribution group.
Set groupDist = contDS.Create("group", "CN=NewDLGroup")

'Set the group type to global distribution group for the distribution list.
iGroupType = ADS_GROUP_TYPE_GLOBAL_GROUP
groupDist.Put "sAMAccountName", "NewDLGroup"
groupDist.Put "groupType", iGroupType
    
groupDist.SetInfo


'
' Step 2: Creating two public queues and adding them to the distribution list
'

' Create the two public queues.
qinfo1.Pathname = ".\QueueName1"
qinfo1.Create
qinfo2.Pathname = ".\QueueName2"
qinfo2.Create

' Public queues are added to the distribution list using their ADs paths.
' One way to do this is simply to use the ADsPath property. Use this method
' to add the first public queue to the distribution list.
groupDist.Add qinfo1.ADsPath

' Another way to add a queue to a distribution list is to
' set the ADs path explicitly.
' To get the computer's full ADs path, we use the ADSystemInfo object. This
' object lets you find information about your computer.
strComputerName = sysInfo.ComputerName

' Now we can compose the full name of the second public queue.
strQ2 = "LDAP://CN=QueueName2,CN=msmq," + strComputerName

' Add the second public queue to the distribution list (these changes will
' take effect later when we call SetInfo).
groupDist.Add strQ2

'
' Step 3: Creating a private queue and a queue alias to the private queue
'         and adding the queue alias to the distribution list
'

' Get the format name for the private queue that we want to create by using
' an MSMQQueueInfo object, and then create the queue.
qinfo.Pathname = ".\PRIVATE$\QueueName3"
qinfo.Create

' To add the private queue to the distribution list, create an
' msMQ-Custom-Recipient object (a queue alias) that can reference
' the private queue.
Set iadsQueueAlias = contDS.Create("msMQ-Custom-Recipient", "cn=QueueAliasToPrivateQueue")

' Make the queue alias reference the private queue.
iadsQueueAlias.Put "msMQ-Recipient-FormatName", qinfo.FormatName
iadsQueueAlias.SetInfo

' Add the queue alias to the distribution list.
groupDist.Add iadsQueueAlias.ADsPath

' Save the changes to the distribution list.
groupDist.SetInfo

'
' Step 4: Sending a message
'

' Now, send a message to the distribution list.
Dim msg As New MSMQMessage
msg.Label = "This is a message"
msg.Send groupDist

End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub
