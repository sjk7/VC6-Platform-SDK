/*****************************************************************************\
*
*       THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*       ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED 
*       TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
*       PARTICULAR PURPOSE.                                              
*                                                                        
*       Copyright (C) 1999  Microsoft Corporation.  All rights reserved. 
*                                                                        
\*****************************************************************************/

/* **********************************************************************
DIBSectn.C  Sample source to demonstrate the use of DIBSections

  Contains the following functions for Creating/Saving/Drawing:
    DSCreateDIBSection()
    DSLoadDIBSectionFromBMPFile()
    DSDrawDIBSectionOnDC()
    DSStoreDIBSectionInBMPFile()

  Contains the following helper functions:
    DSCreatePaletteForDIBSection()
    DSGetBITMAPINFOForDIBSection()
    DSColorTableSize()
    DSImageBitsSize()
    DSTotalBytesSize()
    DSGetPointerToDIBSectionImageBits()
    DSCreateSpectrumPalette() 
	DSBitsperPixel()
	DSGetOptimalDIBFormat()
	DSGetRGBBitsPerPixel()
	DSGetDIBSectionFromClipboard()
	DSPutDIBSectionOnClipboard()
	DSCopyBitmapEx()
	DSCopyBitmap()

  Notes:
    * Most of the functions in this module which are passed an HBITMAP
      as a parameter assume the HBITMAP is not selected into a device
      context at the time of the call. Since the underlying APIs usually
      require this, so do these functions.
    * Throughout this module, code is in place to handle color tables
      in DIBSections (in the BITMAPINFO) even when it is not necessary.
      This helps the re-usability of the code, since it is often desirable
      to include a "suggested" color table when storing 16bpp or higher
      BMP files.
    * 

********************************************************************** */

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "DibSectn.h"

// Macro to determine the number of bytes per line in the DIB bits. This
//  accounts for DWORD alignment by adding 31 bits, then dividing by 32,
//  then rounding up to the next highest count of 4-bytes. Then, we 
//  multiply by 4 to get the total byte count.

#define BYTESPERLINE(Width, BPP) ((WORD)((((DWORD)(Width) * (DWORD)(BPP) + 31) >> 5)) << 2)
#define NEW_DIB_FORMAT(lpbih) (lpbih->biSize != sizeof(BITMAPCOREHEADER))

/* Macro to swap two values */
#define SWAP(x, y)   ((x)^=(y)^=(x)^=(y))

/* **********************************************************************
  HBITMAP DSCreateDIBSection(DWORD dwX, DWORD dwY, WORD wBits)

  PARAMETERS:
    DWORD dwX    - Desired width of the DIBSection
    DWORD dwY    - Desired height of the DIBSection
    WORD  wBits  - Desired bit-depth of the DIBSection

  RETURNS:
    HBITMAP      - a DIBSection HBITMAP of the desired size and bit-depth
                   NULL on failure

  REMARKS:
    Creates a DIBSection based on the criteria passed in as parameters.
    The DIBSection is created with a default color table - for 8bpp and
    above, this is a spectrum palette. For 4bpp, it is a stock 16 color
    table, and for 1bpp it is black and white.

********************************************************************** */

