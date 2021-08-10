Dynamic Dialog Box Creation


SUMMARY
=======

The DYNDLG sample shows how to create the dialog box template at run time. 
Usually, an application defines a dialog box template in an RC or DLG file, 
then creates a dialog box at run time from the template. However, it is 
possible to create the dialog box template at run time. 


MORE INFORMATION
================

The Win32 dialog box template is conceptually similar to the Windows 3.1 
version, but is different enough to require some porting work. For example, 
strings are now stored in Unicode. The dialog box template format is 
documented in the help file included with the dialog box editor.

Run-time dependency:

One of the dialog boxes uses a custom control which is expected to be 
defined in the spincube.dll file. The DYNDLG sample tries to load this DLL 
at run time from the current directory. Note that this poses a potential
security breach. For more information - see the notes in DynDlg.c 

This path can be easily changed, and the sample recompiled. SPINCUBE is 
another sample distributed in the Platform SDK.

