*****************************************
Microsoft Bluetooth SDK supplement 
*****************************************

Prerequisites for development
* Appropriate compiler (Microsoft Visual C++)
* Microsoft Platform SDK (latest - post July 2002)

Prerequisites for testing
* Supported Bluetooth radio hardware (2)
* Microsoft Windows XP SP1 (or later)
* Bluetooth support for Windows XP QFE

These prerequisites must be present on the system before working with this SDK.

Structure of this supplement:

btsdk
  samples -- sample Winsock application(s)
    bthcxn -- sample for connection over RFCOMM using Winsock
  inc -- headers for compiling C/C++ applications for Bluetooth
    bthdef.h -- Common Bluetooth definitions
    bthsdpdef.h -- Common Bluetooth SDP definitions
    ws2bth.h -- Bluetooth Winsock APIs
    bluetoothapis.h -- Bluetooth management APIs
  lib/i386 -- libraries required for linking with Bluetooth interfaces
    irprops.lib -- library for linking with Bluetoothapis.h functionality
  help -- documentation for Bluetooth interfaces
    bluetooth.chm -- documentation for Bluetooth SDK interfaces   
 
The contents in this supplement will be included in future versions of the Microsoft Platform SDK, at which point this supplement is deprecated.

To compile samples, open an appropriate "Build Environment Window" from the Platform SDK section of the start menu, and run 

	nmake /f makefile.sdk


