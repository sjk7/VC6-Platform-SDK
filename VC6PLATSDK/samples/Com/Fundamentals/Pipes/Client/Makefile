#Copyright 1992 - 1999 Microsoft Corporation, All rights reserved. 
#
# 
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
# EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
#
# Processor independent makefile

# Nmake macros for building Windows 32-Bit apps
!include <win32.mak>

!IF "$(MSVCVER)" != "7.0"

!IF EXISTS ("..\include\$(OUTDIR)/$(NULL)")

PROJ = client

all: "$(OUTDIR)\$(PROJ).exe"

CUSTOM_FLAGS = /D_WIN32_DCOM /D_UNICODE /DUNICODE


!ifndef NO_DEBUG
CUSTOM_FLAGS = $(CUSTOM_FLAGS) /D_DEBUG /DDEBUG /D_DEBUGTRACE
!endif

# Define project specific macros
PROJ_OBJS  = $(OUTDIR)\client.obj $(OUTDIR)\pipe.obj $(OUTDIR)\guids.obj

SOURCE=.\client.cxx

"$(OUTDIR)\client.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /I ..\include\$(OUTDIR) $(SOURCE)

SOURCE=.\..\include\pipe.cxx

"$(OUTDIR)\pipe.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

SOURCE=.\..\include\$(OUTDIR)\guids.c

"$(OUTDIR)\guids.obj" : $(SOURCE) "$(OUTDIR)"
    $(cc) $(cdebug) $(cflags) $(cvarsdll) $(CUSTOM_FLAGS) /c /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $(SOURCE)

# use default inference rule for compiling cpp file

EXTRA_LIBS = $(EXTRA_LIBS) kernel32.lib advapi32.lib user32.lib uuid.lib ole32.lib oleaut32.lib

# Build rule for EXE
"$(OUTDIR)\$(PROJ).exe": $(PROJ_OBJS) $(GLOBAL_OBJS) $(OUTDIR)
	$(link) $(linkdebug) $(conlflags) \
	$(PROJ_OBJS) $(guilibsdll) $(EXTRA_LIBS) \
	-out:$(OUTDIR)\$(PROJ).exe $(MAPFILE)

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"


# Rules for cleaning out those old files
clean:
    del $(OUTDIR)\*.obj *.exe *.exp *.lib *.pdb

!ELSE	
!MESSAGE You MUST first build ..\include
!ENDIF

!ELSE
!MESSAGE $(VC6MSG)
!ENDIF
