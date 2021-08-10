Attribute VB_Name = "ADsHelper"
Option Explicit

Public Declare Function FileTimeToLocalFileTime Lib "kernel32" _
   (lpFileTime As FILETIME, _
    lpLocalFileTime As FILETIME) As Long

Public Declare Function FileTimeToSystemTime Lib "kernel32" _
   (lpFileTime As FILETIME, _
   lpSystemTime As SYSTEMTIME) As Long

Public Declare Function SystemTimeToVariantTime Lib "oleaut32.dll" _
   (lpSystemTime As SYSTEMTIME, _
    dbTime As Double) As Long

Public Type FILETIME
        dwLowDateTime As Long
        dwHighDateTime As Long
End Type

Public Type SYSTEMTIME
        wYear As Integer
        wMonth As Integer
        wDayOfWeek As Integer
        wDay As Integer
        wHour As Integer
        wMinute As Integer
        wSecond As Integer
        wMilliseconds As Integer
End Type



Function LargeInteger_To_Time(oLargeInt As LargeInteger, vTime As Variant) As Boolean
'This function will convert the ADSI datatype LargeInteger, in the schema as 'Integer8', to a Variant value

 On Error Resume Next
 Dim pFileTime As FILETIME
 Dim pLocalFT As FILETIME
 Dim pSysTime As SYSTEMTIME
 Dim dbTime As Double
 Dim lResult As Long
 
 If (oLargeInt.HighPart = 0 And oLargeInt.LowPart = 0) Then
   vTime = 0
   'Debug.Print "No Value"
   LargeInteger_To_Time = True
   Exit Function
 End If
 
 If (oLargeInt.LowPart = -1) Then
   vTime = -1
   'Debug.Print "Never Expires"
   LargeInteger_To_Time = True
   Exit Function
 End If
 
 pFileTime.dwHighDateTime = oLargeInt.HighPart
 pFileTime.dwLowDateTime = oLargeInt.LowPart
 
 'Convert the value to Local time
 lResult = FileTimeToLocalFileTime(pFileTime, pLocalFT)
 If lResult = 0 Then
    LargeInteger_To_Time = False
    Debug.Print "FileTimeToLocalFileTime: " + Err.Number + "  - " + Err.Description
    Exit Function
 End If
 
 'Convert the FileTime to System time
 lResult = FileTimeToSystemTime(pLocalFT, pSysTime)
  If lResult = 0 Then
    LargeInteger_To_Time = False
    Debug.Print "FileTimeToSystemTime: " + Err.Number + "  - " + Err.Description
    Exit Function
 End If
 
 'Convert System Time to a Double
 lResult = SystemTimeToVariantTime(pSysTime, dbTime)
   If lResult = 0 Then
    LargeInteger_To_Time = False
    Debug.Print "SystemTimeToVariantTime: " + Err.Number + "  - " + Err.Description
    Exit Function
 End If
 
 'Place the double in the variant
 vTime = CDate(dbTime)
 'debug.print vTime
 LargeInteger_To_Time = True
End Function


Public Function LogonHours_To_String(pLogonHours() As Byte, strLoginHours As String) As Boolean
'This function will take the LogonHours property in the Active Directory and convert it into a
'string of Days and Times, separated by line feeds

'These dates/times will be in GMT

Dim strDay As String
Dim strTime As String
Dim iBase As Integer
Dim iBitMax As Integer
Dim lVal As Long
Dim iTotalBytes As Integer
Dim iOffset As Integer
Dim j As Integer
Dim k As Integer


