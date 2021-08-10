//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Sample Name:    lrsample - Sample Indexing Service Language Resources
//
//--------------------------------------------------------------------------

Description
===========
  The sample (lrsample) is an example wordbreaker and stemmer application
  written in C++ that implements the IWordBreaker and IStemmer interfaces.
  
Path
====
  Source: mssdk\samples\winbase\indexing\lrsample
  
User's Guide
============
  * To build the sample
      1. Set the Lib environment variable to "D:\mssdk\Lib;%Lib%" and the
         Include environment variable to "D:\mssdk\Include;%Include%",
         where D: is the drive on which you installed the Platform SDK.
      2. Correctly set the CPU environment variable to, for example, "i386".
      3. Open a command window and change the directory to the source path
         of the example.
      4. Build the example by entering, at the command-line prompt, "nmake".

  * To register the sample 
      1. Copy the wordbreaker/stemmer DLL file lrsample.dll to your
          %windir%\System32 directory.
      2. Self-register the filter by entering, at the command-line prompt,
         "regsvr32.exe %windir%\System32\lrsample.dll".

      At this point the dll is registered for a fictional locale English
      Sample, with an LCID of 0x4c09. If you can create files or issue
      queries in this locale, the DLL will be loaded and used.  It may
      may be easier to temporarily replace a system-installed language
      resource with this sample. To do so, look in the registry for

          HKLM\system\currentcontrolset\control\ContentIndex\Language

      Choose a language to replace, and change its Locale to the test
      locale.  Then change the English_Sample entry Locale value to the
      value of the locale you're replacing.  Then restart Indexing Service.

      Note that the Locale REG_DWORD value is the only information Indexing
      Service uses to choose a language resource.  The key names aren't
      used.
    
         
Programming Notes
=================
  This example implements the wordbreaker and stemmer interfaces used by
  Indexing Service for building indexes and performing queries.

  The stemmer is only used by Indexing Service for queries.  The
  implementation is limited to just a handful of words. If the list were
  larger it would be best to compress the data to minimize the working set.


