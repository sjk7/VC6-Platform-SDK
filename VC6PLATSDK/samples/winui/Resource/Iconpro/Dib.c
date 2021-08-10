/****************************************************************************\
*            
*     FILE:     DIB.C
*
*     PURPOSE:  DIB functions for IconPro Project
*
*     COMMENTS: Icons are stored in a format almost identical to DIBs. For
*               this reason, it is easiest to deal with the individual
*               icon images as DIBs (or DIBSections). This has the added
*               advantage of retaining color depth even on low-end displays.
*
*     FUNCTIONS:
*      EXPORTS: 
*               FindDIBBits()      - Locate the image bits in a DIB
*               DIBNumColors()     - Calculate number of color table entries
*               PaletteSize()      - Calculate number of color table bytes
*               BytesPerLine()     - Calculate number of bytes per scan line
*               ConvertDIBFormat() - Converts DIBs between formats
*               SetMonoDIBPixel()  - Sets/Clears a pixel in a 1bpp DIB
*               ReadBMPFile()      - Reads a BMP file into CF_DIB memory
*               WriteBMPFile()     - Write a BMP file from CF_DIB memory
*      LOCALS:
*               CopyColorTable()   - Copies color table from DIB to DIB
*
*     Copyright 1995 - 2000 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/
#include <Windows.h>
#include <malloc.h>
#include "Dib.H"


/****************************************************************************/
/* Local Function Prototypes */
BOOL CopyColorTable( PBITMAPINFO pTarget, PBITMAPINFO pSource );
/****************************************************************************/



/****************************************************************************
*
*     FUNCTION: FindDIBits
*
*     PURPOSE:  Locate the image bits in a CF_DIB format DIB.
*
*     PARAMS:   PSTR pbi - pointer to the CF_DIB memory block
*
*     RETURNS:  PSTR - pointer to the image bits
*
* History:
*                July '95 - Copied <g>
*
\****************************************************************************/
PSTR FindDIBBits( 
    PSTR pbi )
{
   return ( pbi + *(PDWORD)pbi + PaletteSize( pbi ) );
}
/* End FindDIBits() *********************************************************/



/****************************************************************************
*
*     FUNCTION: DIBNumColors
*
*     PURPOSE:  Calculates the number of entries in the color table.
*
*     PARAMS:   PSTR pbi - pointer to the CF_DIB memory block
*
*     RETURNS:  WORD - Number of entries in the color table.
*
* History:
*                July '95 - Copied <g>
*
\****************************************************************************/
WORD DIBNumColors( 
    PSTR pbi )
{
    WORD wBitCount;
    DWORD dwClrUsed;

    dwClrUsed = ((PBITMAPINFOHEADER) pbi)->biClrUsed;

    if (dwClrUsed)
    {
        return (WORD) dwClrUsed;
    }

    wBitCount = ((PBITMAPINFOHEADER) pbi)->biBitCount;

    switch (wBitCount)
    {
        case 1: return 2;
        case 4: return 16;
        case 8:	return 256;
        default:return 0;
    }
    return 0;
}
/* End DIBNumColors() ******************************************************/



/****************************************************************************
*
*     FUNCTION: PaletteSize
*
*     PURPOSE:  Calculates the number of bytes in the color table.
*
*     PARAMS:   PSTR pbi - pointer to the CF_DIB memory block
*
*     RETURNS:  WORD - number of bytes in the color table
*
*
* History:
*                July '95 - Copied <g>
*
\****************************************************************************/
WORD PaletteSize( 
    PSTR pbi )
{
    return (WORD)( DIBNumColors( pbi ) * sizeof( RGBQUAD ) );
}
/* End PaletteSize() ********************************************************/



/****************************************************************************
*
*     FUNCTION: BytesPerLine
*
*     PURPOSE:  Calculates the number of bytes in one scan line.
*
*     PARAMS:   PBITMAPINFOHEADER pBMIH - pointer to the BITMAPINFOHEADER
*                                           that begins the CF_DIB block
*
*     RETURNS:  DWORD - number of bytes in one scan line (DWORD aligned)
*
* History:
*                July '95 - Created
*
\****************************************************************************/
DWORD BytesPerLine( 
    PBITMAPINFOHEADER pBMIH )
{
    return WIDTHBYTES(pBMIH->biWidth * pBMIH->biPlanes * pBMIH->biBitCount);
}
/* End BytesPerLine() ********************************************************/




