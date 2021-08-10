//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  DataLink VB Sample: Using ADO Connections and Commands with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The DataLink sample shows how to use ActiveX Data Objects (ADO) with ADSI to
interact with Active Directory.  The sample uses ADO to execute a command and
to construct a report from the information on the objects returned by the
command.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  DataEnvironment1.DCA
  *  DataEnvironment1.Dsr
  *  DataEnvironment1.Dsx
  *  DataProject.Vbp
  *  DataProject.Vbw
  *  DataReport1.DCA
  *  DataReport1.Dsr
  *  DataReport1.Dsx

Running the Sample
==================
When you build this sample using Visual Basic, be sure that you have the
following items selected in the References list for the Project.
  *  Microsoft ActiveX Data Objects 2.5 Library
  *  Microsoft Data Binding Collection VB 6.0
  *  Microsoft Data Report Designer 6.0
  *  Microsoft Data Formatting Object Library 6.0
  *  Microsoft Data Environment Instance 1.0
  *  Microsoft Data Source Interfaces

To build and run this sample
  1.  Open the project DataProject.Vbp.
  2.  In the Project Explorer, open the DataEnvironment1.Dsr designer.
  3.  In the resulting DataEnvironment1 Data Environment, right click
      on Connection1 and select Properties.
  4.  In the resulting Data Link Properties dialog
        *  In the Provider tab, select OLE DB Provider for Microsoft
           Directory Service
        *  In the Connection tab, select Use Windows NT Integrated
           security
      and select OK to close the dialog.
  5.  Again in the DataEnvironment1 Data Environment, right click on
      Command1 and select Properties.
  6.  In the General tab, select SQL Statement as the Source of Data and
      appropriately enter your your domain in the statement box.  For the
      Fabrikam.Com domain, the SQL Statement could be, for example

        SELECT Name from 'LDAP://DC=Fabrikam,DC=com'
        WHERE objectClass='user' AND objectCategory='Person'

      Select OK to close the dialog.
  7.  In the Project Explorer, open the DataReport1.Dsr designer.
  8.  Select the resulting DataReport1 Data Project and set the following
      values in its Properties window.
        *  DataSource = DataEnvironment1
        *  DataMember = Command1
  9.  In the Project Explorer, right click on DataProject and select
      DataProject Properties.
 10.  In the General tab of the resulting Project Properties dialog,
      select DataReport1 as the Startup Object, and select OK to close
      the dialog.
 11.  From the Run menu, select Start.

Example Output
==============
The sample produces a formatted report similar to the following, which is
for the Fabrikam.Com domain.

  Administrator 
  Guest 
  A Helper 
  Test User 
  First User 
  Jeffrey Smith 
  Jane Johnson 
  IUSR_FABRIKAMDC 
  IWAM_FABRIKAMDC 
  ASPNET 

How the Sample Works
====================
The Connection1 object of DataEnvironment1 sets the provider and connection
security for the Data Link.  The Command1 object of DataEnvironment1 sets
the query source and the query statement, which uses the LDAP: provider to
search for all users who are Persons.

DataReport1 is a simple form with the results of the Name field for Command1
as its only content.
