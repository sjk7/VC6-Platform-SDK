////    SETTINGS.CPP - Handles settings dialog
//
//
#include "precomp.hxx"
#include "global.h"

////    HexToInt - convert hex digit string to int value
//
//      Ignores 'x' in the string so accepts input like '0x0100'.
int HexToInt(char szHex[])
{

    int i = 0;
    int h = 0;
    //int d = 0;

    while (szHex[i]  &&  szHex[i] != ' ')
    {
        if (szHex[i] >= '0'  &&  szHex[i] <= '9')
        {

            h = h*16 + szHex[i] - '0';
            //d = d*10 + szHex[i] - '0';

        }
        else if (szHex[i] >= 'a'  &&  szHex[i] <= 'f') 
        {
            h = h*16 + 10 + szHex[i] - 'a';

        }
        else if (szHex[i] >= 'A'  &&  szHex[i] <= 'F')
        {
            h = h*16 + 10 + szHex[i] - 'A';

        }
        else if (szHex[i] != ' '  &&  szHex[i] != ','  &&  szHex[i] != 'x'  &&  szHex[i] != 'X') 
        {
            h = -1;
            break;
        }
        i++;
    }

    return h;
}

BOOL ChangeFont(HWND hDlg, int iStyle, int idFont, int idSize, int idBold, int idItalic, int idUnderline) 
{
    int   iHeight = 0;
    char  sFaceName[100];
    int   i = 0;
    BOOL bSucess = TRUE;

    // Get size
    i = (int)SendDlgItemMessage(hDlg, idSize, CB_GETCURSEL, 0, 0);
    if (SendDlgItemMessage(hDlg, idSize, CB_GETLBTEXT, i, (LPARAM)sFaceName) == CB_ERR) 
    {
        bSucess = FALSE;
        goto RETURN;
    }
    iHeight = -MulDiv(atoi(sFaceName), g_iLogPixelsY, 72);

    // Get facename
    i = (int)SendDlgItemMessage(hDlg, idFont, CB_GETCURSEL, 0, 0);
    if (SendDlgItemMessage(hDlg, idFont, CB_GETLBTEXT, i, (LPARAM)sFaceName) == CB_ERR) 
    {
        bSucess = FALSE;
        goto RETURN;
    }

    SetStyle(
        iStyle,
        iHeight,
        IsDlgButtonChecked(hDlg, idBold)      == BST_CHECKED ? 700 : 400,
        IsDlgButtonChecked(hDlg, idItalic)    == BST_CHECKED,
        IsDlgButtonChecked(hDlg, idUnderline) == BST_CHECKED,
        sFaceName);



    InvalidateText();
    RETURN:
    return bSucess;
}