/****************************************************************************
*
*     FUNCTION: ConvertDIBFormat
*
*     PURPOSE:  Creates a new DIB of the requested format, copies the source
*               image to the new DIB.
*
*     PARAMS:   PBITMAPINFO  pSrcDIB  - the source CF_DIB
*               UINT         nWidth   - width for new DIB
*               UINT         nHeight  - height for new DIB
*               UINT         nbpp     - bpp for new DIB
*               BOOL         bStretch - TRUE to stretch source to dest
*                                       FALSE to take upper left of image
*
*     RETURNS:  PBYTE - pointer to new CF_DIB memory block with new image
*               NULL on failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
PBYTE ConvertDIBFormat( 
    PBITMAPINFO pSrcDIB, 
    UINT nWidth, 
    UINT nHeight, 
    UINT nbpp, 
    BOOL bStretch )
{
    PBITMAPINFO    pbmi            = NULL;
    PBYTE          pSourceBits     = NULL;
    PBYTE          pTargetBits     = NULL;
    PBYTE          pResult         = NULL;
    HDC            hDC              = NULL;
    HDC            hSourceDC        = NULL;
    HDC            hTargetDC        = NULL;
    HBITMAP        hSourceBitmap    = NULL;
    HBITMAP        hTargetBitmap    = NULL;
    HBITMAP        hOldTargetBitmap = NULL;
    HBITMAP        hOldSourceBitmap = NULL;
    DWORD          dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize;

    // Allocate and fill out a BITMAPINFO struct for the new DIB
    // Allow enough room for a 256-entry color table, just in case
    dwTargetHeaderSize = sizeof( BITMAPINFO ) + ( 256 * sizeof( RGBQUAD ) );
    pbmi = malloc( dwTargetHeaderSize );
    pbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
    pbmi->bmiHeader.biWidth = nWidth;
    pbmi->bmiHeader.biHeight = nHeight;
    pbmi->bmiHeader.biPlanes = 1;
    pbmi->bmiHeader.biBitCount = (WORD)nbpp;
    pbmi->bmiHeader.biCompression = BI_RGB;
    pbmi->bmiHeader.biSizeImage = 0;
    pbmi->bmiHeader.biXPelsPerMeter = 0;
    pbmi->bmiHeader.biYPelsPerMeter = 0;
    pbmi->bmiHeader.biClrUsed = 0;
    pbmi->bmiHeader.biClrImportant = 0;
    // Fill in the color table
    if( ! CopyColorTable( pbmi, (PBITMAPINFO)pSrcDIB ) )
    {
        free( pbmi );
        return NULL;
    }

    // Gonna use DIBSections and BitBlt() to do the conversion, so make 'em
    hDC = GetDC( NULL );
    hTargetBitmap = CreateDIBSection( hDC, pbmi, DIB_RGB_COLORS, &pTargetBits, NULL, 0 );
    hSourceBitmap = CreateDIBSection( hDC, pSrcDIB, DIB_RGB_COLORS, &pSourceBits, NULL, 0 );
    hSourceDC = CreateCompatibleDC( hDC );
    hTargetDC = CreateCompatibleDC( hDC );

    // Flip the bits on the source DIBSection to match the source DIB
    dwSourceBitsSize = pSrcDIB->bmiHeader.biHeight * BytesPerLine(&(pSrcDIB->bmiHeader));
    dwTargetBitsSize = pbmi->bmiHeader.biHeight * BytesPerLine(&(pbmi->bmiHeader));
    memcpy( pSourceBits, FindDIBBits((PSTR)pSrcDIB), dwSourceBitsSize );

    // Select DIBSections into DCs
    hOldSourceBitmap = SelectObject( hSourceDC, hSourceBitmap );
    hOldTargetBitmap = SelectObject( hTargetDC, hTargetBitmap );

    // Set the color tables for the DIBSections
    if( pSrcDIB->bmiHeader.biBitCount <= 8 )
    {
        SetDIBColorTable( hSourceDC, 0, 1 << pSrcDIB->bmiHeader.biBitCount, pSrcDIB->bmiColors );
    }
    
    if( pbmi->bmiHeader.biBitCount <= 8 )
    {
        SetDIBColorTable( hTargetDC, 0, 1 << pbmi->bmiHeader.biBitCount, pbmi->bmiColors );
    }

    // If we are asking for a straight copy, do it
    if( (pSrcDIB->bmiHeader.biWidth==pbmi->bmiHeader.biWidth) && (pSrcDIB->bmiHeader.biHeight==pbmi->bmiHeader.biHeight) )
    {
        BitBlt( hTargetDC, 0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY );
    }
    else
    {
        // else, should we stretch it?
        if( bStretch )
        {
            SetStretchBltMode( hTargetDC, COLORONCOLOR );
            StretchBlt( hTargetDC, 0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight, hSourceDC, 0, 0, pSrcDIB->bmiHeader.biWidth, pSrcDIB->bmiHeader.biHeight, SRCCOPY );
        }
        else
        {
            // or just take the upper left corner of the source
            BitBlt( hTargetDC, 0, 0, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY );
        }
    }

    // Clean up and delete the DCs
    SelectObject( hSourceDC, hOldSourceBitmap );
    SelectObject( hSourceDC, hOldTargetBitmap );
    DeleteDC( hSourceDC );
    DeleteDC( hTargetDC );
    ReleaseDC( NULL, hDC );

    // Flush the GDI batch, so we can play with the bits
    GdiFlush();

    // Allocate enough memory for the new CF_DIB, and copy bits
    pResult = malloc( dwTargetHeaderSize + dwTargetBitsSize );
    memcpy( pResult, pbmi, dwTargetHeaderSize );
    memcpy( FindDIBBits( pResult ), pTargetBits, dwTargetBitsSize );

    // final cleanup
    DeleteObject( hTargetBitmap );
    DeleteObject( hSourceBitmap );
    free( pbmi );

    return pResult;
}
/* End ConvertDIBFormat() ***************************************************/



