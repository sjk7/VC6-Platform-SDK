VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "SHDOCVW.DLL"
Begin VB.Form frmClientUI 
   Caption         =   "BYOT Client"
   ClientHeight    =   8880
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8190
   LinkTopic       =   "Form1"
   ScaleHeight     =   8880
   ScaleWidth      =   8190
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "Refresh"
      Height          =   345
      Left            =   6825
      TabIndex        =   4
      Top             =   180
      Width           =   825
   End
   Begin VB.CommandButton cmdForward 
      Caption         =   "Forward"
      Height          =   345
      Left            =   960
      TabIndex        =   3
      Top             =   180
      Width           =   825
   End
   Begin VB.CommandButton cmdBack 
      Caption         =   "Back"
      Height          =   345
      Left            =   105
      TabIndex        =   2
      Top             =   180
      Width           =   825
   End
   Begin VB.CommandButton cmdGo 
      Caption         =   "&Go"
      Height          =   345
      Left            =   5940
      TabIndex        =   1
      Top             =   180
      Width           =   825
   End
   Begin VB.TextBox txtURL 
      Height          =   315
      Left            =   1905
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   195
      Width           =   3990
   End
   Begin SHDocVwCtl.WebBrowser WebBrowser 
      Height          =   2010
      Left            =   105
      TabIndex        =   5
      Top             =   855
      Width           =   7920
      ExtentX         =   13970
      ExtentY         =   3545
      ViewMode        =   0
      Offline         =   0
      Silent          =   0
      RegisterAsBrowser=   0
      RegisterAsDropTarget=   1
      AutoArrange     =   0   'False
      NoClientEdge    =   0   'False
      AlignLeft       =   0   'False
      ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
      Location        =   ""
   End
End
Attribute VB_Name = "frmClientUI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private ByotTxObj As ByotTransObj

Dim WithEvents myDoc As MSHTML.HTMLDocument
Attribute myDoc.VB_VarHelpID = -1
Dim WithEvents cmdAdd As MSHTML.HTMLButtonElement
Attribute cmdAdd.VB_VarHelpID = -1
Dim WithEvents cmdCommit As MSHTML.HTMLButtonElement
Attribute cmdCommit.VB_VarHelpID = -1
Dim WithEvents cmdAbort As MSHTML.HTMLButtonElement
Attribute cmdAbort.VB_VarHelpID = -1
Dim frmAdd As MSHTML.HTMLFormElement
Dim frmCommitAbort As MSHTML.HTMLFormElement

Private Function cmdAbort_onclick() As Boolean

    ' Abort the BYOT Transaction
    ByotTxObj.AbortTransaction
    
    ' Release
    Set ByotTxObj = Nothing
    
    ' Finish up
    SubmitForm ("Abort")
    
    ' Create a new transaction
    Set ByotTxObj = New ByotTransObj
    ByotTxObj.BeginTransaction
    
End Function

Private Function cmdCommit_onclick() As Boolean

    ' Commit the BYOT Transaction
    ByotTxObj.CommitTransaction
    
    ' Release
    Set ByotTxObj = Nothing
    
    ' Finish up
    SubmitForm ("Commit")
        
    ' Create a new transaction
    Set ByotTxObj = New ByotTransObj
    ByotTxObj.BeginTransaction
    
End Function

Private Sub cmdBack_Click()
    WebBrowser.GoBack
End Sub

Private Sub cmdForward_Click()
    WebBrowser.GoForward
End Sub

Private Sub cmdGo_Click()
    WebBrowser.Navigate txtURL.Text
End Sub

Private Sub cmdRefresh_Click()
    WebBrowser.Refresh
End Sub

Private Sub Form_Load()
    
    ' Create our initial transaction
    Set ByotTxObj = New ByotTransObj
    ByotTxObj.BeginTransaction
    
    ' Default URL
    txtURL.Text = "http://localhost/BYOTSampleWeb"
    ' Load blank web page
    WebBrowser.Navigate "about:blank"
        
End Sub

Private Sub Form_Resize()
    WebBrowser.Width = Me.ScaleWidth * 0.95
    WebBrowser.Height = Me.ScaleHeight * 0.85
End Sub

Private Function cmdAdd_onclick() As Boolean
    
Dim sTipURL As String
Dim sURL As String

    ' Get the TIP URL
    sTipURL = ByotTxObj.TipURL
    
    ' Build our submission string
    sURL = sURL & "./add.asp?TIP="
    sURL = sURL & sTipURL
    sURL = sURL & "&FirstName="
    sURL = sURL & frmAdd.All("txtFirstName").Value
    sURL = sURL & "&LastName="
    sURL = sURL & frmAdd.All("txtLastName").Value
    frmAdd.Action = sURL
    
    ' Submit
    frmAdd.submit
        
End Function

Private Sub WebBrowser_DocumentComplete(ByVal pDisp As Object, URL As Variant)
       
    If (pDisp Is WebBrowser.object) Then
        ' Get our webbrowser
        Set myDoc = WebBrowser.Document
        
        ' Set up our form variables
        If InStr(1, URL, "byottx.htm", vbTextCompare) Then
            Set frmAdd = myDoc.Forms("frmAdd")
            Set cmdAdd = myDoc.Forms("frmAdd").elements("cmdAdd")
        ElseIf InStr(1, URL, "add.asp", vbTextCompare) Then
            Set frmCommitAbort = myDoc.Forms("frmCommitAbort")
            Set cmdCommit = myDoc.All("cmdCommit")
            Set cmdAbort = myDoc.All("cmdAbort")
        End If
    End If
End Sub

Sub SubmitForm(sAction As String)

Dim sURL As String

    sURL = sURL & "finish.asp?Action="
    sURL = sURL & sAction
    
    frmCommitAbort.Action = sURL
    frmCommitAbort.submit

End Sub
