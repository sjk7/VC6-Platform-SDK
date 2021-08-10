VERSION 5.00
Begin VB.Form formSenderInfo 
   Caption         =   "Sender and Company Information"
   ClientHeight    =   5070
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8505
   LinkTopic       =   "Form1"
   ScaleHeight     =   5070
   ScaleWidth      =   8505
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame frameCompanyInfo 
      Caption         =   "Company information"
      Height          =   1815
      Left            =   120
      TabIndex        =   23
      Top             =   2520
      Width           =   8175
      Begin VB.TextBox txtOfficePhone 
         Height          =   285
         Left            =   5040
         TabIndex        =   30
         Top             =   1080
         Width           =   2295
      End
      Begin VB.TextBox txtFaxNumb 
         Height          =   285
         Left            =   1200
         TabIndex        =   29
         Top             =   720
         Width           =   2295
      End
      Begin VB.TextBox txtOfficeloc 
         Height          =   285
         Left            =   1200
         TabIndex        =   28
         Top             =   1080
         Width           =   2295
      End
      Begin VB.TextBox txtBillingCode 
         Height          =   285
         Left            =   5040
         TabIndex        =   27
         Top             =   1440
         Width           =   2295
      End
      Begin VB.TextBox txtDept 
         Height          =   285
         Left            =   5040
         TabIndex        =   26
         Top             =   720
         Width           =   2295
      End
      Begin VB.TextBox txtCompany 
         Height          =   285
         Left            =   1200
         TabIndex        =   25
         Top             =   360
         Width           =   2295
      End
      Begin VB.TextBox txtTSID 
         Height          =   285
         Left            =   1200
         TabIndex        =   24
         Top             =   1440
         Width           =   2295
      End
      Begin VB.Label lblBusPhoneNumber 
         Caption         =   "Office phone"
         Height          =   255
         Left            =   3720
         TabIndex        =   37
         Top             =   1080
         Width           =   1095
      End
      Begin VB.Label lblSenderFaxNumber 
         Caption         =   "Fax number"
         Height          =   255
         Left            =   120
         TabIndex        =   36
         Top             =   720
         Width           =   855
      End
      Begin VB.Label lblBillingCode 
         Caption         =   "Billing code"
         Height          =   255
         Left            =   3720
         TabIndex        =   35
         Top             =   1440
         Width           =   855
      End
      Begin VB.Label lblLocation 
         Caption         =   "Office location"
         Height          =   255
         Left            =   120
         TabIndex        =   34
         Top             =   1080
         Width           =   1095
      End
      Begin VB.Label lblDept 
         Caption         =   "Department"
         Height          =   255
         Left            =   3720
         TabIndex        =   33
         Top             =   720
         Width           =   855
      End
      Begin VB.Label lblCompany 
         Caption         =   "Company"
         Height          =   255
         Left            =   120
         TabIndex        =   32
         Top             =   360
         Width           =   735
      End
      Begin VB.Label lblTSID 
         Caption         =   "TSID"
         Height          =   255
         Left            =   120
         TabIndex        =   31
         Top             =   1440
         Width           =   375
      End
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "&Cancel"
      Height          =   375
      Left            =   7080
      TabIndex        =   22
      Top             =   4560
      Width           =   1095
   End
   Begin VB.OptionButton optSaveAsDefault 
      Caption         =   "&Save as default sender"
      Height          =   255
      Index           =   1
      Left            =   3480
      TabIndex        =   21
      Top             =   4680
      Width           =   1935
   End
   Begin VB.OptionButton optSaveAsDefault 
      Caption         =   "&Use for this fax only"
      Height          =   255
      Index           =   0
      Left            =   1680
      TabIndex        =   20
      Top             =   4680
      Width           =   1695
   End
   Begin VB.CommandButton cmdSenderOK 
      Caption         =   "&OK"
      Height          =   375
      Left            =   5760
      TabIndex        =   19
      Top             =   4560
      Width           =   1095
   End
   Begin VB.TextBox txtCity 
      Height          =   285
      Left            =   5280
      TabIndex        =   6
      Top             =   840
      Width           =   2295
   End
   Begin VB.Frame frameSender 
      Caption         =   "Sender Information"
      Height          =   2295
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8175
      Begin VB.TextBox txtEmail 
         Height          =   285
         Left            =   1320
         TabIndex        =   11
         Top             =   1800
         Width           =   2295
      End
      Begin VB.TextBox txtPostalCode 
         Height          =   285
         Left            =   5160
         TabIndex        =   10
         Top             =   1080
         Width           =   2295
      End
      Begin VB.TextBox txtTitle 
         Height          =   285
         Left            =   1320
         TabIndex        =   9
         Top             =   360
         Width           =   2310
      End
      Begin VB.TextBox txtCountry 
         Height          =   285
         Left            =   1320
         TabIndex        =   8
         Top             =   1440
         Width           =   2295
      End
      Begin VB.TextBox txtState 
         Height          =   285
         Left            =   1320
         TabIndex        =   7
         Top             =   1080
         Width           =   2295
      End
      Begin VB.TextBox txtAddress 
         Height          =   285
         Left            =   1320
         TabIndex        =   5
         Top             =   720
         Width           =   2295
      End
      Begin VB.TextBox txtHomePhone 
         Height          =   285
         Left            =   5160
         TabIndex        =   4
         Top             =   1440
         Width           =   2295
      End
      Begin VB.TextBox txtName 
         Height          =   285
         Left            =   5160
         TabIndex        =   1
         Top             =   360
         Width           =   2295
      End
      Begin VB.Label lblEmail 
         Caption         =   "Email address"
         Height          =   255
         Left            =   120
         TabIndex        =   18
         Top             =   1800
         Width           =   975
      End
      Begin VB.Label lblPostalCode 
         Caption         =   "Postal code"
         Height          =   375
         Left            =   3960
         TabIndex        =   17
         Top             =   1080
         Width           =   975
      End
      Begin VB.Label lblTitle 
         Caption         =   "Title"
         Height          =   255
         Left            =   120
         TabIndex        =   16
         Top             =   360
         Width           =   375
      End
      Begin VB.Label lblState 
         Caption         =   "State/province"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   1080
         Width           =   1095
      End
      Begin VB.Label lblCity 
         Caption         =   "City"
         Height          =   255
         Left            =   3960
         TabIndex        =   14
         Top             =   720
         Width           =   375
      End
      Begin VB.Label lblAddress 
         Caption         =   "Address"
         Height          =   255
         Left            =   120
         TabIndex        =   13
         Top             =   720
         Width           =   615
      End
      Begin VB.Label lblCountry 
         Caption         =   "Country/region"
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   1440
         Width           =   1095
      End
      Begin VB.Label lblSenderHomePhoneNumber 
         Caption         =   "Home phone"
         Height          =   255
         Left            =   3960
         TabIndex        =   3
         Top             =   1440
         Width           =   975
      End
      Begin VB.Label lblSenderName 
         Caption         =   "Name"
         Height          =   255
         Left            =   3960
         TabIndex        =   2
         Top             =   360
         Width           =   1215
      End
   End