BOOL Command(HWND hDlg, int iCmd, int iNotify, HWND hItemWnd) 
{
    char str[100];
    WCHAR  wc;
    int    i = 0;
    char   hex[] = "0123456789abcdef";
    BOOL bProcessed = TRUE;

    switch(iCmd) 
    {
    case IDC_LANGUAGE:
        if (iNotify == CBN_SELCHANGE) 
        {
            i = (int)SendMessage(hItemWnd, CB_GETCURSEL, 0, 0);
            if (SendMessage(hItemWnd, CB_GETLBTEXT, i, (LPARAM)str) != CB_ERR) 
            {
                wc = (WCHAR)HexToInt(str);
                g_ScriptControl.uDefaultLanguage = wc;
                InvalidateText();
            }
        } 
        else if (iNotify == CBN_EDITCHANGE)
        {
            if (SendMessage(hItemWnd, WM_GETTEXT, sizeof(str), (LPARAM)str)) 
            {
                wc = (WCHAR)HexToInt(str);
                g_ScriptControl.uDefaultLanguage = wc;
                InvalidateText();
            }
        }
        break;

    case IDC_INSERT_CODEPOINT:
        if (GetDlgItemTextA(g_hSettingsDlg, IDC_CODEPOINT, str, sizeof(str))) 
        {
            wc = (WCHAR)HexToInt(str);
            if (TextInsert(g_iCurChar, &wc, 1)) 
            {
                g_iCurChar++;
                InvalidateText();
            }
        }
        break;

    case IDC_HIGHLIGHT_FROM:  /* fall-through*/
    case IDC_HIGHLIGHT_TO:
        InvalidateText();
        break;

    case IDC_LINEFILL:
        g_fFillLines = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_LTR:
        g_ScriptState.uBidiLevel = 0;
        SendDlgItemMessage(hDlg, IDC_LTR, BM_SETSTATE, TRUE, 0);
        SendDlgItemMessage(hDlg, IDC_RTL, BM_SETSTATE, FALSE, 0);
        InvalidateText();
        break;

    case IDC_RTL:
        g_ScriptState.uBidiLevel = 1;
        SendDlgItemMessage(hDlg, IDC_RTL, BM_SETSTATE, TRUE, 0);
        SendDlgItemMessage(hDlg, IDC_LTR, BM_SETSTATE, FALSE, 0);
        InvalidateText();
        break;

    case IDC_CONTROL_CONTEXT:
        g_ScriptControl.fContextDigits = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_DIGIT_SUBSTITUTE:
        g_ScriptState.fDigitSubstitute = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_ARANUMCONTEXT:
        g_ScriptState.fArabicNumContext = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_LEGACY_BIDI:
        g_ScriptControl.fLegacyBidiClass = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_OVERRIDE:
        g_ScriptState.fOverrideDirection = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_CONTROL_CHARS:
        g_ScriptState.fDisplayZWG = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_LOGICAL_ORDER:
        g_fLogicalOrder = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_NO_GLYPH_INDEX:
        g_fNoGlyphIndex = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_LOGICAL:
        g_fShowLogical = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_PLAINTEXT:
        g_fShowPlainText = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_PLAINTEXT_FIT:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED) 
        {
            g_dwSSAflags |= SSA_FIT;
        }
        else 
        {
            g_dwSSAflags &= ~SSA_FIT;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_CLIP:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED) 
        {
            g_dwSSAflags |= SSA_CLIP;
        }
        else
        {
            g_dwSSAflags &= ~SSA_CLIP;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_TAB:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED)
        {
            g_dwSSAflags |= SSA_TAB;
        }
        else
        {
            g_dwSSAflags &= ~SSA_TAB;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_DX:
        g_fOverrideDx = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        memset(g_iWidthBuf, 0, sizeof(int)*g_iTextLen+1);
        InvalidateText();
        break;

    case IDC_PLAINTEXT_FALLBACK:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED)
        {
            g_dwSSAflags |= SSA_FALLBACK;
        }
        else
        {
            g_dwSSAflags &= ~SSA_FALLBACK;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_LINK:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED)
        {
            g_dwSSAflags |= SSA_LINK;
        }
        else
        {
            g_dwSSAflags &= ~SSA_LINK;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_HOTKEY:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED)
        {
            g_dwSSAflags |= SSA_HOTKEY;
        }
        else
        {
            g_dwSSAflags &= ~SSA_HOTKEY;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_PASSWORD:
        if (IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED) 
        {
            g_dwSSAflags |= SSA_PASSWORD;
        }
        else
        {
            g_dwSSAflags &= ~SSA_PASSWORD;
        }
        InvalidateText();
        break;

    case IDC_PLAINTEXT_FONT:  /* fall-through */
    case IDC_PLAINTEXT_SIZE:
        if (iNotify != CBN_SELCHANGE) 
        {
            bProcessed = FALSE;
            break;
        }

    case IDC_PLAINTEXT_BOLD:  /* fall-through */
    case IDC_PLAINTEXT_ITALIC:  /* fall-through */
    case IDC_PLAINTEXT_UNDERLINE:
        ChangeFont(
            hDlg,
            0,
            IDC_PLAINTEXT_FONT,
            IDC_PLAINTEXT_SIZE,
            IDC_PLAINTEXT_BOLD,
            IDC_PLAINTEXT_ITALIC,
            IDC_PLAINTEXT_UNDERLINE);
        break;

    case IDC_FORMATTED:
        g_fShowFancyText = IsDlgButtonChecked(hDlg, iCmd) == BST_CHECKED;
        InvalidateText();
        break;

    case IDC_FANCY_FONT1:  /* fall-through */
    case IDC_FANCY_SIZE1:
        if (iNotify != CBN_SELCHANGE) 
        {
            bProcessed = FALSE;
            break;
        }
    case IDC_FANCY_BOLD1:  /* fall-through */
    case IDC_FANCY_ITALIC1:  /* fall-through */
    case IDC_FANCY_UNDERLINE1:
        ChangeFont(
            hDlg,
            1,
            IDC_FANCY_FONT1,
            IDC_FANCY_SIZE1,
            IDC_FANCY_BOLD1,
            IDC_FANCY_ITALIC1,
            IDC_FANCY_UNDERLINE1);
        break;

    case IDC_FANCY_FONT2:  /* fall-through */
    case IDC_FANCY_SIZE2:
        if (iNotify != CBN_SELCHANGE) 
        {
            bProcessed = FALSE;
            break;
        }
        
    case IDC_FANCY_BOLD2:  /* fall-through */
    case IDC_FANCY_ITALIC2:  /* fall-through */
    case IDC_FANCY_UNDERLINE2:
        ChangeFont(
            hDlg,
            2,
            IDC_FANCY_FONT2,
            IDC_FANCY_SIZE2,
            IDC_FANCY_BOLD2,
            IDC_FANCY_ITALIC2,
            IDC_FANCY_UNDERLINE2);
        break;

    case IDC_FANCY_FONT3:  /* fall-through */
    case IDC_FANCY_SIZE3:
        if (iNotify != CBN_SELCHANGE)
        {
            bProcessed = FALSE;
            break;
        }

    case IDC_FANCY_BOLD3:  /* fall-through */
    case IDC_FANCY_ITALIC3:  /* fall-through */
    case IDC_FANCY_UNDERLINE3:
        ChangeFont(
            hDlg,
            3,
            IDC_FANCY_FONT3,
            IDC_FANCY_SIZE3,
            IDC_FANCY_BOLD3,
            IDC_FANCY_ITALIC3,
            IDC_FANCY_UNDERLINE3);
        break;

    case IDC_FANCY_FONT4:  /* fall-through */
    case IDC_FANCY_SIZE4:
        if (iNotify != CBN_SELCHANGE)
        {
            bProcessed = FALSE;
            break;
        }

    case IDC_FANCY_BOLD4:  /* fall-through */
    case IDC_FANCY_ITALIC4:  /* fall-through */
    case IDC_FANCY_UNDERLINE4:
        ChangeFont(
            hDlg,
            4,
            IDC_FANCY_FONT4,
            IDC_FANCY_SIZE4,
            IDC_FANCY_BOLD4,
            IDC_FANCY_ITALIC4,
            IDC_FANCY_UNDERLINE4);
        break;

    case IDC_FORMAT1:  /* fall-through */
    case IDC_FORMAT2:  /* fall-through */
    case IDC_FORMAT3:  /* fall-through */
    case IDC_FORMAT4:
        if (g_iTo < g_iFrom) 
        {
            i=g_iTo;  g_iTo=g_iFrom;  g_iFrom=i;
        }

        if (    g_iFrom <  g_iTo
            &&  g_iFrom <  g_iTextLen
            &&  g_iTo   <= g_iTextLen) 
        {

            i=1; // Default
            switch(iCmd) {
                case IDC_FORMAT1:  i=1;  break;
                case IDC_FORMAT2:  i=2;  break;
                case IDC_FORMAT3:  i=3;  break;
                case IDC_FORMAT4:  i=4;  break;
            }
            StyleSetRange(i, g_iFrom, g_iTo-g_iFrom);
            ASSERT(StyleCheckRange());
            InvalidateText();
        }
        break;

    case IDC_APPLYDIGITSUBST:
        ScriptApplyDigitSubstitution(NULL, &g_ScriptControl, &g_ScriptState);

        SendDlgItemMessage(hDlg, IDC_DIGIT_SUBSTITUTE,  BM_SETCHECK, g_ScriptState.fDigitSubstitute ? BST_CHECKED : BST_UNCHECKED, 0);
        SendDlgItemMessage(hDlg, IDC_CONTROL_CONTEXT,   BM_SETCHECK, g_ScriptControl.fContextDigits ? BST_CHECKED : BST_UNCHECKED, 0);
        str[0] = '0';
        str[1] = 'x';
        str[2] = hex[(g_ScriptControl.uDefaultLanguage & 0xf0) >> 4];
        str[3] = hex[ g_ScriptControl.uDefaultLanguage & 0x0f];
        str[4] = 0;
        SendDlgItemMessage(hDlg, IDC_LANGUAGE,          CB_SELECTSTRING, 0, (LPARAM) str);

        InvalidateText();
        break;

    case IDC_PRESENTATION:
        g_fPresentation = TRUE;
        ShowWindow(g_hSettingsDlg, SW_HIDE);
        SetFocus(g_hTextWnd);
        InvalidateText();
        break;

    case IDC_SHOWLEVELS:
        g_fShowLevels = !g_fShowLevels;
        if (g_fShowLevels)
        {
            SetDlgItemTextA(g_hSettingsDlg, IDC_SHOWLEVELS, "Hide levels");
        }
        else
        {
            SetDlgItemTextA(g_hSettingsDlg, IDC_SHOWLEVELS, "Show levels");
        }
        SetFocus(g_hTextWnd);
        InvalidateText();
        break;
    default:
        bProcessed = FALSE;

    }  // end switch

    return bProcessed;
}

