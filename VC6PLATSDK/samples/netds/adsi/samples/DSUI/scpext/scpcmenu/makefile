Proj= SCPCMenu

dll=1
unicode=1
Use_MFC=1

LFLAGS= -def:$(Proj).def

!include <BkOffice.mak>

ObjList =  $(ObjDir)\$(Proj).obj    \
           $(ObjDir)\dsmenu.obj     \
           $(ObjDir)\SCPCMenuUI.obj \
           $(ObjDir)\StdAfx.obj		     

all: $(ObjDir)\$(Proj).dll 

$(ObjDir)\$(Proj).dll: $(ObjList) 