#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!if "$(CPU)" == "IA64"
!message Sorry, building this sample for the 64bit Windows Platform is not currently supported
!else
!include <win32.mak>

LINK32_OBJS = $(OUTDIR)\ui.obj \
              $(OUTDIR)\session.obj \
              $(OUTDIR)\applet.obj \
              $(OUTDIR)\conf.obj \
              $(OUTDIR)\res.res 


#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR) $(OUTDIR)\nmchat2.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\Nmchat2.exe:  $(OUTDIR) $(OUTDIR)\iapplet.h $(OUTDIR)\imsconf2.h $(LINK32_OBJS) $(OUTDIR)\res.res
    $(link) $(ldebug) $(guilflags) /PDB:$(OUTDIR)\program.pdb -out:$(OUTDIR)\nmchat2.exe $(LINK32_OBJS) $(olelibs) shell32.lib comctl32.lib

$(OUTDIR)\iapplet.h $(OUTDIR)\iapplet.c:
	midl /client none /server none /ms_ext /W1 /c_ext /Oicf /out $(OUTDIR) /iid iapplet.c iapplet.idl

$(OUTDIR)\imsconf2.h $(OUTDIR)\imsconf2.c:
	midl /client none /server none /ms_ext /W1 /c_ext /Oicf /out $(OUTDIR) /iid imsconf2.c imsconf2.idl

.cpp{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /I$(OUTDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

$(OUTDIR)\res.res: res.rc
    $(rc) $(rcflags) $(rcvars) /fo $(OUTDIR)\res.res res.rc

# Rules for cleaning out those old files
clean:
        $(CLEANUP)

!endif
