# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#

!include <Win32.Mak>

# Inference Rules
.c.Obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $*.C
.obj.exe:
    $(link) $(ldebug) $(conlflags) -out:$*.exe $** \
      $(conlibs) advapi32.lib user32.Lib

# Macro Defines
PROJ1=client
PROJ2=server

# Target List
All: $(PROJ1).exe $(PROJ2).exe

# Source Objects
$(PROJ1).obj: $(PROJ1).c
$(PROJ2).obj: $(PROJ2).c

# Executables
$(PROJ1).exe: $(PROJ1).obj
$(PROJ2).exe: $(PROJ2).obj

# Clean Up Everything
CleanAll: clean
    del *.Exe

# Clean Up Everything Except .exe Files
Clean:
    del *.obj
