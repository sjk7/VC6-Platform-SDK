VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "clsObjectConstruct"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements IObjectConstruct

' Handle object initialization here now that the object is
' safely associated with a context
Private Sub IObjectConstruct_Construct(ByVal pCtorObj As Object)
  ' Use the IObjectConstructString to get the object constructor string
  Dim iocs As IObjectConstructString
  Set iocs = pCtorObj
  MsgBox "Object construct string is " & iocs.ConstructString
End Sub

