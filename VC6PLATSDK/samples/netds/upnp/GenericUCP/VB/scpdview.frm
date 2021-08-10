VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form SCPDViewer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Service Description Viewer"
   ClientHeight    =   4785
   ClientLeft      =   135
   ClientTop       =   465
   ClientWidth     =   8145
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4785
   ScaleWidth      =   8145
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton cmdAction 
      Caption         =   "Set Action"
      Height          =   495
      Left            =   6600
      TabIndex        =   5
      Top             =   1080
      Width           =   1455
   End
   Begin VB.CommandButton cmdVariable 
      Caption         =   "Set Variable"
      Height          =   495
      Left            =   6600
      TabIndex        =   6
      Top             =   1800
      Width           =   1455
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   495
      Left            =   6600
      TabIndex        =   9
      Top             =   3960
      Width           =   1455
   End
   Begin VB.CommandButton cmdGenActions 
      Caption         =   "Populate Action                List"
      Height          =   495
      Left            =   6600
      TabIndex        =   8
      Top             =   3240
      Width           =   1455
   End
   Begin VB.CommandButton cmdGenVariable 
      Caption         =   "Populate Variable              List"
      Height          =   495
      Left            =   6600
      TabIndex        =   7
      Top             =   2520
      Width           =   1455
   End
   Begin VB.TextBox txtSCPDURL 
      Height          =   375
      Left            =   1680
      TabIndex        =   2
      Top             =   360
      Width           =   4815
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "Go "
      Height          =   375
      Left            =   6720
      TabIndex        =   3
      Top             =   360
      Width           =   1215
   End
   Begin ComctlLib.TreeView tvwXMLData 
      CausesValidation=   0   'False
      Height          =   3855
      Left            =   120
      TabIndex        =   4
      Top             =   840
      Width           =   6375
      _ExtentX        =   11245
      _ExtentY        =   6800
      _Version        =   327682
      Style           =   7
      Appearance      =   1
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Label lblSCPDURL 
      Caption         =   "Service Desc. URL :"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label lblSCPD 
      Alignment       =   2  'Center
      Caption         =   "Service Description Viewer"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   2280
      TabIndex        =   0
      Top             =   0
      Width           =   3135
   End
End
Attribute VB_Name = "SCPDViewer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------------------------------
'
'  Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
Option Explicit
' These variables are used for the selection of the current node in the xml tree
Public WithEvents xml_document As DOMDocument
Attribute xml_document.VB_VarHelpID = -1



'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdBrowse_Click
'
'  Purpose : To reload the tree view control with the new SCPD Url entered
'
'  Arguments:
'
'  Return:
'
'  Note:
'

Public Sub cmdBrowse_Click()
    'clear the tree view
    tvwXMLData.Nodes.Clear
    'load the DOM document from the provided URL
    On Error Resume Next
    xml_document.async = False
    xml_document.Load txtSCPDURL.Text
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdVariable_Click
'
'  Purpose : To copy the variable selected to the main dialog box's variable list box
'
'  Arguments:
'
'  Return:
'
'  Note:
'
Private Sub cmdVariable_Click()
    On Error GoTo Error
    Dim nodeSelected As Node
    If tvwXMLData.SelectedItem Is Nothing Then
        MsgBox "Item is not selected in the tree view control", vbOKOnly
        Exit Sub
    End If
    Set nodeSelected = tvwXMLData.SelectedItem
    Call TraverseXMLTree(nodeSelected.FullPath, nodeSelected.Index, xml_document, nodeSelected.root)
    If global_xml_node Is Nothing Or global_xml_node.parentNode Is Nothing Or global_xml_node.parentNode.parentNode Is Nothing Then
        MsgBox "Selected item is not a valid action name"
        Exit Sub
    End If
    ' We must copy the variable name to the query variable field
    If StrComp(global_xml_node.parentNode.nodeName, "name") = 0 And StrComp(global_xml_node.parentNode.parentNode.nodeName, "stateVariable") = 0 Then
        ' Copy the name to the corresponding field in the main dialog box
        DeviceControl.cboVariable.Text = global_xml_node.nodeValue
        Exit Sub
    Else
        MsgBox "Selected item is not a valid variable name"
        Exit Sub
    End If
    Exit Sub
