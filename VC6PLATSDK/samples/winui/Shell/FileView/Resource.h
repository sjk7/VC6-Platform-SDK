//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright 1994 - 2000 Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM: RESOURCE.H	
//
//	PURPOSE: Definitions specifically pertaining to resources for a FileViewer. 
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: N/A
//
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

//Resource identifiers
#define IDR_MENU                1
#define IDR_MENUVIEWPORT        2
#define IDR_ACCELERATORS        1
#define IDR_STATMESSAGEMAP      1
#define IDB_TOOLS               1
#define IDD_ABOUT               1


//Toolbar bitmaps indexes and other values
#define IDBT_OPENAS              0
#define IDBT_FONTSIZEINCREASE    1
#define IDBT_FONTSIZEDECREASE    2

#define CTBBUTTONS              4
#define CTBBITMAPS              3



//Menu command identifiers.
#define IDM_FILEOPENAS          100
#define IDM_FILEPAGESETUP       110
#define IDM_FILEPRINT           111
#define IDM_FILEEXIT            120

#define IDM_VIEWTOOLBAR         200
#define IDM_VIEWSTATUSBAR       201
#define IDM_VIEWFONT            210
#define IDM_VIEWFONTINCREASE    211     //Toolbar only
#define IDM_VIEWFONTDECREASE    212     //Toolbar only
#define IDM_VIEWREPLACE         223

#define IDM_HELPCONTENTS        300
#define IDM_HELPABOUT           301



//String identifiers.  Keep sequential for each group.

//Main window strings (messages, other variable strings).
#define IDS_MIN                 0

#define IDS_CLASSFRAME          (IDS_MIN+0)
#define IDS_CLASSVIEWPORT       (IDS_MIN+1)
#define IDS_CAPTION             (IDS_MIN+2)
#define IDS_DOCUMENTTYPE        (IDS_MIN+3)
#define IDS_NOHELP              (IDS_MIN+4)
#define IDS_TOOLTIPOPENAS       (IDS_MIN+5)
#define IDS_TOOLTIPFONTINC      (IDS_MIN+6)
#define IDS_TOOLTIPFONTDEC      (IDS_MIN+7)

#define IDS_MAX                 (IDS_MIN+7)

//Length of longest string in this stringtable.
#define CCHSTRINGMAX            40



//Status bar messages for a message map
#define IDS_STATUSMSGMIN        32

#define IDS_MSGEMPTY            (IDS_STATUSMSGMIN+0)
#define IDS_MSGREADY            (IDS_STATUSMSGMIN+1)
#define IDS_MSGSYS              (IDS_STATUSMSGMIN+2)
#define IDS_MSGSYSRESTORE       (IDS_STATUSMSGMIN+3)
#define IDS_MSGSYSMOVE          (IDS_STATUSMSGMIN+4)
#define IDS_MSGSYSSIZE          (IDS_STATUSMSGMIN+5)
#define IDS_MSGSYSMINIMIZE      (IDS_STATUSMSGMIN+6)
#define IDS_MSGSYSMAXIMIZE      (IDS_STATUSMSGMIN+7)
#define IDS_MSGSYSCLOSE         (IDS_STATUSMSGMIN+8)
#define IDS_MSGSYSTASKLIST      (IDS_STATUSMSGMIN+9)
#define IDS_MSGFILE             (IDS_STATUSMSGMIN+10)
#define IDS_MSGFILEOPENAS       (IDS_STATUSMSGMIN+11)
#define IDS_MSGFILEPAGESETUP    (IDS_STATUSMSGMIN+12)
#define IDS_MSGFILEPRINT        (IDS_STATUSMSGMIN+13)
#define IDS_MSGFILEEXIT         (IDS_STATUSMSGMIN+14)
#define IDS_MSGVIEW             (IDS_STATUSMSGMIN+15)
#define IDS_MSGVIEWTOOLBAR      (IDS_STATUSMSGMIN+16)
#define IDS_MSGVIEWSTATUSBAR    (IDS_STATUSMSGMIN+17)
#define IDS_MSGVIEWFONT         (IDS_STATUSMSGMIN+18)
#define IDS_MSGHELP             (IDS_STATUSMSGMIN+19)
#define IDS_MSGHELPCONTENTS     (IDS_STATUSMSGMIN+20)
#define IDS_MSGHELPABOUT        (IDS_STATUSMSGMIN+21)
#define IDS_MSGTIPFONTINC       (IDS_STATUSMSGMIN+22)
#define IDS_MSGTIPFONTDEC       (IDS_STATUSMSGMIN+23)
#define IDS_MSGCHOOSEOPEN       (IDS_STATUSMSGMIN+24)

#define IDS_STATUSMSGMAX        (IDS_STATUSMSGMIN+24)

#define CCHSTATUSMSGMAX         80

/*
 * IDs for status bar mapping of popup menus to string IDs.
 * Those for the menus defined between ID_MENUMIN and ID_MENUMAX
 * that we send to CStatusHelper::MessageMap must be sequential
 * as the popup menu hMenu's are mapped to these values by
 * sequential position, so be sure to define these values in
 * the same sequence as the menus themselves.
 */

#define ID_MSGEMPTY                         1000
#define ID_MSGREADY                         1001
#define ID_MENUSYS                          1002
#define ID_MENUFILE                         1003
#define ID_MENUVIEW                         1004
#define ID_MENUHELP                         1005
#define ID_TIPFONTINC                       1006
#define ID_TIPFONTDEC                       1007
#define ID_MSGCHOOSEOPEN                    1008


#define ID_MENUMIN                          ID_MENUFILE
#define ID_MENUMAX                          ID_MENUHELP


#endif //_RESOURCE_H_
