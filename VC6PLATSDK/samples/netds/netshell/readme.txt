Nshsamp.dll

The nshsamp project is an example of how to build a Netsh helper that implements multiple contexts, each with its own commands.  The Netsh API was published for Whistler, and those that wish to write Netsh helpers might be interested in this sample to assist in creating their own helpers.

How to build: From within the SDK environment, 'nmake' should be all that is required to build the sample.

Installation: once the sample dll is built, copy it to your %windir%\system32 directory and run Netsh.  From within Netsh, run 'add helper nshsamp.dll".  The sample helper implements three contexts - typing show helper from within Netsh will give a list of all the contexts implemented, which dll they reside in, and the guids of those helpers.  You can see the three contexts implemented by nshsamp.dll here.  Move to those contexts just like any other - from the top level Netsh prompt, for example, type 'sample' to enter the sample context.  From within these contexts, entering the '?' command will show you a list of the commands implemented - they are also extensively commented in the code.

Requirements: The sample can be run on x86 and Itanium(TM) versions of Windows XP ONLY.

Highlights: the intent of this sample is to highlight the API's provided as part of the Platform SDK for Netsh (Netshell).