int CALLBACK InitOneFace(
    const ENUMLOGFONTEXA   *lpelfe,    // pointer to logical-font data
    const NEWTEXTMETRICEXA *lpntme,    // pointer to physical-font data
    int                     FontType,  // type of font
    LPARAM                  lParam)    // application-defined data
{
    if (SendDlgItemMessage(
            (HWND)lParam,
            IDC_PLAINTEXT_FONT,
            CB_FINDSTRINGEXACT,
            0, (LPARAM)lpelfe->elfLogFont.lfFaceName) == CB_ERR)
   {
        // It's a new font name
        SendDlgItemMessage(
            (HWND)lParam,
            IDC_PLAINTEXT_FONT,
            CB_ADDSTRING,
            0, (LPARAM)lpelfe->elfLogFont.lfFaceName);

        SendDlgItemMessage(
            (HWND)lParam,
            IDC_FANCY_FONT1,
            CB_ADDSTRING,
            0, (LPARAM)lpelfe->elfLogFont.lfFaceName);

        SendDlgItemMessage(
            (HWND)lParam,
            IDC_FANCY_FONT2,
            CB_ADDSTRING,
            0, (LPARAM)lpelfe->elfLogFont.lfFaceName);

        SendDlgItemMessage(
            (HWND)lParam,
            IDC_FANCY_FONT3,
            CB_ADDSTRING,
            0, (LPARAM)lpelfe->elfLogFont.lfFaceName);

        SendDlgItemMessage(
            (HWND)lParam,
            IDC_FANCY_FONT4,
            CB_ADDSTRING,
            0, (LPARAM)lpelfe->elfLogFont.lfFaceName);
    }


    return 1;   // Continue enumeration
}

