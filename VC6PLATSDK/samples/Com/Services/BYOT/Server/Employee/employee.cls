VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 2  'RequiresTransaction
END
Attribute VB_Name = "Employee"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Public Sub AddEmployee(sFirstName As Variant, sLastName As Variant)

On Error GoTo AddEmployee_Error
Dim ctx As COMSVCSLib.ObjectContext
Dim conn As New ADODB.Connection
Dim sConnection As String
Dim sCommand As String
Dim sConnect As String

    sConnect = "Provider=SQLOLEDB;server=(local);Database=employee"
    conn.Open sConnect, "sa", ""
        
    sCommand = "{call sp_AddEmployee('"
    sCommand = sCommand & sFirstName
    sCommand = sCommand & "', '"
    sCommand = sCommand & sLastName
    sCommand = sCommand & "')}"

    conn.Execute sCommand
    
    Set ctx = GetObjectContext()
    If Not ctx Is Nothing Then
        ctx.SetComplete
    End If
    
    Exit Sub
    
AddEmployee_Error:
    ctx.SetAbort
    
End Sub

