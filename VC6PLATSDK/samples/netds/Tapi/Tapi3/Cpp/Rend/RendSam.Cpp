/*++

Copyright (c) 1995 - 2000 Microsoft Corporation

Module Name:

    rend.cpp

Abstract:

    This demonstrates how to use some of the APIs in TAPI 3.0 Rendezvous 
    Controls, and SDP Blob COM Interfaces to: 

    . open an ILS directory,
    . configure a conference,
    . add a conference,
    . enumerate conferences,
    . delete a conference,
    . configure a user,
    . add a user,
    . enumerate users, and
    . delete a user.

Notes:

    1. Build the program, and the exe is obj\*\rendsam.exe
    2. To run it, type "rendsam <ils>" on the command line.

Author:

    17-Aug-1997

Revision History:

    dd-mmm-yyyy <email>
    11-Feb-1999 massive update for Beta3 release

--*/

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// include                                                                   //
//                                                                           //

#include <windows.h>
#include <objbase.h>
#include <comdef.h>
#include <stdio.h>
#include <winsock.h>
#include <rend.h>
#include <sdpblb.h>
#include <strsafe.h>

const _bstr_t bstrtEMPTY = _bstr_t(L"");



///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// define                                                                    //
//                                                                           //

#define RND_MAX_STRING_FORMAT   4096
WCHAR szText[RND_MAX_STRING_FORMAT];
#define RETURN_IF_FAILED(hr)    \
    {   \
        if (FAILED(hr)) \
        {               \
            return hr;  \
        }               \
    }

#define RELEASE_COM_IF(pInterface)  \
    {   \
        if (NULL != pInterface) \
        {                       \
            pInterface->Release();\
            pInterface = NULL;  \
        }                       \
    }                   

#define START_STEP(wszStep) \
{  \
  StringCbPrintfW(szText, RND_MAX_STRING_FORMAT, L"%s ...\n", wszStep); \
  _putws(szText);  \
}

#define END_STEP(hr) \
    {   \
        if (FAILED(hr)) \
        {               \
           wprintf(L"\tFailed with error 0x%x\n", hr);\
           return hr;   \
        }               \
        else            \
        {               \
            wprintf(L"\tDone.\n");\
        }               \
    }
       

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// functions                                                                 //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


//
// SetConnectionIP
//
HRESULT
SetConnectionIP(ITDirectoryObjectConference *   pIConf,
                _bstr_t                         bstrtMediaName,
                _bstr_t                         bstrtIP
               )
