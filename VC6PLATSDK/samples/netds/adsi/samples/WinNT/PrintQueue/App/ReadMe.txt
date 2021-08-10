//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  PrintQueue App Sample: Displaying Print Queue Information Using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The PrintQueue sample presents a graphical user interface that displays
information about a selected print queue on a specified computer.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  frmConnect.Frm
  *  Helper.Bas
  *  PrintQueue.Frm
  *  PrintQueue.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project PrintQueue.Vbp.
  2.  From the Run menu, select Start.
  3.  A Connect to Computer dialog appears in which you specify the
      computer for the connection.  If you leave the Computer Name
      blank, the sample uses the local host.
  4.  A Print Queue and Print Jobs dialog appears in which you select
      the print queue whose properties to display.
  5.  To change the computer, select Change and enter the new computer
      name in the Connect to Computer dialog.
  6.  To refresh the display, select Refresh Status.

The Print Queue and Print Jobs dialog displays the Description, Location,
Printer Path, Model, Print Status, and Print Jobs for the print queue that
you select.  It also displays the Description, User, Print Time, and Status
of the print jobs in the selected print queue.

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
then uses the following interfaces to perform the specified tasks.

  *  IADsPrintQueue            Enumerate print queues
  *  IADsPrintQueueOperations  Determine print queue status
  *  IADsPrintJob              Enunmerate print jobs
  *  IADsPrintJobOperations    Determine print job status

The sample defines two functions, GetPrintStatus and GetJobStatus in
the Helper module, which translate the status codes into descriptive
character strings.

See Also
========
IADsPrintJob interface
IADsPrintJobOperations interface
IADsPrintQueue interface
IADsPrintQueueOperations interface
WinNT Binding String (ADsPath)

