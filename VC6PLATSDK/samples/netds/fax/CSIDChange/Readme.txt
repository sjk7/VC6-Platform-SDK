*********************************************************************
                          CSIDChange Sample
*********************************************************************
       Copyright(c) Microsoft Corporation. All rights reserved.

The CSIDChange sample is a Visual Basic program that demonstrates
how to make a global TSID and/or CSID change for devices on a fax 
server.

Usage: Type the name of a server in the space provided. The program 
connects to that server, and displays its devices.

If you select a specific device from the list, you can choose to 
assign a new CSID or TSID to either that device, or to all devices. 
If you don’t select a specific device, only the “assign to all 
devices” option is available.

If you leave either the CSID or TSID field blank, that parameter 
will not be changed. To put in a blank CSID or TSID, type a space
in the CSID or TSID field.

Project files: The Visual Basic project contains one form, 
ChangeCSID.frm, which contains the code for operation of the 
form. 

The ListView control is from Microsoft Windows Common Controls 6.0.