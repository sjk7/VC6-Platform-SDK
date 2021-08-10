SCardAPI illustrates how to use the Smart Card SDK Win32 APIs from Visual Basic
to interact with the Smart Card Resource Manager,

Files included in this sample
=============================

1) ReadMe.txt   - This file
2) scrdvb.frm   - Main program
3) scrdvb.vbp   - Visual Basic Project file
4) scrdvb.frx   - Visual Basic Project report file
5) scardapi.bas - prototypes matching winscard.h
6) scarderr.bas - prototypes matching scarderr.h

Smart Card SDK Win32 APIs used in this sample
=============================================
SCardAddReaderToGroup
SCardBeginTransaction
SCardCancel
SCardConnect
SCardControl
SCardDisconnect
SCardEndTransaction
SCardEstablishContext
SCardForgetCardType
SCardForgetReader
SCardGetAttrib
SCardGetCardTypeProviderName
SCardGetProviderId
SCardGetStatusChange
SCardIntroduceCardType
SCardIntroduceReader
SCardIntroduceReaderGroup
SCardListCards
SCardListInterfaces
SCardListReaderGroups
SCardListReaders
SCardLocateCards
SCardReconnect
SCardReleaseContext
SCardRemoveReaderFromGroup
SCardSetAttrib
SCardSetCardTypeProviderName
SCardStatus
SCardTransmit

How to compile
==============

Visual Basic 6.0 or greater is required to build the projects.  You must
install the ActiveX Controls as part of your Visual Basic installation.

The following steps must be successfully completed in sequence:

    1) Open the .vbp project
    2) Build the project
    3) Save the project


