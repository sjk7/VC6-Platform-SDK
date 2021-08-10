/////////////////////////////////////////////////////////////////////////////
MMC SDK Sample Project:  MultiSelect-ToolBar

Summary:
This project implements IExtendToolBar.  ToolBars are added for the
different node types.
Multiselect is also implemented for result pane items.  
The code in IComponent::ControlbarNotify demonstrates how to handle the
MMC Composite Data Object which is recieved when both Toolbars and Multi-
Select are implemented.


/////////////////////////////////////////////////////////////////////////////
//
Notes:  
1.) IExtendControlBar is only queried from IComponent.  It cannot be added
    to IComponentData.

2.) A custom clipboard format ("CCF_MULTISELECT_COOKIES") is used to support
    multiselect along with the MMC SMMCDataObject.  Most of the code to make
    this feature work is in:
    - CDataObject::RetrieveMultiSelectCookies()
    - CComponent::QueryMultiSelDataObject()
    - CComponent::ControlbarNotify()

/////////////////////////////////////////////////////////////////////////////
//

Implementing Toolbars
- Support for IExtendControlbar added to CComponent.
  * QueryInterface in CComponent supports IExtendControlbar
  * Add IExtendControlbar to CComponent's list of derived interfaces
  * Add prototypes of IExtendControlbar's methods to Comp.h
  * Add skeleton implementations to Comp.cpp
  * Add member variables for IControlbar and IToolbar pointers
  * Initialize Toolbar pointers in CComponent's constructor

- Add an include statement for CommCtrl.h to Globals.h for button styles

- Add support for IControlbar to CComponent::GetInterface()
  * Define REQUEST_ICONTROLBAR in Globals.h
  * Add switch statement to CComponent::GetInterface()

- Add support for any IToolbar pointers to CComponent::GetInterface()
  * Define REQUEST_ISTATICTOOLBAR in Globals.h
  * Add switch statement to CComponent::GetInterface()

- Add virtual ControlbarNotify handler to CBaseNode

- Implement ControlbarNotitify handlers in derived nodes
  * Return E_NOTIMPL from nodes which don't have toolbars.
  * Implement the method in nodes which have toolbars.  CStaticNode
    in this sample.

- Implement CComponent::ControlBarNotify 
  * Handle MMCN_SELECT by delegating to the derived node class's
    ControlbarNotify method.
  * Handle MMCN_BTN_CLICK by delegating to the derived node class's
    Command method (part of IExtendContextMenu)

