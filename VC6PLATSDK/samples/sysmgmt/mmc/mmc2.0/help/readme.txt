/////////////////////////////////////////////////////////////////////////////
MMC SDK Sample Project:  MMC Help

Summary:
This project implements Help for MMC. 
ISnapinHelp is implemented and IDisplayHelp are demonstrated. 

The project requires MMC 2.0

/////////////////////////////////////////////////////////////////////////////
//  Steps used to implement Help for your Snap-in

* Add support for ISnapinHelp to your implementation of IComponentData.
  Include it in the derived interface list and QueryInterface

* Implement a global helper method to get the path to the help file  

* Add support for MMCN_CONTEXTHELP in your node objects
 
* Add support for WM_HELP and PSN_HELP in any PropertySheet dialog procs.  

* QueryInterface and cache a pointer IDisplayHelp in your implementation
  of IComponent::Initialize().

* Add support for IDisplayHelp to CComponent::GetInterface().  Also add
  a new REQUEST* define in Globals.h  

/////////////////////////////////////////////////////////////////////////////
// Points of interest

Must add shlwapi.lib to support PathRemoveFileSpec()
This project supports property pages so comctl32.lib must also be added.

This sample assumes the help file is in the same directory as the Snap-in.
This location is recommended since it avoids potential problems from putting
the help file in the system or other directories used by the OS.
You will need to put a copy of the help file in all the build directories
during developent however (DebugUnicode, DebugAnsi...)


