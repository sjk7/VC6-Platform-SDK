
MMC SDK Sample Project:  About

This project is based on the 'Simple' sample project.  The only changes 
are to add an implementation of ISnapinAbout.
Since there are several changes to the base projects files needed to
implement ISnapinAbout which are not obvious, a search word has been
added to the comments.  Search on "NEW:" in the source files to locate
changes which were made to support ISnapinAbout.

Design Considerations for this project

*  Scale efficiently to large projects
*  Easy to accomodate future interfaces and functionality
*  Easy to maintain
*  Simple, easy to learn object model


-------------------------------------------------------------------------------
'About' Object Model:

This project uses a very simple delgation object model.
Most of the work the Snap-in does is delegated to a node which is derived
from CBaseNode.  This class handles many of the calls the console makes to
the Snap-in to get information about the view to display, column text and
other MMC notifications.


CComponentData is the class which interfaces with MMC's namespace.  MMC will
send notifications to CComponentData which will in turn delegate handling
of these events to CStaticNode.

CComponent is the class which represents the Result or Details view.  In this
sample we do not handle result items or leaf nodes or use OCX or URL based
views, so most methods in this class are not implemented.
New instances of this class are created by CComponentData in each time a 
new view is requested through the user interface.

CDataObject is the class used to communicate and pass information between
the various objects in this project.  Data objects are created by 
CComponentData in response to requests from MMC.


-------------------------------------------------------------------------------
Files in this project:

About.h/cpp        Implements ISnapinAbout.

BaseNode.h         BaseNode provides the basic functionality for the Snap-in's
                   nodes.  In this sample on CStaticNode, which represents the
                   single root node, is derived from CBaseNode.


BaseSnap.h/cpp     This file implements IClassFactory and the functions needed
                   to implement the base COM object such as DllCanUnloadNow,
                   DllRegisterServer and other similar required methods.

Comp.h/cpp         Implements IComponent

CompData.h/cpp     Implements IComponentData

DataObj.h/cpp      Implements IDataObject

Globals.h/cpp      Base header file for the project.  Contains all global 
                   information, helper functions, macros and defines.

Guids.h            Defines and documents all GUIDs used in the project

Registry.h/cpp     Implements all the functions needed to register the COM
                   object to to register the Snap-in in MMC's registry key

StaticNode.h/cpp   Implementation of the Snap-in's static node. Derived from
                   CBaseNode

TraceMacro.h/cpp   Implements custom tracing functions and macros which are
                   are used in this project.

