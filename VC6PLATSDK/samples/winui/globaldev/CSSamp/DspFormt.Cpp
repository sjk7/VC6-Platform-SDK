////    DspFormt - Display formatted text and handle caret placement
//
//      Demonstrates use of the formatted string APIs
//
//      ScriptItemize           - Break string on script and direction boundaries
//      ScriptLayout            - Bidi embedding level interpreter
//      ScriptShape             - Unicode to glyph translation
//      ScriptPlace             - Width and position generation
//      ScriptTextOut           - Render to device
//      ScriptXtoCP             - Pixel position to character index
//      ScriptCPtoX             - Character index to pixel position
//      ScriptGetLogicalWidths  - Generate widths in character order
//      ScriptBreak             - Get line breaking flags

#include "precomp.hxx"
#include "global.h"

////    Since this is a sample application we can use fixed size buffers
//
const int MAXITEM   = 200;     // Maximum item supported in a paragraph
const int MAXRUN    = 200;     // Maximum runs supported in a line
const int MAXCHARS  = 200;     // Maximum codepoints in a single run
const int MAXGLYPHS = 200;     // Maximum glyphs in a single run

//      A real application would normally allocate buffers dynamically.
//
//      A glyph buffer 1.5 times as large as the character buffer is
//      currently sufficient for all known scripts and fonts, however you
//      should be prepared to allocate larger buffers dynamically if you
//      receive E_OUT_OF_MEMORY errors, since future fonts could
//      generate more glyphs for some characters.
//
//      One such possibility is a font whose glyphs are individual pen
//      strokes. Such a font might commonly generate 2 or 3 glyphs per
//      character.
//
//      The worst case requirement for the item buffer is one item per
//      character plus a sentinel item. You may be be surprised how often
//      you come across a line composed of alternating characters from
//      different scripts - it can look pretty.
//
//      Since these buffers are allocated dynamically and kept only while
//      the line is being processed, it is recommended to allocate the
//      worst case lengths - it takes no longer to allocate a large buffer
//      than a small one.
//
//      On the other hand, if your design keeps shaping and placement
//      output buffers cached it would usually be worthwhile copying to
//      buffers allocated to the right lengths once the shape/place
//      operations are complete.