/*++

Routine Description:

    Set a multicast IP address of the specified media. If no media is specified,
    the conference's default connection will be used. 

    Note: 1. For simplicity, it is assumed there is at most one ITConnection 
             for each media
          2. Will not check if the given IP address is a valid multicast IP

Arguments:

    pIConf          : the conference
    bstrtMediaName  : name of the media, in lower case, such as "audio" or 
                      "video". if it's an empty string, then the conference's 
                      default connection will be used
    bstrtIP         : the multicast IP address

Return Value:

    HRESULT

--*/
{
    //
    // check parameters
    //

    if (NULL == pIConf)
    {
        return E_POINTER;
    }
    
    if (bstrtEMPTY == bstrtIP)
    {
        return E_INVALIDARG;
    }

    BOOL    fDefault = FALSE;   // if it's the conference's default connection
    if (bstrtEMPTY == bstrtMediaName)
    {
        fDefault = TRUE;
    }

    //
    // get ITConnection interface
    //

    ITConnection *  pIConnection;
    HRESULT         hr;

    if (fDefault)
    {   // the conference's default connection
        hr = pIConf->QueryInterface(IID_ITConnection, 
                                    (void **) &pIConnection);
        RETURN_IF_FAILED(hr);
    }
    else
    {   // search for the specified media, then use its first connection

        //
        // get the media enumerator
        //

        ITSdp * pISdp;
        hr = pIConf->QueryInterface(IID_ITSdp, (void **) &pISdp);
        RETURN_IF_FAILED(hr);

        ITMediaCollection * pIMediaCollec;
        hr = pISdp->get_MediaCollection(&pIMediaCollec);
        RELEASE_COM_IF(pISdp);
        RETURN_IF_FAILED(hr);

        IEnumMedia *    pIEnumMedia;
        hr = pIMediaCollec->get_EnumerationIf(&pIEnumMedia);
        RELEASE_COM_IF(pIMediaCollec);
        RETURN_IF_FAILED(hr);

        //
        // parse each media in the collection to find the one specified
        //

        ITMedia *   pIMedia;
        while ( 1 )
        {
            hr = pIEnumMedia->Next(1, &pIMedia, NULL);

            if (FAILED(hr))
            {
                return hr;
            }
            if (S_FALSE == hr)
            {
                // reach the end of the enumerator, not finding the media
                return E_FAIL;
            }

            //
            // get MediaName then compare it with the given media
            //
            
            BSTR bstrCurrentMediaName;
            hr = pIMedia->get_MediaName(&bstrCurrentMediaName);
            RETURN_IF_FAILED(hr);
            
            BOOL fFound = bstrtMediaName == _bstr_t(bstrCurrentMediaName);
            ::SysFreeString (bstrCurrentMediaName );

            if (fFound)
            {
                break;
            }
            else
            {
                RELEASE_COM_IF(pIMedia);
            }
        }

        RELEASE_COM_IF(pIEnumMedia);

        //
        // query ITConnection interface
        //

        hr = pIMedia->QueryInterface(IID_ITConnection, 
                                     (void **) &pIConnection);
        RELEASE_COM_IF(pIMedia);
        RETURN_IF_FAILED(hr);
    }

    //
    // set the IP address
    //
    hr = pIConnection->SetAddressInfo((BSTR) bstrtIP,
                                      1,
                                      15);    
    
    RELEASE_COM_IF(pIConnection);
    
    return hr;

} // SetConnectionIP

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// OpenILS
//                                                                           
HRESULT
OpenILS(ITRendezvous *  pIRend,
        _bstr_t         bstrtILS,
        ITDirectory **  ppIDir
        )
