////    TEXTWND.CPP
//
//              Maintains the text display panel
#include "precomp.hxx"
#include "global.h"

////    InvalidateText - Force redisplay
//
//
void InvalidateText() 
{
    RECT rc = {0};
    
    rc.left   = g_fPresentation ? 0 : g_iSettingsWidth;
    rc.top    = 0;
    rc.right  = 10000;
    rc.bottom = 10000;
    InvalidateRect(g_hTextWnd, &rc, TRUE);
}

////    Header - Draw a simple header for each text section
//
//      Used to distinguish logical, plaintext and formatted text sections of
//      text window.
//
//      Advances SEPARATORHEIGHT drawing a horizontal line 2/5ths of the way
//      down, and displays a title below the line.
//
//      At the top of the page displays only the title.
const int SEPARATORHEIGHT = 35;

void Header(HDC hdc, char* str, RECT *prc, int *piY) {

    HFONT hf      = NULL;
    HFONT hfold   = NULL;
    RECT  rcClear = {0};

    int iLinePos      = 0;
    int iTextPos      = 0;
    int iFontEmHeight = 0;
    int iHeight       = 0;

    iFontEmHeight = SEPARATORHEIGHT*40/100;
    if (*piY <= prc->top)
    {
        // Prepare settings for title only, at top of window
        iLinePos = -1;
        iTextPos = 0;
        iHeight  = SEPARATORHEIGHT*60/100;
    }
    else
    {
        // Prepare settings for 40% white space, a line, 10% whitespace, text and 3% whitespace
        iLinePos = SEPARATORHEIGHT*30/100;
        iTextPos = SEPARATORHEIGHT*40/100;
        iHeight  = SEPARATORHEIGHT;
    }

    rcClear = *prc;
    rcClear.top = *piY;
    rcClear.bottom = *piY + iHeight;
    FillRect(hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));

    if (*piY > prc->top) 
    {
        // Separate from previous output with double pixel line
        MoveToEx(hdc, prc->left,  *piY+iLinePos, NULL);
        LineTo  (hdc, prc->right, *piY+iLinePos);
        MoveToEx(hdc, prc->left,  *piY+iLinePos+1, NULL);
        LineTo  (hdc, prc->right, *piY+iLinePos+1);
    }

    hf = CreateFont(-iFontEmHeight, 0, 0, 0, 0, 0, 0, 0, 1, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE|DEFAULT_PITCH,TEXT("Arial"));
    hfold = (HFONT) SelectObject(hdc, hf);
    __try
    {
         // If str is not null terminated, this call can cause access violation.
        ExtTextOutA(hdc, prc->left, *piY + iTextPos, 0, prc, str, (int)strlen(str), NULL);
    }
    __except(EXCEPTION_EXECUTE_HANDLER) 
    {
        DeleteObject(hf);
        return;
     }

    *piY += iHeight;

    SelectObject(hdc, hfold);
    DeleteObject(hf);
}

////    ResetCaret - Used during paint by each DSP*.CPP
//
//
void ResetCaret(int iX, int iY, int iHeight) 
{
    g_iCaretX = iX;
    g_iCaretY = iY;

    if (g_iCaretHeight != iHeight) 
    {
        g_iCaretHeight = iHeight;
        HideCaret(g_hTextWnd);
        DestroyCaret();
        CreateCaret(g_hTextWnd, NULL, 0, g_iCaretHeight);
        SetCaretPos(g_iCaretX, g_iCaretY);
        ShowCaret(g_hTextWnd);
    }
    else
    {
        SetCaretPos(g_iCaretX, g_iCaretY);
    }
}