////    BuildParaRunList - Builds runs in this paragraph with analysis from ScriptItemize
//
//      Calls ScriptItemize to break this paragraph into runs by script and bidi direction
//
//      Merges the result with the global style run list
//
//      Returns merged runs for paragraph such that each run has a single script, style
//      and direction.
void BuildParaRunList(
    int    iFirst,            // In    First character of paragraph
    int    iLen,              // In    Length of paragraph
    RUN  **ppFirstParaRun,    // Out   Receives head of paragraph run list
    int   *pcRuns) {          // Out   Number of runs generated

    SCRIPT_ITEM      Items[MAXITEM];
    int              cItems          = 0;      // Number of items returned by ScriptItemize
    RUN             *pFormatRunRider = NULL;   // Rides main formatting run list
    RUN             *pNewRun         = NULL; 
    RUN            **ppLastNext      = NULL;   // Pointer to be updated with new run address
    int              iFormatRunStart = 0;      // Character offset of current formatting run
    int              iParaRunStart   = 0;
    int              iItem           = 0 ;
    SCRIPT_CONTROL   ScriptControl   = {0};
    SCRIPT_STATE     ScriptState     = {0};
    HRESULT          hr              = NULL;
    int              cRuns           = 0;

    // Itemize the paragraph by script and bidi direction
    ScriptControl = g_ScriptControl;
    ScriptState   = g_ScriptState;

    hr = ScriptItemize(
        g_wcBuf+iFirst,
        iLen,
        MAXITEM,
        g_fNullState   ? NULL : &ScriptControl,
        g_fNullState   ? NULL : &ScriptState,
        Items,
       &cItems);

    if (FAILED(hr))
    {
        return;
    }

    /// Build a Paragraph run list by merging itemization with formatting styles.
    //
    //  Generate a linked list of runs specific to this paragraph, such that
    //  each run has a single formatting style and a single item analysis.

    // Find first run for this para
    pFormatRunRider = g_pFirstFormatRun;
    iFormatRunStart = 0;
    while (iFormatRunStart + pFormatRunRider->iLen <= iFirst) 
    {
        iFormatRunStart += pFormatRunRider->iLen;
        pFormatRunRider = pFormatRunRider->pNext;
    }

    // Create a paragraph run for every change of item or formatting
    ppLastNext = ppFirstParaRun;
    iItem = 0;
    iParaRunStart = iFirst;
    cRuns = 0;

    while (iItem < cItems  &&  iFormatRunStart < iFirst + iLen) 
    {
        // Create a run up to the next change of item or formatting
        // style, whichever comes first.
        pNewRun = new RUN;
        pNewRun->iStyle   = pFormatRunRider->iStyle;
        pNewRun->analysis = Items[iItem].a;
        pNewRun->pNext    = NULL;
        *ppLastNext       = pNewRun;
        ppLastNext        = &pNewRun->pNext;
        cRuns++;

        if (iFirst + Items[iItem+1].iCharPos  <=  iFormatRunStart + pFormatRunRider->iLen) 
        {
            // No change of style during the current item
            pNewRun->iLen = iFirst + Items[iItem+1].iCharPos - iParaRunStart;  // Item length

        } 
        else 
        {
            // Style changes before end of current item
            pNewRun->iLen = iFormatRunStart + pFormatRunRider->iLen - iParaRunStart;
        }

        iParaRunStart += pNewRun->iLen;

        if (iParaRunStart >= iFirst + Items[iItem+1].iCharPos) 
        {
            iItem++;  // Advance to next item
        }

        if (iParaRunStart >= iFormatRunStart + pFormatRunRider->iLen) 
        {
            iFormatRunStart += pFormatRunRider->iLen;   // Advance to next run
            pFormatRunRider = pFormatRunRider->pNext;
        }
    }

    *pcRuns = cRuns;
}

///     BuildVisualDisplayOrder
//
//      Collects bidi levels for a line into an array and passes
//      them to ScriptLayout to construct an array of visual
//      positions for each logical run. Uses that array to
//      construct arrays of run pointers and logical character
//      offsets in visual order.

void BuildVisualDisplayOrder(
    RUN   *pFirstLogicalRun,  // In   Some or all of the paragraph run list
    int    cRuns,             // In   Number of runs to process
    RUN  **ppVisualOrder,     // Out  Array of run pointers in visual order
    int   *piPos)            // Out  Array of text indices for runs
{
    BYTE   BidiLevel[MAXRUN];
    int    iLogicalToVisual[MAXRUN];
    int    iRun  = 0;
    RUN   *pRun  = NULL ;
    int    iPos  = 0;

    // Extract bidi levels for the line into an array
    iRun = 0;
    pRun = pFirstLogicalRun;
    while (pRun != NULL  &&  iRun < cRuns  &&  iRun < MAXRUN) 
    {
        BidiLevel[iRun] = (BYTE)pRun->analysis.s.uBidiLevel;
        iRun++;
        pRun = pRun->pNext;
    }

    // Obtain logical to visual order run index mapping
    ScriptLayout(cRuns, BidiLevel, NULL, iLogicalToVisual);

    // Fill in array of run pointers in visual order
    pRun = pFirstLogicalRun;
    iRun = 0;
    iPos = 0;
    while(iRun < cRuns) 
    {
        ppVisualOrder[iLogicalToVisual[iRun]] = pRun;
        piPos[iLogicalToVisual[iRun]] = iPos;
        iPos += pRun->iLen;
        pRun = pRun->pNext;
        iRun++;
    }
}

