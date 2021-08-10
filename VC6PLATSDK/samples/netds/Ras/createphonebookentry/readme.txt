RasEntry

RasEntry is a Visual Basic 6.0 application that allows you to create or delete phone book entries (Dial Up Networking Connectoids).

FILES
=====

The RasEntry application uses the following files

File           		Description

README.TXT     		Readme file for RasEntry application
RASENTRY.VBP   		VB 6.0 project file
RASENTRY.FRM   		RasEntry form file
RASENTRY.BAS   		Module containing functions and structure for creating and deleting the phone book entry.
RASENUMDEVICES.BAS	Module containing function and structure for enumerating the RAS capable devices on the system.
RASENUMENTRIES.BAS	Module containing function and structure for enumerating the RAS Entries.
RASGETCOUNTRYINFO.BAS	Module containing function and structure for obtaining country codes and IDs.
COMMON.BAS		Module containing function and structure for allocating and freeing memory, copying strings, etc.


RAS API's USED
==============

RASSETENTRYPROPERTIES
RASENUMDEVICES
RASENUMENTRIES
RASGETCOUNTRYINFO
RASVALIDATEENTRYNAME
RASDELETEENTRY

----------------------------------------------------
RUNNING THE APPLICATION ON WINDOWS NT AND WINDOWS 9x
----------------------------------------------------

To run the application load the project in VB 6.0 and run it. For Windows 95 (pre OSR 2.0) you will need to download the latest DUN upgrade package from www.microsoft.com