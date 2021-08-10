# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
#

!IF "$(TARGETOS)" == "WINNT"

!include <Win32.Mak>

!IF "$(CPU)" == "IA64"
OUTDIR=.\Release64
!ELSE
OUTDIR=.\Release32
!ENDIF

all: "$(OUTDIR)" $(OUTDIR)\webserver.exe

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

PROJ_OBJS = $(OUTDIR)\webserver.obj

.c{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) /Fo"$(OUTDIR)\\" $(cvars) $<

$(OUTDIR)\webserver.exe: $(PROJ_OBJS)
  $(link) $(ldebug) $(conlflags)  \
  $(PROJ_OBJS)                    \
  -out:$*.exe              \
  $(conlibsdll) advapi32.lib crypt32.lib

clean:
  del $(OUTDIR)\*.bak
  del $(OUTDIR)\*.obj
  del $(OUTDIR)\*.pdb

cleaner: clean
  del $(OUTDIR)\*.exe

!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