////    Paint - Redraw part or all of client area
//
//
void Paint(
    HWND         hWnd) 
{

    PAINTSTRUCT  ps          = {0};
    HDC          hdc         = NULL;
    int          iPos        = 0;
    int          iY          = 0;
    int          iLineHeight = 0;
    RECT         rcText      = {0};
    RECT         rcClear     = {0};

    hdc = BeginPaint(hWnd, &ps);

    // Remove the settings dialog from the repaint rectangle
    if (ps.fErase) 
    {
        // Clear below the settings dialog
        if (!g_fPresentation) 
        {
            rcClear = ps.rcPaint;
            if (rcClear.right > g_iSettingsWidth) 
            {
                rcClear.right = g_iSettingsWidth;
            }
            if (rcClear.top < g_iSettingsHeight) 
            {
                rcClear.top = g_iSettingsHeight;
            }

            FillRect(ps.hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));
        }
    }

    // Clear top and left margin
    GetClientRect(hWnd, &rcText);

    // Left margin
    rcClear = rcText;
    rcClear.left  = g_fPresentation ? 0 : g_iSettingsWidth;
    rcClear.right = rcClear.left + 10;
    FillRect(ps.hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));

    // Top margin
    rcClear = rcText;
    rcClear.left  = g_fPresentation ? 0 : g_iSettingsWidth;
    rcClear.top = 0;
    rcClear.bottom = 8;
    FillRect(ps.hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));

    rcText.left = g_fPresentation ? 10 : g_iSettingsWidth + 10;
    rcText.top  = 8;

    iPos = 0;
    iY = rcText.top;

    if (g_fPresentation) 
    {
        iLineHeight = rcText.bottom*9/20;
    } 
    else
    {
        iLineHeight = 40;
    }

    if (g_fShowLogical) 
    {
        if (!g_fPresentation) 
        {
            Header(hdc, "Logical characters (ScriptGetCmap, ExtTextOut(ETO_GLYPHINDEX))", &rcText, &iY);
        }
        PaintLogical(hdc, &iY, &rcText, iLineHeight);
    }

    if (g_fShowPlainText)
    {
        if (!g_fPresentation) 
        {
            Header(hdc, "Plain text (ScriptStringAnalyse, ScriptStringOut, ScriptStringFree)", &rcText, &iY);
        }
        PaintPlainText(hdc, &iY, &rcText, iLineHeight);
    }

    if (g_fShowFancyText  &&  !g_fPresentation) 
    {
        Header(hdc, "Formatted text (ScriptItemize, ScriptLayout, ScriptShape, ScriptPlace, ScriptTextOut)", &rcText, &iY);
        PaintFormattedText(hdc, &iY, &rcText, iLineHeight);
    }

    // Clear any remaining space below the text
    if (    ps.fErase
        &&  iY < rcText.bottom) 
    {
        rcClear = rcText;
        rcClear.top = iY;
        FillRect(ps.hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));
    }

    EndPaint(hWnd, &ps);
}

////    TextWndProc - Main window message handler and dispatcher
//
//
LRESULT CALLBACK TextWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    HDC hdc = NULL;
    LRESULT lProcessed = 0; 
    switch (message) 
    {
        case WM_CREATE:
            hdc = GetDC(hWnd);
            g_iLogPixelsY = GetDeviceCaps(hdc, LOGPIXELSY);
            ReleaseDC(hWnd, hdc);
            break;

        case WM_ERASEBKGND:
            lProcessed = 0;       // Leave Paint to erase the background
            break;

        case WM_CHAR:

            if (!g_bUnicodeWnd) 
            {
                // Convert ANSI keyboard data to Unicode
                int   iCP = 0;
                switch (PRIMARYLANGID(LOWORD(GetKeyboardLayout(NULL)))) 
                {
                    case LANG_ARABIC:   iCP = 1256;   break;
                    case LANG_HEBREW:   iCP = 1255;   break;
                    case LANG_THAI:     iCP =  874;   break;
                    default:            iCP = 1252;   break;
                }
                DWORD tmpChr = wParam;

                MultiByteToWideChar(iCP, 0, (char*)&tmpChr, 1, (WCHAR*)&wParam, 1);
            }

            if (LOWORD(wParam) == 0x1B) 
            {
                // Exit presentation mode
                g_fPresentation = FALSE;
                ShowWindow(g_hSettingsDlg, SW_SHOW);
                UpdateWindow(g_hSettingsDlg);
                InvalidateText();

            }
            else
            {
                EditChar(LOWORD(wParam));
            }
            break;

        case WM_KEYDOWN:
            EditKeyDown(LOWORD(wParam));
            break;

        case WM_KEYUP:

            if (wParam != VK_ESCAPE) 
            {
                goto DefaultWindowProcedure;
            }
            // Eat all escape key processing
            break;

        case WM_LBUTTONDOWN:
            g_iMouseDownX = LOWORD(lParam);  // horizontal position of cursor
            g_iMouseDownY = HIWORD(lParam);  // vertical position of cursor
            g_fMouseDown  = TRUE;
            SetFocus(hWnd);
            break;

        case WM_MOUSEMOVE:
            // Treat movement like lbuttonup while lbutton is down,
            // so the selection tracks the cursor movement.
            if (wParam & MK_LBUTTON)
            {
                g_iMouseUpX = LOWORD(lParam);  // horizontal position of cursor
                g_iMouseUpY = HIWORD(lParam);  // vertical position of cursor
                g_fMouseUp = TRUE;
                InvalidateText();
                SetActiveWindow(hWnd);
            }
            break;

        case WM_LBUTTONUP:
            g_iMouseUpX = LOWORD(lParam);  // horizontal position of cursor
            g_iMouseUpY = HIWORD(lParam);  // vertical position of cursor
            g_fMouseUp = TRUE;
            InvalidateText();
            SetActiveWindow(hWnd);
            break;

        case WM_SETFOCUS:
            CreateCaret(hWnd, NULL, 0, g_iCaretHeight);
            SetCaretPos(g_iCaretX, g_iCaretY);
            ShowCaret(hWnd);
            break;

        case WM_KILLFOCUS:
            DestroyCaret();
            break;

        case WM_GETMINMAXINFO:

            // Don't let text window size drop too low

            ((LPMINMAXINFO)lParam)->ptMinTrackSize.x = g_fPresentation ? 10 : g_iMinWidth;
            ((LPMINMAXINFO)lParam)->ptMinTrackSize.y = g_fPresentation ? 10 : g_iMinHeight;
            lProcessed = 0;
            break;

        case WM_PAINT:
            Paint(hWnd);
            break;

        case WM_DESTROY:
            DestroyWindow(g_hSettingsDlg);
            PostQuitMessage(0);
            lProcessed = 0;
            break;

        default:
        DefaultWindowProcedure:
            if (g_bUnicodeWnd) 
            {
                lProcessed = DefWindowProcW(hWnd, message, wParam, lParam);
            } 
            else
            {
                lProcessed = DefWindowProcA(hWnd, message, wParam, lParam);
            }
    }

    return lProcessed;
}

