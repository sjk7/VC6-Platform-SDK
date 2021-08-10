# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.
#
# Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
#
# Abstract: MAKEFILE for GINAHOOK.DLL.
#
# Last revision: August 10, 1999
#

!IF "$(TARGETOS)" == "WINNT"
!include <win32.mak>

proj=GinaHook 

all: $(proj).dll

proj_objs  = $(proj).obj
base_objs  = GinaDlg.obj
extra_libs = NetApi32.lib

.c.obj:
  $(cc) $(cdebug) $(cflags) $(cvarsdll) $*.c

$(proj).dll: $(proj_objs) $(base_objs)
  $(link) $(ldebug) $(dlllflags) $(guilibsdll) $(extra_libs) \
  $** -out:$(proj).dll -def:$(proj).def
!ELSE
!MESSAGE Sorry this sample only builds for the Windows NT Platform
!ENDIF