Error:
    With Err
        ErrorPrint (.Number)
    End With
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdAction_Click
'
'  Purpose : To copy the action selected to the main dialog box's action list box
'
'  Arguments:
'
'  Return:
'
'  Note:
'
'
Private Sub cmdAction_Click()
    On Error GoTo Error
    Dim nodeSelected As Node
    If tvwXMLData.SelectedItem Is Nothing Then
        MsgBox "Item is not selected in the tree view control", vbOKOnly
        Exit Sub
    End If
    Set nodeSelected = tvwXMLData.SelectedItem
    Call TraverseXMLTree(nodeSelected.FullPath, nodeSelected.Index, xml_document, nodeSelected.root)
    ' Check that the global_xml_node parents exist
    If global_xml_node Is Nothing Or global_xml_node.parentNode Is Nothing Or global_xml_node.parentNode.parentNode Is Nothing Then
        MsgBox "Selected item is not a valid action name"
        Exit Sub
    End If
    If StrComp(global_xml_node.parentNode.nodeName, "name") = 0 And StrComp(global_xml_node.parentNode.parentNode.nodeName, "action") = 0 Then
        ' Copy the name to the corresponding field in the main dialog box
        DeviceControl.cboActionName.Text = global_xml_node.nodeValue
        Exit Sub
    Else
        MsgBox "Selected item is not a valid action name"
    End If
    Exit Sub
Error:
    With Err
        ErrorPrint (.Number)
    End With
End Sub

'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdGenActions_Click
'
'  Purpose : To generate the list of actions and put them in the action list
'
'  Arguments:
'
'  Return:
'
'  Note:
'


' This parses the scpd for the action names and adds them to the action list in the main dialog box
Public Sub cmdGenActions_Click()
    On Error GoTo Error
    Dim iCount As Integer
    Dim pXmlNode As IXMLDOMNode
    Dim varActionNodes As Variant
    
    'This gives the list of the action names
    Set varActionNodes = xml_document.selectNodes("*/actionList/action/name")
    DeviceControl.cboActionName.Clear
    For iCount = 0 To varActionNodes.length - 1
        Set pXmlNode = varActionNodes(iCount)
        DeviceControl.cboActionName.AddItem pXmlNode.childNodes(0).nodeValue
    Next iCount
    Exit Sub
Error:
    With Err
        ErrorPrint (.Number)
    End With
End Sub

'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdGenVariable_Click
'
'  Purpose : To generate the list of variables and put them in the variable list
'
'  Arguments:
'
'  Return:
'
'  Note:
'

Public Sub cmdGenVariable_Click()
    On Error GoTo Error
    Dim iCount As Integer
    Dim pXmlNode As IXMLDOMNode
    Dim varVariableNodes As Variant
    
    'This gives the list of the variable names
    Set varVariableNodes = xml_document.selectNodes("*/serviceStateTable/stateVariable/name")
    DeviceControl.cboVariable.Clear
    For iCount = 0 To varVariableNodes.length - 1
        Set pXmlNode = varVariableNodes(iCount)
        DeviceControl.cboVariable.AddItem pXmlNode.childNodes(0).nodeValue
    Next iCount
    Exit Sub
Error:
    With Err
        ErrorPrint (.Number)
    End With
End Sub


'-------------------------------------------------------------------------
'   Form Event Handlers
'-------------------------------------------------------------------------
Private Sub Form_Load()
    'create the DOM document
    Set xml_document = CreateObject("Microsoft.XMLDOM")
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Set xml_document = Nothing
End Sub
Private Sub cmdClose_Click()
    Unload Me
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : tvwXMLData_BeforeLableEdit
'
'  Purpose : To cancel the editing operation in the tree view control
'
'  Arguments:
'
'  Return:
'
'  Note:
'

Private Sub tvwXMLData_BeforeLabelEdit(Cancel As Integer)
    Cancel = True
End Sub

'+--------------------------------------------------------------------------------------------------
'
'  Function : tvwXMLData_Click
'
'  Purpose : To traverse to the corresponding right xml node when one of the nodes in tree view is clicked
'
'  Arguments:
'
'  Return:
'
'  Note:
'

Private Sub tvwXMLData_Click()
    Dim nodeSelected As Node
    If tvwXMLData.SelectedItem Is Nothing Then
        MsgBox "Item is not selected in the tree view control", vbOKOnly
        Exit Sub
    End If
    Set nodeSelected = tvwXMLData.SelectedItem
    Call TraverseXMLTree(nodeSelected.FullPath, nodeSelected.Index, xml_document, nodeSelected.root)
End Sub

'+--------------------------------------------------------------------------------------------------
'
'  Function : xml_document_onreadystatechange
'
'  Purpose : Callback for the xml document for asynchronous loading
'
'  Arguments:
'
'  Return:
'
'  Note:
'

