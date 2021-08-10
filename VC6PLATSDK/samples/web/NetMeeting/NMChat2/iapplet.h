/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 18 16:14:45 2002
 */
/* Compiler settings for ..\..\include\iapplet.idl:
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

#ifndef __iapplet_h__
#define __iapplet_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAppletSessionNotify_FWD_DEFINED__
#define __IAppletSessionNotify_FWD_DEFINED__
typedef interface IAppletSessionNotify IAppletSessionNotify;
#endif 	/* __IAppletSessionNotify_FWD_DEFINED__ */


#ifndef __IAppletSession_FWD_DEFINED__
#define __IAppletSession_FWD_DEFINED__
typedef interface IAppletSession IAppletSession;
#endif 	/* __IAppletSession_FWD_DEFINED__ */


#ifndef __IAppletNotify_FWD_DEFINED__
#define __IAppletNotify_FWD_DEFINED__
typedef interface IAppletNotify IAppletNotify;
#endif 	/* __IAppletNotify_FWD_DEFINED__ */


#ifndef __IApplet_FWD_DEFINED__
#define __IApplet_FWD_DEFINED__
typedef interface IApplet IApplet;
#endif 	/* __IApplet_FWD_DEFINED__ */


#ifndef __NmApplet_FWD_DEFINED__
#define __NmApplet_FWD_DEFINED__

#ifdef __cplusplus
typedef class NmApplet NmApplet;
#else
typedef struct NmApplet NmApplet;
#endif /* __cplusplus */

#endif 	/* __NmApplet_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_iapplet_0000 */
/* [local] */ 

typedef USHORT AppletSessionID;

typedef USHORT AppletChannelID;

typedef AppletChannelID AppletUserID;

typedef AppletUserID AppletNodeID;

typedef USHORT AppletTokenID;

typedef USHORT AppletEntityID;

typedef ULONG AppletConfID;

typedef UINT AppletRequestTag;

typedef 
enum tagAppletRegistryCommand
    {	APPLET_REGISTER_CHANNEL	= 0,
	APPLET_ASSIGN_TOKEN	= 1,
	APPLET_SET_PARAMETER	= 2,
	APPLET_RETRIEVE_ENTRY	= 3,
	APPLET_DELETE_ENTRY	= 4,
	APPLET_ALLOCATE_HANDLE	= 5,
	APPLET_MONITOR	= 6
    }	AppletRegistryCommand;

typedef 
enum tagAppletRegistryItemType
    {	APPLET_REGISTRY_CHANNEL_ID	= 1,
	APPLET_REGISTRY_TOKEN_ID	= 2,
	APPLET_REGISTRY_PARAMETER	= 3,
	APPLET_REGISTRY_NONE	= 4
    }	AppletRegistryItemType;

typedef 
enum tagAppletModificationRights
    {	APPLET_OWNER_RIGHTS	= 0,
	APPLET_SESSION_RIGHTS	= 1,
	APPLET_PUBLIC_RIGHTS	= 2,
	APPLET_NO_MODIFICATION_RIGHTS_SPECIFIED	= 3
    }	AppletModificationRights;

typedef 
enum tagAppletChannelCommand
    {	APPLET_JOIN_CHANNEL	= 0,
	APPLET_LEAVE_CHANNEL	= 1,
	APPLET_CONVENE_CHANNEL	= 2,
	APPLET_DISBAND_CHANNEL	= 3,
	APPLET_ADMIT_CHANNEL	= 4,
	APPLET_EXPEL_CHANNEL	= 5
    }	AppletChannelCommand;

typedef 
enum tagAppletChannelType
    {	APPLET_STATIC_CHANNEL	= 0,
	APPLET_DYNAMIC_MULTICAST_CHANNEL	= 1,
	APPLET_DYNAMIC_PRIVATE_CHANNEL	= 2,
	APPLET_DYNAMIC_USER_ID_CHANNEL	= 3,
	APPLET_NO_CHANNEL_TYPE_SPECIFIED	= 4
    }	AppletChannelType;

typedef 
enum tagAppletTokenCommand
    {	APPLET_GRAB_TOKEN	= 0,
	APPLET_INHIBIT_TOKEN	= 1,
	APPLET_GIVE_TOKEN	= 2,
	APPLET_PLEASE_TOKEN	= 3,
	APPLET_RELEASE_TOKEN	= 4,
	APPLET_TEST_TOKEN	= 5,
	APPLET_GIVE_TOKEN_RESPONSE	= 6
    }	AppletTokenCommand;

typedef 
enum tagAppletTokenStatus
    {	APPLET_TOKEN_NOT_IN_USE	= 0,
	APPLET_TOKEN_SELF_GRABBED	= 1,
	APPLET_TOKEN_OTHER_GRABBED	= 2,
	APPLET_TOKEN_SELF_INHIBITED	= 3,
	APPLET_TOKEN_OTHER_INHIBITED	= 4,
	APPLET_TOKEN_SELF_RECIPIENT	= 5,
	APPLET_TOKEN_SELF_GIVING	= 6,
	APPLET_TOKEN_OTHER_GIVING	= 7
    }	AppletTokenStatus;