/****************************************************************************
*
*     FUNCTION: CopyColorTable
*
*     PURPOSE:  Copies the color table from one CF_DIB to another.
*
*     PARAMS:   PBITMAPINFO pTarget - pointer to target DIB
*               PBITMAPINFO pSource - pointer to source DIB
*
*     RETURNS:  BOOL - TRUE for success, FALSE for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL CopyColorTable( 
    PBITMAPINFO pTarget, 
    PBITMAPINFO pSource )
{
    // What we do depends on the target's color depth
    switch( pTarget->bmiHeader.biBitCount )
    {
        // 8bpp - need 256 entry color table
        case 8:
            if( pSource->bmiHeader.biBitCount == 8 )
            { // Source is 8bpp too, copy color table
                memcpy( pTarget->bmiColors, pSource->bmiColors, 256*sizeof(RGBQUAD) );
                return TRUE;
            }
            else
            { // Source is != 8bpp, use halftone palette                
                HPALETTE        hPal;
                HDC            	hDC = GetDC( NULL );
                PALETTEENTRY    pe[256];
                UINT            i;

                hPal = CreateHalftonePalette( hDC );
                ReleaseDC( NULL, hDC );
                GetPaletteEntries( hPal, 0, 256, pe );
                DeleteObject( hPal );
                for(i=0;i<256;i++)
                {
                    pTarget->bmiColors[i].rgbRed = pe[i].peRed;
                    pTarget->bmiColors[i].rgbGreen = pe[i].peGreen;
                    pTarget->bmiColors[i].rgbBlue = pe[i].peBlue;
                    pTarget->bmiColors[i].rgbReserved = pe[i].peFlags;
                }
                return TRUE;
            }
            break; // end 8bpp

        // 4bpp - need 16 entry color table
        case 4:
            if( pSource->bmiHeader.biBitCount == 4 )
            { // Source is 4bpp too, copy color table
                memcpy( pTarget->bmiColors, pSource->bmiColors, 16*sizeof(RGBQUAD) );
                return TRUE;
            }
            else
            { // Source is != 4bpp, use system palette
                HPALETTE        hPal;
                PALETTEENTRY    pe[256];
                UINT            i;

                hPal = GetStockObject( DEFAULT_PALETTE );
                GetPaletteEntries( hPal, 0, 16, pe );
                for(i=0;i<16;i++)
                {
                    pTarget->bmiColors[i].rgbRed = pe[i].peRed;
                    pTarget->bmiColors[i].rgbGreen = pe[i].peGreen;
                    pTarget->bmiColors[i].rgbBlue = pe[i].peBlue;
                    pTarget->bmiColors[i].rgbReserved = pe[i].peFlags;
                }
                return TRUE;
            }
            break; // end 4bpp

        // 1bpp - need 2 entry mono color table
        case 1:
            pTarget->bmiColors[0].rgbRed = 0;
            pTarget->bmiColors[0].rgbGreen = 0;
            pTarget->bmiColors[0].rgbBlue = 0;
            pTarget->bmiColors[0].rgbReserved = 0;
            pTarget->bmiColors[1].rgbRed = 255;
            pTarget->bmiColors[1].rgbGreen = 255;
            pTarget->bmiColors[1].rgbBlue = 255;
            pTarget->bmiColors[1].rgbReserved = 0;
            break; // end 1bpp

        // no color table for the > 8bpp modes
        case 32:    /* fall-through */
        case 24:    /* fall-through */
        case 16:    /* fall-through */
        default:
            return TRUE;
            break;
    }
    return TRUE;
}
/* End CopyColorTable() *****************************************************/



