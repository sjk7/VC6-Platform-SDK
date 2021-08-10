#--------------------------------------------------------------
# Do i386 in conventional way
#
!if "$(CPU)" == "i386"
samplename=Help
!include <..\mmcprerelease.mak>
!else

#--------------------------------------------------------------
# Do 64 bit in following way
#
#----- Include the PSDK's WIN32.MAK to pick up defines------------------------------------
!include <disable.mak>
!include <win32.mak>

#----- OUTDIR is defined in WIN32.MAK This is the name of the destination directory-------
all: $(OUTDIR)\Help.Dll

#----- If OUTDIR does not exist, then create directory
$(OUTDIR) :
    if not exist "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

#------ Compile options ---------
CPP=cl.exe
CPP_PROJ=/nologo /W3 /Gm /ZI /GX /Od /D "WIN32" /D "_WIN64" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HELP_EXPORTS" /D "_UNICODE" /D "UNICODE" /FR"$(OUTDIR)\\" /Fp"$(OUTDIR)\Help.pch" /YX /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /c 

.cpp{$(OUTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

#------ Resource compile options ---------
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(OUTDIR)\Help.res"

# Build rule for resource files
SOURCE=.\Help.rc

"$(OUTDIR)\Help.res" : $(SOURCE) "$(OUTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)

#------ Link options ---------
LINK32=link.exe
LINK32_FLAGS=mmc.lib comctl32.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /def:".\Help.Def" /out:"$(OUTDIR)\Help.dll" /implib:"$(OUTDIR)\Help.lib"

DEF_FILE= \
	".\Help.Def"

LINK32_OBJS= \
	"$(OUTDIR)\About.obj" \
	"$(OUTDIR)\AddDeviceDlg.obj" \
	"$(OUTDIR)\AddVFileDlg.obj" \
	"$(OUTDIR)\BaseDialog.obj" \
	"$(OUTDIR)\BaseSnap.obj" \
	"$(OUTDIR)\Comp.obj" \
	"$(OUTDIR)\Compdata.obj" \
	"$(OUTDIR)\Dataobj.obj" \
	"$(OUTDIR)\DeviceNode.obj" \
	"$(OUTDIR)\FolderNode.obj" \
	"$(OUTDIR)\Globals.obj" \
	"$(OUTDIR)\LListImpl.obj" \
	"$(OUTDIR)\Registry.obj" \
	"$(OUTDIR)\StaticNode.obj" \
	"$(OUTDIR)\TraceMacro.obj" \
	"$(OUTDIR)\VirtualFile.obj" \
	"$(OUTDIR)\Help.res"

# Build rule for DLL
$(OUTDIR)\Help.dll: "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
		$(link) $(LINK32_FLAGS) $(LINK32_OBJS)

#--------------------- Clean Rule --------------------------------------------------------
# Rules for cleaning out those old files
clean:
        $(CLEANUP)

!endif