HBITMAP WINAPI DSCreateDIBSection(DWORD dwX, DWORD dwY, WORD wBits)
{
    HBITMAP         hBitmap;
    LPBYTE          pBits;
    int             nInfoSize;
    LPBITMAPINFO    pbmi;
    HDC             hRefDC;

    nInfoSize = sizeof(BITMAPINFOHEADER);

    if(wBits <= 8)
        nInfoSize += sizeof(RGBQUAD) * (1 << wBits);

    if((wBits == 16) || (wBits == 15) || (wBits == 32))
        nInfoSize += 3 * sizeof(DWORD);

    // Create the header big enough to contain color table and bitmasks if needed
    pbmi = (LPBITMAPINFO)malloc(nInfoSize);
    if ( !pbmi )
        return (HBITMAP)NULL;

    ZeroMemory(pbmi, nInfoSize);
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    pbmi->bmiHeader.biWidth = dwX;
    pbmi->bmiHeader.biHeight = dwY;
    pbmi->bmiHeader.biPlanes = 1; 
    pbmi->bmiHeader.biBitCount = wBits;
    pbmi->bmiHeader.biCompression = BI_RGB; // override below for 16 and 32bpp

    switch(wBits)
    {
        case 24:
            // 24bpp requires no special handling
        break;

        case 15:
		{   // if it's 15bpp, fill in the masks and override the compression
            // these are the default masks - you could change them if needed
            LPDWORD pMasks = (LPDWORD)(pbmi->bmiColors);
            pMasks[0] = 0x00007c00;
            pMasks[1] = 0x000003e0;
            pMasks[2] = 0x0000001f;
            pbmi->bmiHeader.biCompression = BI_BITFIELDS;
			pbmi->bmiHeader.biBitCount = 16;  // 15 bpp is really 16 bpp
        }
        break;		

		case 16:
        {   // if it's 16bpp, fill in the masks and override the compression
            // these are the default masks - you could change them if needed
            LPDWORD pMasks = (LPDWORD)(pbmi->bmiColors);
            pMasks[0] = 0x0000f800;
            pMasks[1] = 0x000007e0;
            pMasks[2] = 0x0000001f;
            pbmi->bmiHeader.biCompression = BI_BITFIELDS;
        }
        break;

        case 32:
        {   // if it's 32bpp, fill in the masks and override the compression
            // these are the default masks - you could change them if needed
            LPDWORD pMasks = (LPDWORD)(pbmi->bmiColors);
            pMasks[0] = 0x00ff0000;
            pMasks[1] = 0x0000ff00;
            pMasks[2] = 0x000000ff;
            pbmi->bmiHeader.biCompression = BI_BITFIELDS; 
        }
        break;

        case 8:
        {
            HPALETTE        hPal;
            PALETTEENTRY    pe[256];
            int             i;

            // at this point, prgb points to the color table, even 
            // if bitmasks are present
            hPal = DSCreateSpectrumPalette();
            GetPaletteEntries(hPal, 0, 256, pe);

            for(i=0;i<256;i++)
            {
                pbmi->bmiColors[i].rgbRed = pe[i].peRed;
                pbmi->bmiColors[i].rgbGreen = pe[i].peGreen;
                pbmi->bmiColors[i].rgbBlue = pe[i].peBlue;
                pbmi->bmiColors[i].rgbReserved = 0;
            }

            DeleteObject(hPal);
            pbmi->bmiHeader.biClrUsed = 256;
        }
        break;

        case 4:
        {   // Use a default 16 color table for 4bpp DIBSections
            RGBTRIPLE       rgb[16] = { { 0x00, 0x00, 0x00 }, // black 
                                        { 0x80, 0x00, 0x00 }, // dark red 
                                        { 0x00, 0x80, 0x00 }, // dark green 
                                        { 0x80, 0x80, 0x00 }, // dark yellow 
                                        { 0x00, 0x00, 0x80 }, // dark blue 
                                        { 0x80, 0x00, 0x80 }, // dark magenta 
                                        { 0x00, 0x80, 0x80 }, // dark cyan 
                                        { 0xC0, 0xC0, 0xC0 }, // light gray 
                                    //  { 0xC0, 0xDC, 0xC0 }, // money green 
                                    //  { 0xA6, 0xCA, 0xF0 }, // sky blue 
                                    //  { 0xFF, 0xFB, 0xF0 }, // cream 
                                    //  { 0xA0, 0xA0, 0xA4 }, // light gray 
                                        { 0x80, 0x80, 0x80 }, // medium gray 
                                        { 0xFF, 0x00, 0x00 }, // red 
                                        { 0x00, 0xFF, 0x00 }, // green 
                                        { 0xFF, 0xFF, 0x00 }, // yellow 
                                        { 0x00, 0x00, 0xFF }, // blue 
                                        { 0xFF, 0x00, 0xFF }, // magenta 
                                        { 0x00, 0xFF, 0xFF }, // cyan 
                                        { 0xFF, 0xFF, 0xFF } }; // white 
            int             i;

            for(i=0;i<16;i++)
            {
                pbmi->bmiColors[i].rgbRed = rgb[i].rgbtRed;
                pbmi->bmiColors[i].rgbGreen = rgb[i].rgbtGreen;
                pbmi->bmiColors[i].rgbBlue = rgb[i].rgbtBlue;
                pbmi->bmiColors[i].rgbReserved = 0;
            }
            pbmi->bmiHeader.biClrUsed = 16;
        }
        break;

        case 1: // BW
            pbmi->bmiColors[0].rgbRed = pbmi->bmiColors[0].rgbGreen = pbmi->bmiColors[0].rgbBlue = 0;
            pbmi->bmiColors[1].rgbRed = pbmi->bmiColors[1].rgbGreen = pbmi->bmiColors[1].rgbBlue = 255;
            pbmi->bmiColors[0].rgbReserved = pbmi->bmiColors[1].rgbReserved = 0;
        break;
    }

    hRefDC = GetDC(NULL);
    hBitmap = CreateDIBSection(hRefDC, pbmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    nInfoSize = GetLastError();
    ReleaseDC(NULL, hRefDC);
    free(pbmi);

    if(hBitmap == NULL)
    {
        TCHAR   szTemp[64];
        _snprintf(szTemp, sizeof(szTemp)-1, "Error %d", nInfoSize);
        szTemp[sizeof(szTemp)-1] = '\0';
        MessageBox(NULL, szTemp, "Error", MB_OK);
    }

    return hBitmap;
}

/* ******************************************************************* */

/* **********************************************************************
  BOOL DSLoadDIBSectionFromBMPFile(LPTSTR, HBITMAP *, HPALETTE *)

  PARAMETERS:
    LPTSTR     - Name of (BMP) file from which to obtain DIBSection
    HBITMAP *  - Pointer to handle which receives HBITMAP DIBSection
    HPALETTE * - Pointer to handle which receives Palette

  RETURNS:
    BOOL    - TRUE for success, FALSE for failure

  REMARKS:
    Creates a DIBSection based on the contents of a BMP file.
    If the HPALETTE pointer is NULL, no palette is retreived.
    If the HPALETTE pointer is non-NULL, the palette is created by
    calling DSCreatePaletteForDIBSection. See its comments for 
    information regarding its functionality.

    The LoadImage() API is used to load the bitmap.

********************************************************************** */

BOOL WINAPI DSLoadDIBSectionFromBMPFile(LPTSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette)
{
    if(phBitmap == NULL)
        return FALSE;
   
	*phBitmap = NULL;

    if(phPalette != NULL)
        *phPalette = NULL;

    // Use LoadImage() to get the image loaded into a DIBSection
    *phBitmap = LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
    if(*phBitmap == NULL)
        return FALSE;

	// if they want a palette, get one
    if(phPalette != NULL)
        *phPalette = DSCreatePaletteForDIBSection(*phBitmap);

	return TRUE;
}

/* ******************************************************************* */

/* **********************************************************************
  BOOL DSDrawDIBSectionOnDC(HDC, HBITMAP, LPRECT)

  PARAMETERS:
    HDC     - HDC on which to draw the DIBSection
    HBITMAP - the DIBSection to be drawn
    LPRECT  - pointer to a rectangle containing the target coordinates

  RETURNS:
    BOOL    - TRUE for success, FALSE for failure

  REMARKS:
    Draws a DIBSection on a target DC.
    The bitmap is drawn using StretchBlt() if the target DC is a screen
    DC and StretchDIBits() otherwise.
    A pallete is used, only if the target DC is a screen DC. A more 
    robust implementation might check RASTERCAPS to see if the target
    device is a palettized device.
    Also, the palette is selected as a background palette. If it is
    desirable to have the palette as a foreground palette, simply 
    obtain and realize the palette in the foreground before calling
    this function.

********************************************************************** */

BOOL WINAPI DSDrawDIBSectionOnDC(HDC hDC, HBITMAP hBitmap, LPRECT pRect)
{
    DIBSECTION  ds;
    HPALETTE    hPal, hOldPal;
    BOOL        bRes;

    GetObject(hBitmap, sizeof(DIBSECTION), &ds);

    if(GetDeviceCaps(hDC, RASTERCAPS) & RC_PALETTE)
    {   // if it's a palette device, select and realize a palette
        // as a background palette (won't cause a problem is the
        // palette was not selected in the foreground in the main app
        hPal = DSCreatePaletteForDIBSection(hBitmap);
        hOldPal = SelectPalette(hDC, hPal, TRUE);
        RealizePalette(hDC);
    }

    if(GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASDISPLAY)
    { // going to the screen, use StretchBlt()
        HDC hMemDC;
        HBITMAP hOldBitmap;

        hMemDC = CreateCompatibleDC(hDC);
        hOldBitmap = SelectObject(hMemDC, hBitmap);
        bRes = StretchBlt(hDC, pRect->left, pRect->top, 
                pRect->right-pRect->left, pRect->bottom-pRect->top, 
                hMemDC, 0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, SRCCOPY);
        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }
    else
    { // going to the printer, use StretchDIBits()
        LPBITMAPINFO    pbmi;

        // if the printer is palettized, 
        pbmi = DSGetBITMAPINFOForDIBSection(hBitmap);
        if ( !pbmi )
            return FALSE;

        bRes = (GDI_ERROR != StretchDIBits(hDC, pRect->left, pRect->top, 
                pRect->right-pRect->left, pRect->bottom-pRect->top,
                0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, ds.dsBm.bmBits, 
                pbmi, DIB_RGB_COLORS, SRCCOPY));
        free(pbmi);
    }

    if(GetDeviceCaps(hDC, RASTERCAPS) & RC_PALETTE)
    {
        SelectPalette(hDC, hOldPal, TRUE);
        DeleteObject(hPal);
    }

    return bRes;
}

/* ******************************************************************* */

/* **********************************************************************
  BOOL DSStoreDIBSectionInBMPFile(LPTSTR, HBITMAP)

  PARAMETERS:
    LPTSTR     - Name of (BMP) file in which to store the DIBSection
    HBITMAP    - handle for HBITMAP DIBSection to be stored

  RETURNS:
    BOOL    - TRUE for success, FALSE for failure
   
  REMARKS:
    Stores the DIBSection in a BMP file.

********************************************************************** */

BOOL WINAPI DSStoreDIBSectionInBMPFile(LPTSTR szFileName, HBITMAP hBitmap)
{
    HANDLE              hFile;
    BITMAPFILEHEADER    bfh;
    LPBITMAPINFO        pbmi;
    DWORD               dwTotalDIBBytes, dwSize, dwWritten;
    LPBYTE              pBits;

    // Open the file for writing (overwrites any previous version of that file)
    if((hFile=CreateFile(szFileName,GENERIC_WRITE,0,NULL ,CREATE_ALWAYS, SECURITY_SQOS_PRESENT | SECURITY_ANONYMOUS,NULL)) == INVALID_HANDLE_VALUE)
        return FALSE;

    if ( GetFileType(hFile) != FILE_TYPE_DISK )
    {
        CloseHandle(hFile);
        return FALSE;
    }

    // Get the BITMAPINFO for the DIBSection
    if((pbmi = DSGetBITMAPINFOForDIBSection(hBitmap)) == NULL)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    // What's the total size of the DIB information (not counting file header)?
    dwTotalDIBBytes = DSTotalBytesSize(pbmi);

    // Construct the file header
    ZeroMemory(&bfh, sizeof(BITMAPFILEHEADER));
    bfh.bfType          = 0x4d42; // 'BM'
    bfh.bfSize          = dwTotalDIBBytes + sizeof(BITMAPFILEHEADER);
    bfh.bfReserved1     = 0;
    bfh.bfReserved2     = 0;
    bfh.bfOffBits       = (DWORD)(sizeof(BITMAPFILEHEADER) + pbmi->bmiHeader.biSize + DSColorTableSize(pbmi));

    // Write the file header
    if((! WriteFile(hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL)) || 
        (dwWritten != sizeof(BITMAPFILEHEADER)))
    {
        free(pbmi);
        CloseHandle(hFile);
        return FALSE;
    }

    // Write the BITMAPINFO
    dwSize = sizeof(BITMAPINFOHEADER) + DSColorTableSize(pbmi);

    if((! WriteFile(hFile, pbmi, dwSize, &dwWritten, NULL)) || 
        (dwWritten != dwSize))
    {
        free(pbmi);
        CloseHandle(hFile);
        return FALSE;
    }

    // Write the bits
    pBits = DSGetPointerToDIBSectionImageBits(hBitmap);
    dwSize = DSImageBitsSize(pbmi);

    if((! WriteFile(hFile, pBits, dwSize, &dwWritten, NULL)) || 
        (dwWritten != dwSize))
    {
        free(pbmi);
        CloseHandle(hFile);
        return FALSE;
    }

    // clean up and leave
    free(pbmi);
    CloseHandle(hFile);

    return TRUE;
}

/* ******************************************************************* */

/* **********************************************************************
  HPALETTE DSCreatePaletteForDIBSection(HBITMAP)

  PARAMETERS:
    HBITMAP - a DIBSection for which to get a palette

  RETURNS:
    HPALETTE - a palette which can be used to display the DIBSection
               on palettized devices

  REMARKS:
    Creates a palette to be used to display the DIBSection on a 
    palettized display device.

    If the DIBSection contains a color table, those colors are used 
    to create the palette. However, if the DIBSection is greater than
    8bpp (ie sans color table), then a suitable palette is derived
    from either CreateHalftonePalette() or GetStockObject() depending
    on the video mode.

********************************************************************** */

HPALETTE WINAPI DSCreatePaletteForDIBSection(HBITMAP hBitmap)
{
    BITMAP      bm;
    HPALETTE    hPalette;

    // Get the color depth of the DIBSection
    if (!GetObject(hBitmap, sizeof(BITMAP), &bm))
		return (HPALETTE)NULL;

    // If the DIBSection is 256 color or less, it has a color table
    if((bm.bmBitsPixel * bm.bmPlanes) <= 8)
    {
        HDC             hMemDC;
        HBITMAP         hOldBitmap;
        RGBQUAD         rgb[256];
        LPLOGPALETTE    pLogPal;
        WORD            i;
        int             nColors;
		
        // Find out how many colors are in the color table
        nColors = 1 << (bm.bmBitsPixel * bm.bmPlanes);

        // Create a memory DC and select the DIBSection into it
        hMemDC = CreateCompatibleDC(NULL);
        hOldBitmap = SelectObject(hMemDC, hBitmap);

        ZeroMemory(rgb, sizeof(rgb));

		// Get the DIBSection's color table
        GetDIBColorTable(hMemDC, 0, nColors, rgb);

        // Create a palette from the color table
        pLogPal = malloc(sizeof(LOGPALETTE) + (nColors*sizeof(PALETTEENTRY)));
        if ( !pLogPal )
        {
            DeleteDC(hMemDC);
            return (HPALETTE)NULL;
        }

        pLogPal->palVersion = 0x300;
        pLogPal->palNumEntries = (WORD)nColors;

        for(i=0;i<nColors;i++)
        {
            pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
            pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
            pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
            pLogPal->palPalEntry[i].peFlags = 0;
        }

        hPalette = CreatePalette(pLogPal);

        // Clean up
        free(pLogPal);
        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);

	} else  {  // It has no color table, so make one for the current video mode
		HDC hdc = GetDC(NULL);
		int iBitsPixel = GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL);
		
		if (iBitsPixel <= 8)
			hPalette = CreateHalftonePalette(hdc);
		else
			hPalette = GetStockObject(DEFAULT_PALETTE);

		ReleaseDC(NULL, hdc);
	}

	return hPalette;
}

