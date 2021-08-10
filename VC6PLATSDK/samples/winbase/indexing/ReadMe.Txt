//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Indexing Service Samples ReadMe File
//
//--------------------------------------------------------------------------

Description
===========
  Indexing Service is a Microsoft(R) Windows(R) 2000 base service.
  Indexing Service creates indexed catalogs for the contents and
  properties of both file systems and virtual Webs.

  Indexing Service is programmatically available to applications and scripts
  for providing an efficient means of managing, querying, and indexing the
  information in file systems or Web servers.  Indexing Service provides
  several query mechanisms for efficiently accessing the information in the
  catalogs.  The indexed information results from filtering the file systems
  and the Webs using Microsoft-supplied filters and, optionally, custom-
  supplied filters.

  The applications and scripts in the subdirectories of the root path for
  the Indexing Service samples illustrate how to program for Indexing
  Service.  For more information, see the "WinBase/Indexing Service" section
  in the Platform SDK documentation.

Root Path
=========
  Source: mssdk\samples\winbase\indexing\

User's Guide
============
  * To build the complete set of C++ samples
      1. Set the Lib environment variable to "D:\mssdk\Lib;%Lib%" and the
         Include environment variable to "D:\mssdk\Include;%Include%",
         where D: is the drive on which you installed the Platform SDK.
      2. Correctly set the CPU environment variable to, for example, "i386".
      3. Open a command window and change the directory to the source root
         path of the set of samples.
      4. Build the set of samples by entering, at the command-line prompt,
         "nmake".

  * The build process does not include the following samples.
      * DHtml                  (requires Internet Explorer)
      * IISAdmin and IISSearch (require Internet Information Services)
      * SQuery                 (requires Windows Script Host)
      * VBAdmin and VBQuery    (require Visual Basic)
      * VJQuery                (requires Visual J++)

    To build or use these samples, see the User's Guide section in the
    ReadMe files in each individual sample directory for additional
    information.