/*++

Description:

    Connect to a specified ILS server, then Bind with currently logged on
    credentials. Since the program does not require logging into a domain,
    the Bind operation may fail, and this routine will ignore Bind error.

    An unsecured channel will be used in Connect, as "secured channel" is not
    supported as of the day this is written (NT5 Beta3)
    
Arguments:

    pIRend  : pointer to an ITRendezvous interface
    bstrtILS: ILS server name
    ppIDir  : pointer to an ITDirectory interface pointer

Return value:

    HRESULT. Bind error will be ignored.

--*/
{
    // 
    // check parameter validity
    //
    if ((NULL == pIRend) || (NULL == ppIDir))
    {
        return E_POINTER;
    }

    if (bstrtEMPTY == bstrtILS)
    {
        return E_INVALIDARG;
    }

    //
    // create an ITDirectory object
    //
    HRESULT hr = pIRend->CreateDirectory(DT_ILS, bstrtILS, ppIDir);
    RETURN_IF_FAILED(hr);

    //
    // Connect to the ILS server using an unsecured connection
    //
    hr = (*ppIDir)->Connect(VARIANT_FALSE);
    RETURN_IF_FAILED(hr);

    //
    // Bind to the ILS server with default credentials
    //
    (*ppIDir)->Bind(NULL,
                    NULL,
                    NULL,
                    RENDBIND_DEFAULTCREDENTIALS || RENDBIND_AUTHENTICATE
                   );
    
    return hr;

} // OpenILS

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// ConfigConference
//
HRESULT
ConfigConference(ITDirectoryObject *    pIObj)
/*++

Routine Description:

    Configure a conference's selected attributes:
    1. set StartTime as current, and StopTime as 1 day later
    2. set the conference's default multicast IP address
    3. set "video" media's multicast IP address. "audio" media will use the
       conference's default IP address set in the above step

Arguments:

    pIObj : ITDirectoryObject interface

Return Value:

    HRESULT

--*/
{
    if (NULL == pIObj)
    {
        return E_POINTER;
    }

    //
    // query the ITDirectoryObjectConference interface
    //

    ITDirectoryObjectConference *   pIConf;
    HRESULT hr = pIObj->QueryInterface(IID_ITDirectoryObjectConference,
                                       (void **) &pIConf
                                       );
    RETURN_IF_FAILED(hr);

    //
    // set StartTime to current local time
    //

    SYSTEMTIME  LocalSysTime;
    GetLocalTime(&LocalSysTime);

    double vTime;
    SystemTimeToVariantTime(&LocalSysTime, &vTime);

    RETURN_IF_FAILED(pIConf->put_StartTime(vTime));

    //
    // set StopTime to one day later
    //

    hr = pIConf->put_StopTime(vTime + 1);

    //
    // set the conference's default multicast IP address
    // use an arbitrary IP address for simplicity
    //

    hr = SetConnectionIP(pIConf,
                         bstrtEMPTY,
                         _bstr_t(L"224.0.0.1"));
    RETURN_IF_FAILED(hr);

    //
    // set media "video"'s multicast IP address
    // for simplicity, use an arbitrary IP address
    //
 
    hr = SetConnectionIP(pIConf,
                         _bstr_t(L"video"),
                         _bstr_t(L"224.0.0.2"));
    RETURN_IF_FAILED(hr);

    // 
    // clean-up
    //

    RELEASE_COM_IF(pIConf);

    return hr;

} // ConfigConference

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// AddConference
//
HRESULT
AddConference(ITRendezvous *   pIRend,
              ITDirectory *    pIDir,
              _bstr_t          bstrtConfName
             )
/*++

Routine Description:
    
    Add a conference to an ILS server. Use ConfigConference to set selected
    attributes of the conference.
    Existing conference with same name is deleted first to avoid "Object
    already exists" error.

Arguments:

    pIRend  : an ITRendezvous interface
    pIDir   : an ITDirectory interface
    bstrtConfName : name of the conference

Return Value:

    HRESULT

--*/
{
    //
    // verify parameter validity
    //
    if ((NULL == pIRend) || (NULL == pIDir))
    {
        return E_POINTER;
    }
    
    if (bstrtEMPTY == bstrtConfName)
    {
        return E_INVALIDARG;
    }

    ITDirectoryObject   *pIObj;
    
    //
    // create an conference object
    //
    HRESULT hr = pIRend->CreateDirectoryObject(OT_CONFERENCE,
                                               bstrtConfName,
                                               &pIObj
                                              );
    RETURN_IF_FAILED(hr);

    // to ensure a successful creating, delete it first in case a same
    // name conference already exists. since it'll fail if the conference 
    // does not exist, i don't bother checking the error code
    pIDir->DeleteDirectoryObject(pIObj);

    //
    // cofigure the conference
    //
    RETURN_IF_FAILED(ConfigConference(pIObj));

    //
    // add the conference to the ILS server
    //
    hr = pIDir->AddDirectoryObject(pIObj);

    // release the ITDirectoryObject interface
    RELEASE_COM_IF(pIObj);

    RETURN_IF_FAILED(hr);
    
    return S_OK;

} // AddConference

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// CreateUser
//
HRESULT
CreateUser(ITRendezvous *       pIRend,
           bstr_t               bstrtUserName,
           bstr_t               bstrtIPPhonePriamry,
           ITDirectoryObject ** ppIObj)