/* ******************************************************************* */

/* **********************************************************************
  LPBITMAPINFO DSGetBITMAPINFOForDIBSection(HBITMAP)

  PARAMETERS:
    HBITMAP - a DIBSection for which to get the BITMAPINFO

  RETURNS:
    LPBITMAPINFO - a pointer to a newly allocated memory block containing
                   the BITMAPINFO structure which describes the DIBSection.

  REMARKS:
    Allocates and returns a pointer to a BITMAPINFO for the DIBSection.
    The returned BITMAPINFO contains a color table, even if the 
    bit-depth does not require one - this way the caller can override
    the optional color table if need be.
    The caller is responsible for de-allocating the memory block using
    the CRT function free().

********************************************************************** */

LPBITMAPINFO WINAPI DSGetBITMAPINFOForDIBSection(HBITMAP hBitmap)
{
    LPBITMAPINFO    pbmi;
    DIBSECTION      ds;
    LPRGBQUAD       prgb;

    GetObject(hBitmap, sizeof(DIBSECTION), &ds);

    // load the header and the bitmasks if present
    // per function comments above, we allocate space for a color 
    // table even if it is not needed 
    if(ds.dsBmih.biCompression == BI_BITFIELDS)
    {   // has a bitmask - be sure to allocate for and copy them
        pbmi = malloc(sizeof(BITMAPINFOHEADER) + (3*sizeof(DWORD)) + (256*sizeof(RGBQUAD)));
        if ( !pbmi )
            return (LPBITMAPINFO)NULL;

        CopyMemory(&(pbmi->bmiHeader), &(ds.dsBmih), sizeof(BITMAPINFOHEADER) + (3*sizeof(DWORD)));
        prgb = (LPRGBQUAD)&(pbmi->bmiColors[3]);
    }
    else
    {   // no bitmask - just the header and color table
        pbmi = malloc(sizeof(BITMAPINFOHEADER) + (256*sizeof(RGBQUAD)));
        if ( !pbmi )
            return (LPBITMAPINFO)NULL;

        CopyMemory(&(pbmi->bmiHeader), &(ds.dsBmih), sizeof(BITMAPINFOHEADER));
        prgb = pbmi->bmiColors;
    }

    // at this point, prgb points to the color table, even 
    // if bitmasks are present

    // Now for the color table
    if((ds.dsBm.bmBitsPixel * ds.dsBm.bmPlanes) <= 8)
    {   // the DIBSection is 256 color or less (has color table)
        HDC             hMemDC;
        HBITMAP         hOldBitmap;
        hMemDC = CreateCompatibleDC(NULL);
        hOldBitmap = SelectObject(hMemDC, hBitmap);
        GetDIBColorTable(hMemDC, 0, 1<<(ds.dsBm.bmBitsPixel*ds.dsBm.bmPlanes), prgb);
        SelectObject(hMemDC, hOldBitmap);
        DeleteDC(hMemDC);
    }
    else
    {   // the DIBSection is >8bpp (has no color table) so make one up
        HPALETTE        hPal;
        PALETTEENTRY    pe[256];
        int             i;

        // where are we going to get the colors? from a spectrum palette
        hPal = DSCreateSpectrumPalette();
        GetPaletteEntries(hPal, 0, 256, pe);

        for(i=0;i<256;i++)
        {
            prgb[i].rgbRed = pe[i].peRed;
            prgb[i].rgbGreen = pe[i].peGreen;
            prgb[i].rgbBlue = pe[i].peBlue;
            prgb[i].rgbReserved = 0;
        }

        DeleteObject(hPal);
        pbmi->bmiHeader.biClrUsed = 256;
    }

    return pbmi;
}

