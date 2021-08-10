# Nmake compatible makefile
# for building under the Visual Studio/Microsoft Platform SDK environment

!include <Win32.Mak>

#
# libs/include appropriate for Bluetooth SDK structure
# btsdk
#       samples
#       lib
#       inc
#
libs = irprops.lib $(conlibs) ws2_32.lib
INCLUDE=..\..\inc;$(INCLUDE)

all: $(OUTDIR) $(OUTDIR)\bthcxn.exe

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\bthcxn.obj: bthcxn.cpp
    $(cc) $(cflags) $(cvars) /WX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" bthcxn.cpp

$(OUTDIR)\bthcxn.exe: $(OUTDIR)\bthcxn.obj
    $(link) $(conflags) -out:$(OUTDIR)\bthcxn.exe $(OUTDIR)\bthcxn.obj $(libs)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)
