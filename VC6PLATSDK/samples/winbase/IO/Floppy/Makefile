# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps

!IF "$(TARGETOS)" == "WINNT"

!include <Win32.Mak>

all: $(OUTDIR) $(OUTDIR)\mfmt.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\mfmt.obj: mfmt.c
    $(cc) $(cflags) $(cvars) $(cdebug) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" mfmt.c

$(OUTDIR)\mfmt.exe: $(OUTDIR)\mfmt.obj
    $(link) $(ldebug) $(conlflags) -out:$(OUTDIR)\mfmt.exe $(OUTDIR)\mfmt.obj $(conlibs)
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
