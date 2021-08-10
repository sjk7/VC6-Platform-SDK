/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 18 16:14:45 2002
 */
/* Compiler settings for ..\..\include\iapplet.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IAppletSessionNotify = {0xf7c10ec0,0xa4d9,0x11d2,{0xb7,0x24,0x00,0x10,0x4b,0xc5,0x13,0x39}};


const IID IID_IAppletSession = {0xe65dc590,0xa4d9,0x11d2,{0xb7,0x24,0x00,0x10,0x4b,0xc5,0x13,0x39}};


const IID IID_IAppletNotify = {0x16153670,0xa4da,0x11d2,{0xb7,0x24,0x00,0x10,0x4b,0xc5,0x13,0x39}};


const IID IID_IApplet = {0x07970b30,0xa4da,0x11d2,{0xb7,0x24,0x00,0x10,0x4b,0xc5,0x13,0x39}};


const IID LIBID_NmApplet = {0x8C3ADF96,0xCCFE,0x11d2,{0xAD,0x10,0x00,0xC0,0x4F,0x72,0xDD,0x47}};


const CLSID CLSID_NmApplet = {0x8C3ADF99,0xCCFE,0x11d2,{0xAD,0x10,0x00,0xC0,0x4F,0x72,0xDD,0x47}};


#ifdef __cplusplus
}
#endif

