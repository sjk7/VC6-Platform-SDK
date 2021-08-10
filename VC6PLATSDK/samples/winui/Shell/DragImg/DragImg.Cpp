/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1998 - 2000 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DragImg.cpp

   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <strsafe.h>
#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))
#include "resource.h"
#include "DragSrc.h"
#include "DataObj.h"
#include "DropTgt.h"
#include "Render.h"

/**************************************************************************
   function prototypes
**************************************************************************/

BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateListView(HINSTANCE, HWND);
void ResizeListView(HWND, HWND);
BOOL InitListView(HWND);
BOOL InsertListViewItems(HWND);
LRESULT HandleNotify(HWND, LPARAM);
void HandleDragDrop(HWND, BOOL);
void SwitchView(HWND, DWORD);

/**************************************************************************
   global variables and definitions
**************************************************************************/

TCHAR       g_szClassName[] = TEXT("DragImageClass");
TCHAR       g_szTitle[] = TEXT("Drag Image Helper Sample Application");
HINSTANCE   g_hInst;
USHORT      g_cfFileContents = 0;
USHORT      g_cfFileGroupDescriptor = 0;
HWND        g_hwndMain;
BOOL        g_fUseList;

#define ID_LISTVIEW  1000

/**************************************************************************

   WinMain()

**************************************************************************/

int CALLBACK WinMain(   HINSTANCE hInstance, 
                        HINSTANCE hPrevInstance, 
                        LPSTR lpCmdLine, 
                        int nCmdShow)
{
MSG   msg;
INITCOMMONCONTROLSEX icc;

icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
icc.dwICC = ICC_LISTVIEW_CLASSES;
InitCommonControlsEx(&icc);

g_hInst = hInstance;

if(OleInitialize(NULL) != S_OK)
   return FALSE;

if(!InitApplication(hInstance))
   return FALSE;

if(!InitInstance(hInstance, nCmdShow))
   return FALSE;

while(GetMessage(&msg, NULL,0, 0))     
   {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
   }

OleUninitialize();

return (int)msg.wParam;
}

/**************************************************************************

   InitApplication()

**************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
WNDCLASS  wc;

wc.style         = CS_HREDRAW | CS_VREDRAW;
wc.lpfnWndProc   = (WNDPROC)MainWndProc;
wc.cbClsExtra    = 0;
wc.cbWndExtra    = 0;
wc.hInstance     = hInstance;
wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON));
wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
wc.lpszClassName = g_szClassName;

return(RegisterClass(&wc));
}

/**************************************************************************

   InitInstance()

**************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
HWND hWnd;

//get the ID for the File Group Descriptor clipboard format
g_cfFileGroupDescriptor = (USHORT) RegisterClipboardFormat(CFSTR_FILEDESCRIPTOR);

//get the ID for the File Contents clipboard format
g_cfFileContents = (USHORT) RegisterClipboardFormat(CFSTR_FILECONTENTS);

// Create a main window for this application instance.
hWnd = CreateWindow( g_szClassName,
                     g_szTitle,
                     WS_OVERLAPPEDWINDOW,
                     CW_USEDEFAULT, 
                     CW_USEDEFAULT, 
                     CW_USEDEFAULT, 
                     CW_USEDEFAULT,
                     NULL,
                     NULL,
                     hInstance,
                     NULL);
   
// If window could not be created, return "failure"
if(!hWnd)
   return FALSE;

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
return TRUE;
}

/**************************************************************************

   MainWndProc()

**************************************************************************/

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
static HWND s_hwndList;

switch(uMsg)
   {
   case WM_CREATE:
      {
      g_hwndMain = hWnd;

      CDropTarget *pDropTarget = new CDropTarget;

      if(pDropTarget)
         RegisterDragDrop(hWnd, pDropTarget);

      s_hwndList = CreateListView(g_hInst, hWnd);
      if(s_hwndList)
         InitListView(s_hwndList);
      
      g_fUseList = TRUE;
      }
      break;
    
   case WM_DESTROY:
      RevokeDragDrop(hWnd);
      
      PostQuitMessage(0);
      break;

   case WM_SIZE:
      ResizeListView(s_hwndList, hWnd);
      break;

   case WM_SETFOCUS:
      SetFocus(s_hwndList);
      return 0;
   
   case WM_INITMENUPOPUP:
      {
      DWORD dwStyle;
      UINT  uID;

      CheckMenuRadioItem((HMENU)wParam, IDM_FROM_WINDOW, IDM_FROM_BITMAP, g_fUseList ? IDM_FROM_WINDOW : IDM_FROM_BITMAP, MF_BYCOMMAND);

      dwStyle = GetWindowLong(s_hwndList, GWL_STYLE);
      switch(dwStyle & LVS_TYPEMASK)
         {
         default:
         case LVS_ICON:
            uID = IDM_LARGEICONS;
            break;
      
         case LVS_SMALLICON:
            uID = IDM_SMALLICONS;
            break;
      
         case LVS_LIST:
            uID = IDM_LIST;
            break;
   
         case LVS_REPORT:
            uID = IDM_REPORT;
            break;
         }
      CheckMenuRadioItem((HMENU)wParam, IDM_LARGEICONS, IDM_REPORT, uID,  MF_BYCOMMAND | MF_CHECKED);
      }
      break;
   
   case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam))
         {
         case IDM_FROM_WINDOW:
            g_fUseList = TRUE;
            break;

         case IDM_FROM_BITMAP:
            g_fUseList = FALSE;
            break;

         case IDM_LARGEICONS:
            SwitchView(s_hwndList, LVS_ICON);
            break;

         case IDM_SMALLICONS:
            SwitchView(s_hwndList, LVS_SMALLICON);
            break;

         case IDM_LIST:
            SwitchView(s_hwndList, LVS_LIST);
            break;

         case IDM_REPORT:
            SwitchView(s_hwndList, LVS_REPORT);
            break;

         case IDM_ABOUT:
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, (DLGPROC)AboutDlgProc);
            break;
        
         case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
         }
      break;

   case WM_NOTIFY:
      return HandleNotify(hWnd, lParam);
   
   default:
      break;
  }

