# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-2002.  Microsoft Corporation.  All rights reserved.
#

!include <Win32.Mak>

all: SessionKey.exe

clean:
  del *.obj *.pdb *.exe

.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

SessionKey.exe: SessionKey.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(conlibsdll) advapi32.lib
