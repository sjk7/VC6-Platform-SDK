# Microsoft Developer Studio Project File - Name="ComSpyCtl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ComSpyCtl - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyCtl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ComSpyCtl.mak" CFG="ComSpyCtl - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ComSpyCtl - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ComSpyCtl - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ComSpyCt"
# PROP BASE Intermediate_Dir "ComSpyCt"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\ReleaseU\x86"
# PROP Intermediate_Dir "ReleaseU\x86"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I "..\idl\ps_win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "..\idl\ps_win32" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 comdlg32.lib shell32.lib rpcrt4.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 comdlg32.lib shell32.lib rpcrt4.lib svcguid.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\..\ReleaseU\x86
TargetPath=\mssdk\Samples\Com\Administration\Spy\ReleaseU\x86\ComSpyCtl.dll
InputPath=\mssdk\Samples\Com\Administration\Spy\ReleaseU\x86\ComSpyCtl.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\DebugU\x86"
# PROP Intermediate_Dir "DebugU\x86"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\idl\ps_win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "..\idl\ps_win32" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 comdlg32.lib shell32.lib rpcrt4.lib svcguid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\..\DebugU\x86
TargetPath=\mssdk\Samples\Com\Administration\Spy\DebugU\x86\ComSpyCtl.dll
InputPath=\mssdk\Samples\Com\Administration\Spy\DebugU\x86\ComSpyCtl.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "ComSpyCtl - Win32 Unicode Release"
# Name "ComSpyCtl - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Adminwrap.cpp

!IF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "ComSpyCtl - Win32 Unicode Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AppInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ComSpy.cpp
# End Source File
# Begin Source File

SOURCE=.\ComSpyCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\ComSpyCtl.def
# End Source File
# Begin Source File

SOURCE=.\ComSpyCtl.rc
# End Source File
# Begin Source File

SOURCE=.\ComSpyPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\crmsub.cpp
# End Source File
# Begin Source File

SOURCE=.\evtstoresub.cpp
# End Source File
# Begin Source File

SOURCE=.\methodsub.cpp
# End Source File
# Begin Source File

SOURCE=.\resourcesub.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectEventsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysLCESub.cpp
# End Source File
# Begin Source File

SOURCE=.\txsub.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\activitysub.h
# End Source File
# Begin Source File

SOURCE=.\Adminwrap.h
# End Source File
# Begin Source File

SOURCE=.\AppInfo.h
# End Source File
# Begin Source File

SOURCE=.\appsub.h
# End Source File
# Begin Source File

SOURCE=.\ComSpyPropPage.h
# End Source File
# Begin Source File

SOURCE=.\crmsub.h
# End Source File
# Begin Source File

SOURCE=.\evtstoresub.h
# End Source File
# Begin Source File

SOURCE=.\exceptionsub.h
# End Source File
# Begin Source File

SOURCE=.\identitysub.h
# End Source File
# Begin Source File

SOURCE=.\InstanceSub.h
# End Source File
# Begin Source File

SOURCE=.\lbsub.h
# End Source File
# Begin Source File

SOURCE=.\methodsub.h
# End Source File
# Begin Source File

SOURCE=.\objconstsub.h
# End Source File
# Begin Source File

SOURCE=.\objpool2sub.h
# End Source File
# Begin Source File

SOURCE=.\objpoolsub.h
# End Source File
# Begin Source File

SOURCE=.\objsub.h
# End Source File
# Begin Source File

SOURCE=.\qcsub.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\resourcesub.h
# End Source File
# Begin Source File

SOURCE=.\securitysub.h
# End Source File
# Begin Source File

SOURCE=.\SelectEventsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysLCESub.h
# End Source File
# Begin Source File

SOURCE=.\threadsub.h
# End Source File
# Begin Source File

SOURCE=.\txsub.h
# End Source File
# Begin Source File

SOURCE=.\usersub.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Comspy1.bin
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ComSpy.rgs
# End Source File
# Begin Source File

SOURCE=.\ComSpyPropPage.rgs
# End Source File
# Begin Source File

SOURCE=.\ShowEvents.rgs
# End Source File
# End Target
# End Project