iBase = 2
iBitMax = 8
iTotalBytes = 21
LogonHours_To_String = False
For k = 1 To iTotalBytes
    
    ' Get the block of time during the day
    Select Case (k - 1)
            Case 0, 1, 2:
                strDay = "Sunday"
            Case 3, 4, 5:
                strDay = "Monday"
            Case 6, 7, 8:
                strDay = "Tuesday"
            Case 9, 10, 11:
                strDay = "Wednesday"
            Case 12, 13, 14:
                strDay = "Thursday"
            Case 15, 16, 17:
                strDay = "Friday"
            Case 18, 19, 20:
                strDay = "Saturday"
    End Select
    
    Select Case (k - 1)
    Case 0, 3, 6, 9, 12, 15, 18:
              For j = 0 To iBitMax - 1
                lVal = iBase ^ j
                If (pLogonHours(k - 1) And (lVal)) = lVal Then
                  Select Case j
                     Case 0:
                        strTime = "00:00-59"
                     Case 1:
                        strTime = "01:00-59"
                     Case 2:
                        strTime = "02:00-59"
                     Case 3:
                        strTime = "03:00-59"
                     Case 4:
                        strTime = "04:00-59"
                     Case 5:
                        strTime = "05:00-59"
                     Case 6:
                        strTime = "06:00-59"
                     Case 7:
                        strTime = "07:00-59"
                  End Select
                  strLoginHours = strLoginHours + strDay + " " + strTime + vbLf
                End If
              Next j
            
    Case 1, 4, 7, 10, 13, 16, 19:
               For j = 0 To iBitMax - 1
                  lVal = iBase ^ j
                  If (pLogonHours(k - 1) And (lVal)) = lVal Then
                    Select Case j
                       Case 0:
                          strTime = "08:00-59"
                       Case 1:
                          strTime = "09:00-59"
                       Case 2:
                          strTime = "10:00-59"
                       Case 3:
                          strTime = "11:00-59"
                       Case 4:
                          strTime = "12:00-59"
                       Case 5:
                          strTime = "13:00-59"
                       Case 6:
                          strTime = "14:00-59"
                       Case 7:
                          strTime = "15:00-59"
                    End Select
                    strLoginHours = strLoginHours + strDay + " " + strTime + vbLf
                  End If
                Next j
                    
    Case 2, 5, 8, 11, 14, 17, 20:
              For j = 0 To iBitMax - 1
                  lVal = iBase ^ j
                  If (pLogonHours(k - 1) And (lVal)) = lVal Then
                    Select Case j
                       Case 0:
                          strTime = "16:00-59"
                       Case 1:
                          strTime = "17:00-59"
                       Case 2:
                          strTime = "18:00-59"
                       Case 3:
                          strTime = "19:00-59"
                       Case 4:
                          strTime = "20:00-59"
                       Case 5:
                          strTime = "21:00-59"
                       Case 6:
                          strTime = "22:00-59"
                       Case 7:
                          strTime = "23:00-59"
                    End Select
                    strLoginHours = strLoginHours + strDay + " " + strTime + vbLf
                  End If
                Next j
    End Select
  Next k
LogonHours_To_String = True
End Function

