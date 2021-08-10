# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1992-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Win32 apps

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!endif

all: $(OUTDIR) $(OUTDIR)\AsyncIO.Exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\AsyncIO.Obj: AsyncIO.c AsyncIO.h
    $(cc) $(cflags) $(cvarsmt) $(cdebug) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" AsyncIO.c

$(OUTDIR)\AsyncIO.Exe: $(OUTDIR)\AsyncIO.Obj
    $(link) $(ldebug) $(conlflags) -out:$(OUTDIR)\AsyncIO.Exe $(OUTDIR)\AsyncIO.Obj $(conlibsmt)

clean:
        $(CLEANUP)
