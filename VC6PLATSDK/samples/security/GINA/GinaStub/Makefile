# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#

!IF "$(TARGETOS)" == "WINNT"
!include <win32.mak>

proj=ginastub

all: $(proj).dll

$(proj).obj: $(proj).c
  $(cc) $(cdebug) $(cflags) $*.c

$(proj).lib: $(proj).obj $(proj).def
  $(implib) -machine:$(CPU) -def:$(proj).def -out:$(proj).lib

$(proj).dll: $(proj).obj
  $(link) $(ldebug) $(dlllflags) $(guilibsdll) \
  $** -out:$(proj).dll -def:$(proj).def
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
