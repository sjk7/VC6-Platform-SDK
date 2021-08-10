/****************************************************************************\
*			 
*     FILE:     Icons.H
*
*     PURPOSE:  IconPro Project Icon handling header file
*
*     COMMENTS: 
*               
*
*     Copyright 1995 - 2000 Microsoft Corp.
*
*
* History:
*                July '95 - Created
*
\****************************************************************************/

#include <windows.h>

/****************************************************************************/
// Structs

// These first two structs represent how the icon information is stored
// when it is bound into a EXE or DLL file. Structure members are WORD
// aligned and the last member of the structure is the ID instead of
// the imageoffset.
#pragma pack( push )
#pragma pack( 2 )
typedef struct
{
    BYTE    bWidth;               // Width of the image
    BYTE    bHeight;              // Height of the image (times 2)
    BYTE    bColorCount;          // Number of colors in image (0 if >=8bpp)
    BYTE    bReserved;            // Reserved
    WORD    wPlanes;              // Color Planes
    WORD    wBitCount;            // Bits per pixel
    DWORD   dwBytesInRes;         // how many bytes in this resource?
    WORD    nID;                  // the ID
} MEMICONDIRENTRY, *PMEMICONDIRENTRY;
typedef struct 
{
    WORD            idReserved;   // Reserved
    WORD            idType;       // resource type (1 for icons)
    WORD            idCount;      // how many images?
    MEMICONDIRENTRY	idEntries[1]; // the entries for each image
} MEMICONDIR, *PMEMICONDIR;
#pragma pack( pop )

// These next two structs represent how the icon information is stored
// in an ICO file.
typedef struct
{
    BYTE    bWidth;               // Width of the image
    BYTE    bHeight;              // Height of the image (times 2)
    BYTE    bColorCount;          // Number of colors in image (0 if >=8bpp)
    BYTE    bReserved;            // Reserved
    WORD    wPlanes;              // Color Planes
    WORD    wBitCount;            // Bits per pixel
    DWORD   dwBytesInRes;         // how many bytes in this resource?
    DWORD   dwImageOffset;        // where in the file is this image
} ICONDIRENTRY, *PICONDIRENTRY;
typedef struct 
{
    WORD            idReserved;   // Reserved
    WORD            idType;       // resource type (1 for icons)
    WORD            idCount;      // how many images?
    ICONDIRENTRY    idEntries[1]; // the entries for each image
} ICONDIR, *PICONDIR;


// The following two structs are for the use of this program in
// manipulating icons. They are more closely tied to the operation
// of this program than the structures listed above. One of the
// main differences is that they provide a pointer to the DIB
// information of the masks.
typedef struct
{
    UINT            Width, Height, Colors; // Width, Height and bpp
    PBYTE           pBits;                 // ptr to DIB bits
    DWORD           dwNumBytes;            // how many bytes?
    PBITMAPINFO     pbi;                   // ptr to header
    PBYTE           pXOR;                  // ptr to XOR image bits
    PBYTE           pAND;                  // ptr to AND image bits
} ICONIMAGE, *PICONIMAGE;
typedef struct
{
    BOOL        bHasChanged;                     // Has image changed?
    TCHAR       szOriginalICOFileName[MAX_PATH]; // Original name
    TCHAR       szOriginalDLLFileName[MAX_PATH]; // Original name
    UINT        nNumImages;                      // How many images?
    ICONIMAGE   IconImages[1];                   // Image entries
} ICONRESOURCE, *PICONRESOURCE;
/****************************************************************************/




/****************************************************************************/
// Exported function prototypes
PICONRESOURCE ReadIconFromICOFile( PCTSTR szFileName );
BOOL WriteIconToICOFile( PICONRESOURCE pIR, PCTSTR szFileName );
HICON MakeIconFromResource( PICONIMAGE pIcon );
PICONRESOURCE ReadIconFromEXEFile( PCTSTR szFileName );
BOOL IconImageToClipBoard( PICONIMAGE pii );
BOOL IconImageFromClipBoard( PICONIMAGE pii, BOOL bStretchToFit );
BOOL CreateBlankNewFormatIcon( PICONIMAGE pii );
BOOL DrawXORMask( HDC hDC, RECT Rect, PICONIMAGE pIcon );
BOOL DrawANDMask( HDC hDC, RECT Rect, PICONIMAGE pIcon );
RECT GetXORImageRect( RECT Rect, PICONIMAGE pIcon );
BOOL MakeNewANDMaskBasedOnPoint( PICONIMAGE pIcon, POINT pt );
BOOL IconImageFromBMPFile( PCTSTR szFileName, PICONIMAGE pii, BOOL bStretchToFit );
BOOL IconImageToBMPFile( PCTSTR szFileName, PICONIMAGE pii );
/****************************************************************************/
