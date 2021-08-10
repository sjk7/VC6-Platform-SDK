/****************************************************************************\
*            
*     FILE:     MDIChild.C
*
*     PURPOSE:  IconPro Project MDI Child Window handling c file
*
*     COMMENTS: This file contains the MDI Child Window handling code
*
*     FUNCTIONS:
*      EXPORTS: 
*               IconChildWndProc   - Window Procedure for the MDI children
*      LOCALS:
*               Draw3DRect         - Draws a rectangle using 3D colors
*               EraseBackground    - Draws the MDI child's background
*               CreateChildren     - Creates MDI child's child windows
*               CreateChildListBox - Creates and shows a list box
*               AddFormatDlgProc   - Dialog Proc for AddFormat dialog
*
*     Copyright 1995 - 2000 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <malloc.h>
#include "Icons.h"
#include "IconPro.h"
#include "Resource.h"
#include "MDIChild.H"


/****************************************************************************/
// External Globals
extern HINSTANCE    hInst;
extern HWND         hWndMain, hMDIClientWnd;
/****************************************************************************/


/****************************************************************************/
// Prototypes for local functions
BOOL Draw3DRect( HDC hDC, RECT Rect, BOOL bSunken );
void EraseBackground( HWND hWnd, HDC hDC );
BOOL CreateChildren( HWND hWnd );
HWND CreateChildListBox( HWND hWndParent, UINT ID, PRECT pRect );
BOOL CALLBACK AddFormatDlgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
/****************************************************************************/