////    CaretHandling - process mouse hits and caret positioning in this run
//
//      When displaying the caret, this code always displays it on the leading
//      edge of g_iCurChar, which is conventionally the logical character before
//      which a new character would be inserted.
//
//      A high quality editing application will distinguish the leading edge
//      of g_iCurChar from the trailing edge of g_iCurChar-1 since for bidi
//      text these may be at very different visual positions.
//
//      A simple rule to follow is to display at the trailing edge of g_iCurChar-1
//      when the cursor is being advanced by typing or by pressing the forward arrow
//      key, and to display on the leading edge of g_iCurChar at all other times.
void CaretHandling(
    int                     iX,             // In  Run x position
    int                     iDx,            // In  Run width
    int                     iY,             // In  Run top
    int                     iDy,            // In  Run height
    int                     iFirst,         // In  First character of run
    int                     cChars,         // In  Character count
    int                     cGlyphs,        // In  Glyph count
    const SCRIPT_ANALYSIS  *psa,
    WORD                   *pwLogClust,
    const SCRIPT_VISATTR   *psva,
    const int              *piAdvance) 
{
    int  iCp        = 0;
    int  iTrailing  = 0;
    int  iCpx       = 0;
    int  iFrom      = 0;
    int  iTo        = 0;

    // Check whether mouse clicks in this item are waiting to be processed
    if (    g_fMouseDown
        &&  g_iMouseDownY >= iY
        &&  g_iMouseDownY <  iY + iDy
        &&  g_iMouseDownX >= iX
        &&  g_iMouseDownX <  iX + iDx)
    {
        // Record position at mouse button down
        ScriptXtoCP(
            g_iMouseDownX - iX,
            cChars,
            cGlyphs,
            pwLogClust,
            psva,
            piAdvance,
            psa,
           &iCp,
           &iTrailing);

        g_iFrom = iCp + iTrailing + iFirst;
        g_fMouseDown = FALSE;
    }

    if (    g_fMouseUp
        &&  g_iMouseUpY >= iY
        &&  g_iMouseUpY <  iY + iDy
        &&  g_iMouseUpX >= iX
        &&  g_iMouseUpX <  iX + iDx) 
    {
        // Process mouse up
        ScriptXtoCP(
            g_iMouseUpX - iX,
            cChars,
            cGlyphs,
            pwLogClust,
            psva,
            piAdvance,
            psa,
           &iCp,
           &iTrailing);

        g_iTo = iCp + iTrailing + iFirst;
        g_fMouseUp = FALSE;

        // Request caret move to this position
        g_iCurChar      = g_iTo;
        g_fUpdateCaret  = TRUE;
        g_iCaretSection = CARET_SECTION_FORMATTED;
    }

    // Check for caret positioning to this run
    if (    g_fUpdateCaret
        &&  g_iCaretSection == CARET_SECTION_FORMATTED
        &&  g_iCurChar >= iFirst
        &&  g_iCurChar <  iFirst+cChars) 
    {
        // Display caret at coordinate corresponding to g_iCurChar
        g_fUpdateCaret = FALSE;
        ScriptCPtoX(
            g_iCurChar - iFirst,
            FALSE,          // Always display on leading edge
            cChars,
            cGlyphs,
            pwLogClust,
            psva,
            piAdvance,
            psa,
           &iCpx);

        ResetCaret(iX+iCpx, iY, iDy);
    }

    // If anypart of this run is selected, redisplay that part with a blue
    // background.
    if (g_iFrom != g_iTo) 
    {
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
    }
}

