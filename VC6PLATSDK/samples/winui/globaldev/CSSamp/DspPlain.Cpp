////    DspPlain.CPP - Display plaintext and handle caret placement
//
//      Demonstrates use of the ScriptString APIs
//
//      ScriptStringAnalyse          - Calls ScriptItemise, Shape, Place etc.
//      ScriptStringGetLogicalWidths - Returns logical widths for the entire line
//      ScriptStringXtoCP            - Pixel position to character index
//      ScriptStringCPtoX            - Character index to pixel position
//      ScriptString_pSize           - Gets points to SIZE structure for the line
//      ScriptStringOut              - Render line to device
//      ScriptStringFree             - All analyses must be freed

#include "precomp.hxx"
#include "global.h"

////    PaintPlainTextLine
//
//      Use the ScriptString APIs to analyse and display a line
//      as plain text.
void PaintPlainTextLine(
    HDC      hdc,               // In   Device
    int     *piY,               // In   Y position
    RECT    *prc,               // In   Clipping rectange
    int      iFirst,            // In   First character of line
    int      iLen,
    int      iLineHeight)       // In   Height to advance per line, in pixels
{
    int      iX         = 0;
    HRESULT  hr         = NULL;
    int      iClipWidth = 0;
    int      iTrailing  = 0;         // ScriptStringXtoCP result - offset to nearest cluster edge
    RECT     rc         = {0};
    RECT     rcClear    = {0};
    int      iFrom      = 0;
    int      iTo        = 0;
    DWORD    dwFlags    = 0;

    SCRIPT_CONTROL         ScriptControl = {0};
    SCRIPT_STATE           ScriptState   = {0};
    SCRIPT_STRING_ANALYSIS ssa           = {0};

    // Clear each line before displaying it
    rcClear        = *prc;
    rcClear.top    = *piY;
    rcClear.bottom = *piY + iLineHeight;
    FillRect(hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));

    if (iLen) 
    {
        // There's at least one character to display
        iX = prc->left;

        // Prepare string analysis input parameters
        dwFlags = g_dwSSAflags | SSA_GLYPHS;    // Require glyph generation for ScriptStringOut

        ScriptControl = g_ScriptControl;
        ScriptState   = g_ScriptState;

        if (ScriptState.uBidiLevel & 1)        // ScriptStringAnalyse requires SSA_RTL for rtl reading order
        {
            dwFlags |= SSA_RTL;
        }

        iClipWidth = prc->right - prc->left - 50;

        // Analyse the string.
        //
        // ScriptStringAnalyse calls the ScriptItemize, ScriptShape,
        // ScriptPlace and ScriptBreak APIs and returns a pointer to a block
        // of memory containing all these results.
        if (!g_fOverrideDx)
        {
            // Normal - no DX override testing required
            hr = ScriptStringAnalyse(
                    hdc,
                    g_wcBuf + iFirst,
                    iLen, 0, -1,
                    dwFlags,
                    iClipWidth,
                    g_fNullState ? NULL : &ScriptControl,
                    g_fNullState ? NULL : &ScriptState,
                    NULL,
                    NULL, NULL, &ssa);

            // Testing
            int iNewLen = *ScriptString_pcOutChars(&ssa);
            // End testing
        } 
        else
        {
            // For logical DX override testing, initialise g_iWidthBuf the
            // first time, subsequently follow it's specification.
            // The UI allows users to adjust individual logical widths.
            if (g_iWidthBuf[iFirst+iLen] == 0)
            {
                g_iWidthBuf[iFirst+iLen] = 1;  // Mark this line as measured
                hr = ScriptStringAnalyse(
                        hdc,
                        g_wcBuf + iFirst,
                        iLen, 0, -1,
                        dwFlags,
                        iClipWidth,
                        g_fNullState ? NULL : &ScriptControl,
                        g_fNullState ? NULL : &ScriptState,
                        NULL,
                        NULL, NULL, &ssa);

                if (SUCCEEDED(hr))
                {
                    hr = ScriptStringGetLogicalWidths(ssa, g_iWidthBuf + iFirst);
                }

                InvalidateText();   // Need to redisplay logical area with corrected sliders


            } 
            else
            {
                hr = ScriptStringAnalyse(
                        hdc,
                        g_wcBuf + iFirst,
                        iLen, 0, -1,
                        dwFlags,
                        iClipWidth,
                        g_fNullState ? NULL : &ScriptControl,
                        g_fNullState ? NULL : &ScriptState,
                        g_iWidthBuf + iFirst,
                        NULL, NULL, &ssa);
            }
        }

        if (SUCCEEDED(hr))
        {
            // Check whether mouse clicks in this line are waiting to be processed
            if (g_fMouseDown  &&  g_iMouseDownY > *piY  &&  g_iMouseDownY < *piY+iLineHeight)
            {
                // Record char pos at left button down
                ScriptStringXtoCP(ssa, g_iMouseDownX-prc->left, &g_iFrom, &iTrailing);
                g_iFrom += iTrailing + iFirst; // Snap to closest cluster edge and make relative to buffer
                g_fMouseDown = FALSE;
            }


            if (g_fMouseUp  &&  g_iMouseUpY > *piY  &&  g_iMouseUpY < *piY+iLineHeight)
            {
                // Complete selection processing
                ScriptStringXtoCP(ssa, g_iMouseUpX-prc->left, &g_iTo, &iTrailing);
                g_iTo += iTrailing + iFirst; // Snap to closest cluster edge and make relative to buffer

                // Caret is where mouse was raised
                g_iCurChar = g_iTo;
                g_fMouseUp = FALSE;     // Signal that the mouse up is processed
                g_fUpdateCaret = TRUE;  // Request caret update
                g_iCaretSection = CARET_SECTION_PLAINTEXT;    // in plaintext section
            }

            // Display this line
            rc        = *prc;          // Clip to line height (important for selection marking)
            rc.top    = *piY;
            rc.bottom = *piY + iLineHeight;

            // Support selection range specified in either direction
            if (g_iFrom <= g_iTo) 
            {
                iFrom = g_iFrom - iFirst;
                iTo   = g_iTo   - iFirst;
            }
            else
            {
                iFrom = g_iTo   - iFirst;
                iTo   = g_iFrom - iFirst;
            }

            hr = ScriptStringOut(
                ssa,
                prc->left,
               *piY,
                ETO_CLIPPED,
               &rc,
                iFrom,   // ScriptStringOut will ignore From/To that are outside this line
                iTo,
                FALSE);

            // Now position the caret if it has moved, either because of a mouse click
            // detected above, or because of an editing function such as a cursor key.

            if (    g_fUpdateCaret
                &&  g_iCaretSection == CARET_SECTION_PLAINTEXT
                &&  g_iCurChar >= iFirst
                &&  g_iCurChar <= iFirst+iLen)
            {
                // Display caret at coordinate corresponding to g_iCurChar
                g_fUpdateCaret = FALSE;
                if (g_iCurChar < iFirst + iLen)
                {
                    ScriptStringCPtoX(ssa, g_iCurChar - iFirst, FALSE, &g_iCaretX);
                } 
                else
                {
                    // represent end of line position by placing caret at right edge
                    g_iCaretX = ScriptString_pSize(ssa)->cx;
                }

                ResetCaret(prc->left + g_iCaretX, *piY, iLineHeight);
            }

            // Show clipping boundary
            if (dwFlags & (SSA_FIT | SSA_CLIP))
            {
                TEXTMETRIC tma = {0};
                GetTextMetrics(hdc, &tma);

                MoveToEx(hdc, iX-1, *piY, NULL);
                LineTo(hdc,   iX-1, *piY + tma.tmAscent + tma.tmDescent);

                MoveToEx(hdc, iX + iClipWidth, *piY, NULL);
                LineTo(hdc,   iX + iClipWidth, *piY + tma.tmAscent + tma.tmDescent);

                MoveToEx(hdc, iX,              *piY-1, NULL);
                LineTo  (hdc, iX + iClipWidth, *piY-1);

                MoveToEx(hdc, iX,              *piY + tma.tmAscent, NULL);
                LineTo  (hdc, iX + iClipWidth, *piY + tma.tmAscent);

                MoveToEx(hdc, iX,              *piY + tma.tmAscent + tma.tmDescent, NULL);
                LineTo  (hdc, iX + iClipWidth, *piY + tma.tmAscent + tma.tmDescent);
            }

            ScriptStringFree(&ssa);
        }
    }
    else
    {
        // Although the line is empty we may still need to display the caret
        if (    g_fUpdateCaret
            &&  g_iCaretSection == CARET_SECTION_PLAINTEXT
            &&  g_iCurChar == iFirst)
        {
            g_fUpdateCaret = FALSE;
            ResetCaret(prc->left, *piY, iLineHeight);
        }
    }

    *piY += iLineHeight;
}