/*++

Routine Description:

    Create an ITDirectoryObject of type user with specified IPPhonePrimary.

Arguments:

    bstrtUserName       : user name
    bstrtIPPhonePriamry : IPPhonePriamry value
    ppIObj              : return the pointer to an ITDirectoryObject pointer

Return Value:

    HRESULT

--*/
{
    if ((NULL == pIRend) || (NULL == ppIObj))
    {
        return E_POINTER;
    }

    if ((bstrtEMPTY == bstrtUserName) || 
        (bstrtEMPTY == bstrtIPPhonePriamry))
    {
        return E_INVALIDARG;
    }

    //
    // create an conference object
    //
    HRESULT hr = pIRend->CreateDirectoryObject(OT_USER,
                                               bstrtUserName,
                                               ppIObj
                                              );
    RETURN_IF_FAILED(hr);

    //
    // query the ITDirectoryObjectUser interface
    //
    ITDirectoryObjectUser *   pIUser;
    hr = (*ppIObj)->QueryInterface(IID_ITDirectoryObjectUser,
                                   (void **) &pIUser
                                  );
    RETURN_IF_FAILED(hr);

    //
    // set IPPhonePriamry
    //
    hr = pIUser->put_IPPhonePrimary((BSTR) bstrtIPPhonePriamry);
    RETURN_IF_FAILED(hr);

    // release the ITDirectoryObjectUser interface
    RELEASE_COM_IF(pIUser);

    return hr;

} // CreateUser

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// ConfigUser
//
HRESULT
ConfigUser(ITDirectoryObject *  pIObj)
/*++

Routine Description:

    Configure selected attributes of a user object. 
    Currently none is selected, so this routine does nothing. 
    Will expand this routine when more attributes are defined.

Arguments:

    pIObj               : ITDirectoryObject interface
    
Return Value:

    HRESULT

--*/
{
    if (NULL == pIObj)
    {
        return E_POINTER;
    }

    //
    // query the ITDirectoryObjectUser interface
    //
    ITDirectoryObjectUser *   pIUser;
    HRESULT hr = pIObj->QueryInterface(IID_ITDirectoryObjectUser,
                                       (void **) &pIUser
                                       );
    RETURN_IF_FAILED(hr);

    //
    // config selected attributes: currently none
    //
    
    // release the ITDirectoryObjectUser interface
    RELEASE_COM_IF(pIUser);

    return hr;

} // ConfigUser

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// AddUser
//
HRESULT
AddUser(ITRendezvous *  pIRend,
        ITDirectory *   pIDir,
        _bstr_t         bstrtUserName,
        _bstr_t         bstrtIPPhonePrimary
       )