Public Sub EnumeratePropertyValue(oPropEntry As PropertyEntry, strValue As String)
   Dim vPropValues, val, vProp As Variant
   Dim oPropValue As PropertyValue
   Dim strTemp As String
   Dim strName As String
   Dim lResult As Integer
   
   vPropValues = oPropEntry.Values
   For Each val In vPropValues
      If TypeName(val) = "Object" Then
        Set oPropValue = val
        Select Case oPropValue.ADsType
         Case ADSTYPE_INVALID:
                strTemp = "Value is invalid"
         Case ADSTYPE_DN_STRING:
                strTemp = oPropValue.DNString
         Case ADSTYPE_CASE_EXACT_STRING:
                strTemp = oPropValue.CaseExactString
         Case ADSTYPE_CASE_IGNORE_STRING:
                strTemp = oPropValue.CaseIgnoreString
         Case ADSTYPE_PRINTABLE_STRING:
                strTemp = oPropValue.PrintableString
         Case ADSTYPE_NUMERIC_STRING:
                strTemp = oPropValue.NumericString
         Case ADSTYPE_BOOLEAN:
                strTemp = CStr(CBool(oPropValue.Boolean))
         Case ADSTYPE_INTEGER:
                strTemp = CStr(oPropValue.Integer)
         Case ADSTYPE_OCTET_STRING:
                'Get the name of the property to handle
                strName = oPropEntry.Name
                
                'Handle differently depending on the name
                If strName = "objectGUID" Then
                   strTemp = "Property is a GUID"
                ElseIf strName = "objectSid" Then
                   Dim oSid As New ADsSID
                   oSid.SetAs ADS_SID_RAW, oPropValue.OctetString
                   strTemp = CStr(oSid.GetAs(ADS_SID_HEXSTRING))
                   'strTemp = CStr(oSid.GetAs(ADS_SID_SDDL))
                   Set oSid = Nothing
                ElseIf strName = "logonHours" Then
                   Dim pHours() As Byte
                   pHours = oPropValue.OctetString
                   LogonHours_To_String pHours, strTemp
                End If
         Case ADSTYPE_UTC_TIME:
                strTemp = CStr(CDate(oPropValue.UTCTime))
         Case ADSTYPE_LARGE_INTEGER:
                'Get the name of the property to handle
                strName = oPropEntry.Name
                If strName = "accountExpires" Or _
                   strName = "badPasswordTime" Or _
                   strName = "lastLogon" Or _
                   strName = "lastLogoff" Or _
                   strName = "lockoutTime" Or _
                   InStr(LCase(strName), "time") Or _
                   InStr(LCase(strName), "date") Or _
                   strName = "pwdLastSet" Then
                 LargeInteger_To_Time oPropValue.LargeInteger, vProp
                 strTemp = CStr(vProp)
                Else
                  Dim oLargeInt As LargeInteger
                  Set oLargeInt = oPropValue.LargeInteger
                  strTemp = "&H" + CStr(Hex(oLargeInt.HighPart)) + CStr(Hex(oLargeInt.LowPart)) + " (LargeInteger)"
                End If
         Case ADSTYPE_PROV_SPECIFIC:
                strTemp = "Value is provider Specific"
         Case ADSTYPE_NT_SECURITY_DESCRIPTOR:
                strTemp = "Value of type NT Security Descriptor"

                
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' The propertyValue.ADsType should not be returned as the below values
' for IADsUser objects
'
         Case ADSTYPE_OBJECT_CLASS:
                strTemp = "Value of object class"
         Case ADSTYPE_CASEIGNORE_LIST:
                strTemp = "Value caseignore list"
         Case ADSTYPE_OCTET_LIST:
                strTemp = "Value of octet list"
         Case ADSTYPE_PATH:
                strTemp = "Value of path"
         Case ADSTYPE_POSTALADDRESS:
                strTemp = "Value of postal address"
         Case ADSTYPE_TIMESTAMP:
                strTemp = "Value of time stamp"
         Case ADSTYPE_BACKLINK:
                strTemp = "Value of back link"
         Case ADSTYPE_TYPEDNAME:
                strTemp = "Value of typedName"
         Case ADSTYPE_HOLD:
                strTemp = "Value of hold"
         Case ADSTYPE_NETADDRESS:
                strTemp = "Value of netaddress"
         Case ADSTYPE_REPLICAPOINTER:
                strTemp = "Value of replica pointer"
         Case ADSTYPE_FAXNUMBER:
                strTemp = "Value of fax number"
         Case ADSTYPE_DN_WITH_BINARY:
                strTemp = "Value of DN with binary"
         Case ADSTYPE_DN_WITH_STRING:
                strTemp = "Value of DN with string"
         Case ADSTYPE_UNKNOWN:
                strTemp = "Value of unknown type"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
         Case Else
                strTemp = "Error : Unknown Property Value type"
  End Select
  Else   'value is not IDispatch
    strTemp = val
  End If
  If strValue = "" Then
     strValue = strTemp
  Else
     strValue = strValue + "# " + strTemp
  End If
 Next val
End Sub

Public Sub GUIDtoBindableString(pGUID() As Byte, strGUIDString As String)

End Sub