typedef 
enum tagAppletCapabilityType
    {	APPLET_UNKNOWN_CAP_TYPE	= 0,
	APPLET_LOGICAL_CAPABILITY	= 1,
	APPLET_UNSIGNED_MINIMUM_CAPABILITY	= 2,
	APPLET_UNSIGNED_MAXIMUM_CAPABILITY	= 3
    }	AppletCapabilityType;

typedef struct  tagAppletCapabilityClass
    {
    AppletCapabilityType eType;
    ULONG nMinOrMax;
    }	AppletCapabilityClass;

typedef 
enum tagAppletCapIDType
    {	APPLET_STANDARD_CAPABILITY	= 0,
	APPLET_NONSTD_CAPABILITY	= 1
    }	AppletCapIDType;

typedef 
enum tagAppletResourceAllocCommand
    {	APPLET_JOIN_DYNAMIC_CHANNEL	= 0,
	APPLET_GRAB_TOKEN_REQUEST	= 1
    }	AppletResourceAllocCommand;

typedef 
enum tagAppletPriority
    {	APPLET_TOP_PRIORITY	= 0,
	APPLET_HIGH_PRIORITY	= 1,
	APPLET_MEDIUM_PRIORITY	= 2,
	APPLET_LOW_PRIORITY	= 3
    }	AppletPriority;

typedef 
enum tagAppletKeyType
    {	APPLET_OBJECT_KEY	= 1,
	APPLET_H221_NONSTD_KEY	= 2
    }	AppletKeyType;


enum tagAppletErrorCode
    {	APPLET_E_NO_SERVICE	= 0x82000001,
	APPLET_E_SERVICE_FAIL	= 0x82000002,
	APPLET_E_ALREADY_REGISTERED	= 0x82000003,
	APPLET_E_NOT_REGISTERED	= 0x82000004,
	APPLET_E_INVALID_CONFERENCE	= 0x82000005,
	APPLET_E_INVALID_COOKIE	= 0x82000006,
	APPLET_E_ALREADY_JOIN	= 0x82000007,
	APPLET_E_NOT_JOINED	= 0x82000008,
	APPLET_E_INVALID_JOIN_REQUEST	= 0x82000009,
	APPLET_E_ENTRY_ALREADY_EXISTS	= 0x8200000a,
	APPLET_E_ENTRY_DOES_NOT_EXIST	= 0x8200000b,
	APPLET_E_NOT_OWNER	= 0x8200000c,
	APPLET_E_NOT_ADVISED	= 0x8200000d,
	APPLET_E_ALREADY_ADVISED	= 0x8200000e
    };
typedef 
enum tagAppletReason
    {	APPLET_R_UNSPECIFIED	= 0,
	APPLET_R_CONFERENCE_GONE	= 1,
	APPLET_R_USER_REJECTED	= 2,
	APPLET_R_RESOURCE_PURGED	= 3
    }	AppletReason;

typedef struct  tagAppletOctetString
    {
    ULONG cbStrSize;
    /* [size_is] */ BYTE __RPC_FAR *pbValue;
    }	AppletOctetString;

typedef struct  tagAppletLongString
    {
    ULONG nStrLen;
    /* [size_is] */ ULONG __RPC_FAR *pnValue;
    }	AppletLongString;

typedef struct  tagAppletObjectKey
    {
    AppletKeyType eType;
    AppletLongString lstrObjectID;
    AppletOctetString ostrH221NonStdID;
    }	AppletObjectKey;

typedef struct  tagAppletSessionKey
    {
    AppletObjectKey AppletProtocolKey;
    AppletSessionID nSessionID;
    }	AppletSessionKey;

typedef struct  tagAppletRegistryKey
    {
    AppletSessionKey SessionKey;
    AppletOctetString ostrResourceID;
    }	AppletRegistryKey;

typedef struct  tagAppletRegistryRequest
    {
    AppletRegistryCommand eCommand;
    AppletRegistryKey RegistryKey;
    AppletChannelID nChannelID;
    AppletOctetString ostrParamValue;
    AppletModificationRights eParamModifyRights;
    ULONG cHandles;
    }	AppletRegistryRequest;

typedef struct  tagAppletChannelRequest
    {
    AppletChannelCommand eCommand;
    AppletChannelID nChannelID;
    ULONG cUsers;
    /* [size_is] */ AppletUserID __RPC_FAR *aUsers;
    }	AppletChannelRequest;

typedef struct  tagAppletTokenRequest
    {
    AppletTokenCommand eCommand;
    AppletTokenID nTokenID;
    AppletUserID uidGiveTo;
    HRESULT hrGiveResponse;
    }	AppletTokenRequest;

typedef struct  tagAppletCapabilityID
    {
    AppletCapIDType eType;
    AppletObjectKey nNonStdCap;
    ULONG nStdCap;
    }	AppletCapabilityID;

typedef struct  tagAppletCapability
    {
    AppletCapabilityID CapID;
    AppletCapabilityClass CapClass;
    ULONG cEntities;
    }	AppletCapability;

typedef struct  tagAppletCapability2
    {
    AppletCapabilityID CapID;
    AppletOctetString __RPC_FAR *pCapData;
    }	AppletCapability2;

typedef struct  tagAppletProtocolEntity
    {
    AppletSessionKey SessionKey;
    AppletChannelType eStartupChannelType;
    BOOL fMustBeInvoked;
    ULONG cExpectedCapabilities;
    /* [size_is] */ AppletCapability __RPC_FAR *__RPC_FAR *apExpectedCapabilities;
    }	AppletProtocolEntity;

typedef struct  tagAppletRecord
    {
    AppletNodeID nNodeID;
    AppletEntityID nEntityID;
    BOOL fEnrolledActively;
    BOOL fConductingCapable;
    AppletChannelType eStartupChannelType;
    AppletUserID nAppletUserID;
    ULONG cCapabilities;
    /* [size_is] */ AppletCapability2 __RPC_FAR *__RPC_FAR *apCapabilities;
    }	AppletRecord;

typedef struct  tagAppletRoster
    {
    AppletSessionKey SessionKey;
    BOOL fRosterChanged;
    ULONG nInstanceNumber;
    BOOL fNodesAdded;
    BOOL fNodesRemoved;
    BOOL fCapabilitiesChanged;
    ULONG cRecords;
    /* [size_is] */ AppletRecord __RPC_FAR *__RPC_FAR *apAppletRecords;
    ULONG cCapabilities;
    /* [size_is] */ AppletCapability __RPC_FAR *__RPC_FAR *apCapabilities;
    }	AppletRoster;

typedef struct  tagAppletRegistryItem
    {
    AppletRegistryItemType ItemType;
    AppletChannelID nChannelID;
    AppletTokenID nTokenID;
    AppletOctetString ostrParamValue;
    }	AppletRegistryItem;

typedef struct  tagAppletRegistryEntryOwner
    {
    BOOL fEntryOwned;
    AppletNodeID nOwnerNodeID;
    AppletEntityID nOwnerEntityID;
    }	AppletRegistryEntryOwner;

typedef struct  tagAppletSessionRequest
    {
    AppletSessionKey SessionKey;
    AppletChannelType nStartupChannelType;
    ULONG cCollapsedCaps;
    /* [size_is] */ AppletCapability __RPC_FAR *__RPC_FAR *apCollapsedCaps;
    ULONG cNonCollapsedCaps;
    /* [size_is] */ AppletCapability2 __RPC_FAR *__RPC_FAR *apNonCollapsedCaps;
    ULONG cStaticChannels;
    /* [size_is] */ AppletChannelID __RPC_FAR *aStaticChannels;
    ULONG cDynamicChannels;
    /* [size_is] */ AppletRegistryKey __RPC_FAR *aChannelRegistryKeys;
    }	AppletSessionRequest;



extern RPC_IF_HANDLE __MIDL_itf_iapplet_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_iapplet_0000_v0_0_s_ifspec;

#ifndef __IAppletSessionNotify_INTERFACE_DEFINED__
#define __IAppletSessionNotify_INTERFACE_DEFINED__

/* interface IAppletSessionNotify */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAppletSessionNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("f7c10ec0-a4d9-11d2-b724-00104bc51339")
    IAppletSessionNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE JoinSessionConfirm( 
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletUserID uidMyself,
            /* [in] */ AppletNodeID nidMyself,
            /* [in] */ AppletSessionID sidMyself,
            /* [in] */ AppletEntityID eidMyself,
            /* [in] */ ULONG cDynamicChannels,
            /* [size_is][in] */ AppletChannelID __RPC_FAR aDynamicChannels[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LeaveSessionIndication( 
            /* [in] */ AppletReason eReason,
            /* [in] */ AppletUserID uidLeave) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendDataIndication( 
            /* [in] */ BOOL fUniformSend,
            /* [in] */ AppletUserID uidInitiator,
            /* [in] */ AppletChannelID nChannelID,
            /* [in] */ AppletPriority eDataPriority,
            /* [in] */ AppletOctetString Data) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RosterReportIndication( 
            /* [in] */ ULONG cRosters,
            /* [size_is][in] */ AppletRoster __RPC_FAR *__RPC_FAR *apAppRosters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InquireRosterConfirm( 
            /* [in] */ HRESULT hrResult,
            /* [in] */ ULONG cRosters,
            /* [size_is][in] */ AppletRoster __RPC_FAR *__RPC_FAR *apAppRosters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvokeAppletConfirm( 
            /* [in] */ AppletRequestTag nReqTag,
            /* [in] */ HRESULT hrResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegistryConfirm( 
            /* [in] */ AppletRegistryCommand eCommand,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletRegistryKey __RPC_FAR *pRegistryKey,
            /* [in] */ AppletRegistryItem __RPC_FAR *pRegistryItem,
            /* [in] */ AppletRegistryEntryOwner __RPC_FAR *pEntryOwner,
            /* [in] */ AppletModificationRights eRights) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocateHandleConfirm( 
            /* [in] */ HRESULT hrResult,
            /* [in] */ ULONG nFirstHandle,
            /* [in] */ ULONG cHandles) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChannelConfirm( 
            /* [in] */ AppletChannelCommand eCommand,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletChannelID nChannelID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChannelIndication( 
            /* [in] */ AppletChannelCommand eCommand,
            /* [in] */ AppletChannelID nChannelID,
            /* [in] */ AppletReason eReason,
            /* [in] */ AppletUserID uidManager) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TokenConfirm( 
            /* [in] */ AppletTokenCommand eCommand,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletTokenID nTokenID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TestTokenConfirm( 
            /* [in] */ AppletTokenID nTokenID,
            /* [in] */ AppletTokenStatus eStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TokenIndication( 
            /* [in] */ AppletTokenCommand eCommand,
            /* [in] */ AppletReason eReason,
            /* [in] */ AppletTokenID nTokenID,
            /* [in] */ AppletUserID uidInitiator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAppletSessionNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAppletSessionNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAppletSessionNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinSessionConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletUserID uidMyself,
            /* [in] */ AppletNodeID nidMyself,
            /* [in] */ AppletSessionID sidMyself,
            /* [in] */ AppletEntityID eidMyself,
            /* [in] */ ULONG cDynamicChannels,
            /* [size_is][in] */ AppletChannelID __RPC_FAR aDynamicChannels[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LeaveSessionIndication )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletReason eReason,
            /* [in] */ AppletUserID uidLeave);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDataIndication )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ BOOL fUniformSend,
            /* [in] */ AppletUserID uidInitiator,
            /* [in] */ AppletChannelID nChannelID,
            /* [in] */ AppletPriority eDataPriority,
            /* [in] */ AppletOctetString Data);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RosterReportIndication )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ ULONG cRosters,
            /* [size_is][in] */ AppletRoster __RPC_FAR *__RPC_FAR *apAppRosters);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InquireRosterConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ HRESULT hrResult,
            /* [in] */ ULONG cRosters,
            /* [size_is][in] */ AppletRoster __RPC_FAR *__RPC_FAR *apAppRosters);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeAppletConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletRequestTag nReqTag,
            /* [in] */ HRESULT hrResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegistryConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletRegistryCommand eCommand,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletRegistryKey __RPC_FAR *pRegistryKey,
            /* [in] */ AppletRegistryItem __RPC_FAR *pRegistryItem,
            /* [in] */ AppletRegistryEntryOwner __RPC_FAR *pEntryOwner,
            /* [in] */ AppletModificationRights eRights);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateHandleConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ HRESULT hrResult,
            /* [in] */ ULONG nFirstHandle,
            /* [in] */ ULONG cHandles);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChannelConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletChannelCommand eCommand,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletChannelID nChannelID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChannelIndication )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletChannelCommand eCommand,
            /* [in] */ AppletChannelID nChannelID,
            /* [in] */ AppletReason eReason,
            /* [in] */ AppletUserID uidManager);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TokenConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletTokenCommand eCommand,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletTokenID nTokenID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TestTokenConfirm )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletTokenID nTokenID,
            /* [in] */ AppletTokenStatus eStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TokenIndication )( 
            IAppletSessionNotify __RPC_FAR * This,
            /* [in] */ AppletTokenCommand eCommand,
            /* [in] */ AppletReason eReason,
            /* [in] */ AppletTokenID nTokenID,
            /* [in] */ AppletUserID uidInitiator);
        
        END_INTERFACE
    } IAppletSessionNotifyVtbl;

    interface IAppletSessionNotify
    {
        CONST_VTBL struct IAppletSessionNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppletSessionNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAppletSessionNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAppletSessionNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAppletSessionNotify_JoinSessionConfirm(This,hrResult,uidMyself,nidMyself,sidMyself,eidMyself,cDynamicChannels,aDynamicChannels)	\
    (This)->lpVtbl -> JoinSessionConfirm(This,hrResult,uidMyself,nidMyself,sidMyself,eidMyself,cDynamicChannels,aDynamicChannels)

#define IAppletSessionNotify_LeaveSessionIndication(This,eReason,uidLeave)	\
    (This)->lpVtbl -> LeaveSessionIndication(This,eReason,uidLeave)

#define IAppletSessionNotify_SendDataIndication(This,fUniformSend,uidInitiator,nChannelID,eDataPriority,Data)	\
    (This)->lpVtbl -> SendDataIndication(This,fUniformSend,uidInitiator,nChannelID,eDataPriority,Data)

#define IAppletSessionNotify_RosterReportIndication(This,cRosters,apAppRosters)	\
    (This)->lpVtbl -> RosterReportIndication(This,cRosters,apAppRosters)

#define IAppletSessionNotify_InquireRosterConfirm(This,hrResult,cRosters,apAppRosters)	\
    (This)->lpVtbl -> InquireRosterConfirm(This,hrResult,cRosters,apAppRosters)

#define IAppletSessionNotify_InvokeAppletConfirm(This,nReqTag,hrResult)	\
    (This)->lpVtbl -> InvokeAppletConfirm(This,nReqTag,hrResult)

#define IAppletSessionNotify_RegistryConfirm(This,eCommand,hrResult,pRegistryKey,pRegistryItem,pEntryOwner,eRights)	\
    (This)->lpVtbl -> RegistryConfirm(This,eCommand,hrResult,pRegistryKey,pRegistryItem,pEntryOwner,eRights)

#define IAppletSessionNotify_AllocateHandleConfirm(This,hrResult,nFirstHandle,cHandles)	\
    (This)->lpVtbl -> AllocateHandleConfirm(This,hrResult,nFirstHandle,cHandles)

#define IAppletSessionNotify_ChannelConfirm(This,eCommand,hrResult,nChannelID)	\
    (This)->lpVtbl -> ChannelConfirm(This,eCommand,hrResult,nChannelID)

#define IAppletSessionNotify_ChannelIndication(This,eCommand,nChannelID,eReason,uidManager)	\
    (This)->lpVtbl -> ChannelIndication(This,eCommand,nChannelID,eReason,uidManager)

#define IAppletSessionNotify_TokenConfirm(This,eCommand,hrResult,nTokenID)	\
    (This)->lpVtbl -> TokenConfirm(This,eCommand,hrResult,nTokenID)

#define IAppletSessionNotify_TestTokenConfirm(This,nTokenID,eStatus)	\
    (This)->lpVtbl -> TestTokenConfirm(This,nTokenID,eStatus)

#define IAppletSessionNotify_TokenIndication(This,eCommand,eReason,nTokenID,uidInitiator)	\
    (This)->lpVtbl -> TokenIndication(This,eCommand,eReason,nTokenID,uidInitiator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAppletSessionNotify_JoinSessionConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ HRESULT hrResult,
    /* [in] */ AppletUserID uidMyself,
    /* [in] */ AppletNodeID nidMyself,
    /* [in] */ AppletSessionID sidMyself,
    /* [in] */ AppletEntityID eidMyself,
    /* [in] */ ULONG cDynamicChannels,
    /* [size_is][in] */ AppletChannelID __RPC_FAR aDynamicChannels[  ]);


void __RPC_STUB IAppletSessionNotify_JoinSessionConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_LeaveSessionIndication_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletReason eReason,
    /* [in] */ AppletUserID uidLeave);


void __RPC_STUB IAppletSessionNotify_LeaveSessionIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_SendDataIndication_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ BOOL fUniformSend,
    /* [in] */ AppletUserID uidInitiator,
    /* [in] */ AppletChannelID nChannelID,
    /* [in] */ AppletPriority eDataPriority,
    /* [in] */ AppletOctetString Data);


void __RPC_STUB IAppletSessionNotify_SendDataIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_RosterReportIndication_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ ULONG cRosters,
    /* [size_is][in] */ AppletRoster __RPC_FAR *__RPC_FAR *apAppRosters);


void __RPC_STUB IAppletSessionNotify_RosterReportIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_InquireRosterConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ HRESULT hrResult,
    /* [in] */ ULONG cRosters,
    /* [size_is][in] */ AppletRoster __RPC_FAR *__RPC_FAR *apAppRosters);


void __RPC_STUB IAppletSessionNotify_InquireRosterConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_InvokeAppletConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletRequestTag nReqTag,
    /* [in] */ HRESULT hrResult);


void __RPC_STUB IAppletSessionNotify_InvokeAppletConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_RegistryConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletRegistryCommand eCommand,
    /* [in] */ HRESULT hrResult,
    /* [in] */ AppletRegistryKey __RPC_FAR *pRegistryKey,
    /* [in] */ AppletRegistryItem __RPC_FAR *pRegistryItem,
    /* [in] */ AppletRegistryEntryOwner __RPC_FAR *pEntryOwner,
    /* [in] */ AppletModificationRights eRights);


void __RPC_STUB IAppletSessionNotify_RegistryConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_AllocateHandleConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ HRESULT hrResult,
    /* [in] */ ULONG nFirstHandle,
    /* [in] */ ULONG cHandles);


void __RPC_STUB IAppletSessionNotify_AllocateHandleConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_ChannelConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletChannelCommand eCommand,
    /* [in] */ HRESULT hrResult,
    /* [in] */ AppletChannelID nChannelID);


void __RPC_STUB IAppletSessionNotify_ChannelConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_ChannelIndication_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletChannelCommand eCommand,
    /* [in] */ AppletChannelID nChannelID,
    /* [in] */ AppletReason eReason,
    /* [in] */ AppletUserID uidManager);


void __RPC_STUB IAppletSessionNotify_ChannelIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_TokenConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletTokenCommand eCommand,
    /* [in] */ HRESULT hrResult,
    /* [in] */ AppletTokenID nTokenID);


void __RPC_STUB IAppletSessionNotify_TokenConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_TestTokenConfirm_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletTokenID nTokenID,
    /* [in] */ AppletTokenStatus eStatus);


void __RPC_STUB IAppletSessionNotify_TestTokenConfirm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSessionNotify_TokenIndication_Proxy( 
    IAppletSessionNotify __RPC_FAR * This,
    /* [in] */ AppletTokenCommand eCommand,
    /* [in] */ AppletReason eReason,
    /* [in] */ AppletTokenID nTokenID,
    /* [in] */ AppletUserID uidInitiator);