void InitOneSize(
    HWND   hDlg,
    char  *str) 
{

    SendDlgItemMessage(hDlg, IDC_PLAINTEXT_SIZE, CB_ADDSTRING, 0, (LPARAM)str);
    SendDlgItemMessage(hDlg, IDC_FANCY_SIZE1,    CB_ADDSTRING, 0, (LPARAM)str);
    SendDlgItemMessage(hDlg, IDC_FANCY_SIZE2,    CB_ADDSTRING, 0, (LPARAM)str);
    SendDlgItemMessage(hDlg, IDC_FANCY_SIZE3,    CB_ADDSTRING, 0, (LPARAM)str);
    SendDlgItemMessage(hDlg, IDC_FANCY_SIZE4,    CB_ADDSTRING, 0, (LPARAM)str);
}

void InitSelection(HWND hDlg, int idFace, int idSize, char *sFaceName)
{
    int i = 0;

    i = (int)SendDlgItemMessage(hDlg, idFace, CB_FINDSTRINGEXACT, 0, (LPARAM)sFaceName);
    if (i == CB_ERR) 
    {
        SendDlgItemMessage(hDlg, idFace, CB_SETCURSEL, 0, 0);
    }
    else
    {
        SendDlgItemMessage(hDlg, idFace, CB_SETCURSEL, i, 0);
    }

    SendDlgItemMessage(hDlg, idSize, CB_SETCURSEL, 10, 0);   // Selection 10 is 18 point
}