' onreadystatechange event handler
Private Sub xml_document_onreadystatechange()
    Dim pXmlParseError As MSXML.IXMLDOMParseError
    Dim pXmlNode As MSXML.IXMLDOMNode
    
    'check if the document reference's status is complete
    If (xml_document.ReadyState = READYSTATE_COMPLETE) Then
        'get a reference to the parseerror object
        Set pXmlParseError = xml_document.parseError
        'check if an error occured
        If TypeName(xml_document.documentElement) = "Nothing" Then
            'display the error
            MsgBox pXmlParseError.reason, vbOKOnly
        Else
            'get a reference to the document
            Set pXmlNode = xml_document
            'display the nodes
            Call DisplayDomNode(0, pXmlNode)
            'expand the first node in the tree
            tvwXMLData.Nodes.Item(1).Expanded = True
        End If
    End If
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : TraverseXMLTree
'
'  Purpose : Recursively traverse the xml document to find the right xml node
'
'  Arguments:
'
'  Return:
'
'  Note:
'
Public Sub TraverseXMLTree(ByVal strRelativePath As String, ByVal iIndexSelected As Integer, ByRef pXmlNode As MSXML.IXMLDOMNode, ByRef nodeTree As Node)

    On Error Resume Next
    Dim strLine As String
    Dim strPrunedString As String
    Dim objTreeNode As Node
    Dim lLoop As Long
    
    g_XMLNodeFlag = False
    Set global_xml_node = Nothing
    
    'check if the provided node is nothing
    If pXmlNode Is Nothing Then
        Exit Sub
    End If
    
    'determine the type of node to get the correct formatting
    strLine = FormatNodeString(pXmlNode)
    If strLine = "" Then
        Exit Sub
    End If
    
    'handle any attributes in the node
    If (pXmlNode.nodeType = NODE_ELEMENT) Then
        strLine = strLine & FormatAttributes(pXmlNode.Attributes)
    End If
    ' First compare the string with the original string to see if this is the node
    If StrComp(strRelativePath, strLine) = 0 Then
        ' Also check if the index of the current node is equal to the passed selected node index
        If iIndexSelected = nodeTree.Index Then
            g_XMLNodeFlag = True
            Set global_xml_node = pXmlNode
            Exit Sub
        Else
            ' The node though it equalled in the string is not the correct one
            Set global_xml_node = Nothing
            Exit Sub
        End If
    End If
    
    strPrunedString = RemoveSecondFromFirstString(strRelativePath, strLine)
    If strPrunedString = "" Then
      ' The returned string is null and therefore we must return with Nothing
      Set global_xml_node = Nothing
      Exit Sub
    End If
    
    strPrunedString = Right(strPrunedString, Len(strPrunedString) - 1) ' to remove the delimiter that the full path introduces
    'call this function recursively to display the child nodes
    If Not (pXmlNode.childNodes Is Nothing) Then
        If pXmlNode.childNodes.length = nodeTree.Children Then
        Set objTreeNode = nodeTree.Child
        For lLoop = 0 To pXmlNode.childNodes.length - 1
            Call TraverseXMLTree(strPrunedString, iIndexSelected, pXmlNode.childNodes.Item(lLoop), objTreeNode)
            If g_XMLNodeFlag = True Then 'If the node has been found, just exit
                Exit Sub
            End If
            Set objTreeNode = objTreeNode.Next
        Next lLoop
        End If
    End If
    Set global_xml_node = Nothing
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : DisplayDomNode
'
'  Purpose : Recursively traverse the xml document to display the nodes in the tree view
'
'  Arguments:
'
'  Return:
'
'  Note:
'

Public Sub DisplayDomNode(ByVal iAncestor As Integer, ByRef pXmlNode As MSXML.IXMLDOMNode)
    On Error Resume Next
   
    Dim strLine As String
    Dim iIndex
    Dim objTreeNode As Node
    Dim lLoop As Long
    
    'check if the provided node is nothing
    If pXmlNode Is Nothing Then
        Exit Sub
    End If
    'determine the type of node to get the correct formatting
    strLine = FormatNodeString(pXmlNode)
    'don't display anything if the line is NULL
    If strLine = "" Then
        Exit Sub
    End If
    'handle any attributes in the node
    If (pXmlNode.nodeType = NODE_ELEMENT) Then
        strLine = strLine & FormatAttributes(pXmlNode.Attributes)
    End If
    'check if the node is the root
    If iAncestor = 0 Then
        Set objTreeNode = tvwXMLData.Nodes.Add(, , , strLine)
    Else
        Set objTreeNode = tvwXMLData.Nodes.Add(iAncestor, tvwChild, , strLine)
    End If
    iIndex = objTreeNode.Index
    'call this function recursively to display the child nodes
    If Not (pXmlNode.childNodes Is Nothing) Then
        For lLoop = 0 To pXmlNode.childNodes.length - 1
            Call DisplayDomNode(iIndex, pXmlNode.childNodes.Item(lLoop))
        Next lLoop
    End If
