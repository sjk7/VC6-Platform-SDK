Proj= SCPWizard

dll=1
unicode=1
Use_MFC=1

LFLAGS= -def:$(Proj).def

!include <BkOffice.mak>

ObjList =  $(ObjDir)\$(Proj).obj    \
           $(ObjDir)\SCPPageUi.obj  \
           $(ObjDir)\SCPWiz.obj     \
           $(ObjDir)\StdAfx.obj	    \
           $(ObjDir)\Util.obj   	     

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 