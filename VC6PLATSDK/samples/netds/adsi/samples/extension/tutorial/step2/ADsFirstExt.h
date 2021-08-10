/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 29 12:54:31 2002
 */
/* Compiler settings for C:\sdk\sdkpublic\samples\netds\adsi\samples\Extension\tutorial\Step2\ADsFirstExt.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ADsFirstExt_h__
#define __ADsFirstExt_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IHelloWorld_FWD_DEFINED__
#define __IHelloWorld_FWD_DEFINED__
typedef interface IHelloWorld IHelloWorld;
#endif 	/* __IHelloWorld_FWD_DEFINED__ */


#ifndef __HelloWorld_FWD_DEFINED__
#define __HelloWorld_FWD_DEFINED__

#ifdef __cplusplus
typedef class HelloWorld HelloWorld;
#else
typedef struct HelloWorld HelloWorld;
#endif /* __cplusplus */

#endif 	/* __HelloWorld_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IHelloWorld_INTERFACE_DEFINED__
#define __IHelloWorld_INTERFACE_DEFINED__

/* interface IHelloWorld */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHelloWorld;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E1E3EDF7-48D1-11D2-B22B-0000F87A6B50")
    IHelloWorld : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Say( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHelloWorldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHelloWorld __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHelloWorld __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHelloWorld __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHelloWorld __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHelloWorld __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHelloWorld __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHelloWorld __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Say )( 
            IHelloWorld __RPC_FAR * This);
        
        END_INTERFACE
    } IHelloWorldVtbl;

    interface IHelloWorld
    {
        CONST_VTBL struct IHelloWorldVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHelloWorld_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHelloWorld_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHelloWorld_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHelloWorld_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHelloWorld_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHelloWorld_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHelloWorld_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IHelloWorld_Say(This)	\
    (This)->lpVtbl -> Say(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHelloWorld_Say_Proxy( 
    IHelloWorld __RPC_FAR * This);


void __RPC_STUB IHelloWorld_Say_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHelloWorld_INTERFACE_DEFINED__ */



#ifndef __ADSFIRSTEXTLib_LIBRARY_DEFINED__
#define __ADSFIRSTEXTLib_LIBRARY_DEFINED__

/* library ADSFIRSTEXTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ADSFIRSTEXTLib;

EXTERN_C const CLSID CLSID_HelloWorld;

#ifdef __cplusplus

class DECLSPEC_UUID("E1E3EDF8-48D1-11D2-B22B-0000F87A6B50")
HelloWorld;
#endif
#endif /* __ADSFIRSTEXTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
