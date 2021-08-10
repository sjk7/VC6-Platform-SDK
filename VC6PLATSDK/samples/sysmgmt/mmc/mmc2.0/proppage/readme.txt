/////////////////////////////////////////////////////////////////////////////
MMC SDK Sample Project:  Property Pages

Summary:
This project implements Property Pages.  

This project requires MMC 2.0

/////////////////////////////////////////////////////////////////////////////
//  Steps used to implement Property Pages

*  Add support for IExtendPropertySheet2 in IComponent::QueryInterface
*  Add IExtendPropertySheet2 interface and methods to Comp.h/cpp
*  Add a callback WndProc to the node class (CVirtualFile)
*  Create a dialog template with 'Child' style and Thin border
*  Add comctl32.lib to Project Settings > Link > Object/Library modules
*  Implement the IExtendPropertySheet2 methods in the node object.
*  Use MMCPropertyChangeNotify in the handler for the Apply button to
   for a redraw of the node.

/////////////////////////////////////////////////////////////////////////////
// Points of interest

*  Most of the new code which addresses Property Page issues can be found
   by searching for the PROPPAGE keyword.

*  Code which has implements features needed for Property Page extensions
   can be found by searching for the XPROPPAGE keyword
       
*  Attributes are now supported in the basenode class.  This will allow us
   to more easily add Property Pages to other nodes and make them extensible.


/////////////////////////////////////////////////////////////////////////////
//  Extensions - We now support Property Page extensions


// Define the new clipformat
#define T_CCF_ATTRIB_PTR      _T("CCF_ATTRIB_PTR") 

// The clipboard format is a pointer to this stuct.
//
typedef struct _tag_NODE_ATTRIB_
{
  DWORD*   pdwAttribs;
  LPWSTR   pszAttribs;

} NODE_ATTRIBS; 
