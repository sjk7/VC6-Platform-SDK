VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmQuery 
   Caption         =   "ADSI Windows Address Book"
   ClientHeight    =   6585
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7050
   LinkTopic       =   "Form1"
   ScaleHeight     =   6585
   ScaleWidth      =   7050
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView lstResult 
      Height          =   3255
      Left            =   360
      TabIndex        =   8
      Top             =   2160
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   5741
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   0
   End
   Begin VB.CommandButton cmdClear 
      Caption         =   "Clear All"
      Height          =   375
      Left            =   5640
      TabIndex        =   7
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton cmdFindNow 
      Caption         =   "Find Now"
      Height          =   375
      Left            =   5640
      TabIndex        =   6
      Top             =   360
      Width           =   1215
   End
   Begin VB.TextBox txtEmail 
      Height          =   315
      Left            =   1320
      TabIndex        =   5
      Top             =   1320
      Width           =   4095
   End
   Begin VB.TextBox txtName 
      Height          =   315
      Left            =   1320
      TabIndex        =   3
      Top             =   840
      Width           =   4095
   End
   Begin VB.ComboBox cbAddress 
      Height          =   315
      Left            =   1320
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   360
      Width           =   4095
   End
   Begin VB.Label lblStatus 
      Height          =   615
      Left            =   1080
      TabIndex        =   12
      Top             =   5880
      Width           =   5775
   End
   Begin VB.Label Label5 
      Caption         =   "Status:"
      Height          =   255
      Left            =   480
      TabIndex        =   11
      Top             =   5880
      Width           =   615
   End
   Begin VB.Label Label4 
      Caption         =   "Record(s) Found"
      Height          =   255
      Left            =   1080
      TabIndex        =   10
      Top             =   5520
      Width           =   2415
   End
   Begin VB.Label lblCount 
      Alignment       =   1  'Right Justify
      Height          =   255
      Left            =   360
      TabIndex        =   9
      Top             =   5520
      Width           =   495
   End
   Begin VB.Label Label3 
      Caption         =   "E-mail:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   1320
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   840
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "Look in:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   360
      Width           =   735
   End
End
Attribute VB_Name = "frmQuery"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Const ACTIVEDIR_SELECTED = 1
Dim con As New Connection




Private Sub cmdClear_Click()
  txtEmail = ""
  txtName = ""
  lstResult.ListItems.Clear ' Clear the user interface
  lblCount = 0
  lblStatus = ""
End Sub

Private Sub cmdFindNow_Click()
    Dim rs As New Recordset
    Dim Com As New Command
    
'    On Error GoTo bailout
    
    sName = txtName
    sEmail = txtEmail
    
    If (sEmail = "" And sName = "") Then
       MsgBox "Please enter some information to look for"
       Exit Sub
    End If
    
    '-- Reset the Result User Interface ----
    lstResult.ListItems.Clear
    lblCount = "..."
    lblStatus = "Searching..."
    frmQuery.Refresh
    
    
    frmQuery.MousePointer = vbHourglass
    
    
    '--------------------------------------------------
    '--- SETUP THE CONNECTION
    '----------------------------------------------------
    If (cbAddress.ListIndex = ACTIVEDIR_SELECTED) Then
      con.Properties("User ID") = vbNullString
      con.Properties("Password") = vbNullString
      con.Properties("Encrypt Password") = True
    Else
      con.Properties("User ID") = ""
      con.Properties("Password") = ""
      con.Properties("Encrypt Password") = False
    End If

    con.Open "Active Directory Provider"
    
    
    

    '-----------------------------------------------------------
    '--- BUILDING ADsPath FOR BASE QUERY ---------------------
    '-----------------------------------------------------------
    sInternet = GetInternetAddress(cbAddress.ListIndex)
    If (sInternet = "") Then   'Default to Active Directory
      Set gc = GetObject("GC:")
      For Each gcPath In gc 'Only one child in the GC: name space
         sPath = gcPath.ADsPath
      Next
    Else
      sPath = "GC://"
      sPath = sPath + sInternet
      sPath = sPath + ":389"
    End If
    
    
    
    
    '------- NAME AND E-MAIL ADDRESS ------------------
    
    If (sEmail <> "") Then
       sFilter = "(mail="
       sFilter = sFilter + sEmail + "*)"
    Else
       sFilter = "(|(|(|(cn="
       sFilter = sFilter + sName
       sFilter = sFilter + "*))(sn="
       sFilter = sFilter + sName
       sFilter = sFilter + "*))(givenName="
       sFilter = sFilter + sName
       sFilter = sFilter + "*))"
    End If
    
   
    
    
    '---- BUILDING THE QUERY------------------------------------
    sQuery = "<" + sPath
    sQuery = sQuery + ">;"
    sQuery = sQuery + sFilter
    sQuery = sQuery + ";cn,mail,givenName,sn,st,c,homePhone;subtree"
    
    ' Create a command object on this connection
    Set Com.ActiveConnection = con
    Com.CommandText = sQuery
    
    '-----------------------------------------
    'Set the preferences for Search
    '--------------------------------------
    Com.Properties("Timeout") = 600 'seconds
    Com.Properties("Cache Results") = False ' do not cache the result, it results in less memory requirements
    Com.Properties("Size Limit") = 200 ' limit the result set returned
    
    
    '--------------------------------------------
    'Execute the query
    '--------------------------------------------
    Set rs = Com.Execute
    
   
    
    '--------------------------------------
    ' Navigate the record set
    '----------------------------------------
    'rs.MoveFirst
    lstResult.ListItems.Clear ' Clear the user interface
    Counter = 0
    lblCount = Counter
    While Not rs.EOF
                
                Set newLine = lstResult.ListItems.Add(, , rs.Fields(0).Value(0))
                
                For i = 1 To rs.Fields.Count - 1
                  If rs.Fields(i).Type = adVariant And Not (IsNull(rs.Fields(i).Value)) Then
                     s = ""
                     For j = LBound(rs.Fields(i).Value) To UBound(rs.Fields(i).Value)
                        If (s <> "") Then
                           s = s + ", "
                        End If
                        s = s + rs.Fields(i).Value(j)
                     Next
                        newLine.SubItems(i) = s
                                      
                Else
                    If (Not (IsNull(rs.Fields(i).Value))) Then
                       newLine.SubItems(i) = rs.Fields(i).Value
                    End If
                  End If
                Next
                
                Counter = Counter + 1
        
        rs.MoveNext
    Wend
         
     '------- CLEAN UP------------------
     lblCount = Counter
     frmQuery.MousePointer = 0
     con.Close
     lblStatus = "Success"
     
     Exit Sub
     
