Hello World 3 (Java) Sample for Microsoft Agent
-----------------------------------------------

*** Required components ***

1. This sample requires the Microsoft Agent Core Components and the
TruVoice Text-To-Speech Engine.  These should be installed before
running this sample.

2. This sample tries to load characters from the 
%windows%\msagent\chars directory. If the characters
cannot be loaded from that directory, it attempts to 
load them from the %program files%\Microsoft Agent\Characters 
directory.

3. This sample requires Microsoft Visual J++ 1.1 or 6.0 (or
another compatible Java environment).

4. This sample requires that the Agent Server COM class be imported
to Java. If you are running Visual J++ 1.1 you can to this by
selecting the Java Type Library Wizard from the Tools menu. If you are 
running Visual J++ 6.0, select the "Add COM Wrapper" option from the Project menu.
Scroll through the list of items and find the entry for 
"Microsoft Agent Server 2.0". Place a check mark in the box next 
to this entry, then click OK. 


*** To run the sample ***

1. Start up Microsoft Visual J++.  From the File menu, select Open Workspace.
Navigate to the folder containing this Readme file.  Select the project file
(Hello3J.dsp) for this sample.  Click Open.

2. For Visual J++ 1.1, select Execute from the Build menu. When prompted 
that files need to be built, click Yes.  When prompted for a Class File Name, enter 
the name of the sample: "Hello3J", then click OK.  Note that the name is case sensitive.
For Visual J++ 6.0, select Start from the Debug menu.
