!include <disable.mak>

#/*+=========================================================================
#  File:       ALLSAMPS.MAK
#
#  Summary:    Makefile for building all of the COM Tutorial Samples.
#              This file and the accompanying .DSW and .DSP files are
#              intended for use from within Microsoft's Visual
#              Developer Studio. To achieve the equivalent build at
#              the command prompt, see the accompanying MAKEALL.BAT
#              (and also Building section in USING.HTM).
#
#  Builds:     All COM Tutorial Samples in proper order. Registers servers.
#
#  Origin:     3-9-98: atrent - Revised for Platform SDK.
#
#--Usage:-------------------------------------------------------------------
#  Run Visual Developer Studio with following command:
#
#  MSDEV TUTSAMP.DSW
#
#  From within Developer Studio you can build all the samples by
#  choosing the 'Build All' choice on the 'Build' menu.
#
#---------------------------------------------------------------------------
#  This file is part of the Microsoft COM Tutorial Code Samples.
#
#  Copyright (C) 1995-1998 Microsoft Corporation.  All rights reserved.
#
#  This source code is intended only as a supplement to Microsoft
#  Development Tools and/or on-line documentation.  See these other
#  materials for detailed information regarding Microsoft code samples.
#
#  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
#  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
#  PARTICULAR PURPOSE.
#=========================================================================+*/

DIRLIST  =  apputil  \
            readtut  \
            exeskel  \
            dllskel  \
            dlluser  \
            comobj   \
            comuser  \
            register \
            dllserve \
            dllclien \
            licserve \
            licclien \
            marshal  \
            marshal2 \
            locserve \
            locclien \
            aptserve \
            aptclien \
            remclien \
            freserve \
            freclien \
            conserve \
            conclien \
            stoserve \
            stoclien \
            perserve \
            pertext  \
            perdraw  \
            perclien \
            dcdmarsh \
            dcdserve \
            dcomdraw

# The final target.
all: $(DIRLIST)

$(DIRLIST):
        cd $@
        @nmake -a
        cd ..