/****************************************************************************
*
*     FUNCTION: SetMonoDIBPixel
*
*     PURPOSE:  Sets/Clears a pixel in a 1bpp DIB by directly poking the bits.
*
*     PARAMS:   PBYTE  pANDBits - pointer to the 1bpp image bits
*               DWORD  dwWidth	- width of the DIB
*               DWORD  dwHeight	- height of the DIB
*               DWORD  x        - x location of pixel to set/clear
*               DWORD  y        - y location of pixel to set/clear
*               BOOL   bWhite	- TRUE to set pixel, FALSE to clear it
*
*     RETURNS:  void
*
* History:
*                July '95 - Created
*
\****************************************************************************/
void SetMonoDIBPixel( 
    PBYTE pANDBits, 
    DWORD dwWidth,
    DWORD dwHeight, 
    DWORD x, 
    DWORD y, 
    BOOL bWhite )
{
    DWORD	ByteIndex;
    BYTE    BitNumber;

    // Find the byte on which this scanline begins
    ByteIndex = (dwHeight - y - 1) * WIDTHBYTES(dwWidth);
    // Find the byte containing this pixel
    ByteIndex += (x >> 3);
    // Which bit is it?
    BitNumber = (BYTE)( 7 - (x % 8) );

    if( bWhite )
    {
        // Turn it on
        pANDBits[ByteIndex] |= (1<<BitNumber);
    }
    else
    {
        // Turn it off
        pANDBits[ByteIndex] &= ~(1<<BitNumber);
    }
}
/* End SetMonoDIBPixel() *****************************************************/



/****************************************************************************
*
*     FUNCTION: ReadBMPFile
*
*     PURPOSE:  Reads a BMP file into CF_DIB format
*
*     PARAMS:   PCTSTR szFileName - the name of the file to read
*
*     RETURNS:  PBYTE - pointer to the CF_DIB, NULL for failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
PBYTE ReadBMPFile( 
    PCTSTR szFileName )
{
    HANDLE              hFile        = NULL;
    BITMAPFILEHEADER    bfh          = {0};
    DWORD               dwBytes      = 0;
    PBYTE               pDIB        = NULL;
    PBYTE               pTemp       = NULL;
    WORD                wPaletteSize = 0;
    DWORD               dwBitsSize   = 0;

    // Open the file
    if( (hFile=CreateFile( szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE )
    {
        MessageBox( NULL, TEXT("Error opening file"), szFileName, MB_OK );
        return NULL;
    }
    // Read the header
    if( ( ! ReadFile( hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytes, NULL ) ) || ( dwBytes != sizeof( BITMAPFILEHEADER ) ) )
    {
        CloseHandle( hFile );
        MessageBox( NULL, TEXT("Error reading file"), szFileName, MB_OK );
        return NULL;
    }
    // Does it look like a BMP file?
    if( ( bfh.bfType != 0x4d42 ) || (bfh.bfReserved1!=0) || (bfh.bfReserved2!=0) )
    {
        CloseHandle( hFile );
        MessageBox( NULL, TEXT("Not a recognised BMP format file"), szFileName, MB_OK );
        return NULL;
    }
    // Allocate some memory
    if( (pDIB = malloc( sizeof( BITMAPINFO ) )) == NULL )
    {
        CloseHandle( hFile );
        MessageBox( NULL, TEXT("Failed to allocate memory for DIB"), szFileName, MB_OK );
        return NULL;
    }
    // Read in the BITMAPINFOHEADER
    if( (!ReadFile( hFile, pDIB, sizeof(BITMAPINFOHEADER), &dwBytes, NULL )) || (dwBytes!=sizeof(BITMAPINFOHEADER)) )
    {
        CloseHandle( hFile );
        free( pDIB );
        MessageBox( NULL, TEXT("Error reading file"), szFileName, MB_OK );
        return NULL;
    }
    if( ((PBITMAPINFOHEADER)pDIB)->biSize != sizeof( BITMAPINFOHEADER ) )
    {
        CloseHandle( hFile );
        free( pDIB );
        MessageBox( NULL, TEXT("OS/2 style BMPs Not Supported"), szFileName, MB_OK );
        return NULL;
    }
    // How big are the elements?
    wPaletteSize = PaletteSize((PSTR)pDIB);
    dwBitsSize = ((PBITMAPINFOHEADER)pDIB)->biHeight * BytesPerLine((PBITMAPINFOHEADER)pDIB);
    // realloc to account for the total size of the DIB
    if( (pTemp = realloc( pDIB, sizeof( BITMAPINFOHEADER ) + wPaletteSize + dwBitsSize )) == NULL )
    {
        CloseHandle( hFile );
        MessageBox( NULL, TEXT("Failed to allocate memory for DIB"), szFileName, MB_OK );
        free( pDIB );
        return NULL;
    }
    pDIB = pTemp;
    // If there is a color table, read it
    if( wPaletteSize != 0 )
    {
        if( (!ReadFile( hFile, ((PBITMAPINFO)pDIB)->bmiColors, wPaletteSize, &dwBytes, NULL )) || (dwBytes!=wPaletteSize) )
        {
            CloseHandle( hFile );
            free( pDIB );
            MessageBox( NULL, TEXT("Error reading file"), szFileName, MB_OK );
            return NULL;
        }
    }
    // Seek to the bits
    // checking against 0 in case some bogus app didn't set this element
    if( bfh.bfOffBits != 0 )
    {
        if( SetFilePointer( hFile, bfh.bfOffBits, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
        {
            CloseHandle( hFile );
            free( pDIB );
            MessageBox( NULL, TEXT("Error reading file"), szFileName, MB_OK );
            return NULL;
        }
    }
    // Read the image bits
    if( (!ReadFile( hFile, FindDIBBits(pDIB), dwBitsSize, &dwBytes, NULL )) || (dwBytes!=dwBitsSize) )
    {
        CloseHandle( hFile );
        free( pDIB );
        MessageBox( NULL, TEXT("Error reading file"), szFileName, MB_OK );
        return NULL;
    }
    // clean up
    CloseHandle( hFile );
    return pDIB;
}
/* End ReadBMPFile() ********************************************************/


