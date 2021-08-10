// CustomDrawButtonDlg.cpp : Defines the entry point for the application.
//

#include "Windows.h"
#include <commctrl.h>
#include "shlwapi.h"
#include "resource.h"


// Forward declarations of functions included in this code module:
LRESULT CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)

{
 	InitCommonControls();
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG), NULL, (DLGPROC)DlgProc);

	return 0;
}




//
//  FUNCTION: DlgProc(HWND, unsigned, WORD, LONG)
//
LRESULT CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	static HWND hStatic = NULL;
	static const int nSleepTime = 750;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
			
			case IDCANCEL:
				EndDialog(hWnd, 0);
				break;
			default:
				return 0;
		}
		break;
	case WM_INITDIALOG:
		{
			hStatic = GetDlgItem(hWnd, IDC_STATIC);
		}
		break;
	case WM_NOTIFY:
		{
			NMHDR* nmhdr = (NMHDR*)lParam;
			
			if (!nmhdr)
				break;
			
			switch (nmhdr->code)
			{
			case NM_CUSTOMDRAW:
				{
					if (nmhdr->idFrom != ID_CUSTOM_BUTTON)
						break;

					LPNMCUSTOMDRAW lpCD = (LPNMCUSTOMDRAW)lParam;
					
					TCHAR szOut[150];
					BOOL bStateAdded = FALSE;
					if ((lpCD->uItemState & CDIS_CHECKED) == CDIS_CHECKED)// The item is
                                                                                              // is checked.
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_CHECKED"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_CHECKED"));
						}
					}

						
					if ((lpCD->uItemState & CDIS_DEFAULT) ==  CDIS_DEFAULT)// The item 
                                                                                               // is in its
                                                                                               // default
                                                                                               // state. 
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_DEFAULT"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_DEFAULT"));
						}
					}
						
					if ((lpCD->uItemState & CDIS_DISABLED) ==  CDIS_DISABLED) // The item is
                                                                                                  // disabled. 
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_DISABLED"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_DISABLED"));
						}
					}
						
					if ((lpCD->uItemState & CDIS_FOCUS) ==  CDIS_FOCUS) // The item is in focus. 
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_FOCUS"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_FOCUS"));
						}
					}
					
					if ((lpCD->uItemState & CDIS_GRAYED) ==  CDIS_GRAYED) // The item is grayed. 
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_GRAYED"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_GRAYED"));
						}
					}
						
					if ((lpCD->uItemState & CDIS_HOT) ==  CDIS_HOT) // The item is currently
                                                                                        // under the pointer
                                                                                        // ("hot"). 
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_HOT"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_HOT"));
						}
					}
						
					if ((lpCD->uItemState & CDIS_INDETERMINATE) == CDIS_INDETERMINATE) 
                                                                                         // The item is in an
                                                                                         // indeterminate state.
                                                                                                           
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_INDETERMINATE"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_INDETERMINATE"));
						}
					}
						
					if ((lpCD->uItemState & CDIS_MARKED) ==  CDIS_MARKED) // The item is marked.
                                                                                              // The meaning of this
                                                                                              // is up to the
                                                                                              // implementation. 
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_MARKED"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_MARKED"));
						}
					}
						
					if ((lpCD->uItemState & CDIS_SELECTED) ==  CDIS_SELECTED) // The item is
                                                                                                  // selected.
					{
						if (bStateAdded)
							StrCat(szOut, TEXT(" | CDIS_SELECTED"));
						else
						{
							bStateAdded = TRUE;
							StrCpy(szOut, TEXT("State = CDIS_SELECTED"));
						}
					}
						

					if (lpCD->dwDrawStage == CDDS_PREPAINT)
					{
						if (!bStateAdded)
							StrCpy(szOut, TEXT("CDDS_PREPAINT"));
						else
							StrCat(szOut, TEXT(", CDDS_PREPAINT"));
						SetWindowText(hStatic, szOut);
						Sleep(nSleepTime);
						SetWindowLong(hWnd, DWL_MSGRESULT, (LONG)(CDRF_NOTIFYITEMDRAW |                                                                  CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYPOSTERASE));
						return 1;
					}

					if (lpCD->dwDrawStage == CDDS_POSTPAINT )
					{
						if (!bStateAdded)
							StrCpy(szOut, TEXT("CDDS_POSTPAINT"));
						else
							StrCat(szOut, TEXT(", CDDS_POSTPAINT"));
						SetWindowText(hStatic, szOut);
						Sleep(nSleepTime);
					}
						

					if (lpCD->dwDrawStage == CDDS_PREERASE )
					{
						if (!bStateAdded)
							StrCpy(szOut, TEXT("CDDS_PREERASE"));
						else
							StrCat(szOut, TEXT(", CDDS_PREERASE"));
						
						SetWindowText(hStatic, szOut);
						Sleep(nSleepTime);
						SetWindowLong(hWnd, DWL_MSGRESULT, (LONG)(CDRF_NOTIFYITEMDRAW |                                                               CDRF_NOTIFYPOSTPAINT | CDRF_NOTIFYPOSTERASE));
						return 1;
					}

					if (lpCD->dwDrawStage == CDDS_POSTERASE)
					{
						if (!bStateAdded)
							StrCpy(szOut, TEXT("CDDS_POSTERASE"));
						else
							StrCat(szOut, TEXT(", CDDS_POSTERASE"));
						
						SetWindowText(hStatic, szOut);
						Sleep(nSleepTime);
					}
				}
			}
			break;
		}
	}
	return 0;
}