void __RPC_STUB IAppletSessionNotify_TokenIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAppletSessionNotify_INTERFACE_DEFINED__ */


#ifndef __IAppletSession_INTERFACE_DEFINED__
#define __IAppletSession_INTERFACE_DEFINED__

/* interface IAppletSession */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAppletSession;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e65dc590-a4d9-11d2-b724-00104bc51339")
    IAppletSession : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetConfID( 
            /* [out] */ AppletConfID __RPC_FAR *pnConfID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsThisNodeTopProvider( 
            /* [out] */ BOOL __RPC_FAR *pfTopProvider) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Join( 
            /* [in] */ AppletSessionRequest __RPC_FAR *pRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Leave( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendData( 
            /* [in] */ BOOL fUniformSend,
            /* [in] */ AppletChannelID nChannelID,
            /* [in] */ AppletPriority ePriority,
            /* [in] */ ULONG cbBufSize,
            /* [size_is][in] */ BYTE __RPC_FAR *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvokeApplet( 
            /* [out] */ AppletRequestTag __RPC_FAR *pnReqTag,
            /* [in] */ AppletProtocolEntity __RPC_FAR *pAPE,
            /* [in] */ ULONG cNodes,
            /* [size_is][in] */ AppletNodeID __RPC_FAR aNodeIDs[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InquireRoster( 
            /* [in] */ AppletSessionKey __RPC_FAR *pSessionKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegistryRequest( 
            /* [in] */ AppletRegistryRequest __RPC_FAR *pRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChannelRequest( 
            /* [in] */ AppletChannelRequest __RPC_FAR *pRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TokenRequest( 
            /* [in] */ AppletTokenRequest __RPC_FAR *pRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IAppletSessionNotify __RPC_FAR *pNotify,
            /* [out] */ DWORD __RPC_FAR *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnAdvise( 
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAppletSessionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAppletSession __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAppletSession __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfID )( 
            IAppletSession __RPC_FAR * This,
            /* [out] */ AppletConfID __RPC_FAR *pnConfID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsThisNodeTopProvider )( 
            IAppletSession __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pfTopProvider);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Join )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ AppletSessionRequest __RPC_FAR *pRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Leave )( 
            IAppletSession __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendData )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ BOOL fUniformSend,
            /* [in] */ AppletChannelID nChannelID,
            /* [in] */ AppletPriority ePriority,
            /* [in] */ ULONG cbBufSize,
            /* [size_is][in] */ BYTE __RPC_FAR *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeApplet )( 
            IAppletSession __RPC_FAR * This,
            /* [out] */ AppletRequestTag __RPC_FAR *pnReqTag,
            /* [in] */ AppletProtocolEntity __RPC_FAR *pAPE,
            /* [in] */ ULONG cNodes,
            /* [size_is][in] */ AppletNodeID __RPC_FAR aNodeIDs[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InquireRoster )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ AppletSessionKey __RPC_FAR *pSessionKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegistryRequest )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ AppletRegistryRequest __RPC_FAR *pRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChannelRequest )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ AppletChannelRequest __RPC_FAR *pRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TokenRequest )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ AppletTokenRequest __RPC_FAR *pRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Advise )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ IAppletSessionNotify __RPC_FAR *pNotify,
            /* [out] */ DWORD __RPC_FAR *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnAdvise )( 
            IAppletSession __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IAppletSessionVtbl;

    interface IAppletSession
    {
        CONST_VTBL struct IAppletSessionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppletSession_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAppletSession_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAppletSession_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAppletSession_GetConfID(This,pnConfID)	\
    (This)->lpVtbl -> GetConfID(This,pnConfID)

#define IAppletSession_IsThisNodeTopProvider(This,pfTopProvider)	\
    (This)->lpVtbl -> IsThisNodeTopProvider(This,pfTopProvider)

#define IAppletSession_Join(This,pRequest)	\
    (This)->lpVtbl -> Join(This,pRequest)

#define IAppletSession_Leave(This)	\
    (This)->lpVtbl -> Leave(This)

#define IAppletSession_SendData(This,fUniformSend,nChannelID,ePriority,cbBufSize,pBuffer)	\
    (This)->lpVtbl -> SendData(This,fUniformSend,nChannelID,ePriority,cbBufSize,pBuffer)

#define IAppletSession_InvokeApplet(This,pnReqTag,pAPE,cNodes,aNodeIDs)	\
    (This)->lpVtbl -> InvokeApplet(This,pnReqTag,pAPE,cNodes,aNodeIDs)

#define IAppletSession_InquireRoster(This,pSessionKey)	\
    (This)->lpVtbl -> InquireRoster(This,pSessionKey)

#define IAppletSession_RegistryRequest(This,pRequest)	\
    (This)->lpVtbl -> RegistryRequest(This,pRequest)

#define IAppletSession_ChannelRequest(This,pRequest)	\
    (This)->lpVtbl -> ChannelRequest(This,pRequest)

#define IAppletSession_TokenRequest(This,pRequest)	\
    (This)->lpVtbl -> TokenRequest(This,pRequest)

#define IAppletSession_Advise(This,pNotify,pdwCookie)	\
    (This)->lpVtbl -> Advise(This,pNotify,pdwCookie)

#define IAppletSession_UnAdvise(This,dwCookie)	\
    (This)->lpVtbl -> UnAdvise(This,dwCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAppletSession_GetConfID_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [out] */ AppletConfID __RPC_FAR *pnConfID);


void __RPC_STUB IAppletSession_GetConfID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_IsThisNodeTopProvider_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pfTopProvider);


void __RPC_STUB IAppletSession_IsThisNodeTopProvider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_Join_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ AppletSessionRequest __RPC_FAR *pRequest);


void __RPC_STUB IAppletSession_Join_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_Leave_Proxy( 
    IAppletSession __RPC_FAR * This);


void __RPC_STUB IAppletSession_Leave_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_SendData_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ BOOL fUniformSend,
    /* [in] */ AppletChannelID nChannelID,
    /* [in] */ AppletPriority ePriority,
    /* [in] */ ULONG cbBufSize,
    /* [size_is][in] */ BYTE __RPC_FAR *pBuffer);


void __RPC_STUB IAppletSession_SendData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_InvokeApplet_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [out] */ AppletRequestTag __RPC_FAR *pnReqTag,
    /* [in] */ AppletProtocolEntity __RPC_FAR *pAPE,
    /* [in] */ ULONG cNodes,
    /* [size_is][in] */ AppletNodeID __RPC_FAR aNodeIDs[  ]);


void __RPC_STUB IAppletSession_InvokeApplet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_InquireRoster_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ AppletSessionKey __RPC_FAR *pSessionKey);