/* ******************************************************************* */

/* **********************************************************************
  DWORD DSColorTableSize(LPBITMAPINFO pbmi)

  PARAMETERS:
    LPBITMAPINFO - pointer to a BITMAPINFO describing a DIB

  RETURNS:
    DWORD    - the size, in bytes, of the color table for the DIB
   
  REMARKS:
    Calculates and returns the size, in bytes, of the color table for
    the DIB described by the BITMAPINFO.

********************************************************************** */

DWORD WINAPI DSColorTableSize(LPBITMAPINFO pbmi)
{
    DWORD dwColors;

    dwColors = 0;
    if(pbmi->bmiHeader.biClrUsed != 0)
        dwColors = pbmi->bmiHeader.biClrUsed;
    else if(pbmi->bmiHeader.biBitCount > 8)
        dwColors = 0;
    else
        dwColors = 1 << (pbmi->bmiHeader.biBitCount * pbmi->bmiHeader.biPlanes);

    if(pbmi->bmiHeader.biCompression == BI_BITFIELDS)
        return (sizeof(DWORD)*3) + (dwColors*sizeof(RGBQUAD));

    return (dwColors*sizeof(RGBQUAD));
}

/* ******************************************************************* */

/* **********************************************************************
  DWORD DSImageBitsSize(LPBITMAPINFO pbmi)

  PARAMETERS:
    LPBITMAPINFO - pointer to a BITMAPINFO describing a DIB

  RETURNS:
    DWORD    - the size, in bytes, of the DIB's image bits

  REMARKS:
    Calculates and returns the size, in bytes, of the image bits for
    the DIB described by the BITMAPINFO.

********************************************************************** */