////    ShapePlaceRun - uses ScriptShape and ScriptPlace to create glyphs and widths for a run
//
//      This sample implementation includes a simple form of font association.
//
//      High quality formatting apps need to measure and render text at different resolutions.
//      Such an app might call ScriptShape once to generate glyphs, then ScriptPlace at
//      screen resolution, printer resulution and/or 'ideal device' resolution.
//      For this sample we are only concerned with screen resolution.
HRESULT ShapePlaceRun(
    HDC              hdc,         // InOut  Device context
    int             *piCurStyle,  // InOut  Current style - helps optimise unnecessary SelectObject calls
    int              iStyle,      // In     Desired style
    SCRIPT_ANALYSIS *psa,         // In     Analysis from paragraph itemization
    int              iPos,        // In     First character of logical item
    int              iLen,        // In     Length in codepoints
    int             *pcGlyphs,    // Out    Glyph count
    WORD            *pGlyphs,     // Out    Glyph indices
    WORD            *pClusters,   // Out    Cluster positions
    SCRIPT_VISATTR  *pVisattrs,   // Out    Visual attributes
    int             *piAdvances,  // Out    Glyph advance widths
    GOFFSET         *pGoffsets,   // Out    Glyph 2D offsets
    int             *piDx)        // Out    Run advance width
{
    ABC             abc = {0};          // Run combined ABC
    HRESULT         hr  = NULL;

    // Obey global settings for logical order and NoGlyphIndex
    if (g_fLogicalOrder)
    {
        psa->fLogicalOrder = TRUE;
    }

    if (g_fNoGlyphIndex) 
    {
        psa->fNoGlyphIndex = TRUE;
    }

    // Select desired style
    if (iStyle != *piCurStyle) 
    {
        *piCurStyle = iStyle;
        SelectObject(hdc, g_style[iStyle].hf);
    }

    // Shape (generate glyphs) with desired style
    hr = ScriptShape(
        hdc,
       &g_style[*piCurStyle].sc,
        g_wcBuf + iPos,
        iLen,
        MAXGLYPHS,
        psa,
        pGlyphs,
        pClusters,
        pVisattrs,
        pcGlyphs);

    if (hr == USP_E_SCRIPT_NOT_IN_FONT) 
    {
        // The desired style does not support the script of this run.
        // Implement font association here.

        // In this sample we simply try style 1. A better application may keep a
        // list of standard fonts to try.
        SelectObject(hdc, g_style[1].hf);
        *piCurStyle = 1;

        // Shape with style 1
        hr = ScriptShape(
            hdc,
           &g_style[*piCurStyle].sc,
            g_wcBuf + iPos,
            iLen,
            MAXGLYPHS,
            psa,
            pGlyphs,
            pClusters,
            pVisattrs,
            pcGlyphs);
    }

    if (hr == USP_E_SCRIPT_NOT_IN_FONT) 
    {
        // Neither the users selected style nor style 1 support the
        // script of this run, so force the script to 'SCRIPT_UNDEFINED'
        // This will display the characters directly through the fonts
        // CMAP table, probably showing the text as square boxes (the
        // missing glyph)
        psa->eScript = SCRIPT_UNDEFINED;

        // Restore original desired style
        if (iStyle != *piCurStyle) 
        {
            *piCurStyle = iStyle;
            SelectObject(hdc, g_style[iStyle].hf);
        }

        // Shape with SCRIPT_UNDEFINED
        hr = ScriptShape(
            hdc,
           &g_style[*piCurStyle].sc,
            g_wcBuf + iPos,
            iLen,
            MAXGLYPHS,
            psa,
            pGlyphs,
            pClusters,
            pVisattrs,
            pcGlyphs);
    }

    // Having generated glyphs, now generate advance widths and combining
    // offsets.
    // A real formatting app would probably use ScriptPlace at more than one
    // resolution, for example at a high 'ideal' resolution for page layout,
    // then again at screen and/or printer resolution for displaying and
    // printing.
    // This sample applet considers only screen resolution.

    if (SUCCEEDED(hr)) 
    {
        hr = ScriptPlace(
            hdc,
           &g_style[*piCurStyle].sc,
            pGlyphs,
           *pcGlyphs,
            pVisattrs,
            psa,
            piAdvances,
            pGoffsets,
           &abc);

        *piDx = abc.abcA + abc.abcB + abc.abcC;
    }

    return hr;
}

