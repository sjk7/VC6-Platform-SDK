//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       UTIL.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"
#include "shlobj.h"


//****************************************************************************
//
// BOOL GetIniBool(LPTSTR pszEntry, BOOL fDefault)
//
// Get the boolean data for an entry
//
//****************************************************************************

BOOL GetIniBool(LPTSTR pszEntry, BOOL fDefault)
{
	return GetPrivateProfileInt(gszAppName, pszEntry, fDefault, gszIniName) != 0;
}

//****************************************************************************
//
// DWORD GetIniInt(LPTSTR pszEntry, DWORD dwDefault)
//
// Get the numeric data for an entry
//
//****************************************************************************

DWORD GetIniInt(LPTSTR pszEntry, DWORD dwDefault)
{
	return GetPrivateProfileInt(gszAppName, pszEntry, dwDefault, gszIniName);
}

//****************************************************************************
//
// LPTSTR GetIniStr(LPTSTR pszEntry, LPTSTR pszDefault)
//
// Get the string data for an entry
//
//****************************************************************************

LPTSTR GetIniStr(LPTSTR pszEntry, LPTSTR pszDefault)
{
	int			cch		= 0;
	LPTSTR		pszRet	= 0;

	TCHAR   sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

	cch = GetPrivateProfileString(gszAppName, pszEntry, pszDefault, sz, MAX_PATH, gszIniName);
	if (cch == 0)
	{
		if (NULL == pszDefault)
			return NULL;

		cch = lstrlen(pszDefault);
		lstrcpyn(sz, pszDefault, MAX_PATH+1);
		sz[MAX_PATH] = 0;
	}

	pszRet = PszAlloc(cch);
	if (pszRet == NULL)
		return NULL;

	ZeroMemory(pszRet, (cch+1)* sizeof(TCHAR));	// PszAlloc allocated cch + 1 characters
	lstrcpyn(pszRet, sz, cch+1);
	pszRet[cch] = 0;

	return pszRet;
}


//****************************************************************************
//
// VOID GetIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
//
// Convert the hex data into binary.
// If no entry is found, lpv isn't modified
//
//****************************************************************************
	
VOID GetIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
{
	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

	if (GetPrivateProfileString(gszAppName, pszEntry, TEXT(""), sz, MAX_PATH, gszIniName) != 0)
	{
		HexToData(sz, lpv, (MAX_PATH < cb) ? MAX_PATH : cb);
	}
}


//****************************************************************************
//
// VOID WriteIniStr(LPTSTR pszEntry, LPTSTR pszData)
//
// Write the data to an entry in the ini file
//
//****************************************************************************

VOID WriteIniStr(LPTSTR pszEntry, LPTSTR pszData)
{
	WritePrivateProfileString(gszAppName, pszEntry, pszData, gszIniName);
}


//****************************************************************************
//
// VOID WriteIniInt(LPTSTR pszEntry, DWORD dw)
//
// Write the numeric data to an entry in the ini file
//
//****************************************************************************

VOID WriteIniInt(LPTSTR pszEntry, DWORD dw)
{
	TCHAR szData[MAX_PATH + 1];
	ZeroMemory(szData, (MAX_PATH + 1) * sizeof(TCHAR));

	_sntprintf(szData, MAX_PATH, TEXT("%d\0"), dw);
	WritePrivateProfileString(gszAppName, pszEntry, szData, gszIniName);
}


//****************************************************************************
//
// VOID WriteIniBool(LPTSTR pszEntry, BOOL f)
//
// Write the boolean value to an entry in the registery
//
//****************************************************************************

VOID WriteIniBool(LPTSTR pszEntry, BOOL f)
{
	WritePrivateProfileString(gszAppName, pszEntry, f ? TEXT("1") : TEXT("0"), gszIniName);
}


//****************************************************************************
//
// VOID WriteIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
//
//****************************************************************************
VOID WriteIniHex(LPTSTR pszEntry, LPVOID lpv, int cb)
{
	if	((NULL == pszEntry) || (NULL == lpv))
	{
		ERROR_MSG(TEXT("WriteIniHex: NULL == in parameter"));
		return;
	}

	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, sizeof(TCHAR) * (MAX_PATH+1));

	DataToHex((LPTSTR) lpv, sz, 2*cb > MAX_PATH ? MAX_PATH : 2*cb);

	WriteIniStr(pszEntry, sz);

}


//****************************************************************************
//
// VOID CenterWindow(HWND hwndChild, HWND hwndParent)
//
// Center a window over another window.
//
//****************************************************************************

