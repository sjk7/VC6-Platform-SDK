# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-2002.  Microsoft Corporation.  All rights reserved.
#

!include <Win32.Mak>

all: RSACert.exe

clean:
  del *.obj *.pdb *.exe

.cpp.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.cpp

RSACert.exe: RSACert.obj
  $(link) $(ldebug) $(conlflags) -out:$*.exe $** $(conlibsdll) advapi32.lib crypt32.lib