return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/**************************************************************************

   AboutDlgProc()

**************************************************************************/

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
switch(uMsg)
   {
   case WM_COMMAND:
      switch(GET_WM_COMMAND_ID(wParam, lParam))
         {
         case IDOK:
            EndDialog(hDlg, IDOK);
            break;

         case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
         }
      break;
   }

return FALSE;
}

/******************************************************************************

   CreateListView

******************************************************************************/

HWND CreateListView(HINSTANCE hInstance, HWND hwndParent)
{
DWORD       dwStyle;
HWND        hwndListView;
BOOL        bSuccess = TRUE;

dwStyle =   WS_TABSTOP | 
            WS_CHILD | 
            WS_BORDER | 
            LVS_AUTOARRANGE |
            LVS_ICON |
            LVS_SHOWSELALWAYS |
            WS_VISIBLE;
            
hwndListView = CreateWindowEx(   WS_EX_CLIENTEDGE,
                                 WC_LISTVIEW,
                                 NULL,
                                 dwStyle,
                                 0,
                                 0,
                                 0,
                                 0,
                                 hwndParent,
                                 (HMENU)ID_LISTVIEW,
                                 g_hInst,
                                 NULL);

if(!hwndListView)
   return NULL;

return hwndListView;
}

/******************************************************************************

   ResizeListView

******************************************************************************/

void ResizeListView(HWND hwndListView, HWND hwndParent)
{
RECT  rc;

GetClientRect(hwndParent, &rc);

MoveWindow( hwndListView, 
            rc.left,
            rc.top,
            rc.right - rc.left,
            rc.bottom - rc.top,
            TRUE);

}

/******************************************************************************

   InitListView

******************************************************************************/

BOOL InitListView(HWND hwndListView)
{
LV_COLUMN   lvColumn;
HIMAGELIST  himlSmall;
HIMAGELIST  himlLarge;

//empty the list
ListView_DeleteAllItems(hwndListView);

//initialize the columns
lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
lvColumn.fmt = LVCFMT_LEFT;
lvColumn.cx = 150;
lvColumn.pszText = TEXT("Source File Name");
ListView_InsertColumn(hwndListView, 0, &lvColumn);

//set the image lists
himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);

if (himlSmall && himlLarge)
   {
   HICON hIcon;

   //set up the small image list
   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_MAINICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
   ImageList_AddIcon(himlSmall, hIcon);

   //set up the large image list
   hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MAINICON));
   ImageList_AddIcon(himlLarge, hIcon);

   ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
   ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
   }

InsertListViewItems(hwndListView);

return TRUE;
}

/******************************************************************************

   InsertListViewItems

******************************************************************************/

#define FILE_COUNT   10

BOOL InsertListViewItems(HWND hwndListView)
{
//empty the list
ListView_DeleteAllItems(hwndListView);

UINT     i;
LVITEM   lvItem;

for(i = 0; i < FILE_COUNT; i++)
   {
   TCHAR szName[MAX_PATH];

   StringCchPrintf(szName, ARRAYSIZE(szName), TEXT("File%02d.txt"), i);

   ZeroMemory(&lvItem, sizeof(lvItem));
   lvItem.iItem = i;
   lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
   lvItem.pszText = szName;
   lvItem.iImage = 0;
   ListView_InsertItem(hwndListView, &lvItem);
   }
   
return TRUE;
}

/**************************************************************************

   HandleNotify()

**************************************************************************/

LRESULT HandleNotify(HWND hWnd, LPARAM lParam)
{
LPNMHDR  lpnmh = (LPNMHDR)lParam;
HWND     hwndList = GetDlgItem(hWnd, ID_LISTVIEW);

switch(lpnmh->code)
   {
   case LVN_BEGINDRAG:
      HandleDragDrop(hwndList, g_fUseList);
      return 0;
   }

return 0;
}

/**************************************************************************

   HandleDragDrop()

**************************************************************************/