void InitFaceLists(HWND hDlg) 
{
    HDC      hdc = NULL;
    LOGFONTA lf = {0};

    SetLogFont(&lf, 0, 0, 0, 0, "");
    hdc = GetDC(g_hTextWnd);
    EnumFontFamiliesExA(hdc, &lf, (FONTENUMPROCA)InitOneFace, (LPARAM)hDlg, 0);
    ReleaseDC(g_hTextWnd, hdc);

    // Initialise sizes
    InitOneSize(hDlg, "6");
    InitOneSize(hDlg, "7");
    InitOneSize(hDlg, "8");
    InitOneSize(hDlg, "9");
    InitOneSize(hDlg, "10");
    InitOneSize(hDlg, "11");
    InitOneSize(hDlg, "12");
    InitOneSize(hDlg, "13");
    InitOneSize(hDlg, "14");
    InitOneSize(hDlg, "16");
    InitOneSize(hDlg, "18");
    InitOneSize(hDlg, "20");
    InitOneSize(hDlg, "22");
    InitOneSize(hDlg, "24");
    InitOneSize(hDlg, "28");
    InitOneSize(hDlg, "32");
    InitOneSize(hDlg, "36");
    InitOneSize(hDlg, "48");
    InitOneSize(hDlg, "60");
    InitOneSize(hDlg, "72");
    InitOneSize(hDlg, "90");
    InitOneSize(hDlg, "108");
    InitOneSize(hDlg, "126");
    InitOneSize(hDlg, "144");

    // Select standard fonts and sizes
    InitSelection(hDlg, IDC_PLAINTEXT_FONT, IDC_PLAINTEXT_SIZE, "Microsoft Sans Serif");

    InitSelection(hDlg, IDC_FANCY_FONT1,    IDC_FANCY_SIZE1,    "Microsoft Sans Serif");
    InitSelection(hDlg, IDC_FANCY_FONT2,    IDC_FANCY_SIZE2,    "Mangal");
    InitSelection(hDlg, IDC_FANCY_FONT3,    IDC_FANCY_SIZE3,    "Latha");
    InitSelection(hDlg, IDC_FANCY_FONT4,    IDC_FANCY_SIZE4,    "Arial");

    ChangeFont(hDlg, 0, IDC_PLAINTEXT_FONT, IDC_PLAINTEXT_SIZE, IDC_PLAINTEXT_BOLD, IDC_PLAINTEXT_ITALIC, IDC_PLAINTEXT_UNDERLINE);
    ChangeFont(hDlg, 1, IDC_FANCY_FONT1, IDC_FANCY_SIZE1, IDC_FANCY_BOLD1, IDC_FANCY_ITALIC1, IDC_FANCY_UNDERLINE1);
    ChangeFont(hDlg, 2, IDC_FANCY_FONT2, IDC_FANCY_SIZE2, IDC_FANCY_BOLD2, IDC_FANCY_ITALIC2, IDC_FANCY_UNDERLINE2);
    ChangeFont(hDlg, 3, IDC_FANCY_FONT3, IDC_FANCY_SIZE3, IDC_FANCY_BOLD3, IDC_FANCY_ITALIC3, IDC_FANCY_UNDERLINE3);
    ChangeFont(hDlg, 4, IDC_FANCY_FONT4, IDC_FANCY_SIZE4, IDC_FANCY_BOLD4, IDC_FANCY_ITALIC4, IDC_FANCY_UNDERLINE4);
}

const char *szUniChar[] = {
    "200B ZWSP",
    "200C ZWNJ",
    "200D ZWJ",
    "200E LRM",
    "200F RLM",
    "202A LRE",
    "202B RLE",
    "202C PDF",
    "202D LRO",
    "202E RLO",
    "206A ISS",
    "206B ASS",
    "206E NADS",
    "206F NODS",
    "0908 Letter Ii",
    "0915 Letter Ka",
    "093f Vowel I",
    "094D Virama",
};