DWORD WINAPI DSImageBitsSize(LPBITMAPINFO pbmi)
{
    switch(pbmi->bmiHeader.biCompression)
    {
        case BI_RLE8:
        case BI_RLE4:
            return pbmi->bmiHeader.biSizeImage;
        break;

		case BI_RGB:
        case BI_BITFIELDS:
            return BYTESPERLINE(pbmi->bmiHeader.biWidth,pbmi->bmiHeader.biBitCount*pbmi->bmiHeader.biPlanes)*pbmi->bmiHeader.biHeight;
        break;
    }

    return 0;
}

/* ******************************************************************* */

/* **********************************************************************
  DWORD DSTotalBytesSize(LPBITMAPINFO pbmi)

  PARAMETERS:
    LPBITMAPINFO - pointer to a BITMAPINFO describing a DIB

  RETURNS:
    DWORD    - the size, in bytes, of the DIB's memory footprint

  REMARKS:
    Calculates and returns the size, in bytes, of the entire CF_DIB 
    bitmap described by the BITMAPINFO - including header, color table,
    and image bits.

********************************************************************** */

DWORD WINAPI DSTotalBytesSize(LPBITMAPINFO pbmi)
{
    return DSImageBitsSize(pbmi) + sizeof(BITMAPINFOHEADER) + DSColorTableSize(pbmi);
}

/* ******************************************************************* */

/* **********************************************************************
  LPBYTE DSGetPointerToDIBSectionImageBits(HBITMAP hBitmap)

  PARAMETERS:
    HBITMAP    - handle for HBITMAP DIBSection

  RETURNS:
    LPBYTE     - pointer to the bitmap's bits

  REMARKS:
    Returns a pointer to the DIBSection's image bits.

********************************************************************** */

// get a pointer which points to the image bits for a DIBSection
LPBYTE WINAPI DSGetPointerToDIBSectionImageBits(HBITMAP hBitmap)
{
    DIBSECTION  ds;

    if (!GetObject(hBitmap, sizeof(DIBSECTION), &ds))
		return NULL;

    return ds.dsBm.bmBits;
}

/* ******************************************************************* */

/* **********************************************************************
  HPALETTE DSCreateSpectrumPalette(void) 

  PARAMETERS:
    void

  RETURNS:
    HPALETTE - a handle to a spectrum palette - NULL on failure

  REMARKS:
    This function was stolen from Mike Irvine's SEEDIB sample. There's
    no source code comments in his version either :)

    This function will build a palette with a spectrum of colors.  It is
    useful when you want to display a number of DIBs each with a different
    palette yet still have an a good selection of colors to which the 
    DIBs' colors will be mapped.

********************************************************************** */

HPALETTE WINAPI DSCreateSpectrumPalette(void) 
{                 
    HPALETTE hPal;
    LPLOGPALETTE lplgPal;
    BYTE red, green, blue;
    int i; 

    lplgPal = (LPLOGPALETTE)GlobalAlloc(GPTR, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256); 

    if (!lplgPal)
      return NULL;

    lplgPal->palVersion = 0x300;
    lplgPal->palNumEntries = 256;

    red = green = blue = 0;

    for (i = 0; i < 256; i++) {
        lplgPal->palPalEntry[i].peRed   = red;
        lplgPal->palPalEntry[i].peGreen = green;
        lplgPal->palPalEntry[i].peBlue  = blue;
        lplgPal->palPalEntry[i].peFlags = (BYTE)0;

        if (!(red += 32))
            if (!(green += 32))
                blue += 64;
    }

    hPal = CreatePalette(lplgPal);
    GlobalFree(lplgPal);

    return hPal;
}

/* ******************************************************************* */

/* **********************************************************************
  DWORD DSBitsPerPixel(HBITMAP) 

  PARAMETERS:
	The handle of the DIB Section to evaluate

  RETURNS:
    DWORD - the total number of color bits used by the surface

********************************************************************** */

DWORD WINAPI DSBitsPerPixel (HBITMAP hBitmap)
{
    DIBSECTION  ds;

    GetObject(hBitmap, sizeof(DIBSECTION), &ds);
    return (ds.dsBmih.biBitCount * ds.dsBmih.biPlanes);
}

/* ******************************************************************* */