Programming Notes
=================
  The Indexing Service sample code illustrates three categories of tasks
  involved with Indexing Service: managing, querying, and indexing.  Each
  of the samples is developed, built, or executed using a "tool" and a
  language to illustrate an Indexing Service application programming
  interface (API).

  Tools
  -----
    Examples of possible tools include the following.
      * Internet Explorer (IE)
      * Internet Information Services (IIS)
      * Visual Studio
      * Windows Scripting Host (WSH)

    Many of the samples can also be built from the command line using a text
    editor and appropriate commands to a compiler or interpreter.

  Languages
  ---------
    The illustrated languages include the following.
      * Internet Data Query (IDQ), Internet Data Administration (IDA),
        and HTML Extension (HTX) facilities with HTML
      * Visual Basic
      * Visual Basic Scripting Edition (VBScript)
      * Visual C++
      * Visual J++
      * JScript

  APIs
  ----
    The Indexing Service APIs include the following.
      * ActiveX Data Objects (ADO)
      * Admin Helper for OLE DB Provider
      * IFilter Component
      * ISAPI Extensions
      * OLE DB Helper for OLE DB Provider
      * OLE DB Provider for Indexing Service
      * Query Helper for ADO

  Samples by Name
  ---------------
    The following is an alphabetical list of the directories (and sample
    name, if different from the directory name) of samples for Indexing
    Service in the Platform SDK and a brief description of each sample.

    AdvQuery
    ++++++++
      A command-line application written in C++ that executes a query using
      the OLE DB Provider interfaces such as ICommand and ICommandTree.
      It shows how to specify a catalog, machine name, and scope.  It can
      also display the OLE DB command tree for the query.

    ChgState
    ++++++++
      A command-line application written in C++ that can either report the
      current state of a catalog or change the state of the catalog using
      the SetCatalogState function of the OLE DB Helper API.

    DHtml (CiDHTML)
    +++++++++++++++
      A dynamic HTML (DHTML) application using VBScript that creates a
      client-side query form to query an Indexing Service catalog.  The
      sample uses the Query Helper API for the query and an ADO recordset
      to return the results.

    HtmlProp
    ++++++++
      An example IFilter implementation written in C++ that specializes
      the Indexing Service HTML filter to extract value-type properties.
      It converts HTML meta properties to data types other than strings as
      specified by a configuration file.

    IFilter (HtmlFilt)
    ++++++++++++++++++
      An example IFilter implementation (HtmlFilt) written in C++ for
      HTML files.  It is more complex than a basic text filter, because it
      demonstrates techniques for extracting both text-type and value-type
      properties.

    IISAdmin
    ++++++++
      A set of HTML and ASP forms that demonstrates how to use Internet
      Information Services (IIS) to administer Indexing Service.  The forms
      retrieve indexing statistics, force a master merge, rescan paths,
      and check for documents that could not be filtered.

    IISSearch
    +++++++++
      A set of HTML and ASP forms that demonstrates how to use Internet
      Information Services (IIS) to query Indexing Service.  The forms use
      Indexing Service Query Language queries and the Query Helper API,
      use SQL queries and the ADO and Query Helper APIs, and use IDQ+HTX
      and the ISAPI Extensions API.

    LRSample
    +++++++++
      A sample wordbreaker and stemmer dll.  Indexing Service loads 
      language resources to perform indexing and queries with text from
      various languages. The sample shows how to implement such resources.

    Simple (QSample)
    ++++++++++++++++
      A command-line application written in C++ that executes a query using
      the OLE DB Helper API functions CCreateICommand and CITextToFullTree
      to simplify the coding needed to create a query to an Indexing Service
      catalog.

    SmpFilt
    +++++++
      An example IFilter implementation written in C++ that reads an un-
      formatted text file (with the extension .smp) using the ANSI code
      page of the current thread, and outputs UNICODE text for the current
      locale.  It accepts as input only single-byte-character text files
      and not multibyte-character or UNICODE text files.  It is the simplest
      example of an IFilter implementation included in the Indexing Service
      sample code.

    SQuery
    ++++++
      Three scripts that execute using Windows Script Host.  VBSQuery is
      written in VBScript and performs a simple query.  JSQuery is a
      translation of VBSQuery to JScript.  QSample is written in
      VBScript and functions similarly to the C++ sample application
      Simple(QSample) with managing and querying functionality.

    VBAdmin
    +++++++
      A Windows application written in Visual Basic that illustrates how to
      administer Indexing Service using the AdminIndexServer, CatAdm, and
      ScopeAdm automation objects of the Admin Helper API.

    VBQuery
    +++++++
      A Windows application written in Visual Basic that illustrates how to
      query Indexing Service using the Indexing Service Query Language and
      the ADO and Query Helper APIs.

    VJQuery
    +++++++
      A command-line application written in Visual J++ that illustrates
      how to query Indexing Service using the SQL query language and the
      ADO API.

  Samples by Task
  ---------------
    The following samples illustrate managing Indexing Service.

    Directory (Name)    Tool           Language            API
    ++++++++++++++++++  +++++++++++++  ++++++++++++++++++  +++++++++++++++++
    ChgState            Visual Studio  Visual C++          OLE DB Helper
    IISAdmin            IIS            VBScript, JScript,  Admin Helper,
                                       IDA+HTX             ISAPI Extensions
    SQuery (QSample)    WSH            VBScript            Admin Helper
    VBAdmin             Visual Studio  Visual Basic        Admin Helper

    The following samples illustrate querying Indexing Service.

    Directory (Name)    Tool           Language            API
    ++++++++++++++++++  +++++++++++++  ++++++++++++++++++  +++++++++++++++++
    AdvQuery            Visual Studio  Visual C++          OLE DB Provider
    CatQ                Visual Studio  Visual C++          OLE DB Provider
    DHtml (CiDHtml)     IE+DHTML       VBScript            Query Helper
    IISSearch           IIS            VBScript, JScript,  ADO, Query Helper,
                                       IDQ+HTX             ISAPI Extensions
    Simple (QSample)    Visual Studio  Visual C++          OLE DB Helper
    SQuery (VBSQuery,   WSH            VBScript,           Query Helper
            JSQuery)                   JScript
    VBQuery             Visual Studio  Visual Basic        ADO, Query Helper
    VJQuery             Visual Studio  Visual J++          ADO

    The following samples illustrate indexing (the filtering component)
    with Indexing Service.

    Directory (Name)    Tool           Language            API
    ++++++++++++++++++  +++++++++++++  ++++++++++++++++++  +++++++++++++++++
    HtmlProp            Visual Studio  Visual C++          IFilter Component
    IFilter (HtmlFilt)  Visual Studio  Visual C++          IFilter Component
    SmpFilt             Visual Studio  Visual C++          IFilter Component

    The following samples illustrate language resources in Indexing Service.

    Directory (Name)    Tool           Language            API
    ++++++++++++++++++  +++++++++++++  ++++++++++++++++++  +++++++++++++++++
    LRSample            Visual Studio  Visual C++          IWordBreaker and
                                                           IStemmer components

