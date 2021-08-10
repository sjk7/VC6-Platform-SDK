//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Services VB Sample: Manipulating Services with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Services sample presents a graphical user interface that displays
information about system services on a specified computer.

The sample also enables you to start, stop, or pause a selected service.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  frmConnect.Frm
  *  Services.Frm
  *  Services.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Services.Vbp.
  2.  From the Run menu, select Start.
  3.  A Connect to Computer dialog appears in which you specify the
      computer for the connection.  If you leave the Computer Name
      blank, the sample uses the local host.
  4.  A Service dialog appears in which you select the service whose
      properties to display.
  5.  To change the computer, select Change and enter the new computer
      name in the Connect to Computer dialog.
  6.  To refresh the display, select Refresh Status.
  7.  To perform an operation on the selected service, appropriately
      select Start, Stop, or Pause.

The Service dialog displays the Computer, Services, and Properties for the
service that you select.  It also displays the operations you can perform
on the selected service.

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
then uses the following interfaces to perform the specified tasks.

  *  IADsService            Enumerate services
  *  IADsServiceOperations  Determine service status and perform
                            operations on services

See Also
========
IADsContainer interface
IADsService interface
IADsServiceOperations interface
WinNT Binding String (ADsPath)