/* **********************************************************************
  BOOL DSGetOptimalDIBFormat(HDC, BITMAPINFOHEADER*)

  PURPOSE:
	Retrieves the optimal DIB format for a display 
	device. The optimal DIB format is the format that 
	exactly matches the format of the target device. 
	Obtaining this is very important when dealing with 
	16bpp modes because you need to know what bitfields 
	value to use (555 or 565 for example).

	You normally use this function to get the best
	format to pass to CreateDIBSection() in order to
	maximize blt'ing performance.

  PARAMETERS:
	hdc - Device to get the optimal format for.
	pbi - Pointer to a BITMAPINFO + color table
		(room for 256 colors is assumed).

  OUTPUT:
	pbi - Contains the optimal DIB format. In the 
		<= 8bpp case, the color table will contain the 
		system palette. In the >=16bpp case, the "color 
		table" will contain the correct bit fields (see 
		BI_BITFIELDS in the Platform SDK documentation 
		for more information).
  
  RETURNS:
    Returns TRUE if the function succeeds

  NOTES:
	If you are going to use this function on a 8bpp device
	you should make sure the color table contains a identity
	palette for optimal blt'ing.

********************************************************************** */

BOOL WINAPI DSGetOptimalDIBFormat(HDC hdc, BITMAPINFOHEADER *pbi)
{
   HBITMAP hbm;
   BOOL bRet = TRUE;

   // Create a memory bitmap that is compatible with the
   // format of the target device.
   hbm = CreateCompatibleBitmap(hdc, 1, 1);
   if (!hbm)
       return FALSE;

   // Initialize the header.
   ZeroMemory(pbi, sizeof(BITMAPINFOHEADER));
   pbi->biSize = sizeof(BITMAPINFOHEADER);

   // First call to GetDIBits will fill in the optimal biBitCount.
   bRet = GetDIBits(hdc, hbm, 0, 1, NULL, (BITMAPINFO*)pbi, DIB_RGB_COLORS);

   // Second call to GetDIBits will get the optimal color table, o
   // or the optimal bitfields values.
   if (bRet)
       bRet = GetDIBits(hdc, hbm, 0, 1, NULL, (BITMAPINFO*)pbi, DIB_RGB_COLORS);
   
   // Clean up.
   DeleteObject(hbm);

   return bRet;
}

/* ******************************************************************* */
// CountBits(DWORD)
//
// Counts the number of set bits in a DWORD.
BYTE CountBits(DWORD dw)
{
   int iBits = 0;
   
   while (dw) {
       iBits += (dw & 1);
       dw >>= 1;
   }

   return (BYTE)iBits;
}

/* **********************************************************************
  BOOL DSGetRGBBitsPerPixel(HDC, PINT, PINT, PINT)

  PURPOSE:
	Retrieves the number of bits of color resolution for each 
	color channel of a specified.

  PARAMETERS:
	hdc - Device to get the color information for.

  OUTPUT:
	pRed   - Number of distinct red levels the device can display.
	pGreen - Number of distinct green levels the device can display.
	pBlue  - Number of distinct blue levels the device can display.

  RETURNS:
    Returns TRUE if the function succeeds

  NOTES:
	This function does not return any meaningful information for
	palette-based devices.

********************************************************************** */

BOOL WINAPI DSGetRGBBitsPerPixel(HDC hdc, PINT pRed, PINT pGreen, PINT pBlue)
{
   BITMAPINFOHEADER *pbi;
   LPDWORD lpdw;
   BOOL bRet = TRUE;

   // If the target device is palette-based, then bail because there is no
   // meaningful way to determine separate RGB bits per pixel.
   if (GetDeviceCaps(hdc, RASTERCAPS) & RC_PALETTE) 
       return FALSE;  

   // Shortcut for handling 24bpp cases.
   if (GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL) == 24) {
       *pRed = *pGreen = *pBlue = 8;
       return TRUE;
   }

   // Allocate room for a header and a color table.
   pbi = (BITMAPINFOHEADER *)GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER) + 
                                               sizeof(RGBQUAD)*256);
   if (!pbi)
       return FALSE;

   // Retrieve a description of the device surface.
   if (DSGetOptimalDIBFormat(hdc, pbi)) {
       // Get a pointer to the bitfields.
       lpdw = (LPDWORD)((LPBYTE)pbi + sizeof(BITMAPINFOHEADER));

       *pRed   = CountBits(lpdw[0]);
       *pGreen = CountBits(lpdw[1]);
       *pBlue  = CountBits(lpdw[2]);
   } else
       bRet = FALSE;

   // Clean up.
   GlobalFree(pbi);

   return bRet;
}

/* ******************************************************************* */

/******************************************************************************
 *                                                                            *
 *  FUNCTION   : DIBNumColors(LPVOID lpv)                                     *
 *                                                                            *
 *  PURPOSE    : Determines the number of colors in the DIB by looking at     *
 *               the BitCount and ClrUsed fields in the info block.           *
 *                                                                            *
 *  RETURNS    : The number of colors in the DIB. With DIBS with more than    *
 *               8-bits-per-pixel that have a color table table included,     *
 *               then the return value will be the number of colors in the    *
 *               color table rather than the number of colors in the DIB.     *
 *                                                                            *
 *                                                                            *
 *****************************************************************************/

WORD DIBNumColors (LPVOID lpv)
{
    INT                 bits;
    LPBITMAPINFOHEADER  lpbih = (LPBITMAPINFOHEADER)lpv;
    LPBITMAPCOREHEADER  lpbch = (LPBITMAPCOREHEADER)lpv;

    /*  With the BITMAPINFO format headers, the size of the palette
     *  is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *  is dependent on the bits per pixel (= 2 raised to the power of
     *  bits/pixel).
     */

    if (NEW_DIB_FORMAT(lpbih)) {
      if (lpbih->biClrUsed != 0)
        return (WORD)lpbih->biClrUsed;
      bits = lpbih->biBitCount;
    }
    else
      bits = lpbch->bcBitCount;

    if (bits > 8) 
      return 0; /* Since biClrUsed is 0, we dont have a an optimal palette */
    else
      return (WORD)(1 << bits); 
}

/* ******************************************************************* */

