//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       SESSION.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1999-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"
#include "nmappstr.h"

//****************************************************************************
//
// Global Varaiables
//
//****************************************************************************

//
// The Applet Session object
//
CAppletSession *g_pSession = NULL;

//
// The global invoke applet information
//
INVOKE_INFO g_InvokeInfo;


//****************************************************************************
//
// Prototypes
//
//****************************************************************************

HRESULT RegisterInvokeInfo(LPSTR pszKey);
LPTSTR PszFromBstr(BSTR bst);


//****************************************************************************
//
// CLASS CAppletSession
//
//****************************************************************************


//****************************************************************************
//
// Constructor
//
//****************************************************************************

CAppletSession::CAppletSession(CApplet *pApplet, IAppletSession *pISession)
:
    CRefCount(),
    m_pApplet(pApplet),
    m_pISession(pISession),
    m_dwCookie(0),
    m_uidMyself(0),
    m_nidMyself(0),
    m_sidMyself(0),
    m_eidMyself(0),
    m_pszMyName(NULL),
    m_nDynamicMulticastChannel(0),
    m_cMembers(0)
{
//    if(NULL == pApplet || NULL == pISession || NULL == m_pISession)
//	{
//		return E_POINTER;
//	}
		
	ASSERT(NULL != m_pISession);

    m_pApplet->AddRef();

    //
    // Build the join session data structure, which contains object key and
    // capabilities if needed.
    //
    BuildJoinSessionStructure();

    //
    // Clean the array of members. To simplify the code, we use an array to
    // hold all members, and assume that the maximum number of members
    // is MAX_MEMBERS.
    //
    ::ZeroMemory(m_apMembers, sizeof(m_apMembers));

    //
    // Get the conference ID.
    //
    HRESULT hr = m_pISession->GetConfID(&m_nConfID);
    ASSERT(S_OK == hr);

    //
    // Query to see if the local node is a top provider or not.
    //
    hr = m_pISession->IsThisNodeTopProvider(&m_fTopProvider);
    ASSERT(S_OK == hr);

    //
    // Get the INmMember pointers from the conference object.
    // We got these INmMember pointers before this session object is created.
    //
    if (NULL != g_pConferenceNotify)
    {
        //
        // Get the total number of these early-arrival members.
        //
        ULONG cIMembers = g_pConferenceNotify->GetIMemberCount();

        //
        // Get the cached array.
        //
        INmMember **apIMembers = g_pConferenceNotify->GetIMemberArray();

        //
        // Iterate through the array and retrieve applet independent
        // node information.
        //
        for (ULONG i = 0; i < cIMembers; i++)
        {
            SetMember(apIMembers[i]);
        }

        //
        // After retrieving all the node information, we release these
        // INmMember pointers and clean the array.
        //
        g_pConferenceNotify->ReleaseIMemberArray();
    }
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CAppletSession::~CAppletSession(void)
{
    delete m_pszMyName;

    ASSERT(NULL != m_pISession);
    m_pISession->Release();

    m_pApplet->Release();
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE
CAppletSession::AddRef(void)
{
    return CRefCount::AddRef();
}


ULONG STDMETHODCALLTYPE
CAppletSession::Release(void)
{
    return CRefCount::Release();
}

HRESULT STDMETHODCALLTYPE
CAppletSession::QueryInterface(REFIID riid, void * *ppvObject)
{
    if(NULL == ppvObject)
	{
		return E_POINTER;
	}
	
	HRESULT hr = NO_ERROR;

    if (riid == IID_IUnknown)
    {
        *ppvObject = (IUnknown *)this;
    }
    else if (riid == IID_IAppletSessionNotify)
    {
        *ppvObject = (IAppletSessionNotify *)this;
    }
    else
    {
        hr = E_NOINTERFACE;
        *ppvObject = NULL;
    }

    if (S_OK == hr)
    {
        AddRef();
    }

    return hr;
}


//****************************************************************************
//
// Methods for IAppletSession
//
//****************************************************************************

HRESULT CAppletSession::SendData
(
    AppletChannelID     nChannelID,
    ULONG               cbBufSize,
    BYTE               *pBuffer
)
{
    if(NULL == pBuffer)
	{
		return E_POINTER;
	}
	
	//
    // If the channel ID is zero, it means a broadcast. We then internally
    // change the channel ID to the broadcast channel.
    //
    if (0 == nChannelID)
    {
        nChannelID = m_nDynamicMulticastChannel;
    }

    //
    // Send the data now.
    //
    HRESULT hr = m_pISession->SendData(
                         FALSE,         // not uniform send
                         nChannelID,    // target channel ID
                         APPLET_MEDIUM_PRIORITY,
                         cbBufSize,
                         pBuffer);
    if (SUCCEEDED(hr))
    {
        ::UiDisplayMsg((LPTSTR) pBuffer, m_pszMyName);
    }

    return hr;
}


HRESULT CAppletSession::InvokeApplet(void)
{
    AppletRequestTag nTag = 0;

    //
    // Build the applet invoke information.
    //
    AppletProtocolEntity ape;
    ::ZeroMemory(&ape, sizeof(ape));
    ape.apExpectedCapabilities = m_JoinSessionReq.apCollapsedCaps;
    ape.cExpectedCapabilities = m_JoinSessionReq.cCollapsedCaps;
    ape.eStartupChannelType = APPLET_DYNAMIC_MULTICAST_CHANNEL;
    ape.fMustBeInvoked = TRUE;
    ape.SessionKey = m_JoinSessionReq.SessionKey;

    //
    // Invoke all. If we want to invoke a specific person, we need to
    // specify the count and the array of nodes. If invoking all, we can
    // simply put 0 and NULL.
    //
    HRESULT hr = m_pISession->InvokeApplet(&nTag, &ape, 0, NULL);
    ASSERT(S_OK == hr);

    return hr;
}


//****************************************************************************
//
// Methods from IAppletSessionNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE
CAppletSession::JoinSessionConfirm
(
    HRESULT             hrResult,
    AppletUserID        uidMyself,
    AppletNodeID        nidMyself,
    AppletSessionID     sidMyself,
    AppletEntityID      eidMyself,
    ULONG               cDynamicChannels,
    AppletChannelID     aDynamicChannels[]
)
{
    //
    // The response to the Join method.
    //
    if (S_OK == hrResult)
    {
        //
        // This applet is successfully join the conference. We should remember
        // applet specific information such as user ID, node ID, entity ID,
        // and session ID.
        //
        m_uidMyself = uidMyself;
        m_nidMyself = nidMyself;
        m_sidMyself = sidMyself;
        m_eidMyself = eidMyself;

        //
        // We also need to remember the broadcast channel.
        //
        ASSERT(1 == cDynamicChannels);
        m_nDynamicMulticastChannel = aDynamicChannels[0];

        //
        // Sanity check.
        //
        ASSERT(0 != m_uidMyself);
        ASSERT(0 != m_nidMyself);
        ASSERT(0 != m_nDynamicMulticastChannel);

        //
        // We are ready to send out text. Put in "everyone".
        //
        ::UiAddMember(NULL);
    }
    else
    {
        ASSERT(S_OK == hrResult);
    }

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::LeaveSessionIndication
(
    AppletReason        eReason,
    AppletUserID        uidLeave
)
{
    //
    // This notification indicates someone (identified by user ID uidLeave)
    // just left the conference. This "someone" can be a node or an applet.
    // In case of an applet, this applet can be of different kind or same kind.
    //
    if (uidLeave == m_uidMyself)
    {
        //
        // I am out of the conference now. So, remove "everyone".
        //
        ::UiRemoveMember(NULL);
    }
    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::SendDataIndication
(
    BOOL                fUniformSend,
    AppletUserID        uidInitiator,
    AppletChannelID     nChannelID,
    AppletPriority      eDataPriority,
    AppletOctetString   Data
)
{
    //
    // I just received data from the person "uidInitiator".
    //
    ::UiDisplayMsg((LPTSTR) Data.pbValue, GetMemberName(uidInitiator));
    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::RosterReportIndication
(
    ULONG               cRosters,
    AppletRoster      **apAppRosters
)
{
    if(NULL == apAppRosters)
	{
		return E_POINTER;
	}
	
	//
    // A roster contains information of each participating applet of the same
    // kind. The information includes applet IDs and capabilities. In this
    // sample code, we do not have capabilities. Therefore, we will only 
    // retrieve applet IDs.
    //

    //
    // Clear out the InRoster flag of the member objects.
    //
    for (ULONG i = 0; i < m_cMembers; i++)
    {
        m_apMembers[i]->ClearInRosterFlag();
    }

    //
    // Iterate through the array of rosters.
    //
    for (ULONG iRoster = 0; iRoster < cRosters; iRoster++)
    {
        AppletRoster *pRoster = apAppRosters[iRoster];

        //
        // Make sure we are in the same session. An applet of the same kind can
        // participate multiple sessions.
        //
        if (pRoster->SessionKey.nSessionID == m_sidMyself)
        {
            //
            // Iterate through the array of applet records.
            //
            for (ULONG iRecord = 0; iRecord < pRoster->cRecords ; iRecord++)
            {
                AppletRecord *pRecord = pRoster->apAppletRecords[iRecord];

                //
                // We only need to keep track of those enrolled actively.
                //
                if (pRecord->fEnrolledActively)
                {
                    //
                    // Retrieve applet IDs.
                    //
                    SetMember(pRecord);
                }
            } // for iRecord
        } // if
    } // for iRoster

    //
    // Iterate through the member array and remove those not in the rosters.
    //
    i = 0;
    while (i < m_cMembers)
    {
        //
        // It is possible that the element is created due to the member
        // notification from the conference object. In this case,
        // the corresponding entry in the roster may not arrive yet.
        // This means that we should not remove this element.
        // Therefore, we only remove those with a valid user ID.
        //
        if (! m_apMembers[i]->IsInRoster() && ! m_apMembers[i]->IsEmptyUID())
        {
            //
            // This element has a valid user ID but does not appear in
            // this roster. This means that it must be gone already.
            //
            delete m_apMembers[i];
            m_apMembers[i] = NULL;

            //
            // Move the last element to this one just deleted.
            //
            m_apMembers[i] = m_apMembers[--m_cMembers];
        }
        else
        {
            i++;
        }
    }

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::InquireRosterConfirm
(
    HRESULT             hrResult,
    ULONG               cRosters,
    AppletRoster      **apAppRosters
)
{
    //
    // This is to handle the inquire roster confirmation. In this sample code,
    // we do not issue InquireRoster; therefore, we do not need to handle
    // this notifcation.
    //

    //
    // The code dealing with this notificaiton is very similar to that of
    // CAppletSession::RosterReportIndication.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::InvokeAppletConfirm
(
    AppletRequestTag    nReqTag,
    HRESULT             hrResult
)
{
    //
    // Make sure the result is successful.
    //
    ASSERT(S_OK == hrResult);

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::RegistryConfirm
(
    AppletRegistryCommand      eCommand,
    HRESULT                    hrResult,
    AppletRegistryKey         *pRegistryKey,
    AppletRegistryItem        *pRegistryItem,
    AppletRegistryEntryOwner  *pEntryOwner,
    AppletModificationRights   eRights
)
{
    //
    // This is to handle the registry confirmation. In this sample code,
    // we do not issue RegistryRequest; therefore, we do not need to handle
    // this notifcation.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::AllocateHandleConfirm
(
    HRESULT             hrResult,
    ULONG               nFirstHandle,
    ULONG               cHandles
)
{
    //
    // This is to handle the allocate-handle confirmation. In this sample code,
    // we do not issue RegistryRequest with APPLET_ALLOCATE_HANDLE;
    // therefore, we do not need to handle this notifcation.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::ChannelConfirm
(
    AppletChannelCommand    eCommand,
    HRESULT                 hrResult,
    AppletChannelID         nChannelID
)
{
    //
    // This is to handle the channel confirmation. In this sample code,
    // we do not issue ChannelRequest; therefore, we do not need to handle
    // this notifcation.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::ChannelIndication
(
    AppletChannelCommand    eCommand,
    AppletChannelID         nChannelID,
    AppletReason            eReason,
    AppletUserID            uidManager
)
{
    //
    // This is to handle the channel indication. In this sample code,
    // we do not issue ChannelRequest; therefore, we do not need to handle
    // this notifcation.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::TokenConfirm
(
    AppletTokenCommand      eCommand,
    HRESULT                 hrResult,
    AppletTokenID           nTokenID
)
{
    //
    // This is to handle the token confirmation. In this sample code,
    // we do not issue TokenRequest; therefore, we do not need to handle
    // this notifcation.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::TestTokenConfirm
(
    AppletTokenID           nTokenID,
    AppletTokenStatus       eStatus
)
{
    //
    // This is to handle the test-token confirmation. In this sample code,
    // we do not issue TokenRequest with APPLET_TEST_TOKEN; therefore,
    // we do not need to handle this notifcation.
    //

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CAppletSession::TokenIndication
(
    AppletTokenCommand      eCommand,
    AppletReason            eReason,
    AppletTokenID           nTokenID,
    AppletUserID            uidInitiator
)
{
    //
    // This is to handle the token indication. In this sample code,
    // we do not issue TokenRequest; therefore, we do not need to handle
    // this notifcation.
    //

    return S_OK;
}


//****************************************************************************
//
// Build Join-Session Structure
//
//****************************************************************************

/*----------------------------------------------------------------------------
            Given a guid and a userid, create the appropriate application key.

            The key is formated as:
            0xB5 0x00 0x53 0x4C  - Microsoft Object Identifier
            0x03                 - guid identifier for NM 3.0 applets
            <binary guid>        - guid data
            <dword node id>      - user node id
----------------------------------------------------------------------------*/

//
// ------ IMPORTANT ------
//
// This is the constant for the SDK applications that use IApplet and
// IAppletSession. Please do not modify the binary value.
//
static const BYTE c_AppletKeyPrefix[5] = { 0xB5, 0x00, 0x53, 0x4c, 0x03 };

//
// ------ IMPORTANT ------
//
// An SDK application should use its own GUID and change the following GUID.
//
static const GUID c_SampleAppletGuid = 
    { 0xf178529, 0xed10, 0x11d2,
            { 0xad, 0x1c, 0x0, 0xc0, 0x4f, 0x72, 0xdd, 0x47 } };


//
// The global applet key structure.
//
#define MY_KEY_SIZE  (sizeof(c_AppletKeyPrefix) + sizeof(GUID) + sizeof(DWORD))
static BYTE g_AppletKey[MY_KEY_SIZE];

//
// A sample channel resource ID. This can be any binary data.
//
#define DYNAMIC_CHANNEL_RESOURCE_ID     "Sample Chat Dynamic Channel"


void BuildAppletKey(void)
{
    //
    // Build the applet key.
    //
    ::ZeroMemory(g_AppletKey, sizeof(g_AppletKey));
    ::CopyMemory(g_AppletKey, c_AppletKeyPrefix, sizeof(c_AppletKeyPrefix));
    ::CopyMemory(g_AppletKey + sizeof(c_AppletKeyPrefix),
                 &c_SampleAppletGuid, sizeof(GUID));
}


void CAppletSession::BuildJoinSessionStructure(void)
{
    //
    // Clean the structure.
    //
    ::ZeroMemory(&m_JoinSessionReq, sizeof(m_JoinSessionReq));

    //
    // We will use dynamic multicast channel which will be created during
    // IAppletSession::Join.
    //
    m_JoinSessionReq.nStartupChannelType = APPLET_DYNAMIC_MULTICAST_CHANNEL;

    //
    // Build the session key which consists of applet key and session ID.
    //
    ::BuildAppletKey();
    m_JoinSessionReq.SessionKey.AppletProtocolKey.eType =
                                        APPLET_H221_NONSTD_KEY;
    m_JoinSessionReq.SessionKey.AppletProtocolKey.ostrH221NonStdID.cbStrSize =
                                        sizeof(g_AppletKey);
    m_JoinSessionReq.SessionKey.AppletProtocolKey.ostrH221NonStdID.pbValue =
                                        g_AppletKey;
    m_JoinSessionReq.SessionKey.nSessionID = m_sidMyself;

    //
    // Build registry key for the dynamic multicast channel.
    //
    ::ZeroMemory(&m_DynChnlRegKey, sizeof(m_DynChnlRegKey));
    m_DynChnlRegKey.SessionKey = m_JoinSessionReq.SessionKey;
    m_DynChnlRegKey.ostrResourceID.cbStrSize =
                                sizeof(DYNAMIC_CHANNEL_RESOURCE_ID);
    m_DynChnlRegKey.ostrResourceID.pbValue =
                                (LPBYTE) DYNAMIC_CHANNEL_RESOURCE_ID;
    m_JoinSessionReq.aChannelRegistryKeys = &m_DynChnlRegKey;
    m_JoinSessionReq.cDynamicChannels = 1;

    //
    // Build the static channel array.
    //
    // In this sample code, we do not use static channels because this sample
    // applet is not a standard applet.
    //

    //
    // Build capabilities
    //
    // In this sample code, we do not use capabilities.
    //
}



//****************************************************************************
//
// Register Applet to be invoked in the future.
//
//****************************************************************************

HRESULT RegisterStandardAppletInvokeInfo(AppletLongString *pKey)
{
    //
    // The format of a standard t120 applet will be as follows.
    //  NM_APPLET_KEY\NM_STD_KEY\{8-hex-dot string}
    //
    char szKey[MAX_PATH + 1];
	::ZeroMemory(szKey, (MAX_PATH + 1) * sizeof(char));

	::_snprintf(szKey, MAX_PATH, "%s\\%s\\%s", NM_APPLET_KEY, NM_STD_KEY_TYPE, "{");
 
    //
    // Build the 8-digit hex dot string.
    //
    LPSTR pszKey = szKey + ::lstrlenA(szKey);
    for (ULONG i = 0; i < pKey->nStrLen; i++)
    {
        ::_snprintf(pszKey, MAX_PATH - ::lstrlenA(szKey), "%08X.", (UINT) pKey->pnValue[i]); 
        pszKey += ::lstrlenA(pszKey);
    }
	::_snprintf(pszKey - 1, 1, "}");	

    //
    // Register the applet information.
    //
    return ::RegisterInvokeInfo(szKey);
}


HRESULT RegisterNonStandardAppletInvokeInfo(void)
{
    //
    // Build the applet key.
    //
    ::BuildAppletKey();

    //
    // The format of a non-standard t120 applet is as follows.
    //  NM_APPLET_KEY\NM_NONSTD_KEY\{2-hex-dot string}
    //
    char szKey[MAX_PATH + 1];
	::ZeroMemory(szKey, (MAX_PATH + 1) * sizeof(char));

	::_snprintf(szKey, MAX_PATH, "%s\\%s\\%s", NM_APPLET_KEY, NM_NONSTD_KEY_TYPE, "{");

    //
    // Build the 2-digit hex dot string.
    //
    LPSTR pszKey = szKey + ::lstrlenA(szKey);
    ULONG cbDataSize = sizeof(g_AppletKey);
    LPBYTE pbData = g_AppletKey;
    for (ULONG i = 0; i < cbDataSize; i++, pbData++)
    {
		::_snprintf(pszKey, MAX_PATH - ::lstrlenA(szKey), "%02X.", (UINT) *pbData);     
        pszKey += ::lstrlenA(pszKey);
    }
    ::_snprintf(pszKey - 1, 1, "}");

    //
    // Register the applet information.
    //
    return ::RegisterInvokeInfo(szKey);
}




HRESULT RegisterInvokeInfo(LPSTR pszKey)
{
    if(NULL == pszKey)
	{
		return E_POINTER;
	}
	
	HKEY hKey = NULL;
    LONG lRet = 0;
    DWORD dwDisposition = 0;
    TCHAR szValue[MAX_PATH + 1];
	::ZeroMemory(szValue, (MAX_PATH + 1) * sizeof(TCHAR));

 	lRet = ::RegCreateKeyEx(
                        HKEY_LOCAL_MACHINE,
                        pszKey,
                        0,
                        NULL,
                        REG_OPTION_NON_VOLATILE,
                        KEY_SET_VALUE,
                        NULL,
                        &hKey,
                        &dwDisposition);

    ASSERT(0 == lRet);
    ASSERT(NULL != hKey);

	if(NULL == hKey)
	{
		return E_HANDLE;
	}

    szValue[0] = TEXT('\0');
    ::GetModuleFileName(g_hInstExe, szValue, MAX_PATH);
    lRet = ::RegSetValueEx(hKey,
                           NM_REGVAL_APP_PATH,
                           0,
                           REG_SZ,
                           (LPBYTE) &szValue[0],
                           (::lstrlen(szValue) + 1) * sizeof(TCHAR));
    ASSERT(0 == lRet);

    szValue[0] = TEXT('\0'); // no command line
    lRet = ::RegSetValueEx(hKey,
                           NM_REGVAL_CMD_LINE,
                           0,
                           REG_SZ,
                           (LPBYTE) &szValue[0],
                           (::lstrlen(szValue) + 1) * sizeof(TCHAR));
    ASSERT(0 == lRet);

    ::GetCurrentDirectory(MAX_PATH, szValue); // default working directory
    lRet = ::RegSetValueEx(hKey,
                           NM_REGVAL_CURR_DIR,
                           0,
                           REG_SZ,
                           (LPBYTE) &szValue[0],
                           (::lstrlen(szValue) + 1) * sizeof(TCHAR));
    ASSERT(0 == lRet);

    ::lstrcpyn((LPTSTR) &szValue[0], TEXT("Microsoft Corporation"), MAX_PATH + 1);
    lRet = ::RegSetValueEx(hKey,
                           NM_REGVAL_MANUFACTURER,
                           0,
                           REG_SZ,
                           (LPBYTE) &szValue[0],
                           (::lstrlen(szValue) + 1) * sizeof(TCHAR));
    ASSERT(0 == lRet);

    ::lstrcpyn((LPTSTR) &szValue[0], TEXT("NetMeeting SDK 3.0 Chat Sample Applet"), MAX_PATH + 1);
    lRet = ::RegSetValueEx(hKey,
                           NM_REGVAL_PRODUCT_NAME,
                           0,
                           REG_SZ,
                           (LPBYTE) &szValue[0],
                           (::lstrlen(szValue) + 1) * sizeof(TCHAR));
    ASSERT(0 == lRet);

    ::lstrcpyn((LPTSTR) &szValue[0], TEXT("SDK Sample using IApplet and IAppletSession"), MAX_PATH + 1);
    lRet = ::RegSetValueEx(hKey,
                           NM_REGVAL_DESCRIPTION,
                           0,
                           REG_SZ,
                           (LPBYTE) &szValue[0],
                           (::lstrlen(szValue) + 1) * sizeof(TCHAR));
    ASSERT(0 == lRet);


    ::RegFlushKey(hKey);
    ::RegCloseKey(hKey);
    return S_OK;
}


BOOL GetInvokeInfo(INVOKE_INFO *pInfo)
{
	TCHAR szValue[MAX_PATH + 1];
	::ZeroMemory(szValue, (MAX_PATH + 1) * sizeof(TCHAR));

    ::ZeroMemory(pInfo, sizeof(*pInfo));

    // retrieve conf ID
    if (::GetEnvironmentVariable(NM_ENV_CONF_ID, szValue, MAX_PATH))
    {
        pInfo->nConfID = ::atoi(szValue);
    }

    // retrieve the node ID of initiator
    if (::GetEnvironmentVariable(NM_ENV_NODE_ID, szValue, MAX_PATH))
    {
        pInfo->nidInitiator = ::atoi(szValue);
    }

    pInfo->fValid = pInfo->nConfID && pInfo->nidInitiator;
    return pInfo->fValid;
}


void CAppletSession::RemoveMember
(
    INmMember          *pIMember
)
{
    if(NULL == pIMember)
	{
		return;
	}
	
	ULONG nMemberID = 0;
    HRESULT hr = pIMember->GetID(&nMemberID);
    ASSERT(S_OK == hr);

    AppletNodeID nid = (AppletNodeID) nMemberID;
    if (nid != m_nidMyself)
    {
        for (ULONG i = 0; i < m_cMembers; i++)
        {
            if (m_apMembers[i]->IsSameMemberID(nid))
            {
                delete m_apMembers[i];
                m_apMembers[i] = NULL;
                m_apMembers[i] = m_apMembers[--m_cMembers];
            }
        }
    }
}


void CAppletSession::SetMember
(
    INmMember          *pIMember
)
{
    if(NULL == pIMember)
	{
		return;
	}
	
	ULONG nMemberID = 0;
    HRESULT hr = pIMember->GetID(&nMemberID);
    ASSERT(S_OK == hr);

    AppletNodeID nid = (AppletNodeID) nMemberID;
    if (nid != m_nidMyself)
    {
        CMember *pMember = NULL;
        for (ULONG i = 0; i < m_cMembers; i++)
        {
            pMember = m_apMembers[i];
            if (pMember->IsSameMemberID(nid))
            {
                if (pMember->IsEmptyMember())
                {
                    pMember->SetMember(pIMember);
                }
                return;
            }
        }

        // cound not find it, create a new entry
        ASSERT(m_cMembers < MAX_MEMBERS);
        pMember = new CMember(pIMember);
        if (NULL != pMember)
        {
            m_apMembers[m_cMembers++] = pMember;
        }
    }
}


void CAppletSession::SetMember
(
    AppletRecord       *pRecord
)
{
	if(NULL == pRecord)
	{
		return;
	}

    if (pRecord->nAppletUserID != m_uidMyself)
    {
        CMember *pMember = NULL;
        for (ULONG i = 0; i < m_cMembers; i++)
        {
            pMember = m_apMembers[i];
            if (pMember->IsSameUID(pRecord->nAppletUserID))
            {
                // this member is already in the list
                pMember->SetInRosterFlag();
                return;
            }

            if (pMember->IsSameMemberID(pRecord->nNodeID))
            {
                if (pMember->IsEmptyUID())
                {
                    pMember->SetMember(pRecord);
                    pMember->SetInRosterFlag();
                }
                return;
            }
        }

        // cound not find it, create a new entry
        ASSERT(m_cMembers < MAX_MEMBERS);
        pMember = new CMember(pRecord);
        if (NULL != pMember)
        {
            m_apMembers[m_cMembers++] = pMember;
            pMember->SetInRosterFlag();
            return;
        }
    }
}


LPTSTR CAppletSession::GetMemberName
(
    AppletUserID        uid
)
{
    CMember *pMember = NULL;
    for (ULONG i = 0; i < m_cMembers; i++)
    {
        pMember = m_apMembers[i];
        if (pMember->IsSameUID(uid))
        {
            return m_apMembers[i]->GetName();
        }
    }
    return NULL;
}



//****************************************************************************
//
// CMember 
//
//****************************************************************************


CMember::CMember(INmMember *pIMember)
{
    Initialize();
    SetMember(pIMember, TRUE);
}


CMember::CMember(AppletRecord *pRecord)
{
    Initialize();
    SetMember(pRecord, TRUE);
}


CMember::~CMember(void)
{
    ::UiRemoveMember(this);
    delete m_pszMemberName;
}


void CMember::Initialize(void)
{
    m_fInRoster = FALSE;
    m_pszMemberName = NULL;
    m_nidMember = 0;
    m_uidMember = 0;
    m_eidMember = 0;
}


void CMember::SetMember(INmMember *pIMember, BOOL fFirstTime)
{
    ASSERT(NULL != pIMember);
	if(NULL == pIMember)
	{
		return;
	}

    BSTR bstr = NULL;
    HRESULT hr = pIMember->GetName(&bstr);
    ASSERT(S_OK == hr);

    m_pszMemberName = ::PszFromBstr(bstr);
    ::SysFreeString(bstr);

    ULONG nMemberID = 0;
    hr = pIMember->GetID(&nMemberID);
    ASSERT(S_OK == hr);
    m_nidMember = (AppletNodeID) nMemberID;

    if (! fFirstTime)
    {
        ::UiAddMember(this);
    }
}


void CMember::SetMember(AppletRecord *pRecord, BOOL fFirstTime)
{
    if(NULL == pRecord)
	{
		return;
	}
	
	ASSERT(0 == m_uidMember);
    ASSERT(0 == m_eidMember);
    m_nidMember = pRecord->nNodeID;
    m_uidMember = pRecord->nAppletUserID;
    m_eidMember = pRecord->nEntityID;

    if (! fFirstTime)
    {
        ::UiAddMember(this);
    }
}





//****************************************************************************
//
// LPTSTR PszFromBstr(BSTR bstr)
//
// Converts a BSTR to a LPSTR
//
//****************************************************************************

LPTSTR PszFromBstr(BSTR bstr)
{
    LPTSTR psz = NULL;

    if (NULL != bstr)
    {
        int cch = ::WideCharToMultiByte(CP_ACP, 0, (LPWSTR)bstr, -1, NULL, 0, NULL, NULL);
        if (cch > 0)
        {
            psz = new TCHAR[cch+1];
            if (NULL != psz)
            {
				ZeroMemory(psz, sizeof(TCHAR) * (cch + 1));
                ::WideCharToMultiByte(CP_ACP, 0, (LPWSTR)bstr, -1, psz, cch, NULL, NULL);
            }
        }
    }
    return psz;
}

