Sample Shell Extension SHELLEXT

Copyright 1993 - 1999 Microsoft Corporation.  All Rights Reserved.

The SHELLEXT sample demonstrates how to implement the basic shell
extensions. These include context menu, property sheet, icon handler,
and copy hook extensions. This sample does not implement a drag-drop
handler, but the implementation would be very similar to context menu
handlers.

All shell extensions are implemented as OLE COM InProc servers. All
shell extensions are limited to the Apartment threading model.

The context menu extension will add four items to the context menu that
is displayed when a file with the .GAK extension is right-clicked in
Explorer. This is done by implementing the IShellExtInit amd
IContextMenu interfaces.

The property sheet extension will add a page to the property sheet that
is displayed for a file with the .GAK extension. This page allows the
user to select the color of the icon that is displayed for the file in
Explorer. This extension implements the IShellExtInit and
IShellPropSheetExt interfaces.

The icon handler allows the extension to determine what icon is
displayed by Explorer for the file based on the properties of the file.
The icon displayed is selected from the file's property sheet extension.
The icon handler is implemented with the IPersistFile and IExtractIcon
interfaces.

The copy hook extension will display a message box whenever a folder or
printer object is moved, copied renamed or deleted. This extension is
implemented with the ICopyHook interface.

To register the extension, double-click the SHELLEXT.REG file from
Explorer. The REG file assumes that SHELLEXT.DLL is in the System
directory. To change the location of the DLL, manually change the value
under: 

HKEY_CLASSES_ROOT
   CLSID
      {87b9bd00-c65c-11cd-a259-00dd010e8c28}
         InProcServer32