////    PaintFormattedRun
//
//
void PaintFormattedRun(
    HDC              hdc,        // InOut
    int              iY,         // In     Vertical poition to write at
    int              iLineHeight,// In
    int             *piX,        // InOut  Horizontal position to start at, updated by length of run
    int             *piCurStyle, // InOut  Current style - helps optimise unnecessary SelectObject calls
    int              iStyle,     // In     Desired style
    SCRIPT_ANALYSIS *psa,        // In     Analysis from paragraph itemization
    int              iPos,       // In     First character of logical item
    int              iLen) {     // In     Length of logical item


    WORD            glyphs[MAXGLYPHS];
    WORD            clusters[MAXGLYPHS];
    SCRIPT_VISATTR  visattrs[MAXGLYPHS];
    int             advances[MAXGLYPHS];    // Glyph advance widths
    GOFFSET         goffsets[MAXGLYPHS];    // Glyph 2D offsets
    int             cGlyphs = 0;
    int             iWidth  = 0;            // Run width
    HRESULT         hr      = NULL;

    // ShapePlaceRun calls ScriptShape and ScriptPlace to generate glyphs and
    // advance widths, and also performs limited font association.
    hr = ShapePlaceRun(
        hdc,
        piCurStyle,
        iStyle,
        psa,
        iPos,
        iLen,
       &cGlyphs,
        glyphs,
        clusters,
        visattrs,
        advances,
        goffsets,
       &iWidth);

    if (SUCCEEDED(hr)) 
    {
        // Set text color to represent any font association applied
        if (*piCurStyle != iStyle) 
        {
            SetTextColor(hdc, 0x00ff0000);  // Show we did font association by marking text blue
        } 
        else if (psa->eScript == SCRIPT_UNDEFINED) 
        {
            SetTextColor(hdc, 0x000000ff);  // Show we forced SCRIPT_UNDEFINED by marking text red
        }
        else 
        {
            SetTextColor(hdc, 0);           // Show text black when no font association required
        }

        hr = ScriptTextOut(
            hdc,
           &g_style[*piCurStyle].sc,
           *piX,
            iY,
            0,
            NULL,
            psa,
            NULL,
            0,
            glyphs,
            cGlyphs,
            advances,
            NULL,
            goffsets);

        // Handle mouse hits in this run and/or caret repositioning in this run
        CaretHandling(
           *piX,            // Run position
            iWidth,         // Width in pixels
            iY,             // Run top
            iLineHeight,    // Run height
            iPos,           // First character
            iLen,           // Character count
            cGlyphs,        // Glyph count
            psa,            // Script analysis
            clusters,       // Clusters
            visattrs,       // Visual attributes
            advances);      // Advance widths

        // Advance x coordinate to right edge of run
        if (SUCCEEDED(hr))
        {
            *piX += iWidth;     // Advance x position over this run
        }

        // Restore black text (we may have changed color to mark font association)
        SetTextColor(hdc, 0);
    }
}