/******************************************************************************
 *                                                                            *
 *  FUNCTION   :  DIBColorTableSize(LPVOID lpv)                               *
 *                                                                            *
 *  PURPOSE    :  Calculates the palette size in bytes. If the info. block    *
 *                is of the BITMAPCOREHEADER type, the number of colors is    *
 *                multiplied by 3 to give the palette size, otherwise the     *
 *                number of colors is multiplied by 4.                        *
 *                                                                            *
 *  RETURNS    :  Color table size in number of bytes.                        *
 *                                                                            *
 *****************************************************************************/

WORD DIBColorTableSize (LPVOID lpv)
{
    LPBITMAPINFOHEADER lpbih = (LPBITMAPINFOHEADER)lpv;

    if (NEW_DIB_FORMAT(lpbih))
    {
      if (((LPBITMAPINFOHEADER)(lpbih))->biCompression == BI_BITFIELDS)
         /* Remember that 16/32bpp dibs can still have a color table */
         return (sizeof(DWORD) * 3) + (DIBNumColors (lpbih) * sizeof (RGBQUAD));
      else
         return (DIBNumColors (lpbih) * sizeof (RGBQUAD));
    }
    else
      return (DIBNumColors (lpbih) * sizeof (RGBTRIPLE));
}

/* ******************************************************************* */

/* **********************************************************************

  HBITMAP DSGetDIBSectionFromClipboard(void)

  RETURNS:
    HBITMAP      - a DIBSection HBITMAP or NULL on failure

  REMARKS:
    Creates a DIBSection based on the attributes of the clipboard

********************************************************************** */

HBITMAP WINAPI DSGetDIBSectionFromClipboard()
{
    HBITMAP         hBitmap = NULL;
    HANDLE			hClipData;
	HDC				hdcRef;
		
	// Is there any bitmap data (that we can use) on the cliboard?
	if (!IsClipboardFormatAvailable(CF_DIB) && !IsClipboardFormatAvailable(CF_BITMAP))
		return (HBITMAP)NULL;  // Nope, bail

	if (!OpenClipboard(NULL))
		return FALSE; 

	// Get a reference DC
	hdcRef = GetDC(NULL);

	if (IsClipboardFormatAvailable(CF_DIB)) {
		PBYTE           pBitsDS, pBitsDIB;
		LPBITMAPINFO    pbmi;

		hClipData = GetClipboardData(CF_DIB);
		if (hClipData) {
			pbmi = (LPBITMAPINFO)GlobalLock(hClipData);

			// Create a DIB section compatible with the clipboard contents
			hBitmap = CreateDIBSection(hdcRef, pbmi, DIB_RGB_COLORS, &pBitsDS, NULL, 0);

			// Get a pinter to the surface bits
			pBitsDIB = (LPBYTE)pbmi + sizeof(BITMAPINFOHEADER) + DIBColorTableSize(pbmi);

			// Copy the surface contents to the surface of our DIB section
			CopyMemory(pBitsDS, pBitsDIB, pbmi->bmiHeader.biSizeImage);

			GlobalUnlock(hClipData);
		}
	} 

	// If we couldn't get a DIB (or we didn't want one) try to get a DDB
	if (!hBitmap && IsClipboardFormatAvailable(CF_BITMAP)) {
		HPALETTE		hPal;
		
		hClipData = GetClipboardData(CF_BITMAP);
		hPal = GetClipboardData(CF_PALETTE);
	
		hBitmap = DSCopyBitmap((HBITMAP)hClipData, hPal);
	}

	ReleaseDC(NULL, hdcRef);
	CloseClipboard();

    return hBitmap;
}

/* ******************************************************************* */

HBITMAP WINAPI DSCreateDDBForDS(HBITMAP hbmp)
{
    HBITMAP		hBitmap;
	HPALETTE	hPal;
	BITMAP		bm;
	HDC			hdcSrc, hdcDst;
	HDC			hdcScreen;
		
	// Get information about the surface
	if (!GetObject(hbmp, sizeof(BITMAP), &bm))
		return (HBITMAP)NULL;
		
	hdcScreen = GetDC(NULL);
	hPal = DSCreatePaletteForDIBSection(hbmp);

	// Create a DIB section to hold our copy of the data
	hBitmap = CreateCompatibleBitmap(hdcScreen, bm.bmWidth, bm.bmHeight);
	hdcSrc = CreateCompatibleDC(hdcScreen); 
	hdcDst = CreateCompatibleDC(hdcScreen);

	// Prepare the source bitmap
	SelectObject(hdcSrc, hbmp);
	SelectPalette(hdcSrc, hPal, FALSE);
	RealizePalette(hdcSrc);

	// Prepare the destination bitmap
	SelectObject(hdcDst, hBitmap);
	SelectPalette(hdcDst, hPal, FALSE);
	RealizePalette(hdcDst);
	
	// Copy the contents of the surface from the source to the destination
	BitBlt(hdcDst, 0,0, bm.bmWidth, bm.bmHeight, hdcSrc, 0,0, SRCCOPY);
		
	// Clean up
	DeleteDC(hdcSrc);
	DeleteDC(hdcDst);
	DeleteObject(hPal);
	
    return hBitmap;
}

/* **********************************************************************
  BOOL DSPutDIBSectionOnClipboard(HBITMAP)

  RETURNS:
    HBITMAP      - Returns TRUE if the call succeeds
    
  REMARKS:
    Places a DIB section on the clipboard in CF_DIB format

********************************************************************** */

BOOL WINAPI DSPutDIBSectionOnClipboard(HBITMAP hbm)
{
    HGLOBAL         hDIB;
	BOOL            bRet;
    
	if (!OpenClipboard(NULL))
		return FALSE; 
	
	if (!(hDIB = DSGetDIBFromDIBSection(hbm)))
		return FALSE;

	// Clear the clipboard
	EmptyClipboard();

	// Add our bitmap to the clipboard
	bRet = (SetClipboardData(CF_DIB, hDIB) != NULL);
	
	CloseClipboard();

    return bRet;
}
/* ******************************************************************* */


