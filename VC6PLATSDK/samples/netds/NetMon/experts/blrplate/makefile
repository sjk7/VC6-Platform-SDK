##############################################################################
#   MODULE: BLRPLATE.dll
#
#   Modification History
#
#   Your Name Here      01/01/70    Created
##############################################################################

!IF ("$(CPU)" == "i386") && "$(TARGETOS)" == "WINNT"
!include <win32.mak>
!if "$(CPU)" == "i386"
CVTRESCPU=IX86
!else
CVTRESCPU=$(CPU)
!endif

MODULE = BLRPLATE

all: $(OUTDIR) $(OUTDIR)\$(MODULE).dll

$(OUTDIR):
     if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

BLRPLATE_LIBS   = $(winlibs) nmapi.lib npptools.lib dprintf.lib
BLRPLATE_LFLAGS = $(lflags) $(ldebug) -dll 


##############################################################################
#   Object list
##############################################################################

OBJS = $(OUTDIR)\BLRPLATE.obj  \
       $(OUTDIR)\config.obj    \
       $(OUTDIR)\$(MODULE).rbj \


##############################################################################
#   Inference rules.
##############################################################################

.c{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

.cpp{$(OUTDIR)}.obj:
     $(cc) $(cflags) $(cdebug) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**


##############################################################################
# Update the resources if necessary
##############################################################################

$(OUTDIR)\$(MODULE).res: $(MODULE).rc resrc1.h
     $(rc) $(rcflags) $(rcvars) /Fo$(OUTDIR)\$(MODULE).res $(MODULE).rc

$(OUTDIR)\$(MODULE).rbj: $(OUTDIR)\$(MODULE).res
    cvtres -MACHINE:$(CVTRESCPU) -OUT:$(OUTDIR)\$(MODULE).rbj $(OUTDIR)\$(MODULE).res 


##############################################################################
#   Update the dll.
##############################################################################

$(OUTDIR)\$(MODULE).dll: $(OBJS) $(MODULE).def
     $(link) $(BLRPLATE_LFLAGS) $(BLRPLATE_LIBS) $(OBJS) /MACHINE:$(CPU) /PDB:$(OUTDIR)\$(PROJ).pdb -out:$(OUTDIR)\$(MODULE).dll 


##############################################################################
#   Clean build
##############################################################################

clean:
        $(CLEANUP)
!ELSE
!MESSAGE Sorry this sample only builds for 32-bit Windows NT Platform
!ENDIF
