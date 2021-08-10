Shell Name Space Extension Sample "SampView"

SampView is a simple example of a shell name space extension. It
implements the minimum number of interfaces required to create a
full-featured, multi-level name space extension. This extension includes
creation, deletion, copy, cut, and drag and drop capabilities. Once the
extension DLL is built and registered, an item called "Sample View" will
be displayed under My Computer within the Explorer tree.

You need to register the server manually, just execute the following 
from the command line, substituting the path where the DLL is located for
"<path>":

regsvr32.exe /s /c <path>\SampView.dll 

To properly register the extension on Windows NT 4.0 and Windows 2000,
the logged on user must have write access to the following registry
key:

   HKEY_LOCAL_MACHINE
      Software
         Microsoft
            Windows
               CurrentVersion
                  Shell Extensions
                     Approved
