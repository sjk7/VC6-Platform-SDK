SCIntro illustrates how to use SCard functions to query and introduce various
smart card components to the smart card database.

It also illustrates how to properly make use of the SCARD_AUTOALLOCATE feature
and SCardFreeMemory function.

Files included in this sample
=============================

1) ReadMe.txt   - This file
2) SCIntro.cpp  - Main program
3) MAKEFILE     - Makefile for NMAKE utility

SCard functions used in this sample
===================================

- SCardEstablishContext
- SCardListReaderGroups
- SCardIntroduceReaderGroup
- SCardListReaders
- SCardAddReaderToGroup
- SCardListCards
- SCardGetStatusChange
- SCardIntroduceCardType
- SCardFreeMemory
- SCardListReaders
- SCardReleaseContext

How to compile
==============

1) Make sure all smart card hardware and software components have been setup
   correctly per %MSSDK%\Samples\Winbase\SCard\ReadMe.txt.
2) From the SCIntro directory, run NMAKE to make SCIntro.exe.

See %MSSDK%\samples\winbase\scard\ReadMe.txt for more information about
running the SmartCard samples in general.