void __RPC_STUB IAppletSession_InquireRoster_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_RegistryRequest_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ AppletRegistryRequest __RPC_FAR *pRequest);


void __RPC_STUB IAppletSession_RegistryRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_ChannelRequest_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ AppletChannelRequest __RPC_FAR *pRequest);


void __RPC_STUB IAppletSession_ChannelRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_TokenRequest_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ AppletTokenRequest __RPC_FAR *pRequest);


void __RPC_STUB IAppletSession_TokenRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_Advise_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ IAppletSessionNotify __RPC_FAR *pNotify,
    /* [out] */ DWORD __RPC_FAR *pdwCookie);


void __RPC_STUB IAppletSession_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletSession_UnAdvise_Proxy( 
    IAppletSession __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IAppletSession_UnAdvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAppletSession_INTERFACE_DEFINED__ */


#ifndef __IAppletNotify_INTERFACE_DEFINED__
#define __IAppletNotify_INTERFACE_DEFINED__

/* interface IAppletNotify */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IAppletNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16153670-a4da-11d2-b724-00104bc51339")
    IAppletNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE PermitToJoinSessionIndication( 
            /* [in] */ AppletConfID nConfID,
            /* [in] */ BOOL fPermissionGranted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AutoJoinSessionIndication( 
            /* [in] */ IAppletSession __RPC_FAR *pSession,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletUserID uidMyself,
            /* [in] */ AppletNodeID nidMyself,
            /* [in] */ AppletSessionID sidMyself,
            /* [in] */ AppletEntityID eidMyself,
            /* [in] */ ULONG cDynamicChannels,
            /* [size_is][in] */ AppletChannelID __RPC_FAR aDynamicChannels[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAppletNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAppletNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAppletNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAppletNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PermitToJoinSessionIndication )( 
            IAppletNotify __RPC_FAR * This,
            /* [in] */ AppletConfID nConfID,
            /* [in] */ BOOL fPermissionGranted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AutoJoinSessionIndication )( 
            IAppletNotify __RPC_FAR * This,
            /* [in] */ IAppletSession __RPC_FAR *pSession,
            /* [in] */ HRESULT hrResult,
            /* [in] */ AppletUserID uidMyself,
            /* [in] */ AppletNodeID nidMyself,
            /* [in] */ AppletSessionID sidMyself,
            /* [in] */ AppletEntityID eidMyself,
            /* [in] */ ULONG cDynamicChannels,
            /* [size_is][in] */ AppletChannelID __RPC_FAR aDynamicChannels[  ]);
        
        END_INTERFACE
    } IAppletNotifyVtbl;

    interface IAppletNotify
    {
        CONST_VTBL struct IAppletNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppletNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAppletNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAppletNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAppletNotify_PermitToJoinSessionIndication(This,nConfID,fPermissionGranted)	\
    (This)->lpVtbl -> PermitToJoinSessionIndication(This,nConfID,fPermissionGranted)

#define IAppletNotify_AutoJoinSessionIndication(This,pSession,hrResult,uidMyself,nidMyself,sidMyself,eidMyself,cDynamicChannels,aDynamicChannels)	\
    (This)->lpVtbl -> AutoJoinSessionIndication(This,pSession,hrResult,uidMyself,nidMyself,sidMyself,eidMyself,cDynamicChannels,aDynamicChannels)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAppletNotify_PermitToJoinSessionIndication_Proxy( 
    IAppletNotify __RPC_FAR * This,
    /* [in] */ AppletConfID nConfID,
    /* [in] */ BOOL fPermissionGranted);


void __RPC_STUB IAppletNotify_PermitToJoinSessionIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAppletNotify_AutoJoinSessionIndication_Proxy( 
    IAppletNotify __RPC_FAR * This,
    /* [in] */ IAppletSession __RPC_FAR *pSession,
    /* [in] */ HRESULT hrResult,
    /* [in] */ AppletUserID uidMyself,
    /* [in] */ AppletNodeID nidMyself,
    /* [in] */ AppletSessionID sidMyself,
    /* [in] */ AppletEntityID eidMyself,
    /* [in] */ ULONG cDynamicChannels,
    /* [size_is][in] */ AppletChannelID __RPC_FAR aDynamicChannels[  ]);


void __RPC_STUB IAppletNotify_AutoJoinSessionIndication_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAppletNotify_INTERFACE_DEFINED__ */


#ifndef __IApplet_INTERFACE_DEFINED__
#define __IApplet_INTERFACE_DEFINED__

/* interface IApplet */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IApplet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07970b30-a4da-11d2-b724-00104bc51339")
    IApplet : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterAutoJoin( 
            /* [in] */ AppletSessionRequest __RPC_FAR *pRequest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterAutoJoin( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSession( 
            /* [out] */ IAppletSession __RPC_FAR *__RPC_FAR *ppSession,
            /* [in] */ AppletConfID nConfID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IAppletNotify __RPC_FAR *pNotify,
            /* [out] */ DWORD __RPC_FAR *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnAdvise( 
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAppletVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IApplet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IApplet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IApplet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IApplet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterAutoJoin )( 
            IApplet __RPC_FAR * This,
            /* [in] */ AppletSessionRequest __RPC_FAR *pRequest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterAutoJoin )( 
            IApplet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSession )( 
            IApplet __RPC_FAR * This,
            /* [out] */ IAppletSession __RPC_FAR *__RPC_FAR *ppSession,
            /* [in] */ AppletConfID nConfID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Advise )( 
            IApplet __RPC_FAR * This,
            /* [in] */ IAppletNotify __RPC_FAR *pNotify,
            /* [out] */ DWORD __RPC_FAR *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnAdvise )( 
            IApplet __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IAppletVtbl;

    interface IApplet
    {
        CONST_VTBL struct IAppletVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IApplet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IApplet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IApplet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IApplet_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IApplet_RegisterAutoJoin(This,pRequest)	\
    (This)->lpVtbl -> RegisterAutoJoin(This,pRequest)

#define IApplet_UnregisterAutoJoin(This)	\
    (This)->lpVtbl -> UnregisterAutoJoin(This)

#define IApplet_CreateSession(This,ppSession,nConfID)	\
    (This)->lpVtbl -> CreateSession(This,ppSession,nConfID)

#define IApplet_Advise(This,pNotify,pdwCookie)	\
    (This)->lpVtbl -> Advise(This,pNotify,pdwCookie)

#define IApplet_UnAdvise(This,dwCookie)	\
    (This)->lpVtbl -> UnAdvise(This,dwCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IApplet_Initialize_Proxy( 
    IApplet __RPC_FAR * This);


void __RPC_STUB IApplet_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IApplet_RegisterAutoJoin_Proxy( 
    IApplet __RPC_FAR * This,
    /* [in] */ AppletSessionRequest __RPC_FAR *pRequest);


void __RPC_STUB IApplet_RegisterAutoJoin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IApplet_UnregisterAutoJoin_Proxy( 
    IApplet __RPC_FAR * This);


void __RPC_STUB IApplet_UnregisterAutoJoin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IApplet_CreateSession_Proxy( 
    IApplet __RPC_FAR * This,
    /* [out] */ IAppletSession __RPC_FAR *__RPC_FAR *ppSession,
    /* [in] */ AppletConfID nConfID);


void __RPC_STUB IApplet_CreateSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IApplet_Advise_Proxy( 
    IApplet __RPC_FAR * This,
    /* [in] */ IAppletNotify __RPC_FAR *pNotify,
    /* [out] */ DWORD __RPC_FAR *pdwCookie);


void __RPC_STUB IApplet_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IApplet_UnAdvise_Proxy( 
    IApplet __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IApplet_UnAdvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IApplet_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_iapplet_0212 */
/* [local] */ 

enum { NmApplet_Ver_Major = 1};
enum { NmApplet_Ver_Minor = 0};


extern RPC_IF_HANDLE __MIDL_itf_iapplet_0212_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_iapplet_0212_v0_0_s_ifspec;


#ifndef __NmApplet_LIBRARY_DEFINED__
#define __NmApplet_LIBRARY_DEFINED__

/* library NmApplet */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_NmApplet;

EXTERN_C const CLSID CLSID_NmApplet;

#ifdef __cplusplus

class DECLSPEC_UUID("8C3ADF99-CCFE-11d2-AD10-00C04F72DD47")
NmApplet;
#endif
#endif /* __NmApplet_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
