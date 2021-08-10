        Microsoft Win32 Smart Card Software Development Kit


---------
Contents:
---------

    1.  Introduction
    2.  Updates
    3.  Documentation
    4.  Contact Information
    5.  Development Tools
    6.  Smart Card SDK Components
    7.  Installation Notes
    8.  C++ Projects
    9.  VB Projects


---------------
1. Introduction
---------------

Welcome to the Microsoft Win32 Smart Card SDK. This release provides
the necessary files and information to build retail and debug
in-process server dynamic link libraries (DLLs) and smart card aware
applications for Windows NT version 4.0 or greater, Windows 95 or
greater, on x86 platforms.

For the latest information on Microsoft's smart card products, please
visit http://www.microsoft.com/smartcard/


----------
2. Updates
----------

The SCardCOM example has been aligned with the target PCSC V1.0 Part 6
specification.

These changes require that applications built against previous versions
of the Smart Card SDK be re-compiled, and any errors resolved.  All
other changes simply fix bugs, and should not affect the interfaces.


----------------
3. Documentation
----------------

Descriptions of all programming interfaces are in the help files
that come with the Microsoft Platform SDK.


----------------------
4. Contact Information
----------------------

SmartCardSDK@DISCUSS.MICROSOFT.COM

The above email address is an external alias setup for the
Smart Card SDK. To subscribe, send email to

        LISTSERV@DISCUSS.MICROSOFT.COM

with this exact command

        SUBSCRIBE SMARTCARDSDK

in the body of the message.


--------------------
5. Development Tools
--------------------

The following tools are required to build the smart card components:

   1. Microsoft Visual C++ version 6.0 or higher (see section 9 below)
      Microsoft Visual Basic version 6.0 or higher (see section 10 below)

   2. Microsoft Win32 Platform Software Development Kit (SDK)

   3. Active Template Library (ATL) 1.2 or later.

Most of the utilities, headers, libraries, documentation, and sample
code in the Win32 Smart Card SDK are useful when building DLLs and
smart card aware applications for Windows NT version 4.0 or greater and
Windows 95 or greater.

There is no compiler, linker, lib utility, or make utility provided
with the Smart Card SDK.


----------------------------
6. Smart Card SDK Components
----------------------------

The following components are included in this version of the Win32
Smart Card SDK.

    \%MSTOOLS%\Samples\WinBase\SCard

        - Makefile
        - ReadMe.Txt
        - ReadSsp.txt

    \%MSTOOLS%\Include

        - scarddat.h    (Obsolete.  Included for backwards compatibility.)
        - scarddat.idl  (Obsolete.  Included for backwards compatibility.)
        - scarderr.h
        - scardmgr.h    (Obsolete.  Included for backwards compatibility.)
        - scardmgr.idl  (Obsolete.  Included for backwards compatibility.)
        - scardsrv.h    (Obsolete.  Included for backwards compatibility.)
        - scardsrv.idl  (Obsolete.  Included for backwards compatibility.)
        - scardssp.h
        - scardssp.idl
        - scardssp_i.c
        - scardssp_p.c
        - sspguid.h
        - sspserr.h     (Obsolete.  Included for backwards compatibility.)
        - sspsidl.h
        - sspsidl.idl

    \%MSTOOLS%\Lib

        - scardssp.tlb
        - SCardDlg.Lib
        - WinSCard.Lib

    \%MSTOOLS%\Samples\WinBase\SCard\aggreg

        - dllaggx.c
        - dllaggx.h
        - preagg.cpp
        - preagg.h
        - resagg.h
        - SCardagg.cpp
        - SCardagg.def
        - SCardagg.Idl
        - Makefile
        - SCardagg.rc
        - SCardni.cpp
        - SCardni.h

    \%MSTOOLS%\Samples\WinBase\SCard\aggreg\test

        - aggtest.cpp
        - Makefile

    \%MSTOOLS%\Samples\WinBase\SCard\app

        - preapp.cpp
        - preapp.h
        - resapp.h
        - SCarddg.cpp
        - SCarddg.h
        - SCardtst.cpp
        - SCardtst.h
        - Makefile
        - SCardtst.rc

     \%MSTOOLS%\Samples\WinBase\SCard\app\res

        - SCardtst.ico
        - SCardtst.rc2

    \%MSTOOLS%\Samples\WinBase\SCard\html

        - download.htm
        - example.htm

    \%MSTOOLS%\Samples\WinBase\SCard\llcom

        - scdtest.cpp
        - Makefile

    \%MSTOOLS%\Samples\WinBase\SCard\SCardcom

        - dlldatax.c
        - dlldatax.h
        - readme.txt
        - resource.h
        - SCardath.cpp
        - SCardath.h
        - SCardcom.cpp
        - SCardcom.def
        - SCardcom.Idl
        - Makefile
        - SCardcom.rc
        - SCardcom.rc2
        - SCarddef.h
        - SCardfil.cpp
        - SCardfil.h
        - SCardman.cpp
        - SCardman.h
        - SCardver.cpp
        - SCardver.h
        - stdafx.cpp
        - stdafx.h
        - wrphelp.cpp
        - wrphelp.h

     \%MSTOOLS%\Samples\WinBase\SCard\SCardcom\cppwrap

        - SCardwrp.cpp
        - SCardwrp.h

     \%MSTOOLS%\Samples\WinBase\SCard\propcert

        - Makefile
        - ReadMe.Txt
        - propcert.cpp

     \%MSTOOLS%\Samples\WinBase\SCard\scintro

        - Makefile
        - ReadMe.Txt
        - SCIntro.cpp

     \%MSTOOLS%\Samples\WinBase\SCard\scquery

        - Makefile
        - ReadMe.Txt
        - SCCommon.cpp
        - SCCommon.h
        - SCQuery.cpp

     \%MSTOOLS%\Samples\WinBase\SCard\setup

        - webssp.cdf
        - webssp.inf

    \%MSTOOLS%\Samples\WinBase\SCard\vb\ssp_test

        - ReadMe.Txt
        - SCardvb.frm
        - SCardvb.vbp

    \%MSTOOLS%\Samples\WinBase\SCard\vb\SCardapi

        - ReadMe.Txt
        - scrdvb.frm
        - scrdvb.frx
        - scrdvb.vbp
        - SCardapi.Bas
        - SCarderr.Bas

