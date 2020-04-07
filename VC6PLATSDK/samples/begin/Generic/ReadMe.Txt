Generic Win32-based Application


The GENERIC sample is a generic Win32-based application with a menu and an
About box, but without any real functionality. The sample demonstrates the
basic steps that are used to create the application.

The files included in this sample are:

GENERIC.C - The .C source file
GENERIC.H - The .H file for the sample
RESOURCE.H - The .H file created by VC++ 2.0
GENERIC.DEF - The definition file
GENERIC.RC - Contains resource information such as menus and dialog boxes
GENERIC.HPJ - The Help file source
GENERIC.CNT - The contents list for the Help file
GENERIC.RTF -  A rich text format file used for Help
GENERIC.MAK - A Microsoft Visual C++ 2.0 make file
MAKEFILE - A command line make file
MAKEHELP.BAT - A batch file that makes the Help file
GENERIC.ICO - The icon for the GENERIC sample
SMALL.ICO - The small-icon for the GENERIC sample
GENERIC.BMP - A bitmap for the GENERIC sample
HELP.BMP - A bitmap for the Help file

Special Note for 64-bit Build Environments:

This sample builds a binary sample and an associated help file. In some 64-bit 
environments, NMAKE is unable to find the help compiler to build the help file 
and will fail. As a result, help-related functions in this sample will be unable 
to find the help file. To resolve this problem, build the sample in a 32-bit 
environment and then copy the help file to the output directory of the 64-bit 
build environment. Alternatively, add the path of the HCRTF.EXE tool (located 
in the installed Visual Studio distribution) to the "PATH" environment variable.