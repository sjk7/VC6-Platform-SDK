//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  DSBrowse VBS Sample: Directory Services Browser
//
//--------------------------------------------------------------------------

Description
===========
The DSBrowse sample demonstrates how to construct an application for viewing
and managing Directory Services.

DSBrowse performs the following tasks.
  *  It enumerates multiple namespaces (each corresponding to a directory
     service).  For each object found in a directory service hierarchy, it
     provides a brief description of the object.  Double clicking on a object
     (container) enumerates objects within that container.
  *  It reads and writes properties of the directory service objects.
     Clicking on Properties allows you to display the properties of an object.
     You can select a specific property and update it by selecting Set.

This sample uses the LDAP:, NDS:, NWCOMPAT:, and WinNT: providers and is
suitable for Windows NT(R) 4.0 networks, Windows 2000 and later networks
running Active Directory, and Novell Directory Services and Novell
Netware networks.

Sample Files
============
  *  bitmaps\*.bmp
  *  bitmaps\*.h
  *  bitmaps\icon1.ico
  *  bitmaps\vbvw.rc
  *  DSBrowse.Vbp
  *  DSBrowse.Vbw
  *  Main.Frm
  *  Property.Frm
  *  Property.Frx
  *  VbADs.bas

Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project DSBrowse.Vbp.
  2.  From the Run menu, select Start.
  3.  In the Active Directory VB Browser dialog that appears, expand one
      of the provider nodes under the ADs: node in the tree view.  Any
      directory service on the network will appear under one or more of
      the LDAP:, NDS:, NWCOMPAT:, and WinNT: nodes.
  4.  Continue to select and/or expand nodes in the tree view.  As you
      select a node (directory service object), the dialog displays its
      Name and Path below the tree view.
  5.  With an object highlighted,  select Properties to display the
      Properties dialog.  The Properties dialog displays the Name,
      ADsPath, Class, and IsContainer properties as well as a list of
      all properties for the object.
  6.  Select a property in the list, type a new value for it in the
      Value text box, and select Set to change the property value.
  7.  Select Close to close the Property dialog, and in the Browser
      dialog, select Exit to stop the application.

How the Sample Works
====================
The sample includes one code module and two forms.

  VbADs.Bas
    Includes the main part of the code, which enumerates all child objects
    of a parent object.
  Main.Frm
    Displays the Active Directory VB Browser dialog, which contains the
    hierarchical tree of directory service objects and the Name and Path
    of the selected object.
  Property.Frm
    Displays the Properties dialog for the selected directory service object.

See Also
========
Binding String (ADsPath)
IADs interface
IADsClass interface
IADsContainter interface
IAdsProperty interface