////    PaintFormattedTextLine - Process and display a line of formatted text
//
//
void PaintFormattedTextLine(
    HDC      hdc,               // InOut  Device
    int     *piCurStyle,        // InOut  Current style - helps optimise unnecessary SelectObject calls
    int     *piY,               // In     Y position
    RECT    *prc,               // In     Clipping rectange
    int      iFirst,            // In     First character of line
    int      iLen,              // In     Length in characters
    RUN     *pFirstRun,         // In     First run of this line
    int      cRuns,             // In     Run count
    int      iLineHeight)       // In     Height to advance per line, in pixels
{

    RUN     *pVisualOrder[MAXRUN];  // Array of run pointers in visual order
    int      iPos[MAXRUN];          // Offset to first logical character of each run
    int      iRun    = 0;
    int      iX      = 0;
    RECT     rcClear = {0};

    // Clear each line before displaying it
    rcClear        = *prc;
    rcClear.top    = *piY;
    rcClear.bottom = *piY + iLineHeight;
    FillRect(hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));

    // Construct array of run pointers in visual order
    BuildVisualDisplayOrder(pFirstRun, cRuns, pVisualOrder, iPos);

    // Display runs in visual order
    iX = prc->left;

    for (iRun = 0; iRun < cRuns; iRun++) 
    {
        PaintFormattedRun(
            hdc,
           *piY,
            iLineHeight,
           &iX,                                         // Horizontal position (will be updated)
            piCurStyle,                                 // Current style (will be updated)
            pVisualOrder[iRun]->iStyle,                 // Desired style
           &pVisualOrder[iRun]->analysis,               // Analysis from ScriptItemize
            iFirst+iPos[iRun],
            pVisualOrder[iRun]->iLen);
    }

    // A pending caret position set may not have been handled in the previous loop
    if (    g_fUpdateCaret
        &&  g_iCaretSection == CARET_SECTION_FORMATTED
        &&  g_iCurChar >= iFirst
        &&  g_iCurChar <= iFirst + iLen) 
    {
        if (g_iCurChar == iFirst + iLen) 
        {
            // Caret is at the end of the line
            g_fUpdateCaret = FALSE;
            ResetCaret(iX, *piY, iLineHeight);
        } 
        else 
        {
            // If the caret position was changed by a mouse click at one end of a
            // formatted run that requires it to be displayed at the corresponding
            // end of another run, and if that other run happened to have been displayed
            // earlier, we may still have a mouse update pending. In that case,
            // rerun the fancy text display algorithm until the caret has been placed.

            iX = prc->left;
            for (iRun = 0;  g_fUpdateCaret && iRun < cRuns;  iRun++) 
            {
                PaintFormattedRun(
                    hdc,
                   *piY,
                    iLineHeight,
                   &iX,                             // Horizontal position (will be updated)
                    piCurStyle,                     // Current style (will be updated)
                    pVisualOrder[iRun]->iStyle,     // Desired style
                   &pVisualOrder[iRun]->analysis,   // Analysis from ScriptItemize
                    iFirst+iPos[iRun],
                    pVisualOrder[iRun]->iLen);
            }
        }
    }

    *piY += iLineHeight;
}

////    BreakRun - Split run at word boundary before given width
//
//      Returns width up to wordbreak
int BreakRun(
    RUN             *pRun,                  // In     Run to break
    int              cGlyphs,
    int             *piAdvances,
    WORD            *pClusters,
    SCRIPT_VISATTR  *pVisattrs,
    int              iMaxWidth,             // In     Width to meet
    int              iPos,                  // In     Position in character buffer
    BOOL             fNeedCluster)          // In     If must return at least one cluster
{

    SCRIPT_LOGATTR   logattrs[MAXCHARS];    // Logical (codepoint) atributes
    int              logwidths[MAXCHARS];   // Codepoint widths
    int              iWidth  = 0;           // Width in pixels
    int              iChars  = 0;           // Width in codepoints
    RUN             *pNewRun = NULL;        // New run for text following wordbreak
    HRESULT          hr      = NULL;

    // Convert the glyph widths to logical widths: in the
    // same order and quantity as the origial codepoints.

    hr = ScriptGetLogicalWidths(
       &pRun->analysis,
        pRun->iLen,
        cGlyphs,
        piAdvances,
        pClusters,
        pVisattrs,
        logwidths);

    if (FAILED(hr)) 
    {
        iWidth = 0;
        goto RETURN;
    }


    // Calculate how many codepoints will fit iMaxWidth
    // ignoring word boundaries.
    iChars = 0;
    iWidth = 0;

    while (    iChars < pRun->iLen
        &&  iWidth + logwidths[iChars] < iMaxWidth)
    {
        iWidth += logwidths[iChars];
        iChars++;
    }

    // Obtain logical attributes including whitespace and
    // wordstart flags.
    hr = ScriptBreak(
        g_wcBuf + iPos,
        pRun->iLen,
       &pRun->analysis,
        logattrs);

    if (FAILED(hr)) 
    {
        iWidth = 0;
        goto RETURN;
    }

    // Back up to a wordbreak
    while(    iChars > 0
          &&  iChars < pRun->iLen
          &&  !logattrs[iChars].fWhiteSpace
          &&  !logattrs[iChars].fSoftBreak)
    {
        iChars--;
        iWidth -= logwidths[iChars];
    }

    if (fNeedCluster  &&  iChars == 0) 
    {
        // Ensure at least one cluster is returned
        iWidth = piAdvances[pClusters[0]];
        iChars = 1;

        while (    iChars < pRun->iLen
               &&  pClusters[iChars] == pClusters[0]) 
        {
            iWidth += piAdvances[pClusters[iChars]];
            iChars++;
        }
    }

    // Include any subsequent whitespace characters
    while (    iChars < pRun->iLen
           &&  logattrs[iChars].fWhiteSpace) 
    {
        iWidth += logwidths[iChars];
        iChars++;
    }

    // Split current run at this point
    if (iChars < pRun->iLen) 
    {
        pNewRun        = new RUN;
        *pNewRun       = *pRun;
        pRun->pNext    = pNewRun;
        pRun->iLen     = iChars;
        pNewRun->iLen -= iChars;
    }

RETURN:
    return iWidth;
}

