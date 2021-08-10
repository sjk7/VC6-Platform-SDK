# Microsoft Developer Studio Project File - Name="ClipBook ServerEx" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ClipBook ServerEx - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClipBook ServerEx.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClipBook ServerEx.mak" CFG="ClipBook ServerEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClipBook ServerEx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ClipBook ServerEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClipBook ServerEx - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /D "MIDL_PASS" /mktyplib203 /win32  /robust
# ADD MTL /nologo /D "NDEBUG" /D "MIDL_PASS" /mktyplib203 /win32  /robust
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 clusapi.lib resutils.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 clusapi.lib resutils.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "ClipBook ServerEx - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"StdAfx.h" /FD /GZ     /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_UNICODE" /D "_USRDLL" /Yu"StdAfx.h" /FD /GZ     /c
# ADD BASE MTL /nologo /D "_DEBUG" /D "MIDL_PASS" /mktyplib203 /win32  /robust
# ADD MTL /nologo /D "_DEBUG" /D "MIDL_PASS" /mktyplib203 /win32  /robust
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 clusapi.lib resutils.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 clusapi.lib resutils.lib /nologo /subsystem:windows /dll /debug /machine:I386

!ENDIF 

# Begin Target

# Name "ClipBook ServerEx - Win32 Release"
# Name "ClipBook ServerEx - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BasePage.cpp
# End Source File
# Begin Source File

SOURCE=".\ClipBook ServerEx.cpp"
# End Source File
# Begin Source File

SOURCE=".\ClipBook ServerEx.def"
# End Source File
# Begin Source File

SOURCE=".\ClipBook ServerEx.rc"
# End Source File
# Begin Source File

SOURCE=.\DDxDDv.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtObj.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtObjData.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtObjID.idl
# ADD MTL /h ".\ExtObjID.h"
# End Source File
# Begin Source File

SOURCE=.\PropList.cpp
# End Source File
# Begin Source File

SOURCE=.\RegExt.cpp
# End Source File
# Begin Source File

SOURCE=.\ResProp.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BasePage.h
# End Source File
# Begin Source File

SOURCE=".\ClipBook ServerEx.h"
# End Source File
# Begin Source File

SOURCE=.\DDxDDv.h
# End Source File
# Begin Source File

SOURCE=.\ExtObj.h
# End Source File
# Begin Source File

SOURCE=.\ExtObjData.h
# End Source File
# Begin Source File

SOURCE=.\PropList.h
# End Source File
# Begin Source File

SOURCE=.\RegExt.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ResProp.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