void HandleDragDrop(HWND hwndList, BOOL fFromWindow)
{
DWORD       dwEffect;
HRESULT     hr;
CDragSource *pDropSource;
CDataObject *pDataObject;
int         nItems;

nItems = ListView_GetSelectedCount(hwndList);
if(!nItems)
   return;

pDropSource = new CDragSource;
if(pDropSource)
   {
   pDataObject = new CDataObject;
   if(pDataObject)
      {
      FORMATETC   fe;
      STGMEDIUM   sm;
      int         i,
                  nStart;
      int         *anItems;
      DWORD       dwChars;

      //get the indexes of the selected items
      anItems = new int[nItems];
      for(i = 0, nStart = -1; i < nItems; i++)
         {
         nStart = anItems[i] = ListView_GetNextItem(hwndList, nStart, LVNI_SELECTED);
         }

      //get the length of the text for each selected item
      for(i = 0, dwChars = 0; i < nItems; i++)
         {
         TCHAR szText[MAX_PATH] = TEXT("");

         ListView_GetItemText(hwndList, anItems[i], 0, szText, MAX_PATH);

         dwChars += lstrlen(szText) + 1;
         }
      
      //add one for the double-NULL terminator
      dwChars += 1;

      LPTSTR pszFiles = new TCHAR[dwChars];
      LPTSTR pszThis;

      //get the text for each selected item
      for(i = 0, pszThis = pszFiles; i < nItems; i++)
         {
         ListView_GetItemText(hwndList, anItems[i], 0, pszThis, dwChars - (DWORD)(pszThis - pszFiles));

         pszThis += lstrlen(pszThis) + 1;
         }
      
      //double NULL terminate the list
      *pszThis = 0;
      
      //initialize the data object
      fe.cfFormat = g_cfFileGroupDescriptor;
      fe.ptd = NULL;
      fe.dwAspect = DVASPECT_CONTENT;
      fe.lindex = -1;
      fe.tymed = TYMED_HGLOBAL;

      sm.tymed = TYMED_HGLOBAL;
      sm.pUnkForRelease = NULL;
      sm.hGlobal = CreateFileGroupDescriptor(pszFiles);

      pDataObject->SetData(&fe, &sm, TRUE);

      fe.cfFormat = g_cfFileContents;
      fe.ptd = NULL;
      fe.dwAspect = DVASPECT_CONTENT;
      fe.tymed = TYMED_HGLOBAL;

      sm.tymed = TYMED_HGLOBAL;
      sm.pUnkForRelease = NULL;

      for(i = 0; i < nItems; i++)
         {
         fe.lindex = i;
         sm.hGlobal = CreateFileContents(pszFiles, i);

         pDataObject->SetData(&fe, &sm, TRUE);
         }

      IDragSourceHelper *pDragSourceHelper = NULL;

      CoCreateInstance( CLSID_DragDropHelper,
                        NULL,
                        CLSCTX_INPROC_SERVER,
                        IID_IDragSourceHelper,
                        (LPVOID*)&pDragSourceHelper);

      if(pDragSourceHelper)
         {
         POINT pt;

         pt.x = 0;
         pt.y = 0;

         GetCursorPos(&pt);
         ScreenToClient(hwndList, &pt);

         if(fFromWindow)
            {
            /*
            The pt parameter appears to be ignored, or at least overridden by 
            the window.
            */
            pDragSourceHelper->InitializeFromWindow(hwndList, &pt, pDataObject);
            }
         else
            {
            SHDRAGIMAGE di;
            HBITMAP     hbm;
            BITMAP      bm;
            RECT  rc;

            hbm = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_DRAG_IMAGE));

            GetObject(hbm, sizeof(bm), &bm);

            di.sizeDragImage.cx = bm.bmWidth;
            di.sizeDragImage.cy = bm.bmHeight;
            di.hbmpDragImage = hbm;
            di.crColorKey = RGB(0, 0, 0); //transparent color

            //get the offset for the cursor compared to the first selected item
            ListView_GetItemRect(hwndList, anItems[0], &rc, LVIR_SELECTBOUNDS);
            di.ptOffset.x = pt.x - rc.left;
            di.ptOffset.y = pt.y - rc.top;

            pDragSourceHelper->InitializeFromBitmap(&di, pDataObject);
            }
         }
      
      delete anItems;
      delete pszFiles;
      
      // do the drag and drop
      hr = DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY, &dwEffect);

      if(pDragSourceHelper)
         {
         pDragSourceHelper->Release();
         }

      pDataObject->Release();
      }
   
   pDropSource->Release();
   }
}

/**************************************************************************

   SwitchView()

**************************************************************************/

void SwitchView(HWND hwndListView, DWORD dwView)
{
DWORD dwStyle = GetWindowLong(hwndListView, GWL_STYLE);

SetWindowLong(hwndListView, GWL_STYLE, (dwStyle & ~LVS_TYPEMASK) | dwView);
ResizeListView(hwndListView, GetParent(hwndListView));
}