/*++

Routine Description:
    
    Add a user object to the ILS server. 
    Existing user with same IPPhonePrimary is deleted first to avoid "Object
    already exists" error.

Arguments:

    pIRend  : an ITRendezvous interface
    pIDir   : an ITDirectory interface
    bstrtUserName       : name of the user
    bstrtIPPhonePrimary : IPPhonePrimary value

Return Value:

    HRESULT

--*/
{
    if (NULL == pIDir)
    {
        return E_POINTER;
    }

    // no need to check other parameter validity. will be done in CreatUser
    
    ITDirectoryObject   *pIObj;
    
    //
    // create the user object with given IPPhonePrimary
    //
    RETURN_IF_FAILED(CreateUser(pIRend,
                                bstrtUserName, 
                                bstrtIPPhonePrimary,
                                &pIObj)
                    );

    //
    // configure other attributes of the user object
    //
    RETURN_IF_FAILED(ConfigUser(pIObj));

    // to ensure a successful creating, delete it first in case a same
    // name user with same IPPhonePrimary already exists. since it'll fail 
    // if the conference does not exist, i won't bother checking the error 
    // code
    pIDir->DeleteDirectoryObject(pIObj);
  
    //
    // add the user object to the ILS server
    //
    HRESULT hr = pIDir->AddDirectoryObject(pIObj);

    // release the ITDirectoryObject interface
    RELEASE_COM_IF(pIObj);

    return S_OK;

} // AddUser

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// ListObject
//
HRESULT
ListObject(ITDirectoryObject *  pIObj)
/*++

Routine Description:

    Print out selected object attributes. 
    For a conference, conference name and description will be printed.
    For a user, user name and IPPhonePrimary will be printed.

Arguments:

    pIObj   : an ITDirectoryObject interface

Return Value:

    HREULST

--*/
{
    if (NULL == pIObj)
    {
        return E_POINTER;
    }

    // 
    // get the object type
    //
    DIRECTORY_OBJECT_TYPE DirectoryObjectType;
    HRESULT hr = pIObj->get_ObjectType(&DirectoryObjectType);
    RETURN_IF_FAILED(hr);

    //
    // get and print object name
    //
    BSTR bstrName;
    hr = pIObj->get_Name( &bstrName);
    RETURN_IF_FAILED(hr);

    if (OT_CONFERENCE == DirectoryObjectType)
    {
        wprintf(L"\t<CONF> ");
    }
    else
    {
        wprintf(L"\t<USER> ");
    }


	WCHAR szName[RND_MAX_STRING_FORMAT]; 
    StringCbPrintfW(szName, RND_MAX_STRING_FORMAT, L"%s\n",(WCHAR *) bstrName); 
    _putws(szName);  

    ::SysFreeString (bstrName);
    
    if (OT_CONFERENCE == DirectoryObjectType)
    {
        ITDirectoryObjectConference * pIConf;
        hr = pIObj->QueryInterface(IID_ITDirectoryObjectConference,
                                   (void **) &pIConf
                                  );
        RETURN_IF_FAILED(hr);
        
        //
        // get the ITConferenceBlob interface
        //
        ITConferenceBlob *  pIConfBlob;
        hr = pIConf->QueryInterface(IID_ITConferenceBlob,
                                    (void **) &pIConfBlob
                                    );
        RETURN_IF_FAILED(hr);

        //
        // get and print the conference's blob
        //

        BSTR bstrBlob;
        hr = pIConfBlob->get_ConferenceBlob(&bstrBlob);
        RELEASE_COM_IF(pIConfBlob);
        RELEASE_COM_IF(pIConf);
        RETURN_IF_FAILED(hr);
        

		WCHAR szBlob[RND_MAX_STRING_FORMAT]; 
		StringCbPrintfW(szBlob, RND_MAX_STRING_FORMAT, L"\t\tBlob:\n%s", (WCHAR *) bstrBlob); 
		_putws(szBlob);  

        ::SysFreeString (bstrBlob);
    }
    else
    {   // OT_USER
        ITDirectoryObjectUser * pIUser;
        hr = pIObj->QueryInterface(IID_ITDirectoryObjectUser,
                                   (void **) &pIUser
                                  );
        RETURN_IF_FAILED(hr);
        
        //
        // get and print the user's IPPhonePrimary
        //

        BSTR bstrIPPhonePrimary;
        hr = pIUser->get_IPPhonePrimary(&bstrIPPhonePrimary);
        RELEASE_COM_IF(pIUser);
        RETURN_IF_FAILED(hr);

		WCHAR szPrimary[RND_MAX_STRING_FORMAT]; 
		StringCbPrintfW(szPrimary, RND_MAX_STRING_FORMAT, L"\t\tIPPhonePrimary: %s\n", (WCHAR *) bstrIPPhonePrimary); 
		_putws(szPrimary);  

        ::SysFreeString(bstrIPPhonePrimary);
    }

    return S_OK;

} // ListObject

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// EnumObjects
//
HRESULT
EnumObjects(ITDirectory *           pIDir,
            DIRECTORY_OBJECT_TYPE   DirectoryObjectType,
            _bstr_t                 bstrtFilter)