/****************************************************************************
*
*     FUNCTION: IconChildWndProc
*
*     PURPOSE:  Window Procedure for MDI child window
*
*     PARAMS:   HWND hWnd     - This window handle
*               UINT Msg      - Which Message?
*               WPARAM wParam - message parameter
*               LPARAM lParam - message parameter
*
*     RETURNS:  LRESULT - depends on message
*
* History:
*                July '95 - Created
*
\****************************************************************************/
LRESULT CALLBACK IconChildWndProc( 
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam )
{
    // Which message is it?
    switch( Msg )
    {
        // User pressed left mouse button
        // Should be re-generate the AND mask?
        case WM_LBUTTONDOWN:
            {
                PCHILDWINDOWDATA pcwd = NULL;

                // Get the icon resource data aassociated with this window
                if( (pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA )) == NULL )
                {
                    break;
                }

                // Do something only if the CNTRL key is pressed too
                if( MK_CONTROL & wParam )
                {
                    POINTS	pts       = MAKEPOINTS(lParam);
                    POINT	pt        = {0};
                    RECT    ImageRect = {0};
                    DWORD	nIndex;

                    pt.x = pts.x; pt.y = pts.y;
                    // Do we have some icon resource data?
                    if( pcwd->pIR != NULL )
                    {
                        // Which image is selected right now?
                        if( (nIndex = (DWORD)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            // Where is it drawn
                            ImageRect = GetXORImageRect( pcwd->XORRect, &(pcwd->pIR->IconImages[nIndex]) );
                            // Is the mouse click in the image?
                            if( PtInRect( &ImageRect, pt ) )
                            {
                                HCURSOR	hOldCursor = NULL;

                                // This might take a while :(
                                hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );
                                pt.x -= ImageRect.left;
                                pt.y -= ImageRect.top;
                                // generate the new AND mask
                                MakeNewANDMaskBasedOnPoint( &(pcwd->pIR->IconImages[nIndex]), pt );
                                // force a redraw
                                InvalidateRect( hWnd, NULL, TRUE );
                                //  Set changed flag
                                pcwd->pIR->bHasChanged = TRUE;
                                // finally, its over, put the cursor back
                                SetCursor( hOldCursor );
                            }
                        }
                    }
                }
            }
            break; // End WM_LBUTTONDOWN

        // Time to say "Goodbye"
        case WM_CLOSE:
            {
                PCHILDWINDOWDATA    pcwd        = NULL;
                TCHAR   szWindowTitle[MAX_PATH] = {0};

                // Get the data associated with this window
                pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                // Is there data associated with this window?
                if( pcwd != NULL )
                {
                    // Does the data include an icon resource
                    if( pcwd->pIR != NULL )
                    {
                        // Has the resource changed?
                        if( pcwd->pIR->bHasChanged )
                        {
                            // Get the title for the message box
                            GetWindowText( hWnd, szWindowTitle, MAX_PATH );
                            if( lstrlen( szWindowTitle ) < 1 )
                            {
                                lstrcpyn( szWindowTitle, TEXT("UnKnown"), 
                                          sizeof(szWindowTitle)/sizeof(szWindowTitle[0]) - 1  );
                            }
                            // User want to save changes?
                            switch( MessageBox( hWnd, TEXT("Icon has Changed, Save Changes?"), szWindowTitle, MB_ICONSTOP | MB_YESNOCANCEL ) )
                            {
                                case IDYES:
                                    SendMessage( hWnd, WM_COMMAND, ID_FILE_SAVE, 0 );
                                    // Fall through to IDNO and kill window
                                case IDNO:
                                    DefMDIChildProc( hWnd, Msg, wParam, lParam );
                                    return 0;
                                    break;
                                case IDCANCEL:
                                    return 1;
                                    break;
                            }
                        }
                    }
                }
                DefMDIChildProc( hWnd, Msg, wParam, lParam );
                return 0;
            }
            break; // End WM_CLOSE

        // We are being created
        case WM_CREATE:
            {
                PCHILDWINDOWDATA pcwd = NULL;

                // Need new data for this new window
                pcwd = malloc( sizeof( CHILDWINDOWDATA ) );
                SetWindowLongPtr( hWnd, GWLP_USERDATA, (LONG_PTR)pcwd );
                pcwd->pIR = NULL;
                // If a resource was passed in, use it
                if( (PVOID)lParam != NULL )
                {
                    pcwd->pIR = (PICONRESOURCE)(((MDICREATESTRUCT *)(((CREATESTRUCT *)lParam)->lpCreateParams))->lParam);
                }
                
                // If no resource was passed in, do minimal initialization
                if( pcwd->pIR == NULL )
                {
                    pcwd->pIR = malloc(sizeof(ICONRESOURCE));
                    lstrcpyn( pcwd->pIR->szOriginalICOFileName, TEXT("Untitled"), MAX_PATH - 1 );
                    lstrcpyn( pcwd->pIR->szOriginalDLLFileName, TEXT(""), MAX_PATH - 1 );
                    pcwd->pIR->nNumImages = 0;
                }
                // Nothing has changed
                pcwd->pIR->bHasChanged = FALSE;
                // Create the list box, etc
                CreateChildren( hWnd );
                return DefMDIChildProc( hWnd, Msg, wParam, lParam );
            }
            break; // End WM_CREATE

        // Won't let window get too small to show our main area
        case WM_GETMINMAXINFO:
            {
                PMINMAXINFO pmmi = (PMINMAXINFO)lParam;

                pmmi->ptMinTrackSize.x = WINDOW_WIDTH;
                pmmi->ptMinTrackSize.y = WINDOW_HEIGHT;
                return 0;
            }
            break; // End WM_GETMINMAXINFO

        // Yikes! We're being destroyed!
        case WM_DESTROY:
            {
                PCHILDWINDOWDATA pcwd = NULL;

                // Get the data associated with this window 
                pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                // Is there some?
                if( pcwd != NULL )
                {
                    // Is there a resource?
                    if( pcwd->pIR != NULL )
                    {
                        UINT i;

                        // Free all the bits
                        for( i=0; i< pcwd->pIR->nNumImages; i++ )
                        {
                            if( pcwd->pIR->IconImages[i].pBits != NULL )
                            {
                                free( pcwd->pIR->IconImages[i].pBits );
                            }
                        }
                        free( pcwd->pIR );
                    }
                    free( pcwd );
                }
                SetWindowLongPtr( hWnd, GWLP_USERDATA, 0 );
            }
            break; // End WM_DESTROY

        // Draw our background (white and black squares, etc)
        case WM_ERASEBKGND:
            EraseBackground( hWnd, (HDC)wParam );
            return 1;
            break; // End WM_ERASEBKGND

        // Ok, time to paint
        case WM_PAINT:
            {
                PCHILDWINDOWDATA    pcwd  = NULL;
                HDC                 hDC   = NULL;
                PAINTSTRUCT         ps    = {0};
                DWORD               nIndex;
                HICON               hIcon = NULL;

                // Obligatory BeginPaint()
                hDC = BeginPaint( hWnd, &ps );
                // Get the data associated with this window
                pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                // Is there some?
                if( pcwd != NULL )
                {
                    // Is there a resource?
                    if( pcwd->pIR != NULL )
                    {
                        // Which image is selected?
                        if( (nIndex = (DWORD)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            int        	Width, Height;

                            // Get an HICON for the currently selected image
                            hIcon = MakeIconFromResource( &(pcwd->pIR->IconImages[nIndex]) );
                            // How big is the icon?
                            Width = pcwd->pIR->IconImages[nIndex].Width;
                            Height = pcwd->pIR->IconImages[nIndex].Height;
                            // Check to see if the icon is NULL
                            // If it is, consider it "unsupported"
                            // In the future, maybe we should look into MakeIconFromResource() and
                            // see why it is null - it may be for another reason than "unsupported"
                            if( hIcon == NULL )
                            {
                                SIZE    Size, Position;

                                // Draw some text in the black rect
                                SetTextColor( hDC, RGB(255,255,255) );
                                GetTextExtentPoint32( hDC, TEXT("Unsupported"), 11, &Size );
                                Position.cx = pcwd->BlackRect.left + ((RectWidth(pcwd->BlackRect)-Size.cx)/2);
                                Position.cy = pcwd->BlackRect.top + (RectHeight(pcwd->BlackRect)/2) - Size.cy;
                                TextOut( hDC, Position.cx, Position.cy, TEXT("Unsupported"), 11 );
                                GetTextExtentPoint32( hDC, TEXT("Format"), 6, &Size );
                                Position.cx = pcwd->BlackRect.left + ((RectWidth(pcwd->BlackRect)-Size.cx)/2);
                                Position.cy = pcwd->BlackRect.top + (RectHeight(pcwd->BlackRect)/2) + 1;
                                TextOut( hDC, Position.cx, Position.cy, TEXT("Format"), 6 );

                                // Draw some text in the white rect
                                SetTextColor( hDC, RGB(0,0,0) );
                                GetTextExtentPoint32( hDC, TEXT("Unsupported"), 11, &Size );
                                Position.cx = pcwd->WhiteRect.left + ((RectWidth(pcwd->WhiteRect)-Size.cx)/2);
                                Position.cy = pcwd->WhiteRect.top + (RectHeight(pcwd->WhiteRect)/2) - Size.cy;
                                TextOut( hDC, Position.cx, Position.cy, TEXT("Unsupported"), 11 );
                                GetTextExtentPoint32( hDC, TEXT("Format"), 6, &Size );
                                Position.cx = pcwd->WhiteRect.left + ((RectWidth(pcwd->WhiteRect)-Size.cx)/2);
                                Position.cy = pcwd->WhiteRect.top + (RectHeight(pcwd->WhiteRect)/2) + 1;
                                TextOut( hDC, Position.cx, Position.cy, TEXT("Format"), 6 );
                            }
                            else
                            {
                                // Draw it on the black background
                                DrawIconEx( hDC, pcwd->BlackRect.left + ((RectWidth(pcwd->BlackRect)-Width)/2),
                                                pcwd->BlackRect.top + ((RectHeight(pcwd->BlackRect)-Height)/2), 
                                                hIcon, Width, Height, 0, NULL, DI_NORMAL );
                                // Draw it on the white background
                                DrawIconEx( hDC, pcwd->WhiteRect.left + ((RectWidth(pcwd->WhiteRect)-Width)/2),
                                                pcwd->WhiteRect.top + ((RectHeight(pcwd->WhiteRect)-Height)/2), 
                                                hIcon, Width, Height, 0, NULL, DI_NORMAL );
                            }
                            // Draw just the XOR mask
                            DrawXORMask( hDC, pcwd->XORRect, &(pcwd->pIR->IconImages[nIndex]) );
                            // Draw just the AND mask
                            DrawANDMask( hDC, pcwd->ANDRect, &(pcwd->pIR->IconImages[nIndex]) );
                            // Kill the icon, we're one with it
                            if( hIcon != NULL )
                                DestroyIcon( hIcon );
                        }
                    }
                }
                // Obligtory EndPaint()
                EndPaint( hWnd, &ps );
            }
            break; // End WM_PAINT

        // WM_COMMAND - menu options, etc
        case WM_COMMAND:
            // which one is it?
            switch( LOWORD(wParam) )
            {
                // Edit->Export BMP - write icon image as BMP file
                case ID_EDIT_EXPORTBMP:
                    {
                    PCHILDWINDOWDATA pcwd                 = NULL;
                    DWORD            nIndex;
                    TCHAR            szFileName[MAX_PATH] = {0};

                    // Get the data associated this window 
                    pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                    // If we have some data, including an icon resource
                    if( (pcwd != NULL ) && (pcwd->pIR != NULL) && (pcwd->hWndFormatListBox!= NULL) )
                    {
                        // Which image is currently selected?
                        if( (nIndex = (DWORD)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                        {
                            // Get the name of the file from which to import the image
                            if( GetSaveIconFileName( szFileName, IDS_BMPFILTERSTRING, TEXT("Export to BMP File") ) )
                            {
                                HCURSOR	hOldCursor;

                                // This might take a while :(
                                hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );
                                IconImageToBMPFile( szFileName, &(pcwd->pIR->IconImages[nIndex]) );
                                SetCursor( hOldCursor );
                            }
                        }
                    }
                    }
                    break; // End ID_EDIT_EXPORTBMP

                // Edit->Import BMP and Edit->Stretch-Import BMP - convert BMP file to icon
                case ID_EDIT_IMPORTBMP:  /* fall-through */
                case ID_EDIT_STRETCHIMPORTBMP:
                    {
                        PCHILDWINDOWDATA    pcwd                 = NULL;
                        DWORD               nIndex;
                        TCHAR               szFileName[MAX_PATH] = {0};

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data, including an icon resource
                        if( (pcwd != NULL ) && (pcwd->pIR != NULL) && (pcwd->hWndFormatListBox!= NULL) )
                        {
                            // Which image is currently selected?
                            if( (nIndex = (DWORD)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                            {
                                // Get the name of the file from which to import the image
                                if( GetOpenIconFileName( szFileName, IDS_BMPFILTERSTRING, TEXT("Import from BMP File") ) )
                                {
                                    HCURSOR	hOldCursor;

                                    // This might take a while :(
                                    hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );
                                    // Import the BMP image data
                                    if( IconImageFromBMPFile( szFileName, &(pcwd->pIR->IconImages[nIndex]), (LOWORD(wParam)==ID_EDIT_STRETCHIMPORTBMP)?TRUE:FALSE ) )
                                    {
                                        // which, of course, changes things
                                        pcwd->pIR->bHasChanged = TRUE;
                                        // Force a repaint
                                        InvalidateRect( hWnd, NULL, TRUE );
                                    }
                                    SetCursor( hOldCursor );
                                }
                            }
                        }
                    }
                    break; // End ID_EDIT_IMPORTBMP/ID_EDIT_STRETCHIMPORTBMP

                // User wants to add an image format
                case ID_EDIT_ADDFORMAT:
                    {
                        PICONIMAGE  pii           = NULL;
                        TCHAR       szBuffer[256] = {0};
                        
                        // Launch the dialog to ask which size and color depth
                        if( DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_ADDFORMATDLG), hWndMain, (DLGPROC)AddFormatDlgProc, (LPARAM)(&pii) ) )
                        {
                            PCHILDWINDOWDATA    pcwd    = NULL;
                            PICONRESOURCE       pNewIR  = NULL;
                            DWORD               nIndex, i;

                            // Get the data associated this window 
                            pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                            // If we have some data, including an icon resource
                            if( (pcwd != NULL ) && (pcwd->pIR != NULL) && (pcwd->hWndFormatListBox!= NULL) )
                            {
                                // Need to see if the new format already exists in the resource
                                // We don't want dupes, so check each image for dupe
                                for(i=0;i<pcwd->pIR->nNumImages;i++)
                                {
                                    // Is it the same as the new one?
                                    if( (pcwd->pIR->IconImages[i].Width==pii->Width) &&
                                        (pcwd->pIR->IconImages[i].Height==pii->Height) && 
                                        (pcwd->pIR->IconImages[i].Colors==pii->Colors) )
                                    {
                                        // Yikes! It is - bail and select the old one
                                        MessageBox( hWnd, TEXT("That format already exists - format not added"), TEXT("Error"), MB_OK );
                                        SendMessage( pcwd->hWndFormatListBox, 	CB_SETCURSEL, (WPARAM)i, (LPARAM)0 );
                                        break;
                                    }
                                }
                                // Need bigger block of memory to hold an extra image format
                                pNewIR = malloc( sizeof( ICONRESOURCE ) + ( ( pcwd->pIR->nNumImages + 1) * sizeof(ICONIMAGE) ) );
                                // Of course this changes things
                                pNewIR->bHasChanged = TRUE;
                                // Copy old to new
                                lstrcpyn( pNewIR->szOriginalICOFileName, pcwd->pIR->szOriginalICOFileName,
                                          MAX_PATH - 1);
                                lstrcpyn( pNewIR->szOriginalDLLFileName, pcwd->pIR->szOriginalDLLFileName,
                                          MAX_PATH - 1);
                                pNewIR->nNumImages = pcwd->pIR->nNumImages + 1;
                                for(i=0;i<pcwd->pIR->nNumImages;i++)
                                {
                                    memcpy( &(pNewIR->IconImages[i]), &(pcwd->pIR->IconImages[i]), sizeof( ICONIMAGE ) );
                                }
                                // Add in the new one
                                memcpy( &(pNewIR->IconImages[i]), pii, sizeof( ICONIMAGE ) );
                                // Add this new one to the list box
                                wsprintf( szBuffer, TEXT("%dx%d, %d Bit Color"), pii->Width, pii->Height, pii->Colors );
                                nIndex = (ULONG)SendMessage( pcwd->hWndFormatListBox, CB_ADDSTRING, 0, (LPARAM)szBuffer );
                                // Select the new one
                                SendMessage( pcwd->hWndFormatListBox, 	CB_SETCURSEL, (WPARAM)i, (LPARAM)0 );
                                // clean up
                                free( pii );
                                free( pcwd->pIR );
                                pcwd->pIR = pNewIR;
                                // Create a nice new blank image for this format
                                CreateBlankNewFormatIcon( &(pcwd->pIR->IconImages[i]) );
                                // force a repaint
                                InvalidateRect( hWnd, NULL, TRUE );
                            }
                        }
                    }
                    break; // End WM_COMMAND -> ID_EDIT_ADDFORMAT
                
                // User wants to remove an image format
                case ID_EDIT_REMOVEFORMAT:
                    {
                        PCHILDWINDOWDATA    pcwd        = NULL;
                        DWORD               nIndex, i;
                        PICONRESOURCE       pNewIR      = NULL;

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data, including an icon resource
                        if( (pcwd != NULL ) && (pcwd->pIR != NULL) && (pcwd->hWndFormatListBox!= NULL) )
                        {
                            // Which image is currently selected?
                            if( (nIndex = (ULONG)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                            {
                                // Remove the entry from the list box
                                SendMessage( pcwd->hWndFormatListBox, CB_DELETESTRING, nIndex, 0 );
                                // Need less memory now
                                pNewIR = malloc( sizeof( ICONRESOURCE ) + ( ( pcwd->pIR->nNumImages - 1) * sizeof(ICONIMAGE) ) );
                                // Of course this changes things
                                pNewIR->bHasChanged = TRUE;
                                // Copy old to new
                                lstrcpyn( pNewIR->szOriginalICOFileName, pcwd->pIR->szOriginalICOFileName,
                                          MAX_PATH - 1);
                                lstrcpyn( pNewIR->szOriginalDLLFileName, pcwd->pIR->szOriginalDLLFileName,
                                          MAX_PATH - 1);
                                pNewIR->nNumImages = pcwd->pIR->nNumImages - 1;
                                // Copy the rest of the images from old to new
                                for(i=0;i<nIndex;i++)
                                {
                                    memcpy( &(pNewIR->IconImages[i]), &(pcwd->pIR->IconImages[i]), sizeof( ICONIMAGE ) );
                                }		 
                                for(;i<pcwd->pIR->nNumImages-1;i++)
                                {
                                    memcpy( &(pNewIR->IconImages[i]), &(pcwd->pIR->IconImages[i+1]), sizeof( ICONIMAGE ) );
                                }
                                // Clean up
                                free( pcwd->pIR );
                                pcwd->pIR = pNewIR;
                                // Select a different image
                                if( (int) --nIndex < 0 )
                                {
                                    nIndex = 0;
                                }
                                SendMessage( pcwd->hWndFormatListBox, CB_SETCURSEL, (WPARAM)nIndex, 0 );
                                // Force a repaint
                                InvalidateRect( hWnd, NULL, TRUE );
                            }
                        }
                    }
                    break; // End WM_COMMAND -> ID_EDIT_REMOVEFORMAT

                // User wants to paste CF_DIB from clipboard into current image
                case ID_EDIT_STRETCHPASTE: /* fall-through */
                case ID_EDIT_PASTE:
                    {
                        PCHILDWINDOWDATA    pcwd    = NULL;
                        DWORD               nIndex;

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data, including an icon resource
                        if( (pcwd != NULL ) && (pcwd->pIR != NULL) && (pcwd->hWndFormatListBox!= NULL) )
                        {
                            // Which image is currently selected?
                            if( (nIndex = (ULONG)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                            {
                                HCURSOR	hOldCursor;

                                // This might take a while :(
                                hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );

                                // Paste over it from the clipboard
                                if( IconImageFromClipBoard( &(pcwd->pIR->IconImages[nIndex]), 
                                                            LOWORD(wParam)!=ID_EDIT_PASTE ) )
                                {
                                    // which, of course, changes things
                                    pcwd->pIR->bHasChanged = TRUE;
                                }
                                // Force a repaint
                                InvalidateRect( hWnd, NULL, TRUE );
                                SetCursor( hOldCursor );
                            }
                        }
                    }
                    break; // End WM_COMMAND -> ID_EDIT_STRETCHPASTE/ID_EDIT_PASTE

                // Put current image on the clipboard in CF_DIB format
                case ID_EDIT_COPY:
                    {
                        PCHILDWINDOWDATA    pcwd  = NULL;
                        DWORD               nIndex;

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data, including an icon resource
                        if( (pcwd != NULL ) && (pcwd->pIR != NULL) && (pcwd->hWndFormatListBox!= NULL) )
                        {
                            // Which image is currently selected?
                            if( (nIndex = (ULONG)SendMessage( pcwd->hWndFormatListBox, CB_GETCURSEL, 0, 0 )) != CB_ERR )
                            {
                                // Send this image to the clipboard
                                IconImageToClipBoard( &(pcwd->pIR->IconImages[nIndex]) );
                            }
                        }
                    }
                    break; // End WM_COMMAND -> ID_EDIT_COPY

                // The filename has changed, update the window title
                case ID_UPDATETITLE:
                    {
                        TCHAR            szFileTitle[MAX_PATH] = {0};
                        PCHILDWINDOWDATA pcwd                  = NULL;

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data
                        if( pcwd != NULL )
                        {
                            // including an icon resource
                            if( pcwd->pIR != NULL )
                            {
                                // The calculate and set the new title
                                if( GetFileTitle( pcwd->pIR->szOriginalICOFileName, szFileTitle, MAX_PATH ) == 0 )
                                {
                                    SetWindowText( hWnd, szFileTitle );
                                }
                            }
                        }
                    }
                    break; // End WM_COMMAND -> ID_UPDATETITLE

                // How many image formats in the icon resource? (return that number)
                case ID_GETNUMFORMATS:
                    {
                        PCHILDWINDOWDATA pcwd = NULL;
                        UINT             nNum = 0;

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data
                        if( pcwd != NULL )
                        {
                            // If we have a listbox, get its count, else 0
                            if( pcwd->hWndFormatListBox != NULL )
                            {
                                nNum = (UINT)SendMessage( pcwd->hWndFormatListBox, CB_GETCOUNT, 0, 0 );
                            }
                            else
                            {
                                nNum = 0;
                            }
                            
                            // If an error occurred, default to 0
                            if( nNum == (UINT)CB_ERR )
                            {
                                nNum = 0;
                            }
                        }
                        // Send it back
                        return nNum;
                    }
                    break; // End WM_COMMAND -> ID_GETNUMFORMATS

                // Has this icon resource changed? return TRUE=yes, FALSE=no
                case ID_HASFILECHANGED:
                    {
                        PCHILDWINDOWDATA pcwd = NULL;
                        UINT             nRet = 0;

                        // Get the data associated this window 
                        pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA );
                        // If we have some data
                        if( pcwd != NULL )
                        {
                            // And it includes an icon resource
                            if( pcwd->pIR != NULL )
                            {
                                // then check whether it has changed
                                return pcwd->pIR->bHasChanged == TRUE;
                            }
                        }
                        // Otherwise, return FALSE
                        return nRet;
                    }
                    break; // End WM_COMMAND -> ID_HASFILECHANGED

                // Handle selection changes, etc from listbox
                case ID_FORMAT_BOX:
                    switch( HIWORD(wParam) )
                    {
                        // If a selection is made, or changes, repaint
                        case CBN_SELCHANGE: /* fall-through */
                        case CBN_SELENDOK:
                            InvalidateRect( hWnd, NULL, TRUE );
                            break;
                    }
                    break; // End WM_COMMAND -> ID_FORMAT_BOX
            
                // User wants to save the ICO file
                case ID_FILE_SAVEAS: /* fall-through */
                case ID_FILE_SAVE:
                {
                    TCHAR	         szFileName[MAX_PATH] = {0};
                    PCHILDWINDOWDATA pcwd                 = NULL;

                    // Get the data associated this window 
                    if( ( pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA ) ) != NULL )
                    {
                        // See if it includes an icon resource
                        if( pcwd->pIR != NULL )
                        {
                            HCURSOR	hOldCursor = NULL;

                            // This might take a while :(
                            hOldCursor = SetCursor( LoadCursor(NULL,IDC_WAIT) );

                            // If we have an original filename, and user did *NOT* 'Save As'
                            if( ( lstrlen(pcwd->pIR->szOriginalICOFileName) > 0 ) && (LOWORD(wParam)!=ID_FILE_SAVEAS) )
                            {
                                // The just write it out
                                WriteIconToICOFile( pcwd->pIR, pcwd->pIR->szOriginalICOFileName );
                                // which, of course, brings it up to date
                                pcwd->pIR->bHasChanged = FALSE;
                            }
                            else
                            {
                                // Either we have no name, or user hit 'Save As'
                                if( GetSaveIconFileName( szFileName, IDS_FILTERSTRING, LOWORD(wParam)==ID_FILE_SAVE?TEXT("Save Icon File"):TEXT("Save Icon File As") ) )
                                {
                                    // So, write it out
                                    WriteIconToICOFile( pcwd->pIR, szFileName );
                                    // Update the name associated with the resource
                                    lstrcpyn( pcwd->pIR->szOriginalICOFileName, szFileName, MAX_PATH - 1 );
                                    // Inform window to update title
                                    SendMessage( hWnd, WM_COMMAND, ID_UPDATETITLE, 0 );
                                    // and, of course, it is now up to date
                                    pcwd->pIR->bHasChanged = FALSE;
                                }
                            }
                            SetCursor( hOldCursor );
                        }
                        else
                        {
                            MessageBox( hWnd, TEXT("Error Getting Icon Info - File Not Saved"), TEXT("Error"), MB_OK );
                        }
                    }
                }
                break; // End WM_COMMAND -> ID_FILE_SAVE/ID_FILE_SAVEAS
            }
            break; // End WM_COMMAND
    }
    return DefMDIChildProc( hWnd, Msg, wParam, lParam );
}
/* End IconChildWndProc() **************************************************/




/****************************************************************************
*
*     FUNCTION: Draw3DRect
*
*     PURPOSE:  draws a rectangle in 3d colors
*
*     PARAMS:   HDC hDC      - The DC on which to draw
*               RECT Rect    - The rectangle itself
*               BOOL bSunken - TRUE  = rect should look sunken
*                              FALSE = rect should look raised
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL Draw3DRect( 
    HDC hDC, 
    RECT Rect, 
    BOOL bSunken )
{
    HBRUSH	hBrush  = NULL;
    HPEN    hPen    = NULL;
    HPEN    hOldPen = NULL;

    // Get the color for the main foreground
    hBrush = CreateSolidBrush( GetSysColor(COLOR_3DFACE) );
    // paint it
    FillRect( hDC, &Rect, hBrush );
    DeleteObject( hBrush );
    // Get the pen for the top and left sides
    if( bSunken )
    {
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW) );
    }
    else
    {
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT) );
    }
    hOldPen = SelectObject( hDC, hPen);
    // Draw the top and left sides
    MoveToEx( hDC, Rect.right, Rect.top, NULL );
    LineTo( hDC, Rect.left, Rect.top );
    LineTo( hDC, Rect.left, Rect.bottom );
    SelectObject( hDC, hOldPen);
    DeleteObject( hPen );
    // Get the pen for the bottom and right sides
    if( bSunken )
    {
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT) );
    }
    else
    {
        hPen = CreatePen( PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW) );
    }
    hOldPen = SelectObject( hDC, hPen);
    // Draw the bottom and right sides
    LineTo( hDC, Rect.right, Rect.bottom );
    LineTo( hDC, Rect.right, Rect.top );
    SelectObject( hDC, hOldPen);
    DeleteObject( hPen );
    return TRUE;
}
/* End Draw3DRect() *******************************************************/




/****************************************************************************
*
*     FUNCTION: EraseBackground
*
*     PURPOSE:  Draws the background for the MDI child
*
*     PARAMS:   HWND hWnd - The MDI window of interest
*               HDC  hDC  - The DC on which to draw
*
*     RETURNS:  void
*
* History:
*                July '95 - Created
*
\****************************************************************************/
void EraseBackground(
    HWND hWnd, 
    HDC hDC )
{
    RECT                Rect     = {0};
    PCHILDWINDOWDATA	pcwd     = NULL;
    HBRUSH            	hBrush   = NULL;
    SIZE                TextSize = {0};

    // Just how big is this window?
    GetClientRect( hWnd, &Rect );
    // Paint the background
    Draw3DRect( hDC, Rect, FALSE );

    // If there is no icon resource yet, bail out
    if( ( pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA ) ) == NULL )
    {
        return;
    }
    // Draw 3d rectangles around areas of interest
    Draw3DRect( hDC, pcwd->WhiteRect, TRUE );
    Draw3DRect( hDC, pcwd->WhiteTextRect, TRUE );
    Draw3DRect( hDC, pcwd->BlackRect, TRUE );
    Draw3DRect( hDC, pcwd->BlackTextRect, TRUE );
    Draw3DRect( hDC, pcwd->XORRect, TRUE );
    Draw3DRect( hDC, pcwd->XORTextRect, TRUE );
    Draw3DRect( hDC, pcwd->ANDRect, TRUE );
    Draw3DRect( hDC, pcwd->ANDTextRect, TRUE );
    // Fill in the white area
    hBrush = GetStockObject( WHITE_BRUSH );
    SelectObject( hDC, hBrush );
    Rectangle( hDC, pcwd->WhiteRect.left, pcwd->WhiteRect.top, pcwd->WhiteRect.right, pcwd->WhiteRect.bottom );
    // Fill in the black area
    hBrush = GetStockObject( BLACK_BRUSH );
    SelectObject( hDC, hBrush );
    Rectangle( hDC, pcwd->BlackRect.left, pcwd->BlackRect.top, pcwd->BlackRect.right, pcwd->BlackRect.bottom );

    // Set texts for the various sections
    SetBkMode( hDC, TRANSPARENT );
    GetTextExtentPoint32( hDC, TEXT("Icon On Black"), 13, &TextSize );
    TextOut( hDC, pcwd->BlackTextRect.left + ((RectWidth(pcwd->BlackTextRect)-TextSize.cx)/2),
             pcwd->BlackTextRect.top + ((RectHeight(pcwd->BlackTextRect)-TextSize.cy)/2), 
             TEXT("Icon On Black"), 13 );
    GetTextExtentPoint32( hDC, TEXT("Icon On White"), 13, &TextSize );
    TextOut( hDC, pcwd->WhiteTextRect.left + ((RectWidth(pcwd->WhiteTextRect)-TextSize.cx)/2),
             pcwd->WhiteTextRect.top + ((RectHeight(pcwd->WhiteTextRect)-TextSize.cy)/2), 
             TEXT("Icon On White"), 13 );
    GetTextExtentPoint32( hDC, TEXT("XOR Mask"), 8, &TextSize );
    TextOut( hDC, pcwd->XORTextRect.left + ((RectWidth(pcwd->XORTextRect)-TextSize.cx)/2),
             pcwd->XORTextRect.top + ((RectHeight(pcwd->XORTextRect)-TextSize.cy)/2), 
             TEXT("XOR Mask"), 8 );
    GetTextExtentPoint32( hDC, TEXT("AND Mask"), 8, &TextSize );
    TextOut( hDC, pcwd->ANDTextRect.left + ((RectWidth(pcwd->ANDTextRect)-TextSize.cx)/2),
             pcwd->ANDTextRect.top + ((RectHeight(pcwd->ANDTextRect)-TextSize.cy)/2), 
             TEXT("AND Mask"), 8 );
}
/* End EraseBackground() ***************************************************/




