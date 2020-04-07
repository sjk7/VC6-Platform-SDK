# Microsoft Developer Studio Project File - Name="perdraw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=perdraw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "perdraw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "perdraw.mak" CFG="perdraw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "perdraw - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "perdraw - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0

!IF  "$(CFG)" == "perdraw - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "perdraw.exe"
# PROP BASE Bsc_Name "perdraw.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "temp"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "perdraw.exe"
# PROP Bsc_Name "perdraw.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "perdraw - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ""
# PROP BASE Intermediate_Dir "temp"
# PROP BASE Cmd_Line "NMAKE /f makefile"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "perdraw.exe"
# PROP BASE Bsc_Name "perdraw.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "temp"
# PROP Cmd_Line "NMAKE /f makefile"
# PROP Rebuild_Opt "/a"
# PROP Target_File "perdraw.exe"
# PROP Bsc_Name "perdraw.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "perdraw - Win32 Release"
# Name "perdraw - Win32 Debug"

!IF  "$(CFG)" == "perdraw - Win32 Release"

!ELSEIF  "$(CFG)" == "perdraw - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=.\Connect.cpp
# End Source File
# Begin Source File

SOURCE=.\Connect.h
# End Source File
# Begin Source File

SOURCE=.\Drawpage.cpp
# End Source File
# Begin Source File

SOURCE=.\Drawpage.h
# End Source File
# Begin Source File

SOURCE=.\Factory.cpp
# End Source File
# Begin Source File

SOURCE=.\Factory.h
# End Source File
# Begin Source File

SOURCE=.\makefile
# End Source File
# Begin Source File

SOURCE=.\Perdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\Perdraw.def
# End Source File
# Begin Source File

SOURCE=.\Perdraw.h
# End Source File
# Begin Source File

SOURCE=.\Perdraw.ico
# End Source File
# Begin Source File

SOURCE=.\Perdraw.rc
# End Source File
# Begin Source File

SOURCE=.\Server.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.h
# End Source File
# End Target
# End Project