////    PaintFormattedTextPara - Break a paragraph into lines and display each line
//
//      Builds a list of runs in the paragraph, then measures each run length in
//      logical order filling and displaying lines one at a time.

void PaintFormattedTextPara(
    HDC      hdc,               // In   Device
    int     *piY,               // In   Y position
    RECT    *prc,               // In   Clipping rectange
    int      iFirst,            // In   First character of line
    int      iLen,
    int      iLineHeight)       // In   Height to advance per line, in pixels
{
    WORD            glyphs[MAXGLYPHS];
    WORD            clusters[MAXGLYPHS];
    SCRIPT_VISATTR  visattrs[MAXGLYPHS];
    int             advances[MAXGLYPHS];    // Glyph advance widths
    GOFFSET         goffsets[MAXGLYPHS];    // Glyph 2D offsets
    int             cGlyphs       = 0;
    HRESULT         hr            = NULL;
    RUN            *pFirstParaRun = NULL;
    RUN            *pLineStartRun = NULL;
    RUN            *pLineEndRun   = NULL;
    RUN            *pDelRun       = NULL;
    int             nRuns         = 0;
    int             iLineWidth    = 0;      // Width measured so far
    int             iRunWidth     = 0;      // Width of an individual run
    int             iMaxWidth     = 0;      // Line width
    int             iLineLen      = 0;      // Length in codepoints
    int             iCurStyle     = 0;

    iCurStyle = -1;             // Force style selection on first run
    iMaxWidth = prc->right - prc->left;

    if (iLen > 0  &&  iMaxWidth > 0) 
    {
        // Itemize paragraph and merge items with style runs
        BuildParaRunList(iFirst, iLen, &pFirstParaRun, &nRuns);

        if (!g_fFillLines) 
        {
            // Display whole para as one line
            PaintFormattedTextLine(
                hdc,
               &iCurStyle,
                piY,
                prc,
                iFirst,
                iLen,
                pFirstParaRun,
                nRuns,
                iLineHeight);

            // Free para run list
            while (pFirstParaRun != NULL) 
            {
                pDelRun = pFirstParaRun;
                pFirstParaRun = pFirstParaRun->pNext;
                delete pDelRun;
                pDelRun = NULL;
            }

        } 
        else 
        {
            // Display paragraph in filled lines
            // Measure runs to fit
            pLineStartRun = pFirstParaRun;

            while (pLineStartRun) 
            {
                pLineEndRun = pLineStartRun;
                iLineWidth  = 0;
                nRuns       = 0;
                iLineLen    = 0;

                hr = ShapePlaceRun(
                    hdc,
                   &iCurStyle,
                    pLineEndRun->iStyle,
                   &pLineEndRun->analysis,
                    iFirst + iLineLen,
                    pLineEndRun->iLen,
                  &cGlyphs,
                    glyphs,
                    clusters,
                    visattrs,
                    advances,
                    goffsets,
                   &iRunWidth);

                if (FAILED(hr)) 
                {
                    return;
                }

                while (pLineEndRun  &&  iLineWidth + iRunWidth <= iMaxWidth) 
                {
                    iLineWidth += iRunWidth;
                    iLineLen   += pLineEndRun->iLen;
                    pLineEndRun = pLineEndRun->pNext;
                    nRuns++;

                    if (pLineEndRun)
                    {
                        hr = ShapePlaceRun(
                            hdc,
                           &iCurStyle,
                            pLineEndRun->iStyle,
                           &pLineEndRun->analysis,
                            iFirst + iLineLen,
                            pLineEndRun->iLen,
                          &cGlyphs,
                            glyphs,
                            clusters,
                            visattrs,
                            advances,
                            goffsets,
                           &iRunWidth);

                        if (FAILED(hr))
                        {
                            return;
                        }
                    }
                }

                // Having filled the line with as many whole runs as possible, now
                // break the next run on a word boundary if possible, or between
                // clusters if not.

                if (pLineEndRun  &&  iLineWidth < iMaxWidth) 
                {

                    iRunWidth   = BreakRun(
                        pLineEndRun,
                        cGlyphs,
                        advances,
                        clusters,
                        visattrs,
                        iMaxWidth - iLineWidth,
                        iFirst + iLineLen,
                        iLineLen == 0);             // Ensure at least one cluster is broken


                    iLineWidth += iRunWidth;
                    iLineLen   += pLineEndRun->iLen;
                    pLineEndRun = pLineEndRun->pNext;
                    nRuns++;
                }

                PaintFormattedTextLine(
                    hdc,
                   &iCurStyle,
                    piY,
                    prc,
                    iFirst,
                    iLineLen,
                    pLineStartRun,
                    nRuns,
                    iLineHeight);


                // Advance to next line
                iFirst += iLineLen;
                while (pLineStartRun != pLineEndRun)
                {
                    pDelRun = pLineStartRun;
                    pLineStartRun = pLineStartRun->pNext;
                    delete pDelRun;
                    pDelRun = NULL;
                }
            }
        }
    } 
    else
    {
        // Empty paragraph
        RECT     rcClear = {0};
        rcClear        = *prc;
        rcClear.top    = *piY;
        rcClear.bottom = *piY + iLineHeight;
        FillRect(hdc, &rcClear, (HBRUSH) GetStockObject(WHITE_BRUSH));
        *piY += iLineHeight;
    }
}

