TARGETOS=BOTH
!include <win32.mak>

objs_ws1=$(OUTDIR)\mcastws1.obj

objs_ws2=$(OUTDIR)\mcastws2.obj

common_objs=$(OUTDIR)\resolve.obj

all: $(OUTDIR) $(OUTDIR)\mcastws1.exe $(OUTDIR)\mcastws2.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

# Update the resource if necessary

# Update the object file if necessary

.c{$(OUTDIR)}.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" $**

# Update the executable file if necessary, and if so, add the resource back in.

$(OUTDIR)\mcastws1.exe: $(objs_ws1) $(common_objs) 
    $(link) $(linkdebug) $(conlflags) -out:$(OUTDIR)\mcastws1.exe $(objs_ws1) $(common_objs) oldnames.lib kernel32.lib wsock32.lib

$(OUTDIR)\mcastws2.exe: $(objs_ws2) $(common_objs) 
    $(link) $(linkdebug) $(conlflags) -out:$(OUTDIR)\mcastws2.exe $(objs_ws2) $(common_objs) $(conlibsmt) ws2_32.lib


#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
