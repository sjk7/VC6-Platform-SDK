#Copyright 1992 - 1999 Microsoft Corporation, All rights reserved. 
#
# 
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
# EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
#
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

!IF EXISTS ("..\include\$(OUTDIR)/$(NULL)")

PROJ = server

all: $(OUTDIR) $(OUTDIR)\$(PROJ).exe

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CUSTOM_FLAGS = /D_WIN32_DCOM /D_UNICODE /DUNICODE


!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\server.obj $(OUTDIR)\component.obj $(OUTDIR)\pipe.obj $(OUTDIR)\guids.obj

# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) advapi32.lib user32.lib uuid.lib ole32.lib oleaut32.lib

SOURCE=.\..\include\pipe.cxx

"$(OUTDIR)\pipe.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\..\include\$(OUTDIR)\guids.c

"$(OUTDIR)\guids.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\server.cxx
"$(OUTDIR)\server.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I ..\include\$(OUTDIR) $(SOURCE)

SOURCE=.\component.cxx

"$(OUTDIR)\component.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I ..\include\$(OUTDIR) $(SOURCE)

# Build rule for EXE
$(OUTDIR)\$(PROJ).exe: $(PROJ_OBJS) $(GLOBAL_OBJS)
	$(link) $(linkdebug) $(guilflags) \
	$(PROJ_OBJS) $(guilibsdll) $(EXTRA_LIBS) \
	-out:$(OUTDIR)\$(PROJ).exe

# Rules for cleaning out those old files
clean:
    del $(OUTDIR)\*.obj $(OUTDIR)\*.exe $(OUTDIR)\*.exp $(OUTDIR)\*.lib $(OUTDIR)\*.pdb

!ELSE	
!MESSAGE You MUST first build ..\include
!ENDIF
