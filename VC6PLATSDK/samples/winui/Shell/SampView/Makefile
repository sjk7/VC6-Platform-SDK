Proj = SampView

# These are "extra" libs beyond the standard set that inetsdk.mak will
#  append to the libs set

libs=shell32.lib comctl32.lib shlwapi.lib

# pull in the master SDK makefile that defines all of the macros
#  and all of the build rules

!include <win32.mak>

all: $(OUTDIR) $(OUTDIR)\$(Proj).dll

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# itemize all of the required Object files

Objs =   $(OUTDIR)\ClsFact.obj \
         $(OUTDIR)\ContMenu.obj \
         $(OUTDIR)\DataObj.obj \
         $(OUTDIR)\DropSrc.obj \
         $(OUTDIR)\DropTgt.obj \
         $(OUTDIR)\EnumIdl.obj \
         $(OUTDIR)\ExtrIcon.obj \
         $(OUTDIR)\PidlMgr.obj \
         $(OUTDIR)\SampView.obj \
         $(OUTDIR)\SampView.res \
         $(OUTDIR)\ShlFldr.obj \
         $(OUTDIR)\ShlView.obj \
         $(OUTDIR)\Utility.obj \
         $(OUTDIR)\ViewList.obj

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


$(OUTDIR)\$(Proj).res:   
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\$(Proj).res $(Proj).rc


$(OUTDIR)\$(Proj).dll: $(Objs) $(OUTDIR)\$(Proj).res
    $(link) $(ldebug) $(dllllflags) \
    $(Objs) $(dlllibs) $(olelibs) \
    -out:$(OUTDIR)\$(Proj).dll $(libs) \
    -def:sampview.def


clean:
        $(CLEANUP)
