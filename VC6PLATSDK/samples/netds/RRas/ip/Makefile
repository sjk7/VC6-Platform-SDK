APPVER          = 5.0
!include <win32.mak>

cflags          = $(cflags) /Gz
cvarsdll        = -DNT -DMPR50
LIBS            = rtm.lib rtutils.lib

all:            $(OUTDIR) $(OUTDIR)\ipsample.dll

$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)


OBJS            =                               \
    $(OUTDIR)\hashtable.obj                               \
    $(OUTDIR)\sync.obj                                    \
    $(OUTDIR)\utils.obj                                   \
    $(OUTDIR)\packet.obj                                  \
    $(OUTDIR)\socket.obj                                  \
    $(OUTDIR)\networkentry.obj                            \
    $(OUTDIR)\networkmgr.obj                              \
    $(OUTDIR)\configentry.obj                             \
    $(OUTDIR)\configmgr.obj                               \
    $(OUTDIR)\mibmgr.obj                                  \
    $(OUTDIR)\rtmapi.obj                                  \
    $(OUTDIR)\rmapi.obj                                   \
    $(OUTDIR)\test.obj                                    \
    $(OUTDIR)\ipsample.obj

# Build rule for converting c files to obj files
.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update messages
msg00001.bin ipsamplemsg.rc ipsamplemsg.h : ipsamplemsg.mc
    mc -v ipsamplemsg.mc

ipsample.rc:    msg00001.bin ipsamplemsg.rc

# Update the resources if necessary
$(OUTDIR)\ipsample.res: ipsample.rc
    $(rc) $(rcflags) $(rcvars) /i $(OUTDIR) /fo $(OUTDIR)\ipsample.res ipsample.rc

# Update the executable file
$(OUTDIR)\ipsample.dll: $(OUTDIR)\ipsample.res $(OBJS)
    $(link) $(linkdebug) $(dlllflags) $(conlibsdll) -machine:$(CPU) $(LIBS) \
    -def:ipsample.def -out:$*.dll $** 

clean:
    $(CLEANUP)
    del *.pdb *.pch *.obj *.dll *.lib *.exp \
        *.res *.bin ipsamplemsg.rc ipsamplemsg.h
