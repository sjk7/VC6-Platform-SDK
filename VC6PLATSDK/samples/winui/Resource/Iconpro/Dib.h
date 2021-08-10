/****************************************************************************\
*			 
*     FILE:     DIB.H
*
*     PURPOSE:  IconPro Project DIB handling header file
*
*     COMMENTS: Icons are stored in something almost identical to DIB
*               format, which makes it real easy to treat them as DIBs
*               when manipulating them.
*
*     Copyright 1995 - 2000 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/


/****************************************************************************/
// local #defines

// How wide, in bytes, would this many bits be, DWORD aligned?
#define WIDTHBYTES(bits)      ((((bits) + 31)>>5)<<2)
/****************************************************************************/


/****************************************************************************/
// Exported function prototypes
PSTR FindDIBBits ( PSTR pbi );
WORD DIBNumColors ( PSTR pbi );
WORD PaletteSize ( PSTR pbi );
DWORD BytesPerLine ( PBITMAPINFOHEADER pBMIH );
PBYTE ConvertDIBFormat ( PBITMAPINFO pSrcDIB, UINT nWidth, UINT nHeight, UINT nColors, BOOL bStretch );
VOID SetMonoDIBPixel ( PBYTE pANDBits, DWORD dwWidth, DWORD dwHeight, DWORD x, DWORD y, BOOL bWhite );
PBYTE ReadBMPFile ( PCTSTR szFileName );
BOOL WriteBMPFile ( PCTSTR szFileName, PBYTE lpDIB );
/****************************************************************************/
