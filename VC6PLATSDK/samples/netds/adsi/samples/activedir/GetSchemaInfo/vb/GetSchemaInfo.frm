VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form frmSchemaInfo 
   Caption         =   "GetSchemaInfo"
   ClientHeight    =   7050
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8250
   LinkTopic       =   "Form1"
   ScaleHeight     =   7050
   ScaleWidth      =   8250
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtQuery 
      BackColor       =   &H8000000B&
      Height          =   375
      Left            =   0
      ScrollBars      =   1  'Horizontal
      TabIndex        =   12
      Top             =   3600
      Width           =   8295
   End
   Begin VB.CommandButton cmdNextSample 
      Caption         =   "Next Query Sample"
      Height          =   495
      Left            =   5760
      TabIndex        =   10
      Top             =   360
      Width           =   2175
   End
   Begin VB.TextBox txtRecordCount 
      Height          =   495
      Left            =   7440
      TabIndex        =   9
      Top             =   2520
      Width           =   615
   End
   Begin RichTextLib.RichTextBox rtxtOutput 
      Height          =   3135
      Left            =   0
      TabIndex        =   7
      Top             =   3960
      Width           =   8295
      _ExtentX        =   14631
      _ExtentY        =   5530
      _Version        =   393217
      ScrollBars      =   2
      TextRTF         =   $"GetSchemaInfo.frx":0000
   End
   Begin VB.CommandButton cmdGetInfo 
      Caption         =   "Get Schema Info"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   5760
      TabIndex        =   6
      Top             =   1080
      Width           =   2175
   End
   Begin VB.TextBox txtFilter 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   240
      TabIndex        =   5
      Top             =   2400
      Width           =   6375
   End
   Begin VB.Frame frmType 
      Caption         =   "Search For:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1575
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   3855
      Begin VB.OptionButton optSearchType 
         Caption         =   "Attributes only"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   3
         Top             =   1200
         Width           =   2415
      End
      Begin VB.OptionButton optSearchType 
         Caption         =   "Classes only"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   195
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   840
         Width           =   2415
      End
      Begin VB.OptionButton optSearchType 
         Caption         =   "Both Classes and Attributes"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   3615
      End
   End
   Begin VB.Label lblInfo 
      Height          =   495
      Left            =   240
      TabIndex        =   11
      Top             =   3000
      Visible         =   0   'False
      Width           =   6615
   End
   Begin VB.Label lblRecordCount 
      Caption         =   "RecordCount:"
      Height          =   255
      Left            =   6960
      TabIndex        =   8
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "LDAP Filter String:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   2040
      Width           =   2655
   End
End
Attribute VB_Name = "frmSchemaInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim iSampleNum As Integer
Const ADS_SYSTEMFLAG_ATTR_NOT_REPLICATED = &H1        ' Non-replicated attribute
Const ADS_SYSTEMFLAG_ATTR_SCHEMA_BASE_OBJECT = &H10   ' Schema base object
Const ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED = &H4        ' Attribute is a constructed att
Private Sub cmdGetInfo_Click()
Dim iMouse As Integer

iMouse = Me.MousePointer
Me.MousePointer = vbHourglass
txtRecordCount = ""
rtxtOutput.Text = ""
txtQuery = ""

If Trim(txtFilter.Text) = "" Then
  Dim iResponse As Integer
  iResponse = MsgBox("You have not specified a search filter.  This will result in a large number of objects returned." _
            + vbLf + "Are you sure you want to do this?", vbYesNo)
  If iResponse = vbNo Then
    Me.MousePointer = iMouse
    Exit Sub
  End If
End If
            
If optSearchType.Item(0).Value Then
 Call GetSchemaInformation("", Trim(txtFilter.Text))
ElseIf optSearchType.Item(1).Value Then
Call GetSchemaInformation("(objectCategory=classSchema)", Trim(txtFilter.Text))
Else
 Call GetSchemaInformation("(objectCategory=attributeSchema)", Trim(txtFilter.Text))
End If
Me.MousePointer = iMouse
End Sub

Private Sub cmdNextSample_Click()
'Clicking this button will cycle through the query examples below
 Select Case iSampleNum
       Case 0:
          txtFilter.Text = "(cn=Domain)"
          optSearchType.Item(1).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find the schema class for a domain"
       Case 1:
          txtFilter.Text = "(cn=Given-Name)"
          optSearchType.Item(2).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find the schema attribute for first name"
       Case 2:
          txtFilter.Text = "(IsSingleValued=FALSE)"
          optSearchType.Item(2).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find all of the attributes in the schema which are multi-valued.  Change to TRUE for all single-valued attributes"
       Case 3:
          txtFilter.Text = "(ldapDisplayName=objectGUID)"
          optSearchType.Item(2).Value = True
           lblInfo.Visible = True
          lblInfo.Caption = "This will find the attribute for GUID by its LDAP name"
       Case 4:
          txtFilter.Text = "(IsMemberOfPartialAttributeSet=TRUE)"
          optSearchType.Item(2).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find all those values which are stored in the Global Catalog"
       Case 5:
          txtFilter.Text = "(searchFlags=1)"
          optSearchType.Item(2).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find all those values which indexed.  Change value to 0(zero) to view all that are not"
       Case 6:
          txtFilter.Text = "(systemFlags=" + CStr(ADS_SYSTEMFLAG_ATTR_NOT_REPLICATED Or ADS_SYSTEMFLAG_ATTR_SCHEMA_BASE_OBJECT) + ")"
          optSearchType.Item(2).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find all those attributes that exactly match the not replicated and the base schema object SystemFlags."
       Case 7:
          txtFilter.Text = "(systemFlags:1.2.840.113556.1.4.804:=" + CStr(ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED) + ")"
          optSearchType.Item(2).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will find all those attributes that contain the contructed attribute in systemFlags."
       Case 8:
          txtFilter.Text = "(subClassOf=organizationalPerson)"
          optSearchType.Item(1).Value = True
          lblInfo.Visible = True
          lblInfo.Caption = "This will display classes which are a subClass of organizationalPerson"
       Case Else:
          txtFilter.Text = ""
          optSearchType.Item(0).Value = True
          lblInfo.Visible = False
 End Select
 iSampleNum = iSampleNum + 1
End Sub

Private Sub Form_Load()
 iSampleNum = 0
End Sub

Private Sub txtFilter_Change()
lblInfo.Visible = False
End Sub
