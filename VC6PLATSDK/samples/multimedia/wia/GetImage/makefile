
!include <win32.mak>

APPVER   = 5.01
TARGETOS = WINNT

PROJECT = GetImage
 
PRECOMP = StdAfx.h

OBJECTS = \
	"$(OUTDIR)\StdAfx.obj"        \
	"$(OUTDIR)\BitmapUtil.obj"    \
	"$(OUTDIR)\BitmapWnd.obj"     \
	"$(OUTDIR)\DataCallback.obj"  \
	"$(OUTDIR)\EventCallback.obj" \
	"$(OUTDIR)\GetImage.obj"      \
	"$(OUTDIR)\GetImage.res"      \
	"$(OUTDIR)\MainWnd.obj"       \
	"$(OUTDIR)\ProgressDlg.obj"   \
	"$(OUTDIR)\WiaWrap.obj"       \

LIBS = \
	gdi32.lib    \
	user32.lib   \
	ole32.lib    \
	oleaut32.lib \
	uuid.lib     \
	wiaguid.lib  \
	comctl32.lib \
	comdlg32.lib \
	shell32.lib  \
	gdiplus.lib  \

all: $(OUTDIR)\$(PROJECT).exe

clean:
	$(CLEANUP)

"$(OUTDIR)":
	if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.rc{$(OUTDIR)\}.res:
	@$(rc) $(rcflags) $(rcvars) /fo $@ $<

.cpp{$(OUTDIR)\}.obj:
	@$(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Fp"$(OUTDIR)\$(PROJECT).pch" /Yu"$(PRECOMP)" $<

"$(OUTDIR)\$(PRECOMP:.h=.obj)":
	@$(cc) $(cdebug) $(cflags) $(cvarsdll) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Fp"$(OUTDIR)\$(PROJECT).pch" /Yc"$(PRECOMP)" $?

"$(OUTDIR)\$(PROJECT).exe": "$(OUTDIR)" $(OBJECTS)
	@$(link) $(ldebug) $(guilflags) $(guilibsdll) -out:"$(OUTDIR)\$(PROJECT).exe" $(OBJECTS) $(LIBS)