/****************************************************************************
*
*     FUNCTION: WriteBMPFile
*
*     PURPOSE:  Writes a BMP file from CF_DIB format
*
*     PARAMS:   PCTSTR szFileName - the name of the file to read
*               PBYTE - pointer to the CF_DIB, NULL for failure
*
*     RETURNS:  BOOL - TRUE for success, FALSE for Failure
*
* History:
*                July '95 - Created
*
\****************************************************************************/
BOOL WriteBMPFile( 
    PCTSTR szFileName, 
    PBYTE pDIB )
{
    HANDLE            	hFile           = NULL;
    BITMAPFILEHEADER    bfh             = {0};
    DWORD            	dwBytes;
    DWORD               dwBytesToWrite;
    PBITMAPINFOHEADER	pbmih           = NULL;

    // Open the file
    if( (hFile=CreateFile( szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE )
    {
        MessageBox( NULL, TEXT("Error opening file"), szFileName, MB_OK );
        return FALSE;
    }
    bfh.bfType = 0x4d42;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + PaletteSize( pDIB );
    bfh.bfSize = (bfh.bfOffBits + ((PBITMAPINFOHEADER)pDIB)->biHeight * BytesPerLine((PBITMAPINFOHEADER)pDIB))/4;
    // Write the header
    if( ( ! WriteFile( hFile, &bfh, sizeof(BITMAPFILEHEADER), &dwBytes, NULL ) ) || ( dwBytes != sizeof( BITMAPFILEHEADER ) ) )
    {
        CloseHandle( hFile );
        MessageBox( NULL, TEXT("Error Writing file"), szFileName, MB_OK );
        return FALSE;
    }
    pbmih = (PBITMAPINFOHEADER)pDIB;
    pbmih->biHeight /= 2;
    dwBytesToWrite = bfh.bfOffBits + (pbmih->biHeight * BytesPerLine(pbmih));
    if( ( ! WriteFile( hFile, pDIB, dwBytesToWrite, &dwBytes, NULL ) ) || ( dwBytes != dwBytesToWrite ) )
    {
        CloseHandle( hFile );
        MessageBox( NULL, TEXT("Error Writing file"), szFileName, MB_OK );
        return FALSE;
    }
    pbmih->biHeight *= 2;
    CloseHandle( hFile );
    return TRUE;
}
/* End WriteBMPFile() *******************************************************/

