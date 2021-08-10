//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  PrintQueue VB Sample: Using a Print Queue in ADSI
//
//--------------------------------------------------------------------------

Description
===========
The PrintQueue sample shows how to enumerate printers connected to a
computer, how to bind to a specific print queue, and how to display print
jobs within a print queue.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  PrintQueue.Bas
  *  PrintQueue.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project PrintQueue.Vbp.
  2.  Open the module PrintQueue.Bas.
  3.  Replace the computer name MSPRINT44 with the name of the computer
      that you want to use in the line
        ComputerName = "MSPRINT44" '--- Change ComputerName accordingly
  4.  Replace the print queue name CORPF with the name of the print queue
      that you want to use in the line
        printQueueName = "CORPF"   ''--- Change PrintQueueName accordingly
  5.  From the Run menu, select Start.

Example Output
==============
If the sample runs successfully, it prints output in the Immediate window
similar to the following for the PRINT print queue on the FABRIKAMNT computer.
In this case the print queue was empty and idle.

PRINT  (\\FABRIKAMNT\PRINT)Status: OK  
PRINT  (\\FABRIKAMNT\PRINT) 
Status: OK 
--- Jobs in the queue ----- 

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
then uses the following interfaces to perform the specified tasks.

  *  IADsPrintQueue            Enumerate print queues
  *  IADsPrintQueueOperations  Determine print queue status
  *  IADsPrintJob              Enunmerate print jobs
  *  IADsPrintJobOperations    Determine print job status

The sample defines two functions, GetPrintStatus and GetJobStatus,
which translate the status codes into descriptive character strings.

See Also
========
IADsPrintJob interface
IADsPrintJobOperations interface
IADsPrintQueue interface
IADsPrintQueueOperations interface
WinNT Binding String (ADsPath)

