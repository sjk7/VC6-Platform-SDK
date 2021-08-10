/*****************************************************************************
 *
 *  FontSize.c
 *
 *  Copyright (c) Microsoft Corporation.
 *
 *  Abstract:
 *
 *      Sample program to demonstrate how a program can obtain
 *      the current screen "logical pixels for inch" setting,
 *      which the end-user can manipulate by choosing "Small fonts",
 *      "Large fonts", or "Custom" from the Control Panel Display
 *      applet.
 *
 *****************************************************************************/

#define STRICT
#include <windows.h>
#include <stdio.h>

/*****************************************************************************
 *
 *      Overview
 *
 *      The logical pixels per inch determines the relationship
 *      between logical dimensions (e.g., points) and pixels.
 *
 *      This relationship can be queried from any type of device.
 *      For example, printing the same bitmap on printers
 *      with different DPI will yield different results unless
 *      the application takes steps to ensure that the DPI is
 *      compensated for by stretching or compressing the bitmap.
 *
 *      An example of using this information for the display can
 *      be seen in the Windows 95 MS-DOS prompt toolbar.  If
 *      the logical DPI is less 120 DPI, then the toolbar
 *      buttons are 16 pixels square.  But if the logical
 *      DPI is 120 DPI or greater, then the toolbar buttons are
 *      24 pixels square.
 *
 *      Applications which are sensitive to the screen DPI can
 *      query the display DPI and adjust their pixel-based
 *      dimensions accordingly.
 *
 *      By convention, the value of 96 corresonds to "Small fonts"
 *      and the value of 120 corresponds to "Large fonts".  However,
 *      applications must be aware that values other than these
 *      can be selected by the user.  Do not assume, for example,
 *      that anything not equal to 120 must mean "Small fonts".
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *  WinMain
 *
 *      Program entry point.
 *
 *      Queries the screen logical DPI and displays the result.
 *
 *****************************************************************************/

int WINAPI
WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR pszCmdLine, int nCmdShow)
{
    HDC hdc;
    int iDPI;
    char sz[1024];

    hdc = GetDC(NULL);                  /* Get DC for screen */
    iDPI = GetDeviceCaps(hdc, LOGPIXELSX);
    ReleaseDC(NULL, hdc);

    if (iDPI < 96)
    {
        _snprintf(sz, sizeof(sz), "%d DPI - Even smaller than Small fonts", iDPI);
    }
    else if (iDPI == 96)
    {
        _snprintf(sz, sizeof(sz), "%d DPI - Small fonts", iDPI);
    }
    else if (iDPI < 120)
    {
        _snprintf(sz, sizeof(sz), "%d DPI - Between Small fonts and Large fonts", iDPI);
    }
    else if (iDPI == 120)
    {
        _snprintf(sz, sizeof(sz), "%d DPI - Large fonts", iDPI);
    }
    else
    {
        _snprintf(sz, sizeof(sz), "%d DPI - Even larger than Large fonts", iDPI);
    }

    MessageBox(NULL, sz, "FontSize", MB_OK);

    return 0;
}
