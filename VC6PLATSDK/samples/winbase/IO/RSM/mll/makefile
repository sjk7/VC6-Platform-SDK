#=--------------------------------------------------------------------------=
# Copyright 1995 - 1999 Microsoft Corporation.  All Rights Reserved.
#
# THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
# ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
# PARTICULAR PURPOSE.
#=--------------------------------------------------------------------------=

Proj= STL_mll

libs=$(libs) -def:$(Proj).Def

dll=1

ObjList =  $(ObjDir)\$(Proj).Obj \
           $(ObjDir)\DllMain.Obj   
          
!include <BkOffice.Mak>

all: $(ObjDir)\$(Proj).Dll

$(ObjDir)\$(Proj).dll: $(ObjList) 