////    CreateTextWindow - create window class and window
//
//      Attempts to use a Unicode window, if this fails uses an ANSI
//      window.
//
//      For example the Unicode window will succeed on Windows NT and
//      Windows CE, but fail on Windows 9x.
HWND CreateTextWindow() 
{
    WNDCLASSA  wcA  = {0};
    WNDCLASSW  wcW  = {0};
    HWND       hWnd = NULL;

    // Try registering as a Unicode window
    wcW.style         = CS_HREDRAW | CS_VREDRAW;
    wcW.lpfnWndProc   = TextWndProc;
    wcW.cbClsExtra    = 0;
    wcW.cbWndExtra    = 0;
    wcW.hInstance     = g_hInstance;
    wcW.hIcon         = LoadIconW(g_hInstance, APPNAMEW);
    wcW.hCursor       = LoadCursorW(NULL, (WCHAR*)IDC_ARROW);
    wcW.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcW.lpszMenuName  = APPNAMEW;
    wcW.lpszClassName = APPNAMEW;

    if (RegisterClassW(&wcW)) 
    {
        // Use a Unicode window
        g_bUnicodeWnd = TRUE;
        hWnd  = CreateWindowW(
            APPNAMEW, APPTITLEW,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, 0,
            CW_USEDEFAULT, 0,
            NULL, NULL,
            g_hInstance,
            NULL);

    }
    else
    {
        // Must use an ANSI window.
        wcA.style         = CS_HREDRAW | CS_VREDRAW;
        wcA.lpfnWndProc   = TextWndProc;
        wcA.cbClsExtra    = 0;
        wcA.cbWndExtra    = 0;
        wcA.hInstance     = g_hInstance;
        wcA.hIcon         = LoadIconA(g_hInstance, APPNAMEA);
        wcA.hCursor       = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
        wcA.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wcA.lpszMenuName  = APPNAMEA;
        wcA.lpszClassName = APPNAMEA;

        if (!RegisterClassA(&wcA)) 
        {
            hWnd = NULL;
        }
        else
        {
            g_bUnicodeWnd = FALSE;

            hWnd  = CreateWindowA(
                APPNAMEA, APPTITLEA,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0,
                CW_USEDEFAULT, 0,
                NULL, NULL,
                g_hInstance,
                NULL);
        }
    }

    return hWnd;
}
