/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Apr 12 22:33:43 2002
 */
/* Compiler settings for C:\UPnPSample\SDKDimmer\DimmerDevice\StepByStep\Step3\MyDevice.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __MyDevice_h__
#define __MyDevice_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IUPnPService_DimmingService_SCPD_FWD_DEFINED__
#define __IUPnPService_DimmingService_SCPD_FWD_DEFINED__
typedef interface IUPnPService_DimmingService_SCPD IUPnPService_DimmingService_SCPD;
#endif 	/* __IUPnPService_DimmingService_SCPD_FWD_DEFINED__ */


#ifndef __Dimmer_FWD_DEFINED__
#define __Dimmer_FWD_DEFINED__

#ifdef __cplusplus
typedef class Dimmer Dimmer;
#else
typedef struct Dimmer Dimmer;
#endif /* __cplusplus */

#endif 	/* __Dimmer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __MYDEVICELib_LIBRARY_DEFINED__
#define __MYDEVICELib_LIBRARY_DEFINED__

/* library MYDEVICELib */
/* [helpstring][version][uuid] */ 

typedef /* [v1_enum] */ 
enum DIMMINGSERVICE_SCPD_DISPIDS
    {	DISPID_POWER	= 1,
	DISPID_DIMLEVEL	= DISPID_POWER + 1,
	DISPID_POWERON	= DISPID_DIMLEVEL + 1,
	DISPID_POWEROFF	= DISPID_POWERON + 1,
	DISPID_GETPOWERVALUE	= DISPID_POWEROFF + 1,
	DISPID_SETDIMLEVEL	= DISPID_GETPOWERVALUE + 1,
	DISPID_GETDIMLEVEL	= DISPID_SETDIMLEVEL + 1,
	DISPID_GETCONFIGDETAILS	= DISPID_GETDIMLEVEL + 1
    }	DIMMINGSERVICE_SCPD_DISPIDS;


EXTERN_C const IID LIBID_MYDEVICELib;

#ifndef __IUPnPService_DimmingService_SCPD_INTERFACE_DEFINED__
#define __IUPnPService_DimmingService_SCPD_INTERFACE_DEFINED__

/* interface IUPnPService_DimmingService_SCPD */
/* [object][unique][oleautomation][uuid] */ 


EXTERN_C const IID IID_IUPnPService_DimmingService_SCPD;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a315fcbd-7f4b-4081-a172-2f534c438957")
    IUPnPService_DimmingService_SCPD : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Power( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPower) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dimLevel( 
            /* [retval][out] */ long __RPC_FAR *pdimLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PowerOn( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PowerOff( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPowerValue( 
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *ppowerVall) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDimLevel( 
            /* [in] */ long dLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDimLevel( 
            /* [out][in] */ long __RPC_FAR *pdLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConfigDetails( 
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *ppowerVal,
            /* [out][in] */ long __RPC_FAR *pdLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUPnPService_DimmingService_SCPDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Power )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPower);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dimLevel )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdimLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PowerOn )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PowerOff )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPowerValue )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *ppowerVall);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDimLevel )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [in] */ long dLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDimLevel )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [out][in] */ long __RPC_FAR *pdLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigDetails )( 
            IUPnPService_DimmingService_SCPD __RPC_FAR * This,
            /* [out][in] */ VARIANT_BOOL __RPC_FAR *ppowerVal,
            /* [out][in] */ long __RPC_FAR *pdLevel);
        
        END_INTERFACE
    } IUPnPService_DimmingService_SCPDVtbl;

    interface IUPnPService_DimmingService_SCPD
    {
        CONST_VTBL struct IUPnPService_DimmingService_SCPDVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUPnPService_DimmingService_SCPD_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUPnPService_DimmingService_SCPD_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUPnPService_DimmingService_SCPD_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUPnPService_DimmingService_SCPD_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUPnPService_DimmingService_SCPD_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUPnPService_DimmingService_SCPD_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUPnPService_DimmingService_SCPD_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUPnPService_DimmingService_SCPD_get_Power(This,pPower)	\
    (This)->lpVtbl -> get_Power(This,pPower)

#define IUPnPService_DimmingService_SCPD_get_dimLevel(This,pdimLevel)	\
    (This)->lpVtbl -> get_dimLevel(This,pdimLevel)

#define IUPnPService_DimmingService_SCPD_PowerOn(This)	\
    (This)->lpVtbl -> PowerOn(This)

#define IUPnPService_DimmingService_SCPD_PowerOff(This)	\
    (This)->lpVtbl -> PowerOff(This)

#define IUPnPService_DimmingService_SCPD_GetPowerValue(This,ppowerVall)	\
    (This)->lpVtbl -> GetPowerValue(This,ppowerVall)

#define IUPnPService_DimmingService_SCPD_SetDimLevel(This,dLevel)	\
    (This)->lpVtbl -> SetDimLevel(This,dLevel)

#define IUPnPService_DimmingService_SCPD_GetDimLevel(This,pdLevel)	\
    (This)->lpVtbl -> GetDimLevel(This,pdLevel)

#define IUPnPService_DimmingService_SCPD_GetConfigDetails(This,ppowerVal,pdLevel)	\
    (This)->lpVtbl -> GetConfigDetails(This,ppowerVal,pdLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_get_Power_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pPower);


void __RPC_STUB IUPnPService_DimmingService_SCPD_get_Power_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_get_dimLevel_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdimLevel);


void __RPC_STUB IUPnPService_DimmingService_SCPD_get_dimLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_PowerOn_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This);


void __RPC_STUB IUPnPService_DimmingService_SCPD_PowerOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_PowerOff_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This);


void __RPC_STUB IUPnPService_DimmingService_SCPD_PowerOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_GetPowerValue_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *ppowerVall);


void __RPC_STUB IUPnPService_DimmingService_SCPD_GetPowerValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_SetDimLevel_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This,
    /* [in] */ long dLevel);


void __RPC_STUB IUPnPService_DimmingService_SCPD_SetDimLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_GetDimLevel_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This,
    /* [out][in] */ long __RPC_FAR *pdLevel);


void __RPC_STUB IUPnPService_DimmingService_SCPD_GetDimLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUPnPService_DimmingService_SCPD_GetConfigDetails_Proxy( 
    IUPnPService_DimmingService_SCPD __RPC_FAR * This,
    /* [out][in] */ VARIANT_BOOL __RPC_FAR *ppowerVal,
    /* [out][in] */ long __RPC_FAR *pdLevel);


void __RPC_STUB IUPnPService_DimmingService_SCPD_GetConfigDetails_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUPnPService_DimmingService_SCPD_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Dimmer;

#ifdef __cplusplus

class DECLSPEC_UUID("d31b8f49-367e-41b7-8fc4-50e23d36625d")
Dimmer;
#endif
#endif /* __MYDEVICELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
