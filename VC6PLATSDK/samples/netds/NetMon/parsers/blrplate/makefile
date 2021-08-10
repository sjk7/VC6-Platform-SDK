##############################################################################
#   MODULE: BLRPLATE.dll
#
#   Modification History
#
#   Your Name Here      01/01/70    Created
##############################################################################

!IF "$(TARGETOS)" == "WINNT" && "$(CPU)" == "i386"
!include <win32.mak>

MODULE = BLRPLATE

all: $(MODULE).dll

BLRPLATE_LIBS   = $(winlibs) msvcrt.lib nmapi.lib bhsupp.lib parser.lib
BLRPLATE_LFLAGS = $(lflags) $(ldebug) -debug:full -debugtype:both -machine:$(CPU) -dll 


##############################################################################
#   Object list
##############################################################################

OBJS   = BLRPLATE.obj


##############################################################################
#   Inference rules.
##############################################################################

.c.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

.cpp.obj:
    $(cc) $(cdebug) $(cflags) $(cvarsmt) -GX $*.cpp


##############################################################################
#   Update the object files if necessary
##############################################################################

BLRPLATE.obj : BLRPLATE.h BLRPLATE.c


##############################################################################
#   Update the dll.
##############################################################################

$(MODULE).dll: $(OBJS) $*.def 
    $(link) $(BLRPLATE_LFLAGS) $(BLRPLATE_LIBS) $(OBJS) \
            -out:$*.dll -map:$*.map -def:$*.def 

##############################################################################
#   Clean build
##############################################################################

clean:
    -del *.dll
    -del *.obj
    -del *.lib
    -del *.exp
    -del *.map
    -del *.sym
    -del *.pdb
    -del *.exp
    -del *.res
    -del *.rbj
    -del *.aps
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT (x86) Platform
!ENDIF
