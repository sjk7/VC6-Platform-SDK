# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1993-1999.  Microsoft Corporation.  All rights reserved.
#
# Nmake macros for building Windows 32-Bit apps
#

!include <Win32.Mak>

all: monkey.exe

# Update the resource if necessary

monkey.res: monkey.rc monkey.h
    rc $(rcflags) $(rcvars) -r -fo monkey.res monkey.rc

# Update the object file if necessary

monkey.obj: monkey.c monkey.h
    $(cc) $(cdebug) $(cflags) $(cvars) monkey.c

# Update the executable file if necessary, and if so, add the resource back in.

monkey.exe: monkey.obj monkey.res
    $(link) $(ldebug) $(guilflags) -out:monkey.exe monkey.obj monkey.res $(guilibs) advapi32.lib
