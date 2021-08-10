//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Internet VB Sample: Windows Address Book
//
//--------------------------------------------------------------------------

Description
===========
The Internet sample demonstrates how to use ADSI to search for and display
users based on their Internet email addresses.

This sample uses the GC: provider and is suitable for Windows 2000 and later
networks running Active Directory.

Sample Files
============
  *  ADSIWab.Frm
  *  ADSIWab.Vbp
  *  ADSIWab.Vbw

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To run this sample you must have a connection to the Internet.  If you
are connected to a corporate LAN, you might need to install a proxy client
that allows you to communicate using TCP port 389 to the Internet.

To build and run this sample
  1.  Open the project ADSIWab.Vbp.
  2.  From the Run menu, select Start.
  3.  In the resulting ADSI Windows Address Book dialog
      a.  Select a directory service from the "Look in" list
          to connect to.
      b.  Enter either an email address in the E-mail text box
          (takes precedence) or a user name in the Name text box.
  4.  Select Find Now.
  5.  Text output at the bottom of the dialog indicates the status of the
      query and how many records were found that match the name or email
      address.  A ListView control shows the Name, E-Mail, First Name,
      Last Name, Address, Country, and Home Phone of each found record.

How the Sample Works
====================
The sample connects to the selected directory service using the binding
string sPath="GC://<internet-address>:389".  <internet-address> is either
a null string for Active Directory in the current domain or the appropriate
Internet domain name for any other selected directory service.

The sample constructs a query filter using the code segment

    If (sEmail <> "") Then
       sFilter = "(mail="
       sFilter = sFilter + sEmail + "*)"
    Else
       sFilter = "(|(|(|(cn="
       sFilter = sFilter + sName
       sFilter = sFilter + "*))(sn="
       sFilter = sFilter + sName
       sFilter = sFilter + "*))(givenName="
       sFilter = sFilter + sName
       sFilter = sFilter + "*))"
    End If

where sEmail is the string you enter for the email address and sName
is the name you enter.  The sample constructs the final form of the query
with the code segment

    sQuery = "<" + sPath
    sQuery = sQuery + ">;"
    sQuery = sQuery + sFilter
    sQuery = sQuery + ";cn,mail,givenName,sn,st,c,homePhone;subtree"

where sPath is given in the preceding paragraph.

See Also
========
Binding to the Global Catalog

