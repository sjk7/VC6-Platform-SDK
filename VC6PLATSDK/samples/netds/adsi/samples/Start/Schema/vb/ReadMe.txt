//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Schema VB Sample: Reading the WinNT Schema
//
//--------------------------------------------------------------------------

Description
===========
The Schema sample program enumerates the objects in the schema using the
WinNT provider.  It also binds to an object and retrieves schema information
about the object's class.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Schema.Bas
  *  Schema.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Schema.Vbp.
  2.  Open the module Schema.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain name,
      such as Fabrikam, in each of its occurences.
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints output similar to the following
in the Immediate window.  Otherwise, an error dialog appears that describes an
error.

Domain (Class)
Computer (Class)
User (Class)
Group (Class)
Service (Class)
FileService (Class)
Session (Class)
Resource (Class)
FileShare (Class)
FPNWFileService (Class)
FPNWSession (Class)
FPNWResource (Class)
FPNWFileShare (Class)
PrintQueue (Class)
PrintJob (Class)
Boolean (Syntax)
Counter (Syntax)
ADsPath (Syntax)
EmailAddress (Syntax)
FaxNumber (Syntax)
Integer (Syntax)
Interval (Syntax)
List (Syntax)
NetAddress (Syntax)
OctetString (Syntax)
Path (Syntax)
PhoneNumber (Syntax)
PostalAddress (Syntax)
SmallInterval (Syntax)
String (Syntax)
Time (Syntax)
MinPasswordLength (Property)
MinPasswordAge (Property)
MaxPasswordAge (Property)
MaxBadPasswordsAllowed (Property)
PasswordHistoryLength (Property)
AutoUnlockInterval (Property)
LockoutObservationInterval (Property)
Owner (Property)
Division (Property)
OperatingSystem (Property)
OperatingSystemVersion (Property)
Processor (Property)
ProcessorCount (Property)
Description (Property)
FullName (Property)
AccountExpirationDate (Property)
PasswordAge (Property)
UserFlags (Property)
LoginWorkstations (Property)
BadPasswordAttempts (Property)
MaxLogins (Property)
MaxStorage (Property)
PasswordExpired (Property)
PasswordExpirationDate (Property)
LastLogin (Property)
LastLogoff (Property)
HomeDirectory (Property)
Profile (Property)
Parameters (Property)
HomeDirDrive (Property)
LoginScript (Property)
LoginHours (Property)
PrimaryGroupID (Property)
objectSid (Property)
RasPermissions (Property)
groupType (Property)
HostComputer (Property)
DisplayName (Property)
ServiceType (Property)
StartType (Property)
Path (Property)
ErrorControl (Property)
LoadOrderGroup (Property)
ServiceAccountName (Property)
Dependencies (Property)
Version (Property)
MaxUserCount (Property)
User (Property)
Computer (Property)
ConnectTime (Property)
IdleTime (Property)
LockCount (Property)
CurrentUserCount (Property)
PrinterPath (Property)
PrinterName (Property)
Model (Property)
Datatype (Property)
PrintProcessor (Property)
ObjectGUID (Property)
Action (Property)
Location (Property)
StartTime (Property)
UntilTime (Property)
DefaultJobPriority (Property)
JobCount (Property)
Priority (Property)
Attributes (Property)
BannerPage (Property)
PrintDevices (Property)
HostPrintQueue (Property)
TimeSubmitted (Property)
TotalPages (Property)
Size (Property)
Notify (Property)
TimeElapsed (Property)
PagesPrinted (Property)
Position (Property)
Name (Property)
WinNT://FABRIKAM/Schema/Domain
MinPasswordLength
MinPasswordAge
MaxPasswordAge
MaxBadPasswordsAllowed
PasswordHistoryLength
AutoUnlockInterval
LockoutObservationInterval
Name

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the
IADsContainer interface to enumerate the objects in the schema.

See Also
========
IADsContainer interface
WinNT ADsPath
WinNT Binding String (ADsPath)