---------------------
7. Installation Notes
---------------------

On platforms earlier than Windows 2000, the Smart Card Base Components
must be installed on your system.  The Smart Card Base Components are
distributed with the SDK, and can be found under the Redistributable
Components Section, in SmartCard Redistributables.  For Windows 2000
and later, the Smart Card Base Components have been incorporated into
the operating system, and need not be installed separately.

Along with the Smart Card Base Components, a smart card reader and
device driver must be installed on your target machine in order for
your application or service provider DLL to communicate with a smart
card (and reader). Please refer to the Smart Card DDK for information
on how to install the DDK components and device drivers.

If you are writing a smart card-aware application, you must either
use a card service provider (provided by the card manufacturer that
exposes the services of the card for your application to call), or you
must know specifics about the card in order to access card-specific
services (e.g., file system).


---------------
8. C++ Projects
---------------

Visual C++ 6.0 or greater is required to build the  C++ projects.

The following steps should be taken to build the projects from within
Developer Studio:

1)  Set the following include paths in the Tools\Options\Directories
    menu property sheet and make certain they are listed first and in
    the following order before any other paths:

        "<Your Full SDK install Path>\include"
        "<Your Full SDK install Path>\Samples\WinBase\SCard\app"
        "<Your Full SDK install Path>\Samples\WinBase\SCard\SCardcom"
        "<Your Full SDK install Path>\Samples\WinBase\SCard\SCardcom\cppwrap"

2)  Make sure the executables path listed in the
    Tools\Options\Directories menu property sheet includes the
    following directories, listed in order and preceding any others:

        <Your Full SDK install Path>\BIN
        <Your Full Visual C++ install Path>\BIN
        <Your Full Developer Studio install Path>\SharedIDE\BIN

3)  Open the project's .dsw or makefile as a Workspace in Visual C++.

    If opening a makefile instead of a .dsw file,

        - Opening the makefile will result in an informational dialog
          about a missing .dsw file, click OK to continue.

        - Choose Yes in the next dialog asking if you want to wrap the
          makefile in a new DevStudio project.  This will create the
          .dsw file for future use.

        - Specify Win32 for the Platform in the Platforms dialog then
          click OK.

4)  Build the project(s) in sequence as specified in the notes below.

Notes:

    1)  To change the default build type (Debug, Release, etc.) edit
        line 9 of the makefile selecting an alternate build.

    2)  The projects may be built from the command line after setting
        the Visual C++ environment variables.

    3)  The APP project is dependent on the SCardCOM project. Build the
        SCardCOM project first then the APP project.

    4)  The TEST project (found in a subdirectory of AGGREG) is
        dependent on the AGGREG project.  Build the AGGREG project
        first, then build the TEST project.


---------------
9. VB Projects
---------------

Visual Basic 6.0 or greater is required to build the projects.  You
must install the ActiveX Controls as part of your Visual Basic
installation.