VOID CenterWindow(HWND hwndChild, HWND hwndParent)
{
	int	xNew		= 0;
	int	yNew		= 0;
	int cxChild		= 0;
	int	cyChild		= 0;
	int	cxParent	= 0;
	int	cyParent	= 0;
	int	cxScreen	= 0;
	int	cyScreen	= 0;

	RECT	rcChild	= {0,0,0,0};
	RECT	rcParent= {0,0,0,0};
	HDC		hdc;

	// Get the Height and Width of the child window
	GetWindowRect(hwndChild, &rcChild);
	cxChild = rcChild.right - rcChild.left;
	cyChild = rcChild.bottom - rcChild.top;

	// Get the Height and Width of the parent window
	GetWindowRect(hwndParent, &rcParent);
	cxParent = rcParent.right - rcParent.left;
	cyParent = rcParent.bottom - rcParent.top;

	// Get the display limits
	hdc = GetDC(hwndChild);
	if (hdc == NULL) {
		// major problems - move window to 0,0
		xNew = yNew = 0;
	} else {
		cxScreen = GetDeviceCaps(hdc, HORZRES);
		cyScreen = GetDeviceCaps(hdc, VERTRES);
		ReleaseDC(hwndChild, hdc);

		if (NULL == hwndParent) {
			cxParent = cxScreen;
			cyParent = cyScreen;
			SetRect(&rcParent, 0, 0, cxScreen, cyScreen);
		}

		// Calculate new X position, then adjust for screen
		xNew = rcParent.left + ((cxParent - cxChild) / 2);
		if (xNew < 0) {
			xNew = 0;
		} else if ((xNew + cxChild) > cxScreen) {
			xNew = cxScreen - cxChild;
		}

		// Calculate new Y position, then adjust for screen
		yNew = rcParent.top  + ((cyParent - cyChild) / 2);
		if (yNew < 0) {
			yNew = 0;
		} else if ((yNew + cyChild) > cyScreen) {
			yNew = cyScreen - cyChild;
		}

	}

	SetWindowPos(hwndChild, NULL, xNew, yNew,	0, 0,
		SWP_NOSIZE | SWP_NOZORDER);
}


//****************************************************************************
//
// LPVOID LpvAlloc(int cb)
//
// Return a pointer to an allocated array of bytes
//
//****************************************************************************

LPVOID LpvAlloc(int cb)
{
	return LocalAlloc(LMEM_FIXED, cb);
}


//****************************************************************************
//
// LPTSTR PszAlloc(int cch)
//
//****************************************************************************

LPTSTR PszAlloc(int cch)
{
	return (LPTSTR) LocalAlloc(LMEM_FIXED, sizeof(TCHAR) * (cch+1));
}


//****************************************************************************
//
// VOID FreePlpv(LPVOID plpv)
//
// Free the data pointed to by plpv and set *plpv to NULL
//
//****************************************************************************

VOID FreePlpv(LPVOID plpv)
{
	if ((plpv == NULL) || (*(VOID FAR * FAR *)plpv == NULL)) {
		return;
	}

	LocalFree(*(VOID FAR * FAR *)plpv);
	*(VOID FAR * FAR *)plpv = NULL;
}


//****************************************************************************
//
// TCHAR ChFromHex(LPTSTR lpch)
//
// Convert from Hex data to ascii character
//
//****************************************************************************

TCHAR ChFromHex(LPTSTR lpch)
{
	if	(NULL == lpch)
		return NULL;

	int		i	= 0;
	int		cch	= 2;
	char	ch	= 0;

	while (cch-- > 0)
	{
		ch = *lpch++;
		if (ch >= 'A')
		{
			i = (i*16) + (ch - ('A'-10));
		} 
		else
		{
			i = (i*16) + (ch - '0');
		}
	}

	return (TCHAR) i;
}


//****************************************************************************
//
// VOID HexToData(LPTSTR lpchSrc, LPVOID lpvDest, int cb)
//
// Convert from Hex data to ascii character
//
//****************************************************************************

VOID HexToData(LPTSTR lpchSrc, LPVOID lpvDest, int cb)
{
	if	((NULL == lpvDest) || (NULL == lpchSrc))
		return;

	PTCHAR lpchDest = (PTCHAR) lpvDest;

	CharUpperBuff(lpchSrc, cb);

	while (cb-- > 0)
	{
		*lpchDest++ = ChFromHex(lpchSrc);
		lpchSrc += 2;
	}
}


//****************************************************************************
//
// LPTSTR HexToBin(LPTSTR lpchSrc, LPVOID lpvDest, int cb)
//
// Convert from Hex data to ascii character
//
//****************************************************************************

