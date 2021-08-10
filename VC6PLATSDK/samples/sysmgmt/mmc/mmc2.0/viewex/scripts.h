/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//

#ifndef _SCRIPTS_DEFINED_HEADER_
#define _SCRIPTS_DEFINED_HEADER_


/////////////////////////////////////////////////////////////////////////////
//  These are mini-scripts which can be used to build larger scripts for
//  nodes which use a View Extension.



//---------------------------------------------------------------------------
//  Define the begining and ending of the form
//
LPWSTR GSCRP_BEGIN_FORM     =  L"<BODY><FORM>";
LPWSTR GSCRP_END_FORM       =  L"</BODY></FORM>";



/////////////////////////////////////////////////////////////////////////////
//  In these scripts 'external' is a predefined alias for a View Object.
//  These can call methods which have a context menu item.  


//---------------------------------------------------------------------------
//  Displays a 'Rename' button.  The script brings up a dialog to get the
//  new name for the node.  The call to external.RenameSelectedItem() will
//  cause MMC to send a MMCN_RENAME notification which can be handled in
//  the normal way.  
//
LPWSTR GSCRP_RENAME_BUTTON  =  
             L"<INPUT TYPE='BUTTON' NAME='btnRename' VALUE='Rename'>"   
             L"<SCRIPT FOR='btnRename' EVENT='onClick' LANGUAGE='VBScript'>"
             L"Dim filename\n"                                               
             L"filename=InputBox(\"Enter the new file name\")\n"              
             L"external.RenameSelectedItem( filename )\n"                    
             L"</SCRIPT>"                                                    
             L"<BR><BR>";


//---------------------------------------------------------------------------
//  Displays a 'Delete' button.  When the button is clicked the Snap-in will
//  recieve a MMCN_DELETE notification.
//
LPWSTR GSCRP_DELETE_BUTTON  =        
             L"<INPUT TYPE='BUTTON' NAME='btnDelete' VALUE='Delete'>"
             L"<SCRIPT FOR='btnDelete' EVENT='onClick' LANGUAGE='VBScript'>"
             L"external.DeleteSelection()\n"
             L"</SCRIPT>"
             L"<BR><BR>";

//---------------------------------------------------------------------------
//  Displays the text "Link to Corporate Home Page" as a link.  Link takes
//  you to Microsoft.com but you can go somewhere else if you really want to.
//  Note:  "target = "_blank" causes the link to open in a new window.
//
//
LPWSTR GSCRP_LINK_HOMEPAGE  = 
             L"<a HREF = \"http://www.microsoft.com\" target = \"_blank\">"
             L"Link to Corporate Home Page</a></p>"
             L"<BR>";


#endif // _SCRIPTS_DEFINED_HEADER_