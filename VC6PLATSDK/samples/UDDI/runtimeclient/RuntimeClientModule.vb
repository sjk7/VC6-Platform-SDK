' =====================================================================
'   This file is part of the Microsoft UDDI SDK Code Samples.
'
'   Copyright (C) Microsoft Corporation.  All rights reserved.
'
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation.  See these other
' materials for detailed information regarding Microsoft code samples.
'
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' =====================================================================
Option Explicit On 

Imports Microsoft.Uddi
Imports Microsoft.Uddi.Businesses
Imports Microsoft.Uddi.Services
Imports Microsoft.Uddi.TModels

Module RuntimeClientModule

    Dim myConn As UddiConnection

    Sub Main()

        ' Construct a connection for inquire and publish activities

        ' To use the test Microsoft UDDI Business Registry:
        Dim myUsername = " *** Insert your username *** "
        Dim myPassword = " *** Insert your password *** "

        myConn = New UddiConnection("http://test.uddi.microsoft.com/inquire", _
                                    "https://test.uddi.microsoft.com/publish", _
                                    "", _
                                    myUsername, myPassword)

        ' To use UDDI Services using Windows Authentication:
        ' myConn = New UddiConnection("http://servername/uddi/inquire.asmx",http://servername/uddi/publish.asmx")


        Dim myServiceKey As String
        Dim myBizKey As String

        Try
            ' Publish a business with a service available at serveral locations
            PerformPublication(myBizKey, myServiceKey)

            ' Simulate access across all of those service instances
            InvokeServiceInstances(myServiceKey)

            ' Remove the business and contained services
            PerformDeletion(myBizKey)

        Catch ex As Exception
            Console.WriteLine(ex.Message)
        End Try

        Console.ReadLine()

    End Sub

    Sub InvokeServiceInstances(ByVal myServiceKey As String)

        ' Initialize random-number generator.
        Randomize()

        ' Create a ManagedUrl specifying criteria for the access points that we wish to use.
        ' Our criteria are service instances supporting the "responds to http" capability and
        ' offered only by the logical service that we created
        Dim fb As New FindBinding(CommonCanonical.UddiOrgHttp)
        fb.ServiceKey = myServiceKey

        ' We construct these criteria into a FindBinding request and 
        ' the ManagedUrl class will expose the matching service instance URLs
        Dim manURL As New ManagedUrl(myConn, fb)

        ' Simulate repeated access of the remote service
        ' but force occasional failures.
        Dim loopCount As Int16

        For loopCount = 1 To 20

            Try
                While True

                    ' Simulate access to the remote service instance
                    Console.WriteLine("Now using " + manURL.Value)

                    ' Force an occasional failure
                    If (CInt(5 * Rnd()) > 4) Then Throw New System.Exception("An exception has occurred.")

                End While

            Catch ex As Exception
                ' In case of failure all that is required is to indicate that failure and proceed
                manURL.FailOver()
            End Try

        Next loopCount

    End Sub

    Sub PerformPublication(ByRef bizKey As String, ByRef servKey As String)

        ' Declare a business entity
        Dim myBiz As New BusinessEntity("MyBizName")

        ' Declare a new service
        Dim myService As New BusinessService("MyService")

        ' Declare a technical capability for the service
        ' Typically this would be an identifier for a tModel holding the location of a WSDL file
        ' For simplicity we will use the predefined identifier for the "responds to http" capability
        Dim tModForHttp As New TModelInstanceInfo(CommonCanonical.UddiOrgHttp)

        ' Declare bindings to the locations of the web service instances and add the capability
        Dim myBinding1 As New BindingTemplate
        myBinding1.AccessPoint = New AccessPoint("http://EastCoastLocation/default.asmx", UrlType.Http)
        myBinding1.TModelInstanceInfos.Add(tModForHttp)

        Dim myBinding2 As New BindingTemplate
        myBinding2.AccessPoint = New AccessPoint("http://WestCoastLocation/default.asmx", UrlType.Http)
        myBinding2.TModelInstanceInfos.Add(tModForHttp)

        Dim myBinding3 As New BindingTemplate
        myBinding3.AccessPoint = New AccessPoint("http://NorthernLocation/default.asmx", UrlType.Http)
        myBinding3.TModelInstanceInfos.Add(tModForHttp)

        ' Attach the bindings to the service
        myService.BindingTemplates.Add(myBinding1)
        myService.BindingTemplates.Add(myBinding2)
        myService.BindingTemplates.Add(myBinding3)

        ' Attach the service to the business
        myBiz.BusinessServices.Add(myService)

        ' Save the business
        Dim mySaveBiz As New SaveBusiness(myBiz)
        Dim savedBizDetail As BusinessDetail = mySaveBiz.Send(myConn)

        Console.WriteLine("SaveBusiness performed:")
        Console.WriteLine()
        Console.WriteLine(savedBizDetail.ToString())
        Console.WriteLine()
        Console.WriteLine("Press any key to continue...")
        Console.Read()

        ' Store the allocated key for the business
        bizKey = savedBizDetail.BusinessEntities(0).BusinessKey

        ' Store the allocated key for the service
        servKey = savedBizDetail.BusinessEntities(0).BusinessServices(0).ServiceKey


    End Sub

    Sub PerformDeletion(ByVal bizKey As String)

        ' Specify the business that we wish to delete
        Dim delBiz As New DeleteBusiness(bizKey)

        ' Send the request
        delBiz.Send(myConn)

        Console.WriteLine()
        Console.WriteLine("DeleteBusiness performed.")
        Console.WriteLine()
        Console.WriteLine("Press any key to finish...")
        Console.Read()

    End Sub

End Module