End Sub

'-------------------------------------------------------------------------
'   Private Methods
'-------------------------------------------------------------------------
Private Function FormatNodeString(ByRef pXmlNode As IXMLDOMNode) As String
    Dim pXmlEntity As IXMLDOMEntity
    Dim pXmlNotation As IXMLDOMNotation
    Dim strLine As String

    If pXmlNode.nodeType = NODE_COMMENT Then
        'format the code comment line
        strLine = "<!--" & pXmlNode.nodeValue & "-->"
    ElseIf pXmlNode.nodeType = NODE_CDATA_SECTION Or pXmlNode.nodeType = NODE_TEXT Then
        'format the node value
        strLine = pXmlNode.nodeValue
    ElseIf pXmlNode.nodeType = NODE_DOCUMENT_TYPE Then
        'format the doc type line
        strLine = "DOCTYPE " & pXmlNode.nodeName
    ElseIf pXmlNode.nodeType = NODE_PROCESSING_INSTRUCTION Then
        'format the processing instruction
        strLine = "<?" & pXmlNode.nodeName & " " & pXmlNode.nodeValue & "?>"
    ElseIf pXmlNode.nodeType = NODE_ENTITY Then
        'get the entity reference
        Set pXmlEntity = pXmlNode
        'format the beginning of the entity line
        strLine = "<!ENTITY " & pXmlNode.nodeName
        'check if public and system IDs exist
        If (pXmlEntity.publicId <> "") Then
            'format the public ID part of the line
            strLine = strLine & " PUBLIC '" & pXmlEntity.publicId & "' '" & pXmlEntity.systemId & "'"
        ElseIf (pXmlEntity.systemId <> "") Then
            'format the system ID part of the line
            strLine = strLine & " SYSTEM '" & pXmlEntity.systemId & "'"
        End If
        'check if a notation name exists
        If (pXmlEntity.notationName <> "") Then
            'format the notation name part of the line
            strLine = strLine & " NDATA " & pXmlEntity.notationName
        End If
        'append the closing string
        strLine = strLine & ">"
    ElseIf pXmlNode.nodeType = NODE_NOTATION Then
        'get the notation reference
        Set pXmlNotation = pXmlNode
        'format the beginning of the notation line
        strLine = "<!NOTATION " & pXmlNode.nodeName
        'check if public and system IDs exist
        If (pXmlNotation.publicId <> "") Then
            'format the public ID part of the line
            strLine = strLine & " PUBLIC '" & pXmlNotation.publicId & "' '" & pXmlNotation.systemId & "'"
        ElseIf (pXmlNotation.systemId <> "") Then
            'format the system ID part of the line
            strLine = strLine & " SYSTEM '" & pXmlNotation.systemId & "'"
        End If
        'append the closing string
        strLine = strLine & ">"
    ElseIf pXmlNode.nodeType = NODE_ENTITY_REFERENCE Then
        'format the entity reference line
        strLine = "&" & pXmlNode.nodeName & ";"
    ElseIf pXmlNode.nodeType = NODE_DOCUMENT Then
        'format the document line
        strLine = txtSCPDURL
    Else
        'format the line for all the rest of the node types
        strLine = pXmlNode.nodeName
    End If
    'return the string
    FormatNodeString = strLine
End Function

Private Function FormatAttributes(ByRef pXmlNamedNodeMap As IXMLDOMNamedNodeMap) As String
    Dim pXmlAttribute As IXMLDOMAttribute
    Dim strLine As String
    Dim lLoop As Long
    
    'iterate through the attributes
    For lLoop = 0 To pXmlNamedNodeMap.length - 1
        'get a reference to the attribute
        Set pXmlAttribute = pXmlNamedNodeMap.Item(lLoop)
        
        'format the return string
        strLine = strLine + " " & pXmlAttribute.Name & "='" & pXmlAttribute.value & "'"
    Next lLoop
    'return the string
    FormatAttributes = strLine
End Function




