# Microsoft Developer Studio Project File - Name="Inc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Inc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Include.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Include.mak" CFG="Inc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Inc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Inc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Inc - Win32 Release"
# Name "Inc - Win32 Debug"
# Begin Source File

SOURCE=.\CpyImage.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling CpyImage.idl
InputPath=.\CpyImage.idl

BuildCmds= \
	midl /Oicf /h ".\CpyImage.h" /tlb ".\CpyImage.tlb" /iid   ".\CpyImage_i.c"    "CpyImage.idl"

".\CopyImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\CopyImage_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\CopyImage.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling CpyImage.idl
InputPath=.\CpyImage.idl

BuildCmds= \
	midl /Oicf /h ".\CpyImage.h" /tlb ".\CpyImage.tlb" /iid   ".\CpyImage_i.c"    "CpyImage.idl"

".\CopyImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\CopyImage_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\CopyImage.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MtsAudit.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\MtsAudit.idl

BuildCmds= \
	midl /Oicf /h ".\MtsAudit.h" /tlb ".\MtsAudit.tlb" /iid   ".\MtsAudit_i.c"    "MtsAudit.idl"

".\MtsAudit.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsAudit_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsAudit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\MtsAudit.idl

BuildCmds= \
	midl /Oicf /h ".\MtsAudit.h" /tlb ".\MtsAudit.tlb" /iid   ".\MtsAudit_i.c"    "MtsAudit.idl"

".\MtsAudit.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsAudit_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsAudit.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MtsSpyCtl.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling  MtsSpyCtl.idl
InputPath=.\MtsSpyCtl.idl

BuildCmds= \
	midl /Oicf /h ".\MtsSpyCtl.h" /tlb ".\MtsSpyCtl.tlb" /iid   ".\MtsSpyCtl_i.c"    "MtsSpyCtl.idl"

".\MtsSpy.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsSpy_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling  MtsSpyCtl.idl
InputPath=.\MtsSpyCtl.idl

BuildCmds= \
	midl /Oicf /h ".\MtsSpyCtl.h" /tlb ".\MtsSpyCtl.tlb" /iid   ".\MtsSpyCtl_i.c"    "MtsSpyCtl.idl"

".\MtsSpy.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsSpy_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsSpy.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MtsUserEventObj.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling MtsUserEventObj.idl
InputPath=.\MtsUserEventObj.idl

BuildCmds= \
	midl /Oicf /h ".\MtsUserEventObj.h" /tlb ".\MtsUserEventObj.tlb"   /iid   ".\MtsUserEventObj_i.c"  "MtsUserEventObj.idl"

".\MtsUserEventObj.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsUserEventObj.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsUserEventObj_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling MtsUserEventObj.idl
InputPath=.\MtsUserEventObj.idl

BuildCmds= \
	midl /Oicf /h ".\MtsUserEventObj.h" /tlb ".\MtsUserEventObj.tlb"   /iid   ".\MtsUserEventObj_i.c"  "MtsUserEventObj.idl"

".\MtsUserEventObj.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsUserEventObj.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\MtsUserEventObj_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RmWorker.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling RmWorker.idl
InputPath=.\RmWorker.idl

BuildCmds= \
	midl /Oicf /h ".\RmWorker.h" /tlb ".\RmWorker.tlb" /iid   ".\RmWorker_i.c"    "RmWorker.idl"

".\rmworker.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\rmworker.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\rmworker_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling RmWorker.idl
InputPath=.\RmWorker.idl

BuildCmds= \
	midl /Oicf /h ".\RmWorker.h" /tlb ".\RmWorker.tlb" /iid   ".\RmWorker_i.c"    "RmWorker.idl"

".\rmworker.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\rmworker.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\rmworker_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TxFileDisp.idl

!IF  "$(CFG)" == "Inc - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling TxFileDisp.idl
InputPath=.\TxFileDisp.idl

BuildCmds= \
	midl /Oicf /h ".\TxFileDisp.h" /tlb ".\TxFileDisp.tlb" /iid     ".\TxFileDisp_i.c"  "TxFileDisp.idl"

".\TxFileDisp.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TxFileDisp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TxFileDisp.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Inc - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Compiling TxFileDisp.idl
InputPath=.\TxFileDisp.idl

BuildCmds= \
	midl /Oicf /h ".\TxFileDisp.h" /tlb ".\TxFileDisp.tlb" /iid     ".\TxFileDisp_i.c"  "TxFileDisp.idl"

".\TxFileDisp.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TxFileDisp_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TxFileDisp.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