////    PaintFormattedText - Demonstrate Itemize/Shape/Place/Out APIs
//
//
void PaintFormattedText(
    HDC   hdc,
    int  *piY,
    RECT *prc,
    int   iLineHeight) {

    int   icpParaStart;     // First character of line
    int   icpParaEnd;       // End of para (end of buffer or index of CR character)


    // Since we'll output each run independantly, we can't paint the character background
    // lest it erase an overhanging part of a glyph at the end of the previous output run.
    // (This is common - for example most of the Arabic glyphs in Arial overhang a few
    // pixels beyond their advance width)
    SetBkMode(hdc, TRANSPARENT);    // Allow runs to overlap
    icpParaStart = 0;

    // Display line by line
    while (icpParaStart < g_iTextLen)
    {
        // Find end of para or end of buffer
        icpParaEnd = icpParaStart;
        while (icpParaEnd < g_iTextLen  &&  g_wcBuf[icpParaEnd] != 0x0D) 
        {
            icpParaEnd++;
        }

        PaintFormattedTextPara(
            hdc,
            piY,
            prc,
            icpParaStart,
            icpParaEnd-icpParaStart,
            iLineHeight);

        // Advance to next line
        if (icpParaEnd < g_iTextLen) 
        {
            icpParaEnd++;
        }
        if (icpParaEnd < g_iTextLen  &&  g_wcBuf[icpParaEnd] == 0x0A) 
        {
            icpParaEnd++;
        }

        icpParaStart = icpParaEnd;
    }
}
