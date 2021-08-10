# Microsoft Developer Studio Project File - Name="CapMFC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CapMFC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CapMFC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CapMFC.mak" CFG="CapMFC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CapMFC - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CapMFC - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CapMFC - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CapMFC - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /ZI /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CapMFC - Win32 Release"
# Name "CapMFC - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\acanim.cpp
# End Source File
# Begin Source File

SOURCE=.\acaudio.cpp
# End Source File
# Begin Source File

SOURCE=.\acball.cpp
# End Source File
# Begin Source File

SOURCE=.\acchar.cpp
# End Source File
# Begin Source File

SOURCE=.\acchars.cpp
# End Source File
# Begin Source File

SOURCE=.\accomm.cpp
# End Source File
# Begin Source File

SOURCE=.\accomms.cpp
# End Source File
# Begin Source File

SOURCE=.\acex.cpp
# End Source File
# Begin Source File

SOURCE=.\acprop.cpp
# End Source File
# Begin Source File

SOURCE=.\acreq.cpp
# End Source File
# Begin Source File

SOURCE=.\acuser.cpp
# End Source File
# Begin Source File

SOURCE=.\CapMFC.cpp
# End Source File
# Begin Source File

SOURCE=.\CapMFC.rc

!IF  "$(CFG)" == "CapMFC - Win32 Release"

!ELSEIF  "$(CFG)" == "CapMFC - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\acanim.h
# End Source File
# Begin Source File

SOURCE=.\acaudio.h
# End Source File
# Begin Source File

SOURCE=.\acball.h
# End Source File
# Begin Source File

SOURCE=.\acchar.h
# End Source File
# Begin Source File

SOURCE=.\acchars.h
# End Source File
# Begin Source File

SOURCE=.\accomm.h
# End Source File
# Begin Source File

SOURCE=.\accomms.h
# End Source File
# Begin Source File

SOURCE=.\acex.h
# End Source File
# Begin Source File

SOURCE=.\acprop.h
# End Source File
# Begin Source File

SOURCE=.\acreq.h
# End Source File
# Begin Source File

SOURCE=.\acuser.h
# End Source File
# Begin Source File

SOURCE=.\CapMFC.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cap.ico
# End Source File
# Begin Source File

SOURCE=.\res\CapMFC.ico
# End Source File
# Begin Source File

SOURCE=.\res\CapMFC.rc2
# End Source File
# End Group
# End Target
# End Project
# Section CapMFC : {B0913410-3B44-11D1-ACBA-00C04FD97575}
# 	2:5:Class:CAgentCtlCommandEx
# 	2:10:HeaderFile:agentctlcommandex.h
# 	2:8:ImplFile:agentctlcommandex.cpp
# End Section
# Section CapMFC : {F5BE8BDF-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlPropertySheet
# 	2:10:HeaderFile:agentctlpropertysheet.h
# 	2:8:ImplFile:agentctlpropertysheet.cpp
# End Section
# Section CapMFC : {D45FD31B-5C6E-11D1-9EC1-00C04FD7081F}
# 	2:21:DefaultSinkHeaderFile:agentctlex.h
# 	2:16:DefaultSinkClass:CAgentCtlEx
# End Section
# Section CapMFC : {6BA90C01-3910-11D1-ACB3-00C04FD97575}
# 	2:5:Class:CAgentCtlCommandsEx
# 	2:10:HeaderFile:agentctlcommandsex.h
# 	2:8:ImplFile:agentctlcommandsex.cpp
# End Section
# Section CapMFC : {1DAB85C3-803A-11D0-AC63-00C04FD97575}
# 	2:5:Class:CAgentCtlRequest
# 	2:10:HeaderFile:agentctlrequest.h
# 	2:8:ImplFile:agentctlrequest.cpp
# End Section
# Section CapMFC : {DE8EF600-2F82-11D1-ACAC-00C04FD97575}
# 	2:5:Class:CAgentCtlCharacterEx
# 	2:10:HeaderFile:agentctlcharacterex.h
# 	2:8:ImplFile:agentctlcharacterex.cpp
# End Section
# Section CapMFC : {822DB1C0-8879-11D1-9EC6-00C04FD7081F}
# 	2:5:Class:CAgentCtlBalloonEx
# 	2:10:HeaderFile:agentctlballoonex.h
# 	2:8:ImplFile:agentctlballoonex.cpp
# End Section
# Section CapMFC : {8563FF20-8ECC-11D1-B9B4-00C04FD97575}
# 	2:5:Class:CAgentCtlEx
# 	2:10:HeaderFile:agentctlex.h
# 	2:8:ImplFile:agentctlex.cpp
# End Section
# Section CapMFC : {F5BE8BE8-7DE6-11D0-91FE-00C04FD701A5}
# 	2:5:Class:CAgentCtlCharacters
# 	2:10:HeaderFile:agentctlcharacters.h
# 	2:8:ImplFile:agentctlcharacters.cpp
# End Section
# Section CapMFC : {8B77181C-D3EF-11D1-8500-00C04FA34A14}
# 	2:5:Class:CAgentCtlAnimationNames
# 	2:10:HeaderFile:agentctlanimationnames.h
# 	2:8:ImplFile:agentctlanimationnames.cpp
# End Section
