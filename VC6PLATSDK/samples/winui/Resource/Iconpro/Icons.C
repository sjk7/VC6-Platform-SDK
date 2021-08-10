	/****************************************************************************\
*            
*     FILE:     ICONS.C
*
*     PURPOSE:  IconPro Project Icon handing Code C file
*
*     COMMENTS: This file contains the icon handling code
*
*     FUNCTIONS:
*      EXPORTS: 
*               ReadIconFromICOFile        - Reads Icon from ICO file
*               WriteIconToICOFile         - Writes Icon to ICO file
*               MakeIconFromResource       - Makes HICON from a resource
*               ReadIconFromEXEFile        - Reads Icon from a EXE or DLL file
*               IconImageToClipBoard       - Puts icon image on clipboard
*               IconImageFromClipBoard     - Gets icon image from clipboard
*               CreateBlankNewFormatIcon   - Makes a new, blank icon image
*               DrawXORMask                - Draws XOR mask using DIBs
*               DrawANDMask                - Draws AND mask using DIBs
*               GetXORImageRect            - Calculates XOR image position
*               MakeNewANDMaskBasedOnPoint - Calculates new AND mask
*               ConvertBMPFileToIcon       - Converts BMP to Icon
*               IconImageToBMPFile         - Writes an icon image to BMP file
*      LOCALS:
*               ReadICOHeader              - Reads ICO file header
*               AdjustIconImagePointers    - Adjusts internal pointers
*               ExtractDlgProc             - Dlg Proc for extract dialog
*               MyEnumProcedure            - For EnumResourceNames()
*               GetIconFromInstance        - Extracts Icon from Instance
*               ChooseIconFromEXEFile      - Gets a user's choice icon from file
*               WriteICOHeader             - Writes ICO file header
*               CalculateImageOffset       - Calcs offset in file of image
*               DIBToIconImage             - Converts DIB to icon image
*
*     Copyright 1995 - 2000 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/
#include <Windows.h>
#include <commdlg.h>
#include <malloc.h>
#include <tchar.h>
#include "Resource.h"
#include "IconPro.h"
#include "Icons.H"
#include "Dib.H"


/****************************************************************************/
// Structs used locally (file scope)
// Resource Position info - size and offset of a resource in a file
typedef struct
{
    DWORD	dwBytes;
    DWORD	dwOffset;
} RESOURCEPOSINFO, *PRESOURCEPOSINFO;

// EXE/DLL icon information - filename, instance handle and ID
typedef struct
{
    PCTSTR    	szFileName;
    HINSTANCE	hInstance;
    PTSTR    	pID;
} EXEDLLICONINFO, *PEXEDLLICONINFO;
/****************************************************************************/


/****************************************************************************/
// External Globals
extern HINSTANCE    hInst;
extern HWND        	hWndMain;
/****************************************************************************/

/****************************************************************************/
// Prototypes for local functions
UINT ReadICOHeader( HANDLE hFile );
BOOL AdjustIconImagePointers( ICONIMAGE* pImage );
BOOL CALLBACK ExtractDlgProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
BOOL CALLBACK MyEnumProcedure( HANDLE  hModule, PCTSTR  pszType, PTSTR  pszName, LPARAM  lParam );
HICON GetIconFromInstance( HINSTANCE hInstance, PTSTR nIndex );
PTSTR ChooseIconFromEXEFile( PEXEDLLICONINFO pEDII );
BOOL WriteICOHeader( HANDLE hFile, UINT nNumEntries );
DWORD CalculateImageOffset( ICONRESOURCE* pIR, UINT nIndex );
BOOL DIBToIconImage( ICONIMAGE* pii, PBYTE pDIB, BOOL bStretch );
/****************************************************************************/



/****************************************************************************
*
*     FUNCTION: MakeIconFromResource
*
*     PURPOSE:  Makes an HICON from an icon resource
*
*     PARAMS:   ICONIMAGE* pIcon - pointer to the icon resource
*
*     RETURNS:  HICON - handle to the new icon, NULL for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
HICON MakeIconFromResource ( 
    ICONIMAGE* pIcon )
{
    HICON  hIcon = NULL;

    // Sanity Check
    if( pIcon == NULL )
    {
        return NULL;
    }
    
    if( pIcon->pBits == NULL )
    {
        return NULL;
    }
    
    // Let the OS do the real work :)
    hIcon = CreateIconFromResourceEx( pIcon->pBits, pIcon->dwNumBytes, TRUE, 0x00030000, 
            (*(PBITMAPINFOHEADER)(pIcon->pBits)).biWidth, (*(PBITMAPINFOHEADER)(pIcon->pBits)).biHeight/2, 0 );
    
    // It failed, odds are good we're on NT so try the non-Ex way
    if( hIcon == NULL )
    {
        // We would break on NT if we try with a 16bpp image
        if(pIcon->pbi->bmiHeader.biBitCount != 16)
        {	
            hIcon = CreateIconFromResource( pIcon->pBits, pIcon->dwNumBytes, TRUE, 0x00030000 );
        }
    }
    return hIcon;
}
/* End MakeIconFromResource() **********************************************/





/****************************************************************************
*
*     FUNCTION: ReadIconFromICOFile
*
*     PURPOSE:  Reads an Icon Resource from an ICO file
*
*     PARAMS:   PCTSTR szFileName - Name of the ICO file
*
*     RETURNS:  PICONRESOURCE - pointer to the resource, NULL for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
ICONRESOURCE* ReadIconFromICOFile (
    PCTSTR szFileName )
{
    ICONRESOURCE*       pIR = NULL;
    ICONRESOURCE*       pNew = NULL;
    HANDLE            	hFile = NULL;
    PRESOURCEPOSINFO    pRPI = NULL;
    UINT                i;
    DWORD            	dwBytesRead;
    ICONDIRENTRY*       pIDE = NULL;


    // Open the file
    if( (hFile = CreateFile( szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL )) == INVALID_HANDLE_VALUE )
    {
        MessageBox( hWndMain, TEXT("Error Opening File for Reading"), szFileName, MB_OK );
        return NULL;
    }
    // Allocate memory for the resource structure
    if( (pIR = malloc( sizeof(ICONRESOURCE) )) == NULL )
    {
        MessageBox( hWndMain, TEXT("Error Allocating Memory"), szFileName, MB_OK );
        CloseHandle( hFile );
        return NULL;
    }
    // Read in the header
    if( (pIR->nNumImages = ReadICOHeader( hFile )) == (UINT)-1 )
    {
        MessageBox( hWndMain, TEXT("Error Reading File Header"), szFileName, MB_OK );
        CloseHandle( hFile );
        free( pIR );
        return NULL;
    }
    // Adjust the size of the struct to account for the images
    if( (pNew = realloc( pIR, sizeof(ICONRESOURCE) + ((pIR->nNumImages-1) * sizeof(ICONIMAGE)) )) == NULL )
    {
        MessageBox( hWndMain, TEXT("Error Allocating Memory"), szFileName, MB_OK );
        CloseHandle( hFile );
        free( pIR );
        return NULL;
    }
    pIR = pNew;
    // Store the original name
    lstrcpyn( pIR->szOriginalICOFileName, szFileName, MAX_PATH - 1);
    lstrcpyn( pIR->szOriginalDLLFileName, TEXT(""), MAX_PATH - 1 );
    // Allocate enough memory for the icon directory entries
    if( (pIDE = malloc( pIR->nNumImages * sizeof( ICONDIRENTRY ) ) ) == NULL )
    {
        MessageBox( hWndMain, TEXT("Error Allocating Memory"), szFileName, MB_OK );
        CloseHandle( hFile );
        free( pIR );
        return NULL;
    }
    // Read in the icon directory entries
    if( ! ReadFile( hFile, pIDE, pIR->nNumImages * sizeof( ICONDIRENTRY ), &dwBytesRead, NULL ) )
    {
        MessageBox( hWndMain, TEXT("Error Reading File"), szFileName, MB_OK );
        CloseHandle( hFile );
        free( pIR );
        return NULL;
    }
    if( dwBytesRead != pIR->nNumImages * sizeof( ICONDIRENTRY ) )
    {
        MessageBox( hWndMain, TEXT("Error Reading File"), szFileName, MB_OK );
        CloseHandle( hFile );
        free( pIR );
        return NULL;
    }
    // Loop through and read in each image
    for( i = 0; i < pIR->nNumImages; i++ )
    {
        // Allocate memory for the resource
        if( (pIR->IconImages[i].pBits = malloc(pIDE[i].dwBytesInRes)) == NULL )
        {
            MessageBox( hWndMain, TEXT("Error Allocating Memory"), szFileName, MB_OK );
            CloseHandle( hFile );
            free( pIR );
            free( pIDE );
            return NULL;
        }
        pIR->IconImages[i].dwNumBytes = pIDE[i].dwBytesInRes;
        // Seek to beginning of this image
        if( SetFilePointer( hFile, pIDE[i].dwImageOffset, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
        {
            MessageBox( hWndMain, TEXT("Error Seeking in File"), szFileName, MB_OK );
            CloseHandle( hFile );
            free( pIR );
            free( pIDE );
            return NULL;
        }
        // Read it in
        if( ! ReadFile( hFile, pIR->IconImages[i].pBits, pIDE[i].dwBytesInRes, &dwBytesRead, NULL ) )
        {
            MessageBox( hWndMain, TEXT("Error Reading File"), szFileName, MB_OK );
            CloseHandle( hFile );
            free( pIR );
            free( pIDE );
            return NULL;
        }
        if( dwBytesRead != pIDE[i].dwBytesInRes )
        {
            MessageBox( hWndMain, TEXT("Error Reading File"), szFileName, MB_OK );
            CloseHandle( hFile );
            free( pIDE );
            free( pIR );
            return NULL;
        }
        // Set the internal pointers appropriately
        if( ! AdjustIconImagePointers( &(pIR->IconImages[i]) ) )
        {
            MessageBox( hWndMain, TEXT("Error Converting to Internal Format"), szFileName, MB_OK );
            CloseHandle( hFile );
            free( pIDE );
            free( pIR );
            return NULL;
        }
    }
    // Clean up	
    free( pIDE );
    free( pRPI );
    CloseHandle( hFile );
    return pIR;
}
/* End ReadIconFromICOFile() **********************************************/




/****************************************************************************
*
*     FUNCTION: AdjustIconImagePointers
*
*     PURPOSE:  Adjusts internal pointers in icon resource struct
*
*     PARAMS:   ICONIMAGE* pImage - the resource to handle
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL AdjustIconImagePointers (
    ICONIMAGE* pImage )
{
    // Sanity check
    if( pImage==NULL )
    {
        return FALSE;
    }
    
    // BITMAPINFO is at beginning of bits
    pImage->pbi = (PBITMAPINFO)pImage->pBits;
    // Width - simple enough
    pImage->Width = pImage->pbi->bmiHeader.biWidth;
    // Icons are stored in funky format where height is doubled - account for it
    pImage->Height = (pImage->pbi->bmiHeader.biHeight)/2;
    // How many colors?
    pImage->Colors = pImage->pbi->bmiHeader.biPlanes * pImage->pbi->bmiHeader.biBitCount;
    // XOR bits follow the header and color table
    pImage->pXOR = (PBYTE)FindDIBBits((PSTR)pImage->pbi);
    // AND bits follow the XOR bits
    pImage->pAND = pImage->pXOR + (pImage->Height*BytesPerLine((PBITMAPINFOHEADER)(pImage->pbi)));
    return TRUE;
}
/* End AdjustIconImagePointers() *******************************************/




/****************************************************************************
*
*     FUNCTION: ReadICOHeader
*
*     PURPOSE:  Reads the header from an ICO file
*
*     PARAMS:   HANDLE hFile - handle to the file
*
*     RETURNS:  UINT - Number of images in file, -1 for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
UINT ReadICOHeader (
    HANDLE hFile )
{
    WORD    Input;
    DWORD	dwBytesRead;

    // Read the 'reserved' WORD
    if( ! ReadFile( hFile, &Input, sizeof( WORD ), &dwBytesRead, NULL ) )
        return (UINT)-1;
    // Did we get a WORD?
    if( dwBytesRead != sizeof( WORD ) )
        return (UINT)-1;
    // Was it 'reserved' ?   (ie 0)
    if( Input != 0 )
        return (UINT)-1;
    // Read the type WORD
    if( ! ReadFile( hFile, &Input, sizeof( WORD ), &dwBytesRead, NULL ) )
        return (UINT)-1;
    // Did we get a WORD?
    if( dwBytesRead != sizeof( WORD ) )
        return (UINT)-1;
    // Was it type 1?
    if( Input != 1 )
        return (UINT)-1;
    // Get the count of images
    if( ! ReadFile( hFile, &Input, sizeof( WORD ), &dwBytesRead, NULL ) )
        return (UINT)-1;
    // Did we get a WORD?
    if( dwBytesRead != sizeof( WORD ) )
        return (UINT)-1;
    // Return the count
    return Input;
}
/* End ReadICOHeader() ****************************************************/




/****************************************************************************
*
*     FUNCTION: MyEnumProcedure
*
*     PURPOSE:  Callback for enumerating resources in a DLL/EXE
*
*     PARAMS:   HANDLE  hModule  - Handle of the module
*               PCTSTR pszType   - Resource Type
*               PTSTR  pszName   - Resource Name
*               LONG    lParam   - Handle of ListBox to add name to
*
*     RETURNS:  BOOL - TRUE to continue, FALSE to stop
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CALLBACK MyEnumProcedure (
    HANDLE  hModule, 
    PCTSTR  pszType, 
    PTSTR  pszName, 
    LPARAM  lParam )	
{
    TCHAR	szBuffer[256] = {0};
    LONG    nIndex        = LB_ERR;
    PTSTR	pID           = NULL;

    // Name is from MAKEINTRESOURCE()
    if( HIWORD(pszName) == 0 )
    {
        wsprintf( szBuffer, TEXT("Icon [%d]"), (DWORD_PTR)pszName );
        pID = pszName;
    }
    else
    {
        // Name is string
        pID = _tcsdup( pszName );
        wsprintf( szBuffer, TEXT("Icon [%s]"), pID );
    }
    // Add it to the listbox
    nIndex = (LONG)SendDlgItemMessage( (HWND)lParam, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)(szBuffer) );
    // Set the item data to be the name of the resource so we can get it later
    SendDlgItemMessage( (HWND)lParam, IDC_LIST1, LB_SETITEMDATA, (WPARAM)nIndex, (LPARAM)pID );
    return TRUE;
}
/* End MyEnumProcedure() ***************************************************/



/****************************************************************************
*
*     FUNCTION: GetIconFromInstance
*
*     PURPOSE:  Callback for enumerating resources in a DLL/EXE
*
*     PARAMS:   HINSTANCE hInstance - Instance handle for this module
*               PTSTR    nIndex    - Resource index
*
*     RETURNS:  HICON - Handle to the icon, NULL for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
HICON GetIconFromInstance (
    HINSTANCE hInstance,
    PTSTR nIndex )
{
    HICON	hIcon   = NULL;
    HRSRC	hRsrc   = NULL;
    HGLOBAL	hGlobal = NULL;
    PVOID	pRes    = NULL;
    int    	nID;

    // Find the group icon
    if( (hRsrc = FindResource( hInstance, nIndex, RT_GROUP_ICON )) == NULL )
        return NULL;
    if( (hGlobal = LoadResource( hInstance, hRsrc )) == NULL )
        return NULL;
    if( (pRes = LockResource(hGlobal)) == NULL )
        return NULL;

    // Find this particular image
    nID = LookupIconIdFromDirectory( pRes, TRUE );
    if( (hRsrc = FindResource( hInstance, MAKEINTRESOURCE(nID), RT_ICON )) == NULL )
        return NULL;
    if( (hGlobal = LoadResource( hInstance, hRsrc )) == NULL )
        return NULL;
    if( (pRes = LockResource(hGlobal)) == NULL )
        return NULL;
    // Let the OS make us an icon
    hIcon = CreateIconFromResource( pRes, SizeofResource(hInstance,hRsrc), TRUE, 0x00030000 );
    return hIcon;
}
/* End GetIconFromInstance() ***********************************************/



/****************************************************************************
*
*     FUNCTION: ExtractDlgProc
*
*     PURPOSE:  Window Procedure for the Extract Dialog
*
*     PARAMS:   HWND hWnd     - This window handle
*               UINT Msg      - Which Message?
*               WPARAM wParam - message parameter
*               LPARAM lParam - message parameter
*
*     RETURNS:  BOOL - FALSE for cancel, TRUE for ok
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CALLBACK ExtractDlgProc (
    HWND hWnd, 
    UINT Msg, 
    WPARAM wParam, 
    LPARAM lParam )
{
    // Variable that holds info on this EXE/DLL
    static PEXEDLLICONINFO pEDII;

    switch( Msg )
    {
        // During Paint, we will draw the currently selected icon
        case WM_PAINT:
            {
                HDC         hDC      = NULL;
                PAINTSTRUCT ps       = {0};
                DWORD       nIndex;
                PTSTR       pIconID  = NULL;

                hDC = BeginPaint( hWnd, &ps );
                // Get the current selection
                if( (nIndex = (DWORD)SendDlgItemMessage( hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0 )) != CB_ERR )
                {
                    // Get the data associated with the current selection - its the icon name
                    if( (pIconID = (PTSTR)SendDlgItemMessage( hWnd, IDC_LIST1, LB_GETITEMDATA, nIndex, 0 )) != (PTSTR)CB_ERR )
                    {
                        RECT        Rect       = {0}; 
                        RECT        ButtonRect = {0};
                        RECT        DlgRect    = {0};
                        HWND        hWndButton = NULL;
                        HICON    	hIcon      = NULL;
                        ICONINFO    IconInfo   = {0};
                        BITMAP    	bm         = {0};
                        POINT    	UpperLeft  = {0};
                        POINT       LowerRight = {0};

                        // Make an Icon
                        hIcon = GetIconFromInstance( pEDII->hInstance, pIconID );
                        // Locate the icon
                        GetIconInfo( hIcon, &IconInfo );
                        GetObject( IconInfo.hbmColor, sizeof(BITMAP), &bm );
                        hWndButton = GetDlgItem( hWnd, IDCANCEL );
                        GetWindowRect( hWndButton, &ButtonRect );
                        GetWindowRect( hWnd, &DlgRect );
                        UpperLeft.x = ButtonRect.left;
                        UpperLeft.y = ButtonRect.bottom;
                        LowerRight.x = ButtonRect.right;
                        LowerRight.y = DlgRect.bottom;
                        ScreenToClient( hWnd, &UpperLeft );
                        ScreenToClient( hWnd, &LowerRight );
                        SetRect( &Rect, UpperLeft.x, UpperLeft.y, LowerRight.x, LowerRight.y );
                        // Draw it
                        DrawIcon( hDC, Rect.left + ((Rect.right - Rect.left - bm.bmWidth)/2), 
                                Rect.top + ((Rect.bottom - Rect.top - bm.bmHeight)/2), hIcon );
                        // Kill it
                        DestroyIcon( hIcon );
                    }
                }
                EndPaint( hWnd, &ps );
            }
            break; // End WM_PAINT

        // Dialog is being initialized
        case WM_INITDIALOG:
            {
                UINT    nCount;
                TCHAR	szBuffer[MAX_PATH]    = {0};
                TCHAR   szFileTitle[MAX_PATH] = {0};

                // Are we being sent data about an EXE/DLL?
                if( (pEDII = (PEXEDLLICONINFO)lParam) != NULL )
                {
                    // Set the title of the dialog to reflect the EXE/DLL filename
                    GetFileTitle( pEDII->szFileName, szFileTitle, MAX_PATH );
                    wsprintf( szBuffer, TEXT("Extract Icon [%s]"), szFileTitle );
                    SetWindowText( hWnd, szBuffer );
                    // Fill in the listbox with the icons available
                    if( ! EnumResourceNames( pEDII->hInstance, RT_GROUP_ICON, MyEnumProcedure, (LPARAM)hWnd ) )
                    {
                        MessageBox( hWnd, TEXT("Error Enumerating Icons"), TEXT("Error"), MB_OK );
                        PostMessage( hWnd, WM_CLOSE, 0, 0 );
                    }
                    SendDlgItemMessage( hWnd, IDC_LIST1, LB_SETCURSEL, 0, 0 );
                    // If we have <= 1, post an OK message
                    if( (nCount = (UINT)SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCOUNT, 0, 0)) == 1 )
                    {
                        PostMessage( hWnd, WM_COMMAND, IDOK, 0 );
                    }
                    // If there were no icons, let the user know
                    if( nCount == 0 )
                    {
                        MessageBox( hWnd, TEXT("No Icons in this File"), TEXT("Error"), MB_OK );
                        PostMessage( hWnd, WM_CLOSE, 0, 0 );
                    }
                }
                return FALSE;
            }
            break; // End WM_INITDIALOG

        // Shut 'er down
        case WM_CLOSE:
            PostMessage( hWnd, WM_COMMAND, IDCANCEL, 0l );
            break; // End WM_CLOSE

        // Children are sending messages
        case WM_COMMAND:
            switch( LOWORD(wParam) )
            {
                // Its the listbox, just redraw the icon
                case IDC_LIST1:
                    switch( HIWORD(wParam) )
                    {
                        case CBN_SELCHANGE: /* fall-through */
                        case CBN_SELENDOK:
                            InvalidateRect( hWnd, NULL, TRUE );
                        break;
                    }
                    break; // End IDC_LIST1

                // User has chosen an icon, shut it down
                case IDOK:
                    {
                        LONG nIndex;

                        pEDII->pID = NULL;
                        if( (nIndex = (LONG)SendDlgItemMessage( hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0 )) != LB_ERR )
                            pEDII->pID = (PTSTR)SendDlgItemMessage( hWnd, IDC_LIST1, LB_GETITEMDATA, nIndex, 0 );
                        EndDialog( hWnd, TRUE );
                    }
                    break; // End IDOK

                // BAIL!
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
}
/* End ExtractDlgProc() ****************************************************/




/****************************************************************************
*
*     FUNCTION: ChooseIconFromEXEFile
*
*     PURPOSE:  Ask the user which icon he/she wants from the DLL/EXE
*
*     PARAMS:   PEXEDLLICONINFO pEDII - info on this DLL/EXE
*
*     RETURNS:  PTSTR - pointer to the resource name
*
* History:
*                July '95 - Created
*
\****************************************************************************/
PTSTR ChooseIconFromEXEFile( 
    PEXEDLLICONINFO pEDII )
{
    // Just launch the dialog box and let it handle it
    if( DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_EXTRACTDLG), 
                        hWndMain, (DLGPROC)ExtractDlgProc, (LPARAM)(pEDII) ) )
    {
        // User chose 'Ok'
        return pEDII->pID;
    }
    // User chose 'Cancel', or an error occurred, fail the call
    return NULL;
}
/* End ChooseIconFromEXEFile() **********************************************/




/****************************************************************************
*
*     FUNCTION: ReadIconFromEXEFile
*
*     PURPOSE:  Load an Icon Resource from a DLL/EXE file
*
*     PARAMS:   PCTSTR szFileName - name of DLL/EXE file
*
*     RETURNS:  PICONRESOURCE - pointer to icon resource
*
* History:
*                July '95 - Created
*
\****************************************************************************/
ICONRESOURCE* ReadIconFromEXEFile( 
    PCTSTR szFileName )
{
    ICONRESOURCE*  pIR      = NULL;
    HINSTANCE      hLibrary = NULL;
    PTSTR          pID      = NULL;
    EXEDLLICONINFO EDII     = {0};

    // Load the DLL/EXE - NOTE: must be a 32bit EXE/DLL for this to work
    if( (hLibrary = LoadLibraryEx( szFileName, NULL, LOAD_LIBRARY_AS_DATAFILE )) == NULL )
    {
        // Failed to load - abort
        MessageBox( hWndMain, TEXT("Error Loading File - Choose a 32bit DLL or EXE"), szFileName, MB_OK );
        return NULL;
    }
    // Store the info
    EDII.szFileName = szFileName;
    EDII.hInstance = hLibrary;
    // Ask the user, "Which Icon?"
    if( (pID = ChooseIconFromEXEFile( &EDII )) != NULL )
    {
        HRSRC       hRsrc   = NULL;
        HGLOBAL     hGlobal = NULL;
        MEMICONDIR* pIcon   = NULL;
        UINT        i;

        // Find the group icon resource
        if( (hRsrc = FindResource( hLibrary, pID, RT_GROUP_ICON )) == NULL )
        {
            FreeLibrary( hLibrary );
            return NULL;
        }
        if( (hGlobal = LoadResource( hLibrary, hRsrc )) == NULL )
        {
            FreeLibrary( hLibrary );
            return NULL;
        }
        if( (pIcon = LockResource(hGlobal)) == NULL )
        {
            FreeLibrary( hLibrary );
            return NULL;
        }
        // Allocate enough memory for the images
        if( (pIR = malloc( sizeof(ICONRESOURCE) + ((pIcon->idCount-1) * sizeof(ICONIMAGE)) )) == NULL )
        {
            MessageBox( hWndMain, TEXT("Error Allocating Memory"), szFileName, MB_OK );
            FreeLibrary( hLibrary );
            return NULL;
        }
        // Fill in local struct members
        pIR->nNumImages = pIcon->idCount;
        lstrcpyn( pIR->szOriginalDLLFileName, szFileName, MAX_PATH - 1 );
        lstrcpyn( pIR->szOriginalICOFileName, TEXT(""), MAX_PATH - 1 );
        // Loop through the images
        for( i = 0; i < pIR->nNumImages; i++ )
        {
            // Get the individual image
            if( (hRsrc = FindResource( hLibrary, MAKEINTRESOURCE(pIcon->idEntries[i].nID), RT_ICON )) == NULL )
            {
                free( pIR );
                FreeLibrary( hLibrary );
                return NULL;
            }
            if( (hGlobal = LoadResource( hLibrary, hRsrc )) == NULL )
            {
                free( pIR );
                FreeLibrary( hLibrary );
                return NULL;
            }
            // Store a copy of the resource locally
            pIR->IconImages[i].dwNumBytes = SizeofResource( hLibrary, hRsrc );
            pIR->IconImages[i].pBits = malloc( pIR->IconImages[i].dwNumBytes );
            memcpy( pIR->IconImages[i].pBits, LockResource( hGlobal ), pIR->IconImages[i].dwNumBytes );
            // Adjust internal pointers
            if( ! AdjustIconImagePointers( &(pIR->IconImages[i]) ) )
            {
                MessageBox( hWndMain, TEXT("Error Converting to Internal Format"), szFileName, MB_OK );
                free( pIR );
                FreeLibrary( hLibrary );
                return NULL;
            }
        }
    }
    FreeLibrary( hLibrary );
    return pIR;
}
/* End ReadIconFromEXEFile() ************************************************/



/****************************************************************************
*
*     FUNCTION: WriteICOHeader
*
*     PURPOSE:  Writes the header to an ICO file
*
*     PARAMS:   HANDLE hFile       - handle to the file
*               UINT   nNumEntries - Number of images in file
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL WriteICOHeader( 
    HANDLE hFile, 
    UINT nNumEntries )
{
    WORD    Output;
    DWORD	dwBytesWritten;
    BOOL    bRet = TRUE;

    // Write 'reserved' WORD
    Output = 0;
    if( ! WriteFile( hFile, &Output, sizeof( WORD ), &dwBytesWritten, NULL ) )
    {
        bRet = FALSE;
        goto exit_func;
    }
    
    // Did we write a WORD?
    if( dwBytesWritten != sizeof( WORD ) )
    {
        bRet = FALSE;
        goto exit_func;
    }
    
    // Write 'type' WORD (1)
    Output = 1;
    if( ! WriteFile( hFile, &Output, sizeof( WORD ), &dwBytesWritten, NULL ) )
    {
        bRet = FALSE;
        goto exit_func;
    }
    
    // Did we write a WORD?
    if( dwBytesWritten != sizeof( WORD ) )
    {
        bRet = FALSE;
        goto exit_func;
    }
    
    // Write Number of Entries
    Output = (WORD)nNumEntries;
    if( ! WriteFile( hFile, &Output, sizeof( WORD ), &dwBytesWritten, NULL ) )
    {
        bRet = FALSE;
        goto exit_func;
    }
    
    // Did we write a WORD?
    if( dwBytesWritten != sizeof( WORD ) )
    {
        bRet = FALSE;
        goto exit_func;
    }

exit_func:    
    return bRet;
}
/* End WriteICOHeader() ****************************************************/



/****************************************************************************
*
*     FUNCTION: CalculateImageOffset
*
*     PURPOSE:  Calculates the file offset for an icon image
*
*     PARAMS:   PICONRESOURCE pIR   - pointer to icon resource
*               UINT           nIndex - which image?
*
*     RETURNS:  DWORD - the file offset for that image
*
* History:
*                July '95 - Created
*
\****************************************************************************/
DWORD CalculateImageOffset( 
    ICONRESOURCE* pIR, 
    UINT nIndex )
{
    DWORD dwSize;
    UINT  i;

    // Calculate the ICO header size
    dwSize = 3 * sizeof(WORD);
    // Add the ICONDIRENTRY's
    dwSize += pIR->nNumImages * sizeof(ICONDIRENTRY);
    // Add the sizes of the previous images
    for(i=0;i<nIndex;i++)
    {
        dwSize += pIR->IconImages[i].dwNumBytes;
    }
    // we're there - return the number
    return dwSize;
}
/* End CalculateImageOffset() ***********************************************/




/****************************************************************************
*
*     FUNCTION: WriteIconToICOFile
*
*     PURPOSE:  Writes the icon resource data to an ICO file
*
*     PARAMS:   PICONRESOURCE pIR       - pointer to icon resource
*               PCTSTR        szFileName - name for the ICO file
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL WriteIconToICOFile( 
    ICONRESOURCE* pIR, 
    PCTSTR szFileName )
{
    HANDLE hFile = NULL;
    UINT   i;
    DWORD  dwBytesWritten;
    BOOL   bSuccess = TRUE;

    // open the file
    if( (hFile = CreateFile( szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL )) == INVALID_HANDLE_VALUE )
    {
        MessageBox( hWndMain, TEXT("Error Opening File for Writing"), szFileName, MB_OK );
        bSuccess = FALSE;
        goto exit_func;
    }
    
    // Write the header
    if( ! WriteICOHeader( hFile, pIR->nNumImages ) )
    {
        MessageBox( hWndMain, TEXT("Error Writing ICO File"), szFileName, MB_OK );
        CloseHandle( hFile );
        bSuccess = FALSE;
        goto exit_func;
    }
    
    // Write the ICONDIRENTRY's
    for( i=0; i<pIR->nNumImages; i++ )
    {
        ICONDIRENTRY ide = {0};

        // Convert internal format to ICONDIRENTRY
        ide.bWidth = (BYTE)pIR->IconImages[i].Width;
        ide.bHeight = (BYTE)pIR->IconImages[i].Height;
        ide.wPlanes = pIR->IconImages[i].pbi->bmiHeader.biPlanes;
        ide.wBitCount = pIR->IconImages[i].pbi->bmiHeader.biBitCount;
        if( (ide.wPlanes * ide.wBitCount) >= 8 )
        {
            ide.bColorCount = 0;
        }
        else
        {
            ide.bColorCount = (BYTE)(1 << (ide.wPlanes * ide.wBitCount));
        }
        ide.dwBytesInRes = pIR->IconImages[i].dwNumBytes;
        ide.dwImageOffset = CalculateImageOffset( pIR, i );
        // Write the ICONDIRENTRY out to disk
        if( ! WriteFile( hFile, &ide, sizeof( ICONDIRENTRY ), &dwBytesWritten, NULL ) )
        {
            bSuccess = FALSE;
            goto exit_func;
        }
        // Did we write a full ICONDIRENTRY ?
        if( dwBytesWritten != sizeof( ICONDIRENTRY ) )
        {
            bSuccess = FALSE;
            goto exit_func;
        }
    }
    // Write the image bits for each image
    for( i=0; i<pIR->nNumImages; i++ )
    {
        DWORD dwTemp = pIR->IconImages[i].pbi->bmiHeader.biSizeImage;

        // Set the sizeimage member to zero
        pIR->IconImages[i].pbi->bmiHeader.biSizeImage = 0;
        // Write the image bits to file
        if( ! WriteFile( hFile, pIR->IconImages[i].pBits, pIR->IconImages[i].dwNumBytes, &dwBytesWritten, NULL ) )
        {
            bSuccess = FALSE;
            goto exit_func;
        }
        
        if( dwBytesWritten != pIR->IconImages[i].dwNumBytes )
        {
            bSuccess = FALSE;
            goto exit_func;
        }
        // set it back
        pIR->IconImages[i].pbi->bmiHeader.biSizeImage = dwTemp;
    }
    CloseHandle( hFile );

exit_func:    
    return bSuccess;
}
/* End WriteIconToICOFile() **************************************************/


/****************************************************************************
*
*     FUNCTION: IconImageToClipBoard
*
*     PURPOSE:  Copies an icon image to the clipboard in CF_DIB format
*
*     PARAMS:   ICONIMAGE* pii - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL IconImageToClipBoard( 
    ICONIMAGE* pii )
{
    HANDLE hGlobal = NULL;
    PSTR   pBits   = NULL;

    // Open the clipboard
    if( OpenClipboard( hWndMain ) )
    {
        // empty it
        if( EmptyClipboard() )
        {
            // Make a buffer to send to clipboard
            hGlobal = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, pii->dwNumBytes );
            pBits = GlobalLock( hGlobal );
            // Copy the bits to the buffer
            memcpy( pBits, pii->pBits, pii->dwNumBytes );
            // Adjust for funky height*2 thing
            ((PBITMAPINFOHEADER)pBits)->biHeight /= 2;
            GlobalUnlock( hGlobal );
            // Send it to the clipboard
            SetClipboardData( CF_DIB, hGlobal );
            CloseClipboard();
            return TRUE;
        }
    }
    return FALSE;
}
/* End IconImageToClipBoard() ***********************************************/



/****************************************************************************
*
*     FUNCTION: IconImageFromClipBoard
*
*     PURPOSE:  Creates an icon image from the CF_DIB clipboard entry
*
*     PARAMS:   ICONIMAGE*  pii           - pointer to icon image data
*               BOOL        bStretchToFit - TRUE to stretch, FALSE to take
*                                           the upper left corner of the DIB
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL IconImageFromClipBoard( 
    ICONIMAGE* pii, 
    BOOL bStretchToFit )
{
    PBITMAPINFO pbi         = NULL;
    HANDLE      hClipGlobal = NULL;
    BOOL        bRet        = FALSE;

    // Open the clipboard
    if( OpenClipboard( hWndMain ) )
    {
        // Get the CF_DIB data from it
        if( (hClipGlobal = GetClipboardData( CF_DIB )) != NULL )
        {
            // Lock it down
            if( (pbi=GlobalLock(hClipGlobal)) != NULL )
            {
                // Convert it to an icon image
                bRet = DIBToIconImage( pii, (PBYTE)pbi, bStretchToFit );
                GlobalUnlock( hClipGlobal );
            }
        }
        CloseClipboard();
    }
    return bRet;
}
/* End IconImageFromClipBoard() ********************************************/



/****************************************************************************
*
*     FUNCTION: DIBToIconImage
*
*     PURPOSE:  Converts a CF_DIB memory block to an icon image
*
*     PARAMS:   ICONIMAGE* pii           - pointer to icon image data
*               PBYTE      pDIB          - a pointer to the CF_DIB block
*               BOOL       bStretchToFit - TRUE to stretch, FALSE to take
*                                          the upper left corner of the DIB
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL DIBToIconImage( 
    ICONIMAGE* pii, 
    PBYTE pDIB, 
    BOOL bStretch )
{
    PBYTE pNewDIB = NULL;

    // Sanity check
    if( pDIB == NULL )
    {
        return FALSE;
    }

    // Let the DIB engine convert color depths if need be
    pNewDIB = ConvertDIBFormat( (PBITMAPINFO)pDIB, pii->Width, pii->Height, pii->Colors, bStretch );

    // Now we have a cool new DIB of the proper size/color depth
    // Lets poke it into our data structures and be done with it

    // How big is it?
    pii->dwNumBytes = sizeof( BITMAPINFOHEADER )                        // Header
                    + PaletteSize( (PSTR)pNewDIB )                      // Palette
                    + pii->Height * BytesPerLine( (PBITMAPINFOHEADER)pNewDIB )  // XOR mask
                    + pii->Height * WIDTHBYTES( pii->Width );           // AND mask

    // If there was already an image here, free it
    if( pii->pBits != NULL )
    {
        free( pii->pBits );
    }
    
    // Allocate enough room for the new image
    if( (pii->pBits = malloc( pii->dwNumBytes )) == NULL )
    {
        free( pii );
        return FALSE;
    }
    // Copy the bits
    memcpy( pii->pBits, pNewDIB, sizeof( BITMAPINFOHEADER ) + PaletteSize( (PSTR)pNewDIB ) );
    // Adjust internal pointers/variables for new image
    pii->pbi = (PBITMAPINFO)(pii->pBits);
    pii->pbi->bmiHeader.biHeight *= 2;
    pii->pXOR = (PBYTE)FindDIBBits( (PSTR)(pii->pBits) );
    memcpy( pii->pXOR, FindDIBBits((PSTR)pNewDIB), pii->Height * BytesPerLine( (PBITMAPINFOHEADER)pNewDIB ) );
    pii->pAND = pii->pXOR + pii->Height * BytesPerLine( (PBITMAPINFOHEADER)pNewDIB );
    memset( pii->pAND, 0, pii->Height * WIDTHBYTES( pii->Width ) );
    // Free the source
    free( pNewDIB );
    return TRUE;
}
/* End DIBToIconImage() ***************************************************/




/****************************************************************************
*
*     FUNCTION: CreateBlankNewFormatIcon
*
*     PURPOSE:  Creates a blank icon image for a new format
*
*     PARAMS:   ICONIMAGE* pii  - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CreateBlankNewFormatIcon( 
    ICONIMAGE* pii )
{
    DWORD            dwFinalSize = 0;
    BITMAPINFOHEADER bmih        = {0};

    // Fill in the bitmap header
    ZeroMemory( &bmih, sizeof( BITMAPINFOHEADER ) );
    bmih.biSize = sizeof( BITMAPINFOHEADER );
    bmih.biBitCount = (WORD)pii->Colors;
    bmih.biClrUsed = 0;
    
    // How big will the final thing be?
    // Well, it'll have a header
    dwFinalSize = sizeof( BITMAPINFOHEADER );
    // and a color table (even if it's zero length)
    dwFinalSize += PaletteSize( (PSTR)&bmih );
    // and XOR bits
    dwFinalSize += pii->Height * WIDTHBYTES( pii->Width * pii->Colors );
    // and AND bits. That's about it :)
    dwFinalSize += pii->Height * WIDTHBYTES( pii->Width );

    // Allocate some memory for it
    pii->pBits = malloc( dwFinalSize );
    ZeroMemory( pii->pBits, dwFinalSize );
    pii->dwNumBytes = dwFinalSize;
    pii->pbi = (PBITMAPINFO)(pii->pBits);
    pii->pXOR = (PBYTE)(pii->pbi) + sizeof(BITMAPINFOHEADER) + PaletteSize( (PSTR)&bmih );
    pii->pAND = pii->pXOR + (pii->Height * WIDTHBYTES( pii->Width * pii->Colors ));

    // The bitmap header is zeros, fill it out
    pii->pbi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
    pii->pbi->bmiHeader.biWidth = pii->Width;
    // Don't forget the funky height*2 icon resource thing
    pii->pbi->bmiHeader.biHeight = pii->Height * 2; 
    pii->pbi->bmiHeader.biPlanes = 1; 
    pii->pbi->bmiHeader.biBitCount = (WORD)pii->Colors; 
    pii->pbi->bmiHeader.biCompression = BI_RGB; 
                   
    return TRUE;
}
/* End CreateBlankNewFormatIcon() ******************************************/



/****************************************************************************
*
*     FUNCTION: GetXORImageRect
*
*     PURPOSE:  Given a bounding Rect, calculates the XOR mask display Rect 
*
*     PARAMS:   RECT        Rect  - Bounding rect for drawing area
*               ICONIMAGE*  pIcon - pointer to icon image data
*
*     RETURNS:  RECT - the rect where the XOR image will be drawn
*
* History:
*                July '95 - Created
*
\****************************************************************************/
RECT GetXORImageRect( 
    RECT Rect, 
    ICONIMAGE* pIcon )
{
    RECT NewRect = {0};

    // Just center the thing in the bounding display rect
    NewRect.left = Rect.left + ((RectWidth(Rect)-pIcon->pbi->bmiHeader.biWidth)/2);
    NewRect.top = Rect.top + ((RectHeight(Rect)-(pIcon->pbi->bmiHeader.biHeight/2))/2);
    NewRect.bottom = NewRect.top + (pIcon->pbi->bmiHeader.biHeight/2);
    NewRect.right = NewRect.left + pIcon->pbi->bmiHeader.biWidth;
    return NewRect;
}
/* End GetXORImageRect() ***************************************************/




/****************************************************************************
*
*     FUNCTION: DrawXORMask
*
*     PURPOSE:  Using DIB functions, draw XOR mask on hDC in Rect
*
*     PARAMS:   HDC         hDC    - The DC on which to draw
*               RECT        Rect   - Bounding rect for drawing area
*               ICONIMAGE*  pIcon  - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*     COMMENTS: Does not use any palette information since the
*               OS won't when it draws the icon anyway.
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL DrawXORMask( 
    HDC hDC, 
    RECT Rect, 
    ICONIMAGE* pIcon )
{
    int x, y;

    // Sanity checks
    if( pIcon == NULL )
    {
        return FALSE;
    }
    
    if( pIcon->pBits == NULL )
    {
        return FALSE;
    }

    // Account for height*2 thing
    pIcon->pbi->bmiHeader.biHeight /= 2;

    // Locate it
    x = Rect.left + ((RectWidth(Rect)-pIcon->pbi->bmiHeader.biWidth)/2);
    y = Rect.top + ((RectHeight(Rect)-pIcon->pbi->bmiHeader.biHeight)/2);

    // Blast it to the screen
    SetDIBitsToDevice( hDC, x, y, pIcon->pbi->bmiHeader.biWidth, pIcon->pbi->bmiHeader.biHeight, 0, 0, 0, pIcon->pbi->bmiHeader.biHeight, pIcon->pXOR, pIcon->pbi, DIB_RGB_COLORS );

    // UnAccount for height*2 thing
    pIcon->pbi->bmiHeader.biHeight *= 2;

    return TRUE;
}
/* End DrawXORMask() *******************************************************/




/****************************************************************************
*
*     FUNCTION: DrawANDMask
*
*     PURPOSE:  Using DIB functions, draw AND mask on hDC in Rect
*
*     PARAMS:   HDC         hDC    - The DC on which to draw
*               RECT        Rect   - Bounding rect for drawing area
*               ICONIMAGE*  pIcon  - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL DrawANDMask( 
    HDC hDC, 
    RECT Rect, 
    ICONIMAGE* pIcon )
{
    PBITMAPINFO pbi = NULL;
    int         x, y;
    BOOL        bSuccess = TRUE;

    // Sanity checks
    if( pIcon == NULL )
    {
        bSuccess = FALSE;
        goto exit_func;
    }
    
    if( pIcon->pBits == NULL )
    {
        bSuccess = FALSE;
        goto exit_func;
    }

    // Need a bitmap header for the mono mask
    pbi = malloc( sizeof(BITMAPINFO) + (2 * sizeof( RGBQUAD )) );
    pbi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
    pbi->bmiHeader.biWidth = pIcon->pbi->bmiHeader.biWidth;
    pbi->bmiHeader.biHeight = pIcon->pbi->bmiHeader.biHeight/2;
    pbi->bmiHeader.biPlanes = 1;
    pbi->bmiHeader.biBitCount = 1;
    pbi->bmiHeader.biCompression = BI_RGB;
    pbi->bmiHeader.biSizeImage = 0;
    pbi->bmiHeader.biXPelsPerMeter = 0;
    pbi->bmiHeader.biYPelsPerMeter = 0;
    pbi->bmiHeader.biClrUsed = 0;
    pbi->bmiHeader.biClrImportant = 0;
    pbi->bmiColors[0].rgbRed = 0;
    pbi->bmiColors[0].rgbGreen = 0;
    pbi->bmiColors[0].rgbBlue = 0;
    pbi->bmiColors[0].rgbReserved = 0;
    pbi->bmiColors[1].rgbRed = 255;
    pbi->bmiColors[1].rgbGreen = 255;
    pbi->bmiColors[1].rgbBlue = 255;
    pbi->bmiColors[1].rgbReserved = 0;

    // Locate it
    x = Rect.left + ((RectWidth(Rect)-pbi->bmiHeader.biWidth)/2);
    y = Rect.top + ((RectHeight(Rect)-pbi->bmiHeader.biHeight)/2);

    // Blast it to the screen
    SetDIBitsToDevice( hDC, x, y, pbi->bmiHeader.biWidth, pbi->bmiHeader.biHeight, 0, 0, 0, pbi->bmiHeader.biHeight, pIcon->pAND, pbi, DIB_RGB_COLORS );

    // clean up
    free( pbi );

exit_func:
    return bSuccess;
}
/* End DrawANDMask() *******************************************************/




