
!IF ("$(CPU)" == "i386")

Proj= Hello

libs= oleaut32.lib 

!include <BkOffice.mak>

ObjList =  $(ObjDir)\$(Proj).obj  

$(ObjDir)\$(Proj).exe: $(ObjList)        

all: $(ObjDir)\$(Proj).exe 

!ELSE
!MESSAGE Sorry this sample is not intended for 64-bit Windows platforms
!ENDIF
