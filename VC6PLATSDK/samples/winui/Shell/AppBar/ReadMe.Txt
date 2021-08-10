The information below and the APPBAR sample applies to the following platforms:
   Windows 95
   Windows 98
   Windows 2000
   Windows NT 4.0

SUMMARY
=======

The Explorer shell allows an application to register an application desktop toolbar that behaves with the same look and feel as the Explorer taskbar. The application desktop toolbar is always attached to one of the outside edges of the screen and can cause the size of the desktop to be reduced so that other applications do not overlap the application desktop toolbar.

The APPBAR sample code demonstrates how to implement an application desktop toolbar that is resizable, can attach to any side of the screen, and allows itself to be hidden in the same way the Explorer taskbar automatically hides.


MORE INFORMATION
================

The application desktop toolbar interface provides an easy way for an application to attach windows to the edge of the screen so that they don't overlap the Explorer desktop or other applications. The ability to do this is especially useful in an application-launching program such as the Microsoft Office Manager (MOM) utility or in an application that needs to provide status information to the user as it runs in the background.

The application creates its window normally and then registers itself with the system as an application desktop toolbar (appbar). Once registered as an appbar, any time the window moves it must negotiate with the system for screen space by sending the requested rectangle to the system as part of an ABM_QUERYSETPOS message. The system then checks to see if any other appbars are using that space and adjusts the rectangle requested so as not to overlap. When the appbar is moved, the system resizes the desktop and moves any currently running applications so they do not overlap the appbar.
