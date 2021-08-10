# ============================================================================
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1995-1999.  Microsoft Corporation.  All rights reserved.
# ============================================================================
#
# Usage:    NMAKE DEBUG=1   (build DEBUG exe)
#           NMAKE NODEBUG=1 (build RELEASE exe)
#
# ============================================================================

!include <Win32.Mak>

APP       = HTTPAUTH

CPP          = $(cc)
CPPFLAGS     = $(cflags) $(cvars) $(cdebug)
LINKFLAGS    = $(ldebug) $(conlflags)
APP_OBJS     = httpget.obj httpauth.obj get_sock.obj

# ----------------------------------------------------------------------------
#                          O V E R A L L    G O A L
# ----------------------------------------------------------------------------

goal: $(APP).exe



# ----------------------------------------------------------------------------
#                      L I N K / R E S   C O M M A N D S
# ----------------------------------------------------------------------------

$(APP).exe: $(APP_OBJS)
    @echo Linking ...
     $(link) $(LINKFLAGS) $(APP_OBJS) $(conlibs) -out:$@

# ----------------------------------------------------------------------------
#                           B U I L D   R U L E S
# ----------------------------------------------------------------------------

{$(SRC_DIR)}.c{}.obj:
    @echo Compiling $<...
    $(CPP) $(CPPFLAGS) /c $<


# ----------------------------------------------------------------------------
#                       D E P E N D E N C Y   R U L E S
# ----------------------------------------------------------------------------

httpget.obj: httpget.c proto.h

get_sock.obj: get_sock.c proto.h httpauth.h

httpauth.obj: httpauth.c httpauth.h
