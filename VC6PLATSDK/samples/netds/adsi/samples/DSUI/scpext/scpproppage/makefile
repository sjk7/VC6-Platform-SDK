Proj= SCPproppage

dll=1
unicode=1
Use_MFC=1

LFLAGS= -def:$(Proj).def

!include <BkOffice.mak>

libs = $(libs) activeds.lib adsiid.lib dsprop.lib

ObjList =  $(ObjDir)\$(Proj).obj    \
           $(ObjDir)\SCP.obj  \
	   $(ObjDir)\SCPProppage.obj  \
           $(ObjDir)\SCPUI.obj     \
           $(ObjDir)\StdAfx.obj	    \
           $(ObjDir)\Util.obj   	     

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 