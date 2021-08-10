/*******************************************************************************
 *                                                                             *
 *  MODULE      : OpenDIB.C                                                   *
 *                                                                             *
 *  DESCRIPTION : Routines for managing file open/save dialog                  *
 *                                                                             *
 *                                                                             *
 ******************************************************************************/  

#include <windows.h>
#include <stdio.h>
#include <commdlg.h>
#define IDC_IMAGE     1061
#define IDC_FILEINFO  1062
#define IDC_LOCATION  1119

LRESULT CALLBACK PreviewWindowHookProc(HWND, UINT, WPARAM, LPARAM);

// ****** Code for managing on-the-fly dialog template creation ****** 

int nCopyAnsiToWideChar (LPWORD lpWCStr, LPSTR lpAnsiIn, int size)
{
  int cchAnsi = lstrlen(lpAnsiIn);

  return MultiByteToWideChar(GetACP(), MB_PRECOMPOSED, lpAnsiIn, cchAnsi, lpWCStr, size/sizeof(WCHAR)) + 1;
}

LPWORD lpwAlign ( LPWORD lpIn)
{
  ULONG_PTR ul;

  ul = (ULONG_PTR) lpIn;
  ul +=3;
  ul >>=2;
  ul <<=2;
  return (LPWORD) ul;
}

LPWORD AddItemToTemplate(LPWORD lpw, 
                         int lpwSize,
						 DWORD dwStyle,
						 DWORD dwExtStyle,
						 WORD x, WORD y, WORD cx, WORD cy,
						 WORD wID,
						 WORD wClassID,
						 LPSTR lpszTitle)
{
	int nchar;

	// Start on a DWORD boundary
	lpw = lpwAlign(lpw);
  
	*lpw++ = LOWORD(dwStyle);
	*lpw++ = HIWORD(dwStyle);
	*lpw++ = LOWORD(dwExtStyle); 
	*lpw++ = HIWORD(dwExtStyle); 
	*lpw++ = x;        // x
	*lpw++ = y;        // y
	*lpw++ = cx;       // cx
	*lpw++ = cy;       // cy
	*lpw++ = wID;      // ID

	/* fill in class i.d. (static in this case) */
	*lpw++ = (WORD)0xffff;   // standard class prefix
	*lpw++ = (WORD)wClassID;

	/* copy the text of the first item */
	nchar = nCopyAnsiToWideChar (lpw, TEXT(lpszTitle), lpwSize - sizeof(WORD)*11);
	lpw += nchar;
	*lpw++ = 0;  // advance pointer over nExtraStuff WORD

	return lpw;
}

LPDLGTEMPLATE CreateDialogTemplate()
{
  LPWORD  p, pdlgtemplate;
  int   nchar;
  DWORD lStyle;

  /* allocate some memory to play with  */
  int wSize = 1000;
  int cSize = 0;
  pdlgtemplate = p = (PWORD) GlobalAlloc (GPTR, wSize);
  if ( !p )
      return (LPDLGTEMPLATE)NULL;

  /* start to fill in the dlgtemplate information.  addressing by WORDs */
  lStyle = DS_3DLOOK | DS_CONTROL | WS_CHILD | WS_CLIPSIBLINGS;
  *p++ = LOWORD (lStyle);
  *p++ = HIWORD (lStyle);
  *p++ = 0;          // LOWORD (lExtendedStyle)
  *p++ = 0;          // HIWORD (lExtendedStyle)
  *p++ = 3;          // Number of items being added
  *p++ = 0;          // x
  *p++ = 0;          // y
  *p++ = 86;         // cx
  *p++ = 122;        // cy
  *p++ = 0;          // Menu
  *p++ = 0;          // Class

  /* copy the title of the dialog */
  nchar = nCopyAnsiToWideChar (p, TEXT(""), wSize - (int)(p - pdlgtemplate)*sizeof(WORD));
  p += nchar;
  
  cSize = wSize - (int)(p - pdlgtemplate)*sizeof(WORD);
  // Add the template positioning control
  p = AddItemToTemplate(p, cSize, WS_CHILD, 0, 0,1,3,122, IDC_LOCATION, 0x82, "");

  cSize = wSize - (int)(p - pdlgtemplate)*sizeof(WORD);
  // Add the image display area
  p = AddItemToTemplate(p, cSize, WS_VISIBLE | WS_CHILD, WS_EX_STATICEDGE, 4,3,80,82, IDC_IMAGE, 0x82, "");

  cSize = wSize - (int)(p - pdlgtemplate)*sizeof(WORD);
  // Add filename display area
  p = AddItemToTemplate(p, cSize, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER | ES_READONLY, WS_EX_STATICEDGE, 4,86,80,12, IDC_FILEINFO, 0x81, "");
  
  return (LPDLGTEMPLATE)pdlgtemplate;
}