/****************************************************************************
*
*     FUNCTION: CreateChildren
*
*     PURPOSE:  Create the listbox, fills it with entries
*
*     PARAMS:   HWND hWnd - The MDI window of interest
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CreateChildren( 
    HWND hWnd )
{
    RECT             ClientRect = {0};
    RECT             TempRect   = {0};
    PCHILDWINDOWDATA pcwd       = NULL;
    HDC              hDC        = NULL;
    SIZE             size       = {0};
    BOOL             bSuccess   = TRUE;

    // Get the data associated with this window
    if( (pcwd = (PCHILDWINDOWDATA)GetWindowLongPtr( hWnd, GWLP_USERDATA )) == NULL )
    {
        bSuccess = FALSE;
        goto exit_func;
    }
    
    // Just how big is this window?
    GetClientRect( hWnd, &ClientRect );
    // Calculate listbox size and position
    SetRect( &(pcwd->BoxRect), 10, ClientRect.bottom-30, (MAX_ICON_WIDTH*2)+14, ClientRect.bottom+50 );
    // Create the listbox
    if((pcwd->hWndFormatListBox=CreateChildListBox( hWnd, ID_FORMAT_BOX, &(pcwd->BoxRect) )) == NULL )
    {
        bSuccess = FALSE;
        goto exit_func;
    }
    
    // If we have an icon resource
    if( pcwd->pIR != NULL )
    {
        UINT  i, nIndex;
        TCHAR szBuffer[256] = {0};

        // For each image in the resoure
        for(i=0;i<pcwd->pIR->nNumImages;i++)
        {
            // Add the type of the image to the listbox
            wsprintf( szBuffer, TEXT("%dx%d, %d Bit Color"), pcwd->pIR->IconImages[i].Width, 
                        pcwd->pIR->IconImages[i].Height, pcwd->pIR->IconImages[i].Colors );
            nIndex = (ULONG)SendMessage( pcwd->hWndFormatListBox, CB_ADDSTRING, 0, (LPARAM)szBuffer );
        }
        // Select the first entry
        SendMessage( pcwd->hWndFormatListBox, 	CB_SETCURSEL, (WPARAM)0, (LPARAM)0 );
    }
    // Adjust the box size based on the listbox's real size
    GetClientRect( pcwd->hWndFormatListBox, &TempRect );
    pcwd->BoxRect.bottom = pcwd->BoxRect.top + TempRect.bottom;

    // How big is text these days?
    hDC = GetDC( hWnd );
    GetTextExtentPoint32( hDC, TEXT("Icon on Black"), 13, &size );
    ReleaseDC( hWnd, hDC );

    // Set the rectangles for the various squares to be drawn later
#define DIVIDER 5
    SetRect( &(pcwd->DrawingRect), 10, 10, (MAX_ICON_WIDTH*2)+14, 20 + (MAX_ICON_HEIGHT*2) + (TempRect.bottom*2) );
    SetRect( &(pcwd->BlackRect), pcwd->DrawingRect.left, pcwd->DrawingRect.top, pcwd->DrawingRect.left + MAX_ICON_WIDTH + 1, pcwd->DrawingRect.top + MAX_ICON_HEIGHT + 1 );
    SetRect( &(pcwd->BlackTextRect), pcwd->BlackRect.left, pcwd->BlackRect.bottom+1, pcwd->BlackRect.right, pcwd->BlackRect.bottom + TempRect.bottom + 1 );
    SetRect( &(pcwd->WhiteRect), pcwd->BlackRect.right+1, pcwd->BlackRect.top, pcwd->DrawingRect.right, pcwd->BlackRect.bottom );
    SetRect( &(pcwd->WhiteTextRect), pcwd->WhiteRect.left, pcwd->WhiteRect.bottom+1, pcwd->WhiteRect.right, pcwd->WhiteRect.bottom + TempRect.bottom + 1 );
    SetRect( &(pcwd->XORRect),	pcwd->BlackTextRect.left, pcwd->BlackTextRect.bottom + 1 + DIVIDER, pcwd->BlackRect.right, pcwd->BlackTextRect.bottom + 2 + DIVIDER + MAX_ICON_HEIGHT ); 
    SetRect( &(pcwd->XORTextRect),	pcwd->XORRect.left, pcwd->XORRect.bottom + 1, pcwd->XORRect.right, pcwd->DrawingRect.bottom ); 
    SetRect( &(pcwd->ANDRect),	pcwd->WhiteTextRect.left, pcwd->WhiteTextRect.bottom + 1 + DIVIDER, pcwd->WhiteRect.right, pcwd->WhiteTextRect.bottom + 2 + DIVIDER + MAX_ICON_HEIGHT ); 
    SetRect( &(pcwd->ANDTextRect),	pcwd->ANDRect.left, pcwd->ANDRect.bottom + 1, pcwd->ANDRect.right, pcwd->DrawingRect.bottom ); 
#undef DIVIDER

exit_func:
    return bSuccess;
}
/* End CreateChildren() ****************************************************/




