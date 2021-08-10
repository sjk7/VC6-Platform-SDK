# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1997-1999.  Microsoft Corporation.  All rights reserved
#

# Nmake macros for building Win32 applications
!IF "$(TARGETOS)" == "WINNT"

!Include <Win32.Mak>

# Inference Rules
.C.Obj:
    $(cc) $(cdebug) $(cflags) $(cvars) $*.C
.Obj.Exe:
    $(link) $(ldebug) $(conlflags) -out:$*.Exe $**\
      advapi32.lib user32.lib winspool.lib netapi32.lib $(conlibs)

# Macro Defines
PROJ1=Check_SD
PROJ2=Helper
PROJ3=SD
PROJ4=SecObjects

# Target List
All: $(PROJ1).Exe

# Source Objects
$(PROJ1).obj: $(PROJ1).c
$(PROJ2).obj: $(PROJ2).c
$(PROJ3).obj: $(PROJ3).c
$(PROJ4).obj: $(PROJ4).c

# Executables
$(PROJ1).exe: $(PROJ1).obj $(PROJ2).obj $(PROJ3).obj $(PROJ4).obj

# Clean Up Everything
CleanAll: clean
    del *.Exe

# Clean Up Everything Except .Exe Files
Clean:
    del *.Obj
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
