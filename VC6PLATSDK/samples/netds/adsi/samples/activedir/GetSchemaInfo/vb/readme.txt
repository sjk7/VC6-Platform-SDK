//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  GetSchemaInfo VB Sample: Querying the Active Directory Schema
//
//--------------------------------------------------------------------------

Description
===========
The GetSchemaInfo sample uses ADSI to bind to the Active Directory schema
container and search for classSchema and/or attributeSchema objects that
match a specified query.

For example, you can search for all global catalog attributes
(IsMemberOfPartialAttributeSet=TRUE) or search for a specific class
(cn=user).

The sample uses ActiveX Data Objects (ADO) to perform the search.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  GetSchemaInfo.Bas
  *  GetSchemaInfo.Frm
  *  GetSchemaInfo.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project GetSchemaInfo.Vbp.
  2.  From the Run menu, select Start.

Example Output
==============
When you run the sample, a dialog appears in which you specify a query.
In this dialog, you specify to search for either
  *  Both Classes and Attributes
  *  Classes only
  *  Attributes only

You have a choice of how to specify an LDAP filter string for the query.
  *  Enter a desired query string in the LDAP Filter String text box.
  *  Click the Next Query Sample button one or more times to select one
     of several predetermined sample query strings.

To perform the search, click the Get Schema button.  The dialog shows the
complete LDAP query, the number of resulting matches, and the attributes
of the matching items.

The predetermined sample query strings include the following.

  (cn=Domain)
    Finds the schema class for a domain.
  (cn=Given-Name)
    Finds the schema attribute for first name.
  (IsSingleValued=FALSE)
    Finds all of the attributes in the schema which are multi-valued.
    Change the FALSE to TRUE to find all single-valued attributes.
  (ldapDisplayName=objectGUID)
    Finds the attribute for GUID by its LDAP name.
  (IsMemberOfPartialAttributeSet=TRUE)
    Finds the attributes that are stored in the Global Catalog.
  (searchFlags=1)
    Finds all indexed values.
    Change 1 to 0 (zero) to find all non-indexed values.
  (systemFlags=" + CStr(ADS_SYSTEMFLAG_ATTR_NOT_REPLICATED Or
   ADS_SYSTEMFLAG_ATTR_SCHEMA_BASE_OBJECT) + ")
    Finds all attributes that are unreplicated and match the base schema object.
  (systemFlags:1.2.840.113556.1.4.804:=" + CStr(ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED) + ")
    Finds all constructed attributes.
  (subClassOf=organizationalPerson)
    Finds classes that are a subclass of organizationalPerson.


How the Sample Works
====================
The sample defines one module and one form.

  GetSchemaInfo
    Initializes using the IADs interface, performs the search using
    Active Data Objects (ASO), and uninitializes.  Selects these attributes
    to return with the query:
      *  cn
      *  adspath
      *  ldapDisplayName
      *  objectClass
      *  objectCategory

  frmSchemaInfo
    Manages the dialog for specifying the query, including the predetermined
    sample queries.

See Also
========
IADs interface
Reading the Abstract Schema
Searching with ActiveX Data Objects (ADO)
