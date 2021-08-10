VERSION 5.00
Begin VB.Form frmGroup 
   Caption         =   "Group"
   ClientHeight    =   5805
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4905
   LinkTopic       =   "Form1"
   ScaleHeight     =   5805
   ScaleWidth      =   4905
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox lstADsPath 
      Height          =   255
      Left            =   3330
      TabIndex        =   7
      Top             =   5550
      Visible         =   0   'False
      Width           =   945
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   390
      Left            =   1710
      TabIndex        =   6
      Top             =   5355
      Width           =   1140
   End
   Begin VB.ListBox lstMembers 
      Height          =   3375
      Left            =   195
      TabIndex        =   5
      Top             =   1830
      Width           =   3405
   End
   Begin VB.TextBox txtDescription 
      Height          =   345
      Left            =   1335
      TabIndex        =   3
      Top             =   1035
      Width           =   3315
   End
   Begin VB.Label lblName 
      Height          =   285
      Left            =   1320
      TabIndex        =   9
      Top             =   195
      Width           =   2775
   End
   Begin VB.Label lblGroup 
      Caption         =   "Group Name:"
      Height          =   300
      Left            =   165
      TabIndex        =   8
      Top             =   210
      Width           =   990
   End
   Begin VB.Label lblGroupType 
      Height          =   285
      Left            =   1335
      TabIndex        =   1
      Top             =   585
      Width           =   2775
   End
   Begin VB.Label Label2 
      Caption         =   "Group Type:"
      Height          =   300
      Left            =   135
      TabIndex        =   0
      Top             =   570
      Width           =   1035
   End
   Begin VB.Label lblMember 
      Caption         =   "Members:"
      Height          =   255
      Left            =   210
      TabIndex        =   4
      Top             =   1530
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "&Description:"
      Height          =   285
      Left            =   180
      TabIndex        =   2
      Top             =   1080
      Width           =   945
   End
End
Attribute VB_Name = "frmGroup"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       frmGroup.frm
'
'  Contents:   Displaying Group Properties and Membership
'
'----------------------------------------------------------------------------

Dim grpObject As IADsGroup

Sub SetObject(o As IADs)
  Set grpObject = Nothing
  Set grpObject = o
  PopulateGroup
End Sub

Private Sub cmdClose_Click()
 frmGroup.Hide
End Sub



Private Sub PopulateGroup()
Dim members As IADsMembers
Dim member As IADs

'------------------------------
' Group Properties
'-----------------------------
lblName = grpObject.Name
lblGroupType = GetGroupType(grpObject)

txtDescription = grpObject.Description

'------------------------
' Members
'-----------------------
Set members = grpObject.members

lstMembers.Clear 'reset the list box
lstADsPath.Clear


For Each member In members
  lstMembers.AddItem member.Name & " (" & member.Class & ")"
  lstADsPath.AddItem member.ADsPath
Next



End Sub