/*++

Routine Description:
    
    Enumerate all conference or user objects whose names starting with a 
    string specified by bstrtFilter.

Arguments:

    pIDir   : an ITDirectory interface
    DirectoryObjectType : type of objects to enumerate
    bstrtFilter : conference name filter

Return Value:

    HRESULT

--*/
{
    //
    // verify parameter validity
    //
    if (NULL == pIDir)
    {
        return E_POINTER;
    }

    if (bstrtEMPTY == bstrtFilter)
    {
        return E_INVALIDARG;
    }

    //
    // get the enumerator
    //
    IEnumDirectoryObject *  pIEnumObjects;
    HRESULT hr = pIDir->EnumerateDirectoryObjects(DirectoryObjectType,
                                                  bstrtFilter,
                                                  &pIEnumObjects
                                                  );
    RETURN_IF_FAILED(hr);

    //
    // enumerate objects returned in the enumerator
    //
    while (1)
    {
        ITDirectoryObject * pIObj;
        ULONG   cFetched;

        //
        // get an object
        //
        hr = pIEnumObjects->Next(1, &pIObj, &cFetched);

        if (S_OK != hr)
        {
            // either reach the end of the enumerator: hr == S_FALSE
            // or get an error: FAILED(hr) == TRUE
            break;
        }
        
        ListObject(pIObj);

        RELEASE_COM_IF(pIObj);
    }

    RELEASE_COM_IF(pIEnumObjects);

    return hr;
} // EnumObjects

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// DeleteConference
//
HRESULT
DeleteConference(ITRendezvous * pIRend,
                 ITDirectory *  pIDir,
                 _bstr_t        bstrtConfName)
/*++

Routine Description:

    Delete an object

Arguments:

    pIRend  : pointer to an ITRendezvous interface
    pIDir   : pointer to the ILS server's ITDirectory interface
    bstrtConfName : name of the conference to delete

Return Value:

    HRESULT

--*/
{
    if ((NULL == pIRend) || (NULL == pIDir))
    {
        return E_POINTER;
    }

    if (bstrtEMPTY == bstrtConfName)
    {
        return E_INVALIDARG;
    }

    //
    // create the object
    //
    ITDirectoryObject * pIObj;
    HRESULT hr = pIRend->CreateDirectoryObject(OT_CONFERENCE,
                                               bstrtConfName,
                                               &pIObj
                                               );
    RETURN_IF_FAILED(hr);

    //
    // delete it
    //

    hr = pIDir->DeleteDirectoryObject(pIObj);

    RELEASE_COM_IF(pIObj);

    return hr;

} // DeleteConference

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// DeleteUser
//
HRESULT
DeleteUser(ITRendezvous *  pIRend,
           ITDirectory *   pIDir,
           _bstr_t         bstrtUserName,
           _bstr_t         bstrtIPPhonePrimary
          )
/*++

Routine Description:
    
    Delete a user object from the ILS server. 

Arguments:

    pIRend  : an ITRendezvous interface
    pIDir   : an ITDirectory interface
    bstrtUserName       : name of the user
    bstrtIPPhonePrimary : IPPhonePrimary value

Return Value:

    HRESULT

--*/
{
    // no need to other check parameter validity. will be done in CreatUser
    if (NULL == pIDir)
    {
        return E_POINTER;
    }
    
    ITDirectoryObject   *pIObj;
    
    //
    // create the user object with given IPPhonePrimary
    //
    RETURN_IF_FAILED(CreateUser(pIRend,
                                bstrtUserName, 
                                bstrtIPPhonePrimary,
                                &pIObj)
                    );
    
    HRESULT hr = pIDir->DeleteDirectoryObject(pIObj);
  
    // release the ITDirectoryObject interface
    RELEASE_COM_IF(pIObj);

    return hr;
    
} // AddUser

