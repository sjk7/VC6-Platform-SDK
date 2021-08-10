Instructions for using the parser boilerplate

(Throughout these instructions, <YPN> should be your actual protocol name, 
 for example "IPX" or "NETBIOS")


    1. Copy the contents of the BLRPLATE directory into your own directory.
    2. Rename BLRPLATE.* to <YPN>.*.
    3. Load <YPN>.c, <YPN>.h, and <YPN>.def into your editor.
    4. Replace all occurrences of "BLRPLATE" with <YNP>.
    5. Replace all occurrences of "Your Name Here" with your name.
    6. Replace all occurrences of "01/01/70" with today's date.
    7. Replace all occurrences of "rfcXXXX" with the name of the document that
       you are using.


Now you need to determine whether this parser is going to live in its own DLL,
or if it will be included in another parser's DLL.

    If it is going to be in its own DLL, then:
        1. Load makefile, <YPN>.rc, and <YPN>.def into your editor.
        2. Make all of the same textural substitutions that you made above.

    If it is going to be put in another DLL, <Another>.dll:
        1. Delete makefile and <YPN>.rc.
        2. Copy all of the lines in the EXPORTS section of <YPN>.def (except 
           ParserAutoInstallInfo) to <Another>.def.
        3. Delete <YPN>.def.
        4. Copy the "h<YPN> = CreateProtocol(...)" line from <YPN>.c to 
           the same spot on the DriverEntry() in <Another>.c.
        5. Copy the "DestroyProtocol(...)" line from <YPN>.c to 
           the same spot on the DriverEntry() in <Another>.c.
        6. Add a new line to <Another>.c: "extern ENTRYPOINTS <YPN>EntryPoints;".
        7. Add a new line to <Another>.c: "extern HPROTOCOL h<YPN>;".
        8. Add the proper lines to the makefile for <Another>.dll to 
           build and link in <YPN>.obj.
        9. Remove the following line from <YPN>.c: "DWORD     Attached = 0;".
        10. Remove the following functions from <YPN>.c: 
            ParserAutoInstallInfo() and DLLEntry().

Now you can begin creating your parser's property lists, labeled sets, and 
RecognizeFrame and AttachProperties functions (using the boilerplate stuff
as examples.)

