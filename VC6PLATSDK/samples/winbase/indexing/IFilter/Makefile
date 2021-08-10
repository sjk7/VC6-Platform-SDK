# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (c) Microsoft Corporation. All rights reserved.
#
#
# Processor independent makefile
#

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\htmlfilt.dll

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\htmlfilt.res: htmlfilt.rc
    $(rc) $(rcvars) $(rcflags) /fo $(OUTDIR)\htmlfilt.res htmlfilt.rc

objs =  $(OUTDIR)\anchor.obj     \
        $(OUTDIR)\assert.obj     \
        $(OUTDIR)\bag.obj        \
        $(OUTDIR)\charhash.obj   \
        $(OUTDIR)\codepage.obj   \
        $(OUTDIR)\except.obj     \
        $(OUTDIR)\htmlelem.obj   \
        $(OUTDIR)\htmlfilt.obj   \
        $(OUTDIR)\htmlguid.obj   \
        $(OUTDIR)\htmliflt.obj   \
        $(OUTDIR)\htmlscan.obj   \
        $(OUTDIR)\imagetag.obj   \
        $(OUTDIR)\inpstrm.obj    \
        $(OUTDIR)\inputtag.obj   \
        $(OUTDIR)\main.obj       \
        $(OUTDIR)\metatag.obj    \
        $(OUTDIR)\mmbuf.obj      \
        $(OUTDIR)\mmscbuf.obj    \
        $(OUTDIR)\mmstrm.obj     \
        $(OUTDIR)\propspec.obj   \
        $(OUTDIR)\proptag.obj    \
        $(OUTDIR)\regacc32.obj   \
        $(OUTDIR)\register.obj   \
        $(OUTDIR)\scriptag.obj   \
        $(OUTDIR)\serstrm.obj    \
        $(OUTDIR)\start.obj      \
        $(OUTDIR)\textelem.obj   \
        $(OUTDIR)\titletag.obj

.cxx{$(OUTDIR)}.obj:
    $(cc) $(cflags) $(cvarsdll) $(cdebug) -Dtry=try /EHa /GX /GR -DWINNT=1 -DUNICODE -DOFSDBG=0 -DDBG=0 -I. /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

.cxx.pp:
    $(cc) $(cflags) $(cvars) $(cdebug) -Dtry=try /E /Z7 /GX /GR -DWINNT=1 -DUNICODE -DOFSDBG=0 -DDBG=0 -I. $*.cxx > $*.pp

$(OUTDIR)\htmlfilt.dll: $(objs)  $(OUTDIR)\htmlfilt.res
    $(link) $(dlllflags) $(ldebug) -out:$(OUTDIR)\htmlfilt.dll $(objs) /def:htmlfilt.def $(OUTDIR)\htmlfilt.res $(olelibs)

clean:
        $(CLEANUP)