///////////////////////////////////////////////////////////////////////////////
//                                                                           
// main                                                                      
//                                                                           
int _cdecl
main(int argc,
     char *argv[]
     )
{
    /*
     * 0. Get ILS server name, if it is specified
     */
    if (argc != 2)
    {
        wprintf(L"No ILS server specified.\n");
        return 1;
    }

    _bstr_t bstrtILSServer = _bstr_t(argv[1]);

    /*
     * 1. Create ITRendezvous interface
     */

    wprintf(L"\n\n");
    START_STEP(L"Initialize Rendezvous Control");

    ::CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // create an ITRendezvous interface
    ITRendezvous    *pIRend;
    HRESULT hr = ::CoCreateInstance(CLSID_Rendezvous,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_ITRendezvous,
                                    (void**)&pIRend
                                   );
    END_STEP(hr);

    /*
     * 2. Connect and bind to the ILS server
     */

    START_STEP(L"Connect and Bind to the ILS server");
    ITDirectory *pIDir;
    hr = OpenILS(pIRend, 
                 bstrtILSServer, 
                 &pIDir
                );
    END_STEP(hr);

    /*
     * 3. Add a conference
     */

    START_STEP(L"Add a conference");
    _bstr_t bstrtConfName = _bstr_t(L"Rendezvous Controls Sample Program");
    hr = AddConference(pIRend,
                       pIDir,
                       bstrtConfName
                      );
    END_STEP(hr);

    /*
     * 4. Enumerate conferences
     */
    
    // use the conference name as a filter for enumeration to limit the set of 
    // conferences that will be retrieved.
    // if no filter is set, all conferences will be retrieved
    
    START_STEP(L"Enumerate conferences");
    hr = EnumObjects(pIDir, 
                     OT_CONFERENCE, 
                     bstrtConfName);
    END_STEP(hr);

    /*
     * 5. Delete a conference
     */

    START_STEP(L"Delete a conference");
    hr = DeleteConference(pIRend, 
                          pIDir, 
                          bstrtConfName);
    END_STEP(hr);

    /*
     * 6. Add a user: must specify the IPPhonePrimary value associated with
     *    this user
     */

    //
    // get the local machine's name
    // note: WSAStartup is called in creating ITRendezvous *, so no need to
    // start Winsock for the gethostbyname call
    //

    const int MAXHOSTNAMELEN = 255;
    CHAR        LocalHostName[MAXHOSTNAMELEN];

    if (SOCKET_ERROR == gethostname(LocalHostName, MAXHOSTNAMELEN))
    {
        wprintf(L"Can't find local host name.\n");
        return E_FAIL;
    }

    _bstr_t bstrtUserName = _bstr_t(L"TAPI3 Rend SDK User");
    _bstr_t bstrtIPPhonePrimary = _bstr_t(LocalHostName);

    START_STEP(L"Add a user");
    hr = AddUser(pIRend,
                 pIDir,
                 bstrtUserName,
                 bstrtIPPhonePrimary
                );
    END_STEP(hr);

    /*
     * 7. Enumerate users
     */
    
    // use the user name as a filter for enumeration to limit the set of 
    // users that will be retrieved. all user objects (may having different
    // IPPhonePrimary) with this name will be retrieved
    // if no filter is set, all users will be retrieved
    
    START_STEP(L"Enumerate users");
    hr = EnumObjects(pIDir, 
                     OT_USER, 
                     bstrtUserName);
    END_STEP(hr);

    /*
     * 8. Delete a user: must specify the IPPhonePrimary associated with
     *    this user to identify which entry to delete. Note one user may
     *    have several different IPPhonePrimary values.
     */

    START_STEP(L"Delete a user");
    hr = DeleteUser(pIRend, 
                    pIDir, 
                    bstrtUserName,
                    bstrtIPPhonePrimary);
    END_STEP(hr);

    /*
     * 9. Clean-up
     */

    RELEASE_COM_IF(pIDir);
    RELEASE_COM_IF(pIRend);
    
    ::CoUninitialize();

    wprintf(L"\n\n");

    return 0;

} // end of main



			
