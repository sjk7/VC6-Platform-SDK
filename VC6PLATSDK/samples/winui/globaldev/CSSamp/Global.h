////    GLOBAL.H - Global variables for CSSAMP
//
//

////    Constants
//
//

#define APPNAMEA   "CSSamp"
#define APPTITLEA  "CSSamp - Uniscribe complex script sample application"
#define APPNAMEW   L"CSSamp"
#define APPTITLEW  L"CSSamp - Uniscribe complex script sample application"

const int MAX_STYLES = 5;      // Better implementation would use dynamic memory
const int MAX_TEXT   = 10000;  // Buffer size in Unicode characters

const int CARET_SECTION_LOGICAL    = 0;
const int CARET_SECTION_PLAINTEXT  = 1;
const int CARET_SECTION_FORMATTED  = 2;

////    RUN - A run of characters with similar attributes
//
//
struct RUN {
    struct RUN       *pNext;
    int               iLen;
    int               iStyle;       // Index to style sheet (global 'g_style').
    SCRIPT_ANALYSIS   analysis;     // Uniscribe analysis
};

////    STYLE - Text attribute
//
struct STYLE {
    HFONT         hf;       // Handle to font described by lf
    SCRIPT_CACHE  sc;       // Uniscribe cache associated with this style
};

////    Global variables
//
//
#ifdef GLOBALS_HERE
#define GLOBAL
#define GLOBALINIT(a) = a
#else
#define GLOBAL extern
#define GLOBALINIT(a)
#endif


GLOBAL  HINSTANCE       g_hInstance         GLOBALINIT(NULL);  // The one and only instance
GLOBAL  HWND            g_hSettingsDlg      GLOBALINIT(NULL);  // Settings panel
GLOBAL  HWND            g_hTextWnd          GLOBALINIT(NULL);  // Text display/editing panel
GLOBAL  BOOL            g_bUnicodeWnd       GLOBALINIT(FALSE); // If text window is Unicode
GLOBAL  int             g_iSettingsWidth;
GLOBAL  int             g_iSettingsHeight;
GLOBAL  BOOL            g_fPresentation     GLOBALINIT(FALSE); // Hide settings, show text very large
GLOBAL  BOOL            g_fShowLevels       GLOBALINIT(FALSE); // Show bidi levels for each codepoint
GLOBAL  int             g_iMinWidth;                           // Main window minimum size
GLOBAL  int             g_iMinHeight;

GLOBAL  BOOL            g_fOverrideDx       GLOBALINIT(FALSE);  // Provide UI for changing logical widths
GLOBAL  BOOL            g_fFillLines        GLOBALINIT(TRUE);

GLOBAL  SCRIPT_CONTROL  g_ScriptControl     GLOBALINIT({0});
GLOBAL  SCRIPT_STATE    g_ScriptState       GLOBALINIT({0});
GLOBAL  BOOL            g_fNullState        GLOBALINIT(FALSE);

GLOBAL  BOOL            g_fLogicalOrder     GLOBALINIT(FALSE);
GLOBAL  BOOL            g_fNoGlyphIndex     GLOBALINIT(FALSE);

GLOBAL  BOOL            g_fShowLogical      GLOBALINIT(TRUE);
GLOBAL  BOOL            g_fShowWidths       GLOBALINIT(FALSE);
GLOBAL  BOOL            g_fShowStyles       GLOBALINIT(FALSE);

GLOBAL  BOOL            g_fShowPlainText    GLOBALINIT(TRUE);
GLOBAL  DWORD           g_dwSSAflags        GLOBALINIT(SSA_FALLBACK);

GLOBAL  BOOL            g_fShowFancyText    GLOBALINIT(TRUE);
GLOBAL  STYLE           g_style[MAX_STYLES];                    // 0 for plaintext, 1-4 for formatted text



GLOBAL  WCHAR           g_wcBuf[MAX_TEXT];
GLOBAL  int             g_iWidthBuf[MAX_TEXT];

GLOBAL  RUN            *g_pFirstFormatRun   GLOBALINIT(NULL);   // Formatting info

GLOBAL  int             g_iTextLen          GLOBALINIT(0);

