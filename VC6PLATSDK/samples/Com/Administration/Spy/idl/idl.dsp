# Microsoft Developer Studio Project File - Name="idl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=idl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "idl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "idl.mak" CFG="idl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "idl - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "idl - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
MTL=midl.exe

!IF  "$(CFG)" == "idl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "ps_Win32\Release"
# PROP Target_Dir ""
# ADD MTL /out "ps_Win32" /env win32

!ELSEIF  "$(CFG)" == "idl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "ps_win32\Debug"
# PROP Target_Dir ""
# ADD MTL /out "ps_win32" /env win32

!ENDIF 

# Begin Target

# Name "idl - Win32 Release"
# Name "idl - Win32 Debug"
# Begin Source File

SOURCE=..\ComSpy\ComSpy.idl
# End Source File
# Begin Source File

SOURCE=.\ComSpyAudit.idl
# End Source File
# Begin Source File

SOURCE=.\ComSpyCtl.idl
# End Source File
# End Target
# End Project
