Platform SDK Sample: ViewDIB

SUMMARY
=======

The ViewDIB sample demonstrates how to:

  - Load, display, save, and print DIBs using DIB sections
  - Create DIB sections with specific surface attributes
  - Convert between different pixel formats
  - Store and retrieve DIBs to/from the clipboard
  - Retrieve surface information for a DIB section
  - Retrieve color information for a DIB section

MORE INFORMATION
================

The main application window contains provides the following menu options:

File->Open  -- Browse for and load a BMP file
File->Print -- Select a printer and print the DIB that is currently loaded
File->Exit  -- Exit the program

Edit->Copy  -- Copy the currently loaded DIB to the clipboard 
Edit->Paste -- past the image currently on the clipboard into ViewDIB
Edit->Display Image Attributes -- Display the surface attributes of the
               currently loaded DIB
Edit->Color Depth -- Convert the current DIB to another color depth

Help->About -- Displays an "About Box"


NOTES
=====

  The code in the DIBSectn.C module contains the majority of the 
  routines that carry out the work for this sample.  The functions are
  written to be as reusable as possible.  if you use this code you 
  should be aware that:
   
  - Most of the functions in this module that are passed an HBITMAP
    as a parameter assume the HBITMAP is not selected into a device
    context at the time of the call. Since the underlying APIs usually
    require this, so do these functions.

  - Throughout this module, code is in place to handle color tables
    in DIBSections (in the BITMAPINFO) even when it is not necessary.
    This helps the re-usability of the code, since it is often desirable
    to include a "suggested" color table when storing 16bpp or higher
    BMP files.