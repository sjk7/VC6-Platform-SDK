Demonstrate Halftone Capabilities


The Halftone sample allows you to load and display bitmaps while allowing
you to dynamically changing the color filters that are applied.

The core functions used are:
                                                              
   GetColorAdjustment
   SetColorAdjustment -- Retrieve/set the current color adjustment filters

   CreateHalftonePalette -- to create a halftone palette to work with

   SetStretchBltMode -- to force the output to the DC to use halftoning


Usage
------

To use the sample after building it with NMAKE, run Halftone.EXE.  This will
bring up the main window.  From here, you can choose, from the file menu, to 
load a bitmap.  Once the bitmap is loaded, you can adjust the color filters
dynamically using the dialog under the Halftone->Properties menu.


Notes
-----

Halftone support is only available on Windows NT/2000.  On Windows 95/98, 
the HALFTONE stretch mode will be treated like COLORONCOLOR.

On Windows NT 4.0 (and earlier), the COLORADJUSTMENT filters are not applied
when the video mode of the target display contect is set to 24 bits-per-pel
or higher.

This sample uses LoadImage() to load bitmap files.  LoadImage only supports 
loading bitmaps from *.BMP files on Windows 95, Windows, 98, Windows 2000, 
and Windows NT 4.0.