End
Attribute VB_Name = "formSenderInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Copyright (c) Microsoft Corporation.  All rights reserved.
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
'OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
'LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
'FITNESS FOR A  PARTICULAR PURPOSE
Private Sub Form_Load()
    formSenderInfo.Show
    Call Form_Init
End Sub
Private Sub Form_Init()

    'Error handling
    On Error GoTo Error_Handler
    
    'Set default to "Use for this fax only"
    optSaveAsDefault(0).Value = 1
    
    'Set the tab order for the text fields
    txtTitle.TabIndex = 1
    txtName.TabIndex = 2
    txtAddress.TabIndex = 3
    txtCity.TabIndex = 4
    txtState.TabIndex = 5
    txtPostalCode.TabIndex = 6
    txtCountry.TabIndex = 7
    txtHomePhone.TabIndex = 8
    txtEmail.TabIndex = 9
    txtCompany.TabIndex = 10
    txtFaxNumb.TabIndex = 11
    txtDept.TabIndex = 12
    txtOfficeloc.TabIndex = 13
    txtOfficePhone.TabIndex = 14
    txtTSID.TabIndex = 15
    txtBillingCode.TabIndex = 16
    optSaveAsDefault(0).TabIndex = 17
    optSaveAsDefault(1).TabIndex = 18
    cmdSenderOK.TabIndex = 19
    
    'Start the cursor in the title text box
    txtTitle.SetFocus
       
    'Create the fax sender object
    Set g_objFaxSender = g_objFaxDocument.Sender
    
    'Load and display the default sender info
    g_objFaxSender.LoadDefaultSender
    txtTitle.Text = g_objFaxSender.Title
    txtName.Text = g_objFaxSender.Name
    txtFaxNumb.Text = g_objFaxSender.FaxNumber
    txtOfficePhone.Text = g_objFaxSender.OfficePhone
    txtAddress.Text = g_objFaxSender.StreetAddress
    txtCity.Text = g_objFaxSender.City
    txtState.Text = g_objFaxSender.State
    txtPostalCode.Text = g_objFaxSender.ZipCode
    txtCountry.Text = g_objFaxSender.Country
    txtEmail.Text = g_objFaxSender.Email
    txtHomePhone.Text = g_objFaxSender.HomePhone
    txtTSID.Text = g_objFaxSender.TSID
    txtCompany.Text = g_objFaxSender.Company
    txtDept.Text = g_objFaxSender.Department
    txtBillingCode.Text = g_objFaxSender.BillingCode
    txtOfficeloc.Text = g_objFaxSender.OfficeLocation

    Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Sub
Private Sub cmdSenderOK_Click()
    
    'Error handling
    On Error GoTo Error_Handler

    'Put text entries into FaxSender object
    g_objFaxSender.Title = txtTitle.Text
    g_objFaxSender.Name = txtName.Text
    g_objFaxSender.FaxNumber = txtFaxNumb.Text
    g_objFaxSender.OfficePhone = txtOfficePhone.Text
    g_objFaxSender.StreetAddress = txtAddress.Text
    g_objFaxSender.City = txtCity.Text
    g_objFaxSender.State = txtState.Text
    g_objFaxSender.ZipCode = txtPostalCode.Text
    g_objFaxSender.Country = txtCountry.Text
    g_objFaxSender.Email = txtEmail.Text
    g_objFaxSender.HomePhone = txtHomePhone.Text
    g_objFaxSender.TSID = txtTSID.Text
    g_objFaxSender.Company = txtCompany.Text
    g_objFaxSender.Department = txtDept.Text
    g_objFaxSender.BillingCode = txtBillingCode.Text
    g_objFaxSender.OfficeLocation = txtOfficeloc.Text

    'If the option "Save as default sender" is selected, save as default
    If optSaveAsDefault(1).Value = True Then g_objFaxSender.SaveDefaultSender
            
    'Close the form
    Unload formSenderInfo
    
    Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    
End Sub
Private Sub cmdCancel_Click()
    Unload formSenderInfo
End Sub
