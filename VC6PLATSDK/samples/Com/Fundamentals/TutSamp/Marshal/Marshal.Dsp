# Microsoft Developer Studio Project File - Name="marshal" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=marshal - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "marshal.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "marshal.mak" CFG="marshal - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "marshal - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "marshal - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0

!IF  "$(CFG)" == "marshal - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "marshal.exe"
# PROP BASE Bsc_Name "marshal.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "temp"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "marshal.exe"
# PROP Bsc_Name "marshal.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "marshal - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "marshal.exe"
# PROP BASE Bsc_Name "marshal.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "temp"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "marshal.exe"
# PROP Bsc_Name "marshal.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "marshal - Win32 Release"
# Name "marshal - Win32 Debug"

!IF  "$(CFG)" == "marshal - Win32 Release"

!ELSEIF  "$(CFG)" == "marshal - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\makefile
# End Source File
# Begin Source File

SOURCE=.\Marshal.def
# End Source File
# Begin Source File

SOURCE=.\Micars.idl
# End Source File
# End Target
# End Project