////    PaintPlainText - Demonstrate ScriptString APIs
//
//
void PaintPlainText(
    HDC      hdc,
    int     *piY,
    RECT    *prc,
    int      iLineHeight) 
{
    int      icpLineStart = 0;     // First character of line
    int      icpLineEnd   = 0;       // End of line (end of buffer or index of CR character)
    HFONT    hFont        = NULL;
    HFONT    hOldFont     = NULL;
    LOGFONT  lf           = {0};

    icpLineStart = 0;

    if (    g_fPresentation
        &&  GetObject(g_style[0].hf, sizeof(lf), &lf))
    {
        // Select font using the entire line height
        hFont = CreateFont(
            iLineHeight,
            0, 0, 0,
            lf.lfWeight,
            lf.lfItalic,
            lf.lfUnderline,
            lf.lfStrikeOut,
            lf.lfCharSet,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            FF_DONTCARE|DEFAULT_PITCH,
            lf.lfFaceName);
        hOldFont = (HFONT) SelectObject(hdc, hFont);
    }
    else
    {
        // Select users font
        hOldFont = (HFONT) SelectObject(hdc, g_style[0].hf);
    }

    // Display line by line
    while (icpLineStart < g_iTextLen) 
    {
        // Find end of line or end of buffer
        icpLineEnd = icpLineStart;
        while (icpLineEnd < g_iTextLen  &&  g_wcBuf[icpLineEnd] != 0x0D) 
        {
            icpLineEnd++;
        }

        PaintPlainTextLine(
            hdc,
            piY,
            prc,
            icpLineStart,
            icpLineEnd-icpLineStart,
            iLineHeight);

        if (g_fPresentation)
        {
            // Display only one line in presentation mode
            icpLineStart = g_iTextLen;
        }
        else
        {
            // Advance to next line
            if (icpLineEnd < g_iTextLen) 
            {
                icpLineEnd++;
            }
            if (icpLineEnd < g_iTextLen  &&  g_wcBuf[icpLineEnd] == 0x0A)
            {
                icpLineEnd++;
            }
            icpLineStart = icpLineEnd;
        }
    }

    if (g_fPresentation)
    {
        SelectObject(hdc, hOldFont);
    }
}
