/////////////////////////////////////////////////////////////////////////////
MMC SDK Sample Project:  View Extensions

This project requires MMC 2.0

Summary:
This project implements View Extensions.  

Keyword:  VIEWEX

/////////////////////////////////////////////////////////////////////////////
//  Steps used to implement View Extensions

*  In BaseSnap.cpp change DllRegisterServer.  The last parameter in the call
   to RegisterSnapin must be set to TRUE.   

*  Add the SetNodeTypesKey method to REGISTRY.CPP to add the GUID for the
   node which will be extended.  CFolderNode in this example

*  Add the SetExtensionKey method to REGISTRY.CPP.  This method adds MMC's
   view extension object to the NodeTypes key so it will extend us.

*  Make the changes to RegisterSnapin in REGISTRY.CPP to call the methods
   which configure the registry keys to support the view extension.

*  Add support for INodeProperties to IComponentData or IComponent.
   CComponentData/CComponent will be derived from INodeProperties so a
   QueryInterface must be added as well as the GetProperty method.

*  Implement INodeProperties::GetProperty() to support CCF_DESCRIPTION 
   and CCF_HTML_DETAILS.  The virtual method should be added to CBaseNode
   and implemented in the dervived node classes.


/////////////////////////////////////////////////////////////////////////////
// Points of interest

*  All that is required to get MMC's default view extension to show up as 
   the default view for the extended node, is to set the registry entries
   correctly.  It is not necessary to make any changes to GetResultViewType2.


