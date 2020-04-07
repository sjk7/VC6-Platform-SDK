VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 2  'RequiresTransaction
END
Attribute VB_Name = "MkCOMApp"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ----------------------------------------------------------------------------
'
' This file is part of the Microsoft COM+ Samples.
'
' Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
'
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation. See these other
' materials for detailed information regarding Microsoft code samples.
'
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' ----------------------------------------------------------------------------

'
' TransactAdmin.vbp, MkCOMApp.cls
'
'
' The TransactAdmin sample provides an example of using the COMAdmin objects
' to administer COM+ applications inside a transaction.  By encompassing a
' series of changes to the catalog in a transaction, applications may be
' configured while maintaining the catalog in a consistent state.   This
' benefits your applications by simplifying the cleanup code required.

' Note that while changes to the regdb are transacted, any changes to the
' registry, file system and MSI are not because these resources don't
' participate in DTC transactions.  Therefore changes to these must be
' cleaned up manually.


'TransactAdmin.MkCOMApp
'
' This component is installed as a COM+ Application, using the Component
' Services administration tool (MMC snap-in).  The transactional support
' is declaratively configured by setting the Class Modules MTSTransactionMode
' to 'Requires Transaction', ensuring that the actions performed within the
' methods of this component are executed as a single transaction when
' committed. This setting can also be viewed in the Properties of this
' application when selected in the COM+ Applications folder using the
' Component Services administration tool.
'
Dim objContext As ObjectContext

Public Sub CommitChanges(bSucceedFail As Boolean)
'
' Method: CommitChanges
' Parameters: bSucceedFail - True if transaction should call SetComplete,
'                            False if it should call SetAbort on exit.
'
' This method is called to commit one or more changes that have been made
' to the COM+ catalog.  To demonstrate the benefits of administering COM+
' applications in a transaction, it allows you to explicitly call either
' SetComplete or SetAbort.  Note that in a typical application, you would call
' SetComplete if all steps completed successfully or SetAbort if there were
' problems requiring a rollback to maintain consistency.
'
    On Error GoTo handler

    If bSucceedFail Then
        objContext.SetComplete
    Else
        objContext.SetAbort
        
    End If
    
Exit Sub

handler:
             objContext.SetAbort
             Err.Raise Err.Number, , Err.Description

End Sub

Public Sub CreateApp(strAppName As String)
'
' Method: CreateApp
' Parameters: strAppName - Name of the COM+ Application to create
'
' This method creates a single application in the COM+ Catalog using the
' COMAdmin object model.
'

    Dim objContext As ObjectContext
    Dim objCat As COMAdminCatalog
    Dim Apps As COMAdminCatalogCollection
    Dim objApp As COMAdminCatalogObject
    
    On Error GoTo handler
    
    Set objCat = CreateObject("COMAdmin.COMAdminCatalog")

    Set Apps = objCat.GetCollection("Applications")

    Set objApp = Apps.Add()

    objApp.Value("Name") = strAppName

    Apps.SaveChanges

    
Exit Sub
    
handler:
             objContext.SetAbort
             Err.Raise Err.Number, , Err.Description
End Sub

Private Sub Class_Initialize()
' Method: Class_Initialize()
'
' This method gets a pointer to the Object Context for this application,
' used on exit to set the completion status (SetComplete or SetAbort) of the
' transaction.
'

    Set objContext = GetObjectContext()
        

End Sub