/****************************************************************************
*
*     FUNCTION: MakeNewANDMaskBasedOnPoint
*
*     PURPOSE:  Creates a new AND mask for the icon image
*
*     PARAMS:   ICONIMAGE* pIcon  - pointer to icon image data
*               POINT      pt     - coords of transparent pixel
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
*     COMMENTS: Creates the AND mask using the color of the pixel at pt
*               as a transparent color. The XOR mask is changed as well.
*               This is because the OS expects the XOR mask to have the
*               AND mask already applied (ie black in transparent areas)
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL MakeNewANDMaskBasedOnPoint( 
    ICONIMAGE* pIcon, 
    POINT pt )
{
    HBITMAP     hXORBitmap          = NULL;
    HBITMAP     hOldXORBitmap       = NULL;
    HDC         hDC                 = NULL;
    HDC         hMemDC1             = NULL;
    PBYTE       pXORBits            = NULL;
    COLORREF    crTransparentColor  = {0};
    LONG        i,j;


    // Account for height*2 thing
    pIcon->pbi->bmiHeader.biHeight /= 2;

    // Need a DC
    hDC = GetDC( NULL );

    // Use DIBSection for source
    hXORBitmap = CreateDIBSection( hDC, pIcon->pbi, DIB_RGB_COLORS, &pXORBits, NULL, 0  );
    memcpy( pXORBits, pIcon->pXOR, (pIcon->pbi->bmiHeader.biHeight) * BytesPerLine((PBITMAPINFOHEADER)(pIcon->pbi)) );
    hMemDC1 = CreateCompatibleDC( hDC );
    hOldXORBitmap = SelectObject( hMemDC1, hXORBitmap );

    // Set the color table if need be
    if( pIcon->pbi->bmiHeader.biBitCount <= 8 )
    {
        SetDIBColorTable( hMemDC1, 0, DIBNumColors((PSTR)(pIcon->pbi)), pIcon->pbi->bmiColors);
    }
    
    // What's the transparent color?
    crTransparentColor = GetPixel( hMemDC1, pt.x, pt.y );

    // Loop through the pixels
    for(i=0;i<pIcon->pbi->bmiHeader.biWidth;i++)
    {
        for(j=0;j<pIcon->pbi->bmiHeader.biHeight;j++)
        {
            // Is the source transparent at this point?
            if( GetPixel( hMemDC1, i, j ) == crTransparentColor )
            {
                // Yes, so set the pixel in AND mask, and clear it in XOR mask
                SetMonoDIBPixel( pIcon->pAND, pIcon->pbi->bmiHeader.biWidth, 
                                 pIcon->pbi->bmiHeader.biHeight, i, j, TRUE );     
                if( pIcon->pbi->bmiHeader.biBitCount == 1 )
                {
                    SetMonoDIBPixel( pXORBits, pIcon->pbi->bmiHeader.biWidth, 
                                     pIcon->pbi->bmiHeader.biHeight, i, j, FALSE );     
                }
                else
                {
                    SetPixelV( hMemDC1, i, j, RGB(0,0,0) );
                }
            }
            else
            {
                // No, so clear pixel in AND mask
                SetMonoDIBPixel( pIcon->pAND, pIcon->pbi->bmiHeader.biWidth, pIcon->pbi->bmiHeader.biHeight, i, j, FALSE );    
            }
        }
    }
    // Flush the SetPixelV() calls
    GdiFlush();

    SelectObject( hMemDC1, hOldXORBitmap );

    // Copy the new XOR bits back to our storage
    memcpy( pIcon->pXOR, pXORBits, (pIcon->pbi->bmiHeader.biHeight) * BytesPerLine((PBITMAPINFOHEADER)(pIcon->pbi)) );

    // Clean up
    DeleteObject( hXORBitmap );
    DeleteDC( hMemDC1 );
    ReleaseDC( NULL, hDC );


    // UnAccount for height*2 thing
    pIcon->pbi->bmiHeader.biHeight *= 2;
    return TRUE;
}
/* End MakeNewANDMaskBasedOnPoint() *****************************************/


/****************************************************************************
*
*     FUNCTION: IconImageFromBMPFile
*
*     PURPOSE:  Creates an icon image from a BMP file
*
*     PARAMS:   PCTSTR     szFileName     - Filename for BMP file
*               ICONIMAGE* pii            - pointer to icon image data
*               BOOL       bStretchToFit  - TRUE to stretch, FALSE to take
*                                           the upper left corner of the DIB
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL IconImageFromBMPFile( 
    PCTSTR szFileName, 
    ICONIMAGE* pii, 
    BOOL bStretchToFit )
{
    PBYTE   pDIB = NULL;
    BOOL    bRet = FALSE;

    if( (pDIB=ReadBMPFile(szFileName)) == NULL )
    {
        return FALSE;
    }
    
    // Convert it to an icon image
    bRet = DIBToIconImage( pii, pDIB, bStretchToFit );
    free( pDIB );
    return bRet;
}
/* End IconImageFromBMPFile() ********************************************/




/****************************************************************************
*
*     FUNCTION: IconImageToBMPFile
*
*     PURPOSE:  Creates BMP file from an icon image
*
*     PARAMS:   PCTSTR     szFileName   - Filename for BMP file
*               ICONIMAGE* pii          - pointer to icon image data
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL IconImageToBMPFile( 
    PCTSTR szFileName, 
    ICONIMAGE* pii )
{
    return WriteBMPFile( szFileName, (PBYTE)pii->pbi );
}