/**********************************************************************\

  BOOL GetDIBFilename(LPSTR szFilename, LPSTR szDefault, BOOL  bSave)

  szFilename: Returns the file that the user picks.  This must be at
              least MAX_PATH bytes long
			  
  szDefault:  Default directory.  If this is NULL then the current
              directory is used.  

  bSave:      Do we plan on opening or saving the file?

\**********************************************************************/
BOOL GetDIBFilename(LPSTR lpstrFilename, LPSTR lpstrDefault, BOOL  bSave)
{
	LPSTR lpstrFilters = "Bitmaps (*.bmp,*.dib,*.rle)\0*.BMP;*.DIB;*.RLE\0\0";
	OPENFILENAME ofn; 
	BOOL bReturnValue = FALSE;
	char szDirName[MAX_PATH];
    // Establish the default directory
	if (!lpstrDefault) {
		GetCurrentDirectory(MAX_PATH, szDirName);
	} else {
        if ((GetFileAttributes(lpstrDefault) & FILE_ATTRIBUTE_DIRECTORY) && (GetFileAttributes(lpstrDefault) !=  0xFFFFFFFF) && lstrlen(lpstrDefault))  {
			lstrcpyn(szDirName, lpstrDefault, sizeof(szDirName)-1);
           szDirName[sizeof(szDirName)-1] = '\0';
       }
        else
			GetCurrentDirectory(MAX_PATH, szDirName);
	}    
	
    // Zero initialize the members of the OPENFILENAME structure
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
    
    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = GetActiveWindow();
    ofn.nFilterIndex = 1;
	ofn.lpstrFilter  = lpstrFilters;
    ofn.lpstrFile    = lpstrFilename;
    ofn.nMaxFile     = MAX_PATH;
    ofn.lpstrInitialDir = szDirName;
	
	// If we are retreiving a filename to save...
	if (bSave) {
        ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
        ofn.lpstrTitle = "Save Bitmap";
		
		// Display the Save dialog box.
		bReturnValue = GetSaveFileName(&ofn);
	} else  {
        ofn.lpstrTitle = "Open Bitmap";
		ofn.Flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
		ofn.lpfnHook = (LPOFNHOOKPROC)PreviewWindowHookProc;
		ofn.hInstance = (HINSTANCE)CreateDialogTemplate();
		
		// Display the Open dialog box.
		bReturnValue = GetOpenFileName(&ofn);

		// Free the dialog template we created
		GlobalFree(ofn.hInstance);

   }
	
    return bReturnValue;
}


// ****** Code for displaying DIB in preview window ****** 

BOOL DisplayBitmapInWindow(HWND hWnd, HBITMAP hbm)
{
    DIBSECTION ds;
	HDC     hDC, hdcMem;
	RECT	rc;
    BOOL    bResult;

    GetClientRect(hWnd, &rc);

	hDC = GetDC(hWnd);

	if (!hbm) {
        PatBlt(hDC, 0, 0, rc.right, rc.bottom, BLACKNESS);
		ReleaseDC(hWnd, hDC);
		return FALSE;
	}
		
	if (!GetObject(hbm, sizeof(ds), &ds))
		return FALSE;
    
	SetStretchBltMode(hDC, HALFTONE);
	
	hdcMem = CreateCompatibleDC(NULL);
	SelectObject(hdcMem, hbm);
	
    bResult = StretchBlt(hDC, 
		                 0, 0, rc.right, rc.bottom,
                         hdcMem, 
						 0, 0, ds.dsBmih.biWidth, ds.dsBmih.biHeight, 
						 SRCCOPY);

	ReleaseDC(hWnd, hDC);
	DeleteDC(hdcMem);

    return bResult;
}

BOOL DisplayFileToDialog(LPSTR szFile, HWND hWnd, HBITMAP *hbm)
{
	char szBuffer[256];

	if (*hbm)
		DeleteObject(*hbm);

	*hbm = (HBITMAP)LoadImage(NULL, 
			szFile, 
			IMAGE_BITMAP, 
			0, 0,
			LR_CREATEDIBSECTION | LR_LOADFROMFILE);       

	if (*hbm) {
		BITMAP bm;
		GetObject(*hbm, sizeof(bm), &bm);

		_snprintf(szBuffer, sizeof(szBuffer)-1, "%lux%lux%lubpp", bm.bmWidth, bm.bmHeight, bm.bmBitsPixel * bm.bmPlanes);
        szBuffer[sizeof(szBuffer)-1] = '\0';

		SetDlgItemText(hWnd, IDC_FILEINFO, szBuffer);
	}

	// If *hbm is bogus, DisplayDIBInWindow will display BLACKNESS
	return DisplayBitmapInWindow(GetDlgItem(hWnd,IDC_IMAGE), *hbm);
}

BOOL NEAR PASCAL HandleNotify(HWND hDlg, LPOFNOTIFY pofn, LPSTR szFile, HBITMAP *hbm)
{
  switch (pofn->hdr.code) {
    case CDN_SELCHANGE:  // The selection has changed.

	// Get the path of the selected file.
	if (CommDlg_OpenSave_GetFilePath(GetParent(hDlg), szFile, MAX_PATH)) {
		DisplayFileToDialog(szFile, hDlg, hbm);
	}

    break;
  }

  return(TRUE);
}


LRESULT CALLBACK PreviewWindowHookProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static char szFile[MAX_PATH];
	static HBITMAP hbm;

    switch (msg) {
	case WM_INITDIALOG:
		// Initialize values
		szFile[0] = 0;
		hbm = NULL;
		SetDlgItemText(hDlg, IDC_FILEINFO, "");
		{
			HFONT hf = (HFONT)SendMessage(GetParent(hDlg), WM_GETFONT, 0, 0);
		
			SendMessage(GetDlgItem(hDlg, IDC_FILEINFO), WM_SETFONT, (WPARAM)hf, lParam);
		}
		break;

	case WM_DESTROY:
		if (hbm)
			DeleteObject(hbm);
		break;
								 
	case WM_CTLCOLORSTATIC:
		if (GetDlgItem(hDlg, IDC_IMAGE) == (HWND) lParam) {
			
			DisplayBitmapInWindow(GetDlgItem(hDlg, IDC_IMAGE), hbm);

			return (LRESULT)GetStockObject(NULL_BRUSH);
		} 
		break;
		
	case WM_NOTIFY:
		{
			int idCtrl = (int) wParam; 
			LPOFNOTIFY lpof = (LPOFNOTIFY)lParam;
					
			HandleNotify(hDlg, lpof, szFile, &hbm);
		}
		break;
		
	}

	return 0;
}