const char *szLanguage[] = {
    "0x00  Neutral"   ,
    "0x36  Afrikaans" ,
    "0x1c  Albanian"  ,
    "0x01  Arabic"    ,
    "0x2b  Armenian"  ,
    "0x4d  Assamese"  ,
    "0x2c  Azeri"     ,
    "0x2d  Basque"    ,
    "0x23  Belarusian",
    "0x45  Bengali"   ,
    "0x02  Bulgarian" ,
//  "      Burmese"   ,
    "0x03  Catalan"   ,
    "0x04  Chinese"   ,
    "0x1a  Croatian"  ,
    "0x05  Czech"     ,
    "0x06  Danish"    ,
    "0x13  Dutch"     ,
    "0x09  English"   ,
    "0x25  Estonian"  ,
    "0x38  Faeroese"  ,
    "0x29  Farsi"     ,
    "0x0b  Finnish"   ,
    "0x0c  French"    ,
    "0x37  Georgian"  ,
    "0x07  German"    ,
    "0x08  Greek"     ,
    "0x47  Gujarati"  ,
    "0x0d  Hebrew"    ,
    "0x39  Hindi"     ,
    "0x0e  Hungarian" ,
    "0x0f  Icelandic" ,
    "0x21  Indonesian",
    "0x10  Italian"   ,
    "0x11  Japanese"  ,
    "0x4b  Kannada"   ,
    "0x60  Kashmiri"  ,
    "0x3f  Kazak"     ,
//  "      Khmer"     ,
    "0x57  Konkani"   ,
    "0x12  Korean"    ,
//  "      Lao"       ,
    "0x26  Latvian"   ,
    "0x27  Lithuanian",
    "0x2f  Macedonian",
    "0x3e  Malay"     ,
    "0x4c  Malayalam" ,
    "0x58  Manipuri"  ,
    "0x4e  Marathi"   ,
    "0x61  Nepali"    ,
//  "      Mongolian" ,
    "0x14  Norwegian" ,
    "0x48  Oriya"     ,
    "0x15  Polish"    ,
    "0x16  Portuguese",
    "0x46  Punjabi"   ,
    "0x18  Romanian"  ,
    "0x19  Russian"   ,
    "0x4f  Sanskrit"  ,
    "0x1a  Serbian"   ,
    "0x59  Sindhi"    ,
    "0x1b  Slovak"    ,
    "0x24  Slovenian" ,
    "0x0a  Spanish"   ,
    "0x41  Swahili"   ,
    "0x1d  Swedish"   ,
    "0x49  Tamil"     ,
    "0x44  Tatar"     ,
    "0x4a  Telugu"    ,
    "0x1e  Thai"      ,
//  "      Tibetan"   ,
    "0x1f  Turkish"   ,
    "0x22  Ukrainian" ,
    "0x20  Urdu"      ,
    "0x43  Uzbek"     ,
    "0x2a  Vietnamese",
};

INT_PTR CALLBACK SettingsDlgProc(
        HWND    hDlg,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam) 
{
        int i = 0;

        switch (uMsg) 
        {
        case WM_INITDIALOG:
            // Populate the Unicode codepoint combo box
            for (i = 0; i < sizeof(szUniChar)/sizeof(szUniChar[0]); ++i) 
            {
                SendDlgItemMessage(hDlg, IDC_CODEPOINT, CB_ADDSTRING, 0, (LPARAM)szUniChar[i]);
            }

            for (i = 0; i < sizeof(szLanguage)/sizeof(szLanguage[0]); ++i) 
            {
                SendDlgItemMessage(hDlg, IDC_LANGUAGE, CB_ADDSTRING, 0, (LPARAM)szLanguage[i]);
            }

            SendDlgItemMessage(hDlg, IDC_LANGUAGE, CB_SETCURSEL, 0, 0);
            SendDlgItemMessage(hDlg, IDC_LTR,       BM_SETSTATE, TRUE, 0);
            SendDlgItemMessage(hDlg, IDC_HORIZ,     BM_SETSTATE, TRUE, 0);
            SendDlgItemMessage(hDlg, IDC_LOGICAL,   BM_SETCHECK, BST_CHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_PLAINTEXT, BM_SETCHECK, BST_CHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_FORMATTED, BM_SETCHECK, BST_CHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_LINEFILL,  BM_SETCHECK, BST_CHECKED, 0);
            SendDlgItemMessage(hDlg, IDC_PLAINTEXT_FALLBACK, BM_SETCHECK, BST_CHECKED, 0);

            InitFaceLists(hDlg);
            break;

        case WM_COMMAND:
            Command(hDlg, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
            break;

        }


        return FALSE;
}