LPTSTR HexToBin(LPTSTR lpchSrc, LPVOID lpvDest, int cb)
{
	if	((NULL == lpvDest) || (NULL == lpchSrc))
		return NULL;

	TCHAR * lpchDest = ((TCHAR *) lpvDest) + cb;

	CharUpperBuff(lpchSrc, cb);

	while (cb-- > 0)
	{
		lpchDest--;
		*lpchDest = ChFromHex(lpchSrc);
		lpchSrc += 2;
	}
	return lpchSrc;
}

//****************************************************************************
//
// VOID DataToHex(LPTSTR lpchSrc, LPTSTR lpchDest, int cb)
//
//****************************************************************************

VOID DataToHex(LPTSTR lpchSrc, LPTSTR lpchDest, int cbDest)
{
	int	cb	= cbDest / 2;
	UINT ch	= 0;

	if	(NULL == lpchDest)
	{
		ERROR_MSG(TEXT("DataToHex: Destination string is NULL"));
		return;
	}

	if (lpchSrc == NULL)
	{
		lpchDest[0] = 0;	// return empty string 
		return;
	}

	while (cb-- > 0)
	{
		ch = 0x00FF & (unsigned char) (*lpchSrc++);
		_sntprintf(lpchDest, 2, TEXT("%02X"), ch);
		lpchDest += 2;
	}
}


//****************************************************************************
//
// VOID SetMenuCheck(UINT idm, BOOL fCheck)
//
// Set the menu item's check mark.
//
//****************************************************************************

VOID SetMenuCheck(UINT idm, BOOL fCheck)
{
	CheckMenuItem(ghMenu, idm,
		fCheck ? (MF_CHECKED  | MF_BYCOMMAND) : (MF_UNCHECKED | MF_BYCOMMAND));
}


//****************************************************************************
//
// VOID MaybeDeleteObject(HGDIOBJ * phgdi)
//
// Check usage count, delete if we can
//
//****************************************************************************

VOID MaybeDeleteObject(HGDIOBJ * phgdi)
{
	if ((NULL == phgdi) || (NULL == *phgdi))
		return;

	DeleteObject(*phgdi);
	*phgdi = NULL;	
}

//****************************************************************************
//
// BOOL FGetFileName(LPTSTR szFileName)
//
//****************************************************************************

BOOL FGetFileName(LPTSTR szFileName)
{
	if	(NULL == szFileName)
	{
		ERROR_MSG(TEXT("FGetFileName: NULL == szFileName"));
		return FALSE;
	}

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	szFileName[0] = TEXT('\0');

	ofn.lStructSize   = sizeof(OPENFILENAME);
	ofn.hwndOwner     = ghwndMain;
	ofn.hInstance     = (HINSTANCE) ghInst;
	ofn.lpstrFilter   = TEXT("All Files\0*.*\0Text Files (*.txt)\0*.TXT\0");
	ofn.nFilterIndex  = 1L;
	ofn.lpstrFile     = szFileName;
	ofn.nMaxFile      = MAX_PATH;
	ofn.lpstrTitle    = TEXT("Pick a file to send\0");
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	if (!GetOpenFileName(&ofn))
		return FALSE;

	return TRUE;
}


//****************************************************************************
//
// BOOL FGetDirectory(LPTSTR szDir)
//
//****************************************************************************

BOOL FGetDirectory(LPTSTR szDir)
{
	BOOL			fRet		= FALSE;
	LPITEMIDLIST	pidl		= NULL;
	LPITEMIDLIST	pidlRoot	= NULL;
	LPMALLOC		lpMalloc	= NULL;

	TCHAR			szPath[MAX_PATH + 1];
	ZeroMemory(szPath, sizeof(TCHAR) * (MAX_PATH + 1));

	BROWSEINFO bi = {
		ghwndMain,
		NULL,
		szPath,
		TEXT("Select a Directory\0"),
		BIF_RETURNONLYFSDIRS,
		NULL, 0L, 0	};

	if	(0 != SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DRIVES, &pidlRoot))
		return FALSE;

	if	(NULL == pidlRoot)
		return FALSE;

	bi.pidlRoot = pidlRoot;
	pidl = SHBrowseForFolder(&bi);

	if	(NULL != pidl)
		fRet = SHGetPathFromIDList(pidl, szDir);
	else
		fRet = FALSE;

	// Get the shell's allocator to free PIDLs
	if (!SHGetMalloc(&lpMalloc) && (NULL != lpMalloc))
	{
		if (NULL != pidlRoot)
		{
			lpMalloc->Free(pidlRoot);
			pidlRoot = NULL;
		}

		if (NULL != pidl)
		{
			lpMalloc->Free(pidl);
			pidl = NULL;
		}

		lpMalloc->Release();
		lpMalloc = NULL;
	}

	return fRet;
}