GLOBAL  int             g_iCaretX           GLOBALINIT(0);      // Caret position in text window
GLOBAL  int             g_iCaretY           GLOBALINIT(0);      // Caret position in text window
GLOBAL  int             g_iCaretHeight      GLOBALINIT(0);      // Caret height in pixels
GLOBAL  int             g_fUpdateCaret      GLOBALINIT(TRUE);   // Caret requires updating

GLOBAL  int             g_iCaretSection     GLOBALINIT(CARET_SECTION_LOGICAL);  // Whether caret is in logical, plain or formatted text
GLOBAL  int             g_iCurChar          GLOBALINIT(0);      // Caret sits on leading edge of buffer[iCurChar]

GLOBAL  int             g_iMouseDownX       GLOBALINIT(0);
GLOBAL  int             g_iMouseDownY       GLOBALINIT(0);
GLOBAL  BOOL            g_fMouseDown        GLOBALINIT(FALSE);
GLOBAL  int             g_iMouseUpX         GLOBALINIT(0);
GLOBAL  int             g_iMouseUpY         GLOBALINIT(0);
GLOBAL  BOOL            g_fMouseUp          GLOBALINIT(FALSE);

GLOBAL  int             g_iFrom             GLOBALINIT(0);      // Highlight start
GLOBAL  int             g_iTo               GLOBALINIT(0);      // Highlight end


GLOBAL  HFONT           g_hfCaption         GLOBALINIT(NULL);   // Caption font
GLOBAL  int             g_iLogPixelsY       GLOBALINIT(0);


////    Function prototypes
//
//

// DspLogcl.cpp
void PaintLogical(
    HDC   hdc,
    int  *piY,
    RECT *prc,
    int   iLineHeight);

// DspPlain.cpp
void PaintPlainText(
    HDC   hdc,
    int  *piY,
    RECT *prc,
    int   iLineHeight);

//  DspFormt.cpp
void PaintFormattedText(
    HDC   hdc,
    int  *piY,
    RECT *prc,
    int   iLineHeight);

// Setting.cpp
INT_PTR CALLBACK SettingsDlgProc(
        HWND    hDlg,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam);


// Text.cpp
void InitText();

BOOL TextInsert(
    int   iPos,
    PWCH  pwc,
    int   iLen);

BOOL TextDelete(
    int iPos,
    int iLen);

// TextWnd.cpp
HWND CreateTextWindow();

void ResetCaret(int iX, int iY, int iHeight);

LRESULT CALLBACK TextWndProc(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam);

void InvalidateText();

// Edit.cpp
BOOL EditChar(WCHAR wc);
BOOL EditKeyDown(WCHAR wc);
void EditFreeCaches();
void EditInsertUnicode();

// Style.cpp
void SetStyle(
    int     iStyle,
    int     iHeight,
    int     iWeight,
    int     iItalic,
    int     iUnderline,
    char   *pcFaceName);

void InitStyles();

void FreeStyles();

void SetLogFont(
    PLOGFONTA   plf,
    int         iHeight,
    int         iWeight,
    int         iItalic,
    int         iUnderline,
    char       *pcFaceName);

void StyleDeleteRange(
    int     iDelPos,
    int     iDelLen);

void StyleExtendRange(
    int     iExtPos,
    int     iExtLen);

void StyleSetRange(
    int    iSetStyle,
    int    iSetPos,
    int    iSetLen);

BOOL StyleCheckRange();

// Debugging support
#define TRACEMSG(a)   {DG.psFile=__FILE__; DG.iLine=__LINE__; DebugMsg a;}
#define ASSERT(a)     {if (!(a)) TRACEMSG(("Assertion failure: "#a));}
#define ASSERTS(a,b)  {if (!(a)) TRACEMSG(("Assertion failure: "#a" - "#b));}
#define ASSERTHR(a,b) {if (!SUCCEEDED(a)) {DG.psFile=__FILE__; \
                        DG.iLine=__LINE__; DG.hrLastError=a; DebugHr b;}}

///     Debug variables
//
struct DebugGlobals {
    char   *psFile;
    int     iLine;
    HRESULT hrLastError;        // Last hresult from GDI
    CHAR    sLastError[100];    // Last error string
};

///     Debug function prototypes
//
extern "C" void WINAPIV DebugMsg(char *fmt, ...);
extern "C" void WINAPIV DebugHr(char *fmt, ...);

GLOBAL DebugGlobals DG   GLOBALINIT({0});
GLOBAL UINT debug        GLOBALINIT(0);
