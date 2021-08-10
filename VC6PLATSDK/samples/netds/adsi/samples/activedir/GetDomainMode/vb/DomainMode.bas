Attribute VB_Name = "DomainMode"
' This sample demonstrates how to determine the mode of a given domain

Sub Main()
Dim oRootDSE As IADs
Dim oDomain As IADs

Set oRootDSE = GetObject("LDAP://RootDSE")
Set oDomain = GetObject("LDAP://" + oRootDSE.Get("defaultNamingContext"))

Call GetDomainMode(oDomain)

Set oDomain = Nothing
Set oRootDSE = Nothing

End Sub


Sub GetDomainMode(oDomain As IADs)
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' This function actually determines the mode of the domain
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Dim vMixed As Variant
Dim strMode As String
 vMixed = oDomain.Get("ntMixedDomain")

Select Case vMixed
 Case 0: strMode = "Native Mode"
 Case 1: strMode = "Mixed Mode"
 Case Else: strMode = "Error in getting value"
End Select

MsgBox "The domain " + oDomain.Get("name") + " is in " + strMode

End Sub

Sub CheckDomainModeOfObject(oIADsObject As IADs)
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' For a given IADs object, this function will parse the domain
' information out of its canonical name, bind to that domain
' then pass it into GetDomainMode() to determine its mode
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
   Dim strCanonical As String
   Dim iFound As Integer
   Dim strDomainPath As String
   Dim oRootDSE As IADs
   Dim strNamingContext As String
   
   oIADsObject.GetInfoEx Array("canonicalName"), 0
   strCanonical = oIADsObject.Get("canonicalName")
   
   iFound = InStr(strCanonical, "/")
   strDomainPath = Left(strCanonical, iFound - 1)
   Set oRootDSE = GetObject("LDAP://" + strDomainPath + "/RootDSE")
   strNamingContext = oRootDSE.Get("defaultNamingContext")
   GetDomainMode GetObject("LDAP://" + strNamingContext)
End Sub
