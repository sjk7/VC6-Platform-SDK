This is an updated Visual C++ 6.0 Cluster Resource Type Wizard. It
contains bug fixes for previous versions and new options for more
complete generated application control, checkpoint support, Cluster
Configuration extensions, and context menu extensions.  Additionally,
the generated code uses the String Safe library of string functions to
mitigate the chance of buffer overruns.

To update the wizard:
1.  Make sure no instances of Visual Studio 6.0 are running.
2.  Locate any copies of CResTyp.Awx under your Visual Studio 6.0
    installation directory and rename them with new file extensions
    or delete them.
3.  Locate the IDE directory, which will be something like this:
    "C:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\IDE"
4.  Copy CResTyp.Awx and CResTyp.Hlp to this directory.

To run the wizard select "File, New, Projects, Cluster Resource Type 
Wizard", enter a project name, then hit "OK".

If there are multiple entries for "Cluster Resource Type Wizard" under
the Projects tab then Visual Studio found multiple Awx files that
implement the wizard.  Search for other files under the install
directory that may not have been renamed correctly.
