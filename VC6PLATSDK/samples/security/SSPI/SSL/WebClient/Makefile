# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999  Microsoft Corporation.  All rights reserved.
#

!IF "$(TARGETOS)" == "WINNT"

!IF "$(CPU)" == "IA64"
OUTDIR=.\Release64
!ELSE
OUTDIR=.\Release32
!ENDIF

!include <Win32.Mak>

all: "$(OUTDIR)" $(OUTDIR)\webclient.exe $(OUTDIR)\wi_ssl_client.exe 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.c{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) /Fo"$(OUTDIR)\\"  $(cvars) $<

.cpp{$(OUTDIR)}.obj:
  $(cc) $(cdebug) $(cflags) /Fo"$(OUTDIR)\\"$(cvars) $<


$(OUTDIR)\webclient.exe: $(OUTDIR)\webclient.obj
  $(link) $(ldebug) $(conlflags) \
  $(OUTDIR)\webclient.obj \
  -out:$*.exe \
  $(conlibsdll) advapi32.lib crypt32.lib


$(OUTDIR)\wi_ssl_client.exe: $(OUTDIR)\wi_ssl_client.obj
  $(link) $(ldebug) $(conlflags) \
  $(OUTDIR)\wi_ssl_client.obj              \
  -out:$*.exe  \
  $(conlibsdll) wininet.lib user32.lib

clean:
  del $(OUTDIR)\*.bak
  del $(OUTDIR)\*.obj
  del $(OUTDIR)\*.pdb

cleaner: clean
  del $(OUTDIR)\*.exe
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
