/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 22:33:43 2002
 */
/* Compiler settings for C:\UPnPSample\SDKDimmer\DimmerDevice\StepByStep\Step3\MyDevice.idl:
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

const IID LIBID_MYDEVICELib = {0x51AC2F4C,0x3F4F,0x48B3,{0xA0,0x18,0x91,0x0E,0x81,0x67,0x7E,0xEF}};


const IID IID_IUPnPService_DimmingService_SCPD = {0xa315fcbd,0x7f4b,0x4081,{0xa1,0x72,0x2f,0x53,0x4c,0x43,0x89,0x57}};


const CLSID CLSID_Dimmer = {0xd31b8f49,0x367e,0x41b7,{0x8f,0xc4,0x50,0xe2,0x3d,0x36,0x62,0x5d}};


#ifdef __cplusplus
}
#endif

