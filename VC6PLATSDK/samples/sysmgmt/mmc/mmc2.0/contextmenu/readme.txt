/////////////////////////////////////////////////////////////////////////////
MMC SDK Sample Project:  ContextMenu

Summary:
This project implements IExtendContextMenu for CComponentData.  Context 
menus are added for the different node types which are present in the
scope pane.  This project does not have result items but the implementation
details are the same.

This project requires MMC Version 2.0

/////////////////////////////////////////////////////////////////////////////
//
The NODE_PROPERTIES struct defined in BaseNode.h has been modified.  A new 
member which is a pointer to the object's parent has been added.  A second 
new member which represents the objects attributes has also been added.


/////////////////////////////////////////////////////////////////////////////
//
New Stuff:

- Support for IExtendContextMenu added to CComponentData.

- A simple modeless dialog class has been added.  CBaseDialog for details.

- Differenet icons are used to show the status of a scope node.

- New scope nodes can by dynamically added.

- The "New Device" context menu selection is disabled when the "Add New Device"
  modeless dialog is running.

- CStaticNode node now implements a hidden window for communication with 
  objects running in seperate threads.

