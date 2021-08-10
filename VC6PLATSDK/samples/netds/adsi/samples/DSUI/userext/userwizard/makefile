Proj= userwizard

dll=1
unicode=1
Use_MFC=1

LFLAGS= -def:$(Proj).def

!include <BkOffice.mak>

libs = $(libs) activeds.lib adsiid.lib dsprop.lib

ObjList =  $(ObjDir)\$(Proj).obj    \
           $(ObjDir)\userwizard.obj  \
	   $(ObjDir)\extpageuser.obj \
           $(ObjDir)\wizext.obj     \
           $(ObjDir)\StdAfx.obj	    \
           $(ObjDir)\Util.obj   	     

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 