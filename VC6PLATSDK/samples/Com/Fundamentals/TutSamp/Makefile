DIRS = \
    apputil\~   \
    register\~   \
    marshal\~   \
    marshal2\~   \
    aptclien\~   \
    aptserve\~   \
    comobj\~   \
    comuser\~   \
    conclien\~   \
    conserve\~   \
    dcdmarsh\~   \
    dcdserve\~   \
    dcomdraw\~   \
    dllclien\~   \
    dllserve\~   \
    dllskel\~   \
    dlluser\~   \
    exeskel\~   \
    freclien\~   \
    freserve\~   \
    licclien\~   \
    licserve\~   \
    locclien\~   \
    locserve\~   \
    perclien\~   \
    perdraw\~   \
    perserve\~   \
    pertext\~   \
    readtut\~   \
    remclien\~   \
    stoclien\~   \
    stoserve\~   \
    

SDKPROJ =COM\Fundamentals\tutsamp


#
# This is a Platform SDK non-leaf-node .  It is used to allow NMAKE, 
#  or a similar tool, to recursively build all of the samples in a directory 
#  tree.  To add or remove a directory from the build process, modify the 
#  DIRS list above.  
#
# The SDKPROJ macro (above) is defined solely for the purpose of echoing
#  the current directory location to the screen.  
#
# Do not modify this  except for the DIRS and SDKPROJ macros above.
#

#
# Include sdkpropbld.mak in order to get standard build options, environment
#  variables, and macros.  The sdkpropbld.mak file is installed with the SDK 
#  in the include directory.
# 

!include <sdkpropbld.mak>

# 
# In order to build "all," process each of the entries in the DIRS list.
#

all: $(DIRS)


#
# In order to build each of the entries in the DIRS list, change dir into the
#  directory in question, echo the current location, run nmake recursively, 
#  and change dir back to the original directory level.  This four step process 
#  is encapsulated in sdkbld.mak which is installed with the SDK in the include
#  directory.
#

$(DIRS):
!include <sdkbld.mak>
