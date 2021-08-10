/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 29 12:54:31 2002
 */
/* Compiler settings for C:\sdk\sdkpublic\samples\netds\adsi\samples\Extension\tutorial\Step2\ADsFirstExt.idl:
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

const IID IID_IHelloWorld = {0xE1E3EDF7,0x48D1,0x11D2,{0xB2,0x2B,0x00,0x00,0xF8,0x7A,0x6B,0x50}};


const IID LIBID_ADSFIRSTEXTLib = {0xE1E3EDEA,0x48D1,0x11D2,{0xB2,0x2B,0x00,0x00,0xF8,0x7A,0x6B,0x50}};


const CLSID CLSID_HelloWorld = {0xE1E3EDF8,0x48D1,0x11D2,{0xB2,0x2B,0x00,0x00,0xF8,0x7A,0x6B,0x50}};


#ifdef __cplusplus
}
#endif

