# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.
#


# nmake macros for building Windows 32-Bit apps included with the Platform SDK

!IF "$(TARGETOS)" == "WINNT"

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\enumstreams.exe

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

.c{$(OUTDIR)}.obj:
    $(cc) $(cflags) $(cdebug) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\enumstreams.exe: $(OUTDIR)\enumstreams.obj $(OUTDIR)\findstream.obj
    $(link) $(ldebug) $(conlflags) \
           $(OUTDIR)\enumstreams.obj $(OUTDIR)\findstream.obj \
           $(conlibs) \
           -out:$(OUTDIR)\enumstreams.exe 
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