/****************************************************************************
*
*     FUNCTION: CreateChildListBox
*
*     PURPOSE:  Creates a listbox and shows it
*
*     PARAMS:   HWND   hWndParent - The MDI window to be a parent
*               UINT   ID         - the ID of the new listbox
*               PRECT  pRect      - the RECT for the listbox
*
*     RETURNS:  HWND - handle to listbox window, NULL for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
HWND CreateChildListBox( 
    HWND hWndParent, 
    UINT ID, 
    PRECT pRect )
{
    HWND hWnd;

    hWnd = CreateWindow( TEXT("COMBOBOX"), TEXT(""), CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | WS_CHILD | WS_VSCROLL,
                        pRect->left, pRect->top, 
                        pRect->right - pRect->left + 1, pRect->bottom - pRect->top + 1,
                        hWndParent, (HMENU)(LONG_PTR)ID, hInst, 0 );
    if( hWnd != NULL )
    {
        ShowWindow( hWnd, SW_SHOW );
    }
    return hWnd;
}
/* End CreateChildListBox() ************************************************/




/****************************************************************************
*
*     FUNCTION: AddFormatDlgProc
*
*     PURPOSE:  Dialog Procedure for "Add Format" dialog
*
*     PARAMS:   HWND hWnd     - This dialog's window handle
*               UINT Msg      - Which Message?
*               WPARAM wParam - message parameter
*               LPARAM lParam - message parameter
*
*     RETURNS:  BOOL - TRUE for OK, FALSE for Cancel
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CALLBACK AddFormatDlgProc( 
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam )
{
    // Support all DIB color formats known at this time
    #define MAX_COLOR_FORMAT    5
    TCHAR	ColorFormats[MAX_COLOR_FORMAT+1][20] = { TEXT("Monochrome (1bpp)"), TEXT("16 Color (4bpp)"), TEXT("256 Color (8bpp)"),
                                    TEXT("16 Bit Color"), TEXT("24 Bit Color"), TEXT("32 Bit Color") };
    UINT    Bits[MAX_COLOR_FORMAT+1] = { 1, 4, 8, 16, 24, 32 };
    static	bSquareOnly = TRUE;
    static	LPARAM lInitParam;


    switch( Msg )
    {
        // Dialog is being initialized
        case WM_INITDIALOG:
            {
                TCHAR szBuffer[100] = {0};

                // We are passed a pointer to a LPICONIMAGE in lParam, save it
                lInitParam = lParam;
                // Set the range and position of the sliders
                SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(MIN_ICON_WIDTH,MAX_ICON_WIDTH) );
                SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)MIN_ICON_WIDTH );
                wsprintf( szBuffer, TEXT("%d Width"), MIN_ICON_WIDTH );
                SetDlgItemText( hWnd, ID_WIDTHTEXT, szBuffer );
                SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(MIN_ICON_HEIGHT,MAX_ICON_HEIGHT) );
                SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)MIN_ICON_HEIGHT );
                wsprintf( szBuffer, TEXT("%d Height"), MIN_ICON_HEIGHT );
                SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                SendDlgItemMessage( hWnd, ID_COLORSLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0,MAX_COLOR_FORMAT) );
                SendDlgItemMessage( hWnd, ID_COLORSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)2);
                SetDlgItemText( hWnd, ID_COLORTEXT, ColorFormats[2] );
                CheckDlgButton( hWnd, IDC_SQUAREONLY, bSquareOnly );
            }
            break; // End WM_INITDIALOG

        // Scroll message from the sliders
        case WM_HSCROLL:
            {
                int	nPos;
                TCHAR szBuffer[100] = {0};

                // Get the current position
                if( ( LOWORD(wParam) == TB_THUMBPOSITION ) || ( LOWORD(wParam) == TB_THUMBTRACK ) )
                    nPos = HIWORD( wParam );
                else
                    nPos = (int)SendMessage( (HWND)lParam, TBM_GETPOS, 0, 0 );
                // Was it the width slider?
                if( (HWND)lParam == GetDlgItem( hWnd, ID_WIDTHSLIDER) )
                {
                    // Update the text
                    wsprintf( szBuffer, TEXT("%d Width"), nPos );
                    SetDlgItemText( hWnd, ID_WIDTHTEXT, szBuffer );
                    // If dealing with width=height, adjust height too
                    if( bSquareOnly )
                    {
                        SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)nPos );
                        wsprintf( szBuffer, TEXT("%d Height"), nPos );
                        SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                    }
                }
                else
                {
                    // Was it the height slider?
                    if( (HWND)lParam == GetDlgItem( hWnd, ID_HEIGHTSLIDER) )
                    {
                        // Update the text
                        wsprintf( szBuffer, TEXT("%d Height"), nPos );
                        SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                        // If dealing with width=height, adjust width too
                        if( bSquareOnly )
                        {
                            SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)nPos );
                            wsprintf( szBuffer, TEXT("%d Width"), nPos );
                            SetDlgItemText( hWnd, ID_WIDTHTEXT, szBuffer );
                        }
                    }
                    else
                    {
                        // Was it the color slider?
                        if( (HWND)lParam == GetDlgItem( hWnd, ID_COLORSLIDER) )
                        {
                            // Update the text
                            SetDlgItemText( hWnd, ID_COLORTEXT, ColorFormats[nPos] );
                        }
                    }
                }
            }
            break; // End WM_HSCROLL

        // Time to say 'goodbye'
        case WM_CLOSE:
            PostMessage( hWnd, WM_COMMAND, IDCANCEL, 0l );
            break; // End WM_CLOSE


        // Messages from user items - checkboxes etc
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                // Checkbox for width=height restriction
                case IDC_SQUAREONLY:
                    // Is it checked now?
                    bSquareOnly = IsDlgButtonChecked( hWnd, IDC_SQUAREONLY );
                    // If it is, set height equal to width
                    if( bSquareOnly )
                    {
                        int nPos;
                        TCHAR szBuffer[100] = {0};

                        nPos = (int)SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_GETPOS, 0, 0 );
                        SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)nPos );
                        wsprintf( szBuffer, TEXT("%d Height"), nPos );
                        SetDlgItemText( hWnd, ID_HEIGHTTEXT, szBuffer );
                    }
                    break; // End IDC_SQUAREONLY

                // Add Format button has been pressed
                case IDOK:
                    {
                        PICONIMAGE pii = NULL;

                        // Were we passed a valid PICONIMAGE pointer?
                        if( ((PICONIMAGE)lInitParam) != NULL )
                        {
                            // allocate the new ICONIMAGE
                            if( (pii = malloc( sizeof( ICONIMAGE ) )) == FALSE )
                            {
                                EndDialog( hWnd, FALSE );
                            }
                            else
                            {
                                // initialize it
                                ZeroMemory( pii, sizeof( ICONIMAGE ) );
                                pii->Width = (UINT)SendDlgItemMessage( hWnd, ID_WIDTHSLIDER, TBM_GETPOS, 0, 0 );
                                pii->Height = (UINT)SendDlgItemMessage( hWnd, ID_HEIGHTSLIDER, TBM_GETPOS, 0, 0 );
                                pii->Colors = Bits[SendDlgItemMessage( hWnd, ID_COLORSLIDER, TBM_GETPOS, 0, 0 )];
                                // update the pointer that we were passed
                                *(PICONIMAGE *)lInitParam = pii;
                                // bail
                                EndDialog( hWnd, TRUE );
                            }
                        }
                        else
                        {
                            // bail
                            EndDialog( hWnd, FALSE );
                        }
                    }
                    break; // End IDOK

                // Time to cancel
                case IDCANCEL:
                    EndDialog( hWnd, FALSE );
                    break; // End IDCANCEL
            }
            break;
            
        default:
            return FALSE;
            break;
    }
    
    return TRUE;
    #undef MAX_COLOR_FORMAT
}
/* End AddFormatDlgProc() ************************************************/