bailout:
             lblStatus = "Error (" & Hex(Err.Number) & ") - " & Error(Err.Number)
             frmQuery.MousePointer = 0
             con.Close
             Exit Sub
    
    
End Sub

Private Sub Form_Load()
    On Error GoTo bailout
   
    
    '----------------------------------------------------
    '-------- DIRECTORY INTERNET ------------------------
    '----------------------------------------------------
    cbAddress.AddItem "Yahoo! People Search"
    cbAddress.AddItem "Active Directory"
    cbAddress.AddItem "BigFoot Internet Directory Service"
    cbAddress.AddItem "InfoSpace Business Directory Service"
    cbAddress.AddItem "InfoSpace Internet Directory Service"
    cbAddress.AddItem "Switchboard Internet Directory Service"
    cbAddress.AddItem "VeriSign Internet Directory Service"
    cbAddress.AddItem "WhoWhere Internet Directory Service"
    cbAddress.ListIndex = 0
    
    '----------------------------------------------------
    '-------- COLUMN HEADERS ----------------------------
    '----------------------------------------------------
    lstResult.ColumnHeaders.Add , , "Name"
    lstResult.ColumnHeaders.Add , , "E-Mail"
    lstResult.ColumnHeaders.Add , , "First Name"
    lstResult.ColumnHeaders.Add , , "Last Name"
    lstResult.ColumnHeaders.Add , , "Address"
    lstResult.ColumnHeaders.Add , , "Country"
    lstResult.ColumnHeaders.Add , , "Home Phone"
    
    
    '--- Set to Report View ---------------
    lstResult.View = 3
    
    '---SET UP THE ADO/OLEDB PROVIDER ------------------
    con.Provider = "ADsDSOObject"
    
    
    

    Exit Sub
    
bailout:     Debug.Print "Error", Hex(Err.Number), " :", Error(Err.Number)
             Exit Sub
    
End Sub

Function GetInternetAddress(index As Integer) As String


Select Case index
Case 0
  GetInternetAddress = "ldap.yahoo.com"
Case 1
  GetInternetAddress = "" 'Active Directory
Case 2
  GetInternetAddress = "ldap.bigfoot.com"
Case 3
  GetInternetAddress = "ldap.infospace.com"
Case 4
  GetInternetAddress = "ldapbiz.infospace.com"
Case 5
  GetInternetAddress = "ldap.switchboard.com"
Case 6
  GetInternetAddress = "directory.verisign.com"
Case 7
  GetInternetAddress = "ldap.whowhere.com"
Case Else
  GetInternetAddress = ""
End Select


End Function