/* **********************************************************************

  HBITMAP WINAPI DSCopyBitmapEx(HBITMAP, HPALETTE, WORD)

  RETURNS:
    HBITMAP - a DIBSection copy of the HBITMAP passed in
    
  REMARKS:
    Makes a copy of a DIBSection or DDB/Palette.  Use a NULL HPALETTE
	if the HBITMAP parameter is	a DIBSection

********************************************************************** */

HBITMAP WINAPI DSCopyBitmapEx(HBITMAP hbmp, HPALETTE hPal, WORD wBits)
{
    HBITMAP         hBitmap = NULL;
	BOOL			bNeedToCleanUp = FALSE;
    BITMAP			bm;
	HDC				hdcSrc, hdcDst;
	RGBQUAD			rgbq[256];
	int				iNumColors, i;
		
	if (!GetObject(hbmp, sizeof(BITMAP), &bm))
		return (HBITMAP)NULL;
		
	// Create a DIB section to hold our copy of the data
	hBitmap = DSCreateDIBSection(bm.bmWidth, bm.bmHeight, wBits);

	hdcSrc = CreateCompatibleDC(NULL); 
	hdcDst = CreateCompatibleDC(NULL);

	if (hPal) {
		// Get the colors from the palette and copy them to our color table
		iNumColors = GetPaletteEntries(hPal, 0, 256, (LPPALETTEENTRY)rgbq);
		
		// RGB in PALETTEENTRYs and RGBQUADs are in different order so adjust
		for (i=0; i<iNumColors; i++) {
			SWAP(rgbq[i].rgbBlue, rgbq[i].rgbRed);
			rgbq[i].rgbReserved = 0;
		}
	} else 
		if (wBits <= 8) { // We need some sort of color table for the target image
			// We're creating the palette rather than using one that was 
			// passed in so we need to remember to clean it up before returning
			bNeedToCleanUp = TRUE;  

			// Get the palette from the source images
			hPal = DSCreatePaletteForDIBSection(hbmp);
			
			// Convert it to RGBQUAD format
			iNumColors = GetPaletteEntries(hPal, 0, 256, (LPPALETTEENTRY)rgbq);
			
			// RGB in PALETTEENTRYs and RGBQUADs are in different order so adjust
			for (i=0; i<iNumColors; i++) {
				SWAP(rgbq[i].rgbBlue, rgbq[i].rgbRed);
				rgbq[i].rgbReserved = 0;
			}
		} else {
			hPal = GetStockObject(DEFAULT_PALETTE);
			iNumColors = 0;
		}
		
	// Prepare the source bitmap
	SelectObject(hdcSrc, hbmp);
	SelectPalette(hdcSrc, hPal, FALSE);
	RealizePalette(hdcSrc);

	// Prepare the destination bitmap
	SelectObject(hdcDst, hBitmap);
	SelectPalette(hdcDst, hPal, FALSE);
	RealizePalette(hdcDst);
	if (iNumColors)
		SetDIBColorTable(hdcDst, 0, iNumColors, rgbq);

	BitBlt(hdcDst, 0,0, bm.bmWidth, bm.bmHeight, hdcSrc, 0,0, SRCCOPY);
		
	DeleteDC(hdcSrc);
	DeleteDC(hdcDst);

	if (bNeedToCleanUp)
		DeleteObject(hPal);
		
    return hBitmap;
}
/* ******************************************************************* */


/* **********************************************************************
  HBITMAP WINAPI DSCopyBitmap(HBITMAP, HPALETTE)

  RETURNS:
    HBITMAP - a DIBSection copy of the HBITMAP passed in
    
  REMARKS:
    Makes a copy of a DIBSection or DDB/Palette.  Use a NULL HPALETTE
	if the HBITMAP parameter is	a DIBSection

********************************************************************** */

HBITMAP WINAPI DSCopyBitmap(HBITMAP hbmp, HPALETTE hPal)
{
    BITMAP			bm;
		
	if (!GetObject(hbmp, sizeof(BITMAP), &bm))
		return (HBITMAP)NULL;
		
	// Create a DIB section to hold our copy of the data
	return DSCopyBitmapEx(hbmp, hPal, (WORD)(bm.bmPlanes*bm.bmBitsPixel));
}
/* ******************************************************************* */

/***************************************************************************\
* DSGetDIBFromDIBSection
*
* Creates a memory block in CF_DIB format
*
* CF_DIB format consists of a BITMAPINFOHEADER + RGB colors + DIB bits.
*
\***************************************************************************/

HGLOBAL WINAPI DSGetDIBFromDIBSection(HBITMAP  hbmp)
{
	HGLOBAL		 hDIB;
	LPBYTE       pDIB; 
	LPBITMAPINFO pbmi;
	LPBYTE       pBits;
	DWORD		 dwSize;
	
	// Attempt to get a pointer to the image bits
    pBits = DSGetPointerToDIBSectionImageBits(hbmp);

	// Did we get one?
	if (!pBits)
		return NULL; // No.  It's not a DIB section

	// Get a BITMAPINFO that describes the surface
    if (!(pbmi = DSGetBITMAPINFOForDIBSection(hbmp)))
		return NULL;

	// Get the size of the entire CF_DIB image
	dwSize = sizeof(BITMAPINFOHEADER) + DSColorTableSize(pbmi) + DSImageBitsSize(pbmi);
    
	// Allocate memory to hold the CF_DIB image
	if (!(hDIB = GlobalAlloc(GPTR, dwSize))) {
		free(pbmi);
		return NULL;
	}

	// Get a pointer to the memory block
	pDIB = (LPBYTE)GlobalLock(hDIB);	 

	// Copy over the DIB header information and the color table
	CopyMemory(pDIB, pbmi, sizeof(BITMAPINFOHEADER) + DSColorTableSize(pbmi));

	// Advance the pointer to where the surface bits should go
	pDIB += sizeof(BITMAPINFOHEADER) + DSColorTableSize(pbmi);

	CopyMemory(pDIB, pBits, DSImageBitsSize(pbmi));

    // clean up and leave
    free(pbmi);

    GlobalUnlock(hDIB);

	return hDIB;
}

