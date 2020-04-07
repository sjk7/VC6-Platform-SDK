# Microsoft Developer Studio Project File - Name="apputil" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=apputil - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "apputil.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "apputil.mak" CFG="apputil - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "apputil - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "apputil - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0

!IF  "$(CFG)" == "apputil - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "apputil.exe"
# PROP BASE Bsc_Name "apputil.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "temp"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "apputil.exe"
# PROP Bsc_Name "apputil.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "apputil - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "apputil.exe"
# PROP BASE Bsc_Name "apputil.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "temp"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "apputil.exe"
# PROP Bsc_Name "apputil.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "apputil - Win32 Release"
# Name "apputil - Win32 Debug"

!IF  "$(CFG)" == "apputil - Win32 Release"

!ELSEIF  "$(CFG)" == "apputil - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\Apputil.cpp
# End Source File
# Begin Source File

SOURCE=.\Apputil.h
# End Source File
# Begin Source File

SOURCE=.\makefile
# End Source File
# End Target
# End Project