//****************************************************************************
//
// VOID GetDlgItemPsz(HWND hdlg, UINT id, LPTSTR *ppsz)
//
// Get the text in the dialog item and retun a pointer to it in *ppsz.
// Note: Any previous data in ppsz is released.
//
//****************************************************************************

VOID GetDlgItemPsz(HWND hdlg, UINT id, LPTSTR *ppsz)
{
	if	(NULL == ppsz)
	{
		ERROR_MSG(TEXT("GetDlgItemPsz: NULL = ppsz"));
		return;
	}

	UINT	cch		= 0;

	TCHAR	sz[MAX_PATH+1];
	ZeroMemory(sz, sizeof(TCHAR) * (MAX_PATH + 1));

	FreePlpv(ppsz);
	
	cch = GetDlgItemText(hdlg, id, sz, MAX_PATH);
	if (0 == cch)
		return;

	*ppsz = (LPTSTR) PszAlloc(cch);
	if (NULL == *ppsz)
		return;

	ZeroMemory(*ppsz, (cch+1)* sizeof(TCHAR));	//PszAlloc allocates number of bytes passed + 1
	lstrcpyn(*ppsz, sz, cch+1);
	(*ppsz)[cch] = 0;
}


//****************************************************************************
//
// int GetRadioButton(HWND hdlg, int idrFirst, int idrLast)
//
//****************************************************************************

int GetRadioButton(HWND hdlg, int idrFirst, int idrLast)
{
	for (int id = idrFirst; id <= idrLast; id++)
	{
		if (BST_UNCHECKED != IsDlgButtonChecked(hdlg, id))
			return id;
	}
	return idrFirst;
}

//****************************************************************************
//
// VOID GuidToSz(GUID * pguid, LPTSTR lpchDest)
//
// Convert the guid to a special hex string.
// Assumes lpchDest has space for at least sizeof(GUID)*2 +6 chars.
// LENGTH_SZGUID_FORMATTED is 30 and includes space for the null terminator.
//
// Note the difference between this and UuidToString (or StringFromGUID2)
//
// GUID Format: {12345678-1234-1234-1234-567890123456}
//
//****************************************************************************

VOID GuidToSz(GUID * pguid, LPTSTR lpchDest)
{
	ASSERT(NULL != pguid);
	ASSERT(NULL != lpchDest);

	if	((NULL == pguid) || (NULL == lpchDest))
	{
		ERROR_MSG(TEXT("GuidToSz: Null pointer passed in as parameter"));
		return;
	}

	_sntprintf(lpchDest, 25, TEXT("{%08X-%04X-%04X-%02X%02X-"),
		pguid->Data1, pguid->Data2, pguid->Data3, pguid->Data4[0], pguid->Data4[1]);
	lpchDest += 1+8+1+4+1+4+1+2+2+1;

	for (int i = 2; i < 8; i++)
	{
		_sntprintf(lpchDest, 2, TEXT("%02X"), pguid->Data4[i]);
		lpchDest += 2;
	}

	lpchDest[0]	= TEXT('}');
}


//****************************************************************************
//
// VOID SzToGuid(LPTSTR lpchSrc, GUID * pguid)
//
//****************************************************************************

VOID SzToGuid(LPTSTR lpchSrc, GUID * pguid)
{
	if	(NULL == pguid)
		return;

	ZeroMemory(pguid, sizeof(GUID));

	if ((NULL == lpchSrc) || (NULL == lpchSrc[0]) || (lstrlen(lpchSrc) < sizeof(GUID)*2 + 6))
	{
		return;
	}

	if (_T('{') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data1, sizeof(pguid->Data1));
	if (_T('-') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data2, sizeof(pguid->Data2));
	if (_T('-') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data3, sizeof(pguid->Data3));
	if (_T('-') != *lpchSrc++)
		return;
	lpchSrc = HexToBin(lpchSrc, &pguid->Data4[0], sizeof(BYTE));
	lpchSrc = HexToBin(lpchSrc, &pguid->Data4[1], sizeof(BYTE));
	if (_T('-') != *lpchSrc++)
		return;
	HexToData(lpchSrc, &pguid->Data4[2], sizeof(pguid->Data4) - 2*sizeof(BYTE));
}
	

//****************************************************************************
//
// LPTSTR SzFindLastCh(LPTSTR lpsz, TCHAR ch)
//
// Returns a pointer to the ch within the lpsz or NULL if not found
//
//****************************************************************************

LPTSTR SzFindLastCh(LPTSTR lpsz, TCHAR ch)
{
	if	(NULL == lpsz)
		return NULL;

	LPTSTR	lpchRet	= NULL;

	for (lpchRet = NULL; *lpsz; lpsz = CharNext(lpsz))
	{
		if (ch == *lpsz)
			lpchRet = lpsz;
	}

	return lpchRet;
}

