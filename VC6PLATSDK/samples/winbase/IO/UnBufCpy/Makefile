# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1994-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps
#

!IF "$(TARGETOS)" == "WINNT"

!include <Win32.Mak>

!if "$(CPU)" == "i386"
cflags = $(cflags) -D_CRTAPI1=_cdecl -D_CRTAPI2=_cdecl
!else
cflags = $(cflags) -D_CRTAPI1= -D_CRTAPI2=
!endif

ALLEXES = $(OUTDIR)\unbufcp1.exe $(OUTDIR)\unbufcp2.exe

all: $(OUTDIR) $(ALLEXES)

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

.c{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsmt) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(ALLEXES): $*.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $*.obj user32.lib $(conlibsmt)

clean:
        $(CLEANUP)
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
