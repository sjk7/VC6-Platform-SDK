#define INC_OLE2
#define UNICODE 1
#define _WIN32_DCOM

#include <windows.h>
#include <winuser.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <winldap.h>
#include <activeds.h>
#include "ADSIhelpers.h"
#include <assert.h>


void main()
{
// Initialize COM
CoInitialize(0);
 
WCHAR pwszADsPathObject[1024];
WCHAR pwszBindByGuidStr[1024]; 
HRESULT hr;

IADs * pIADsObject = NULL;
IADs * pIADsObjectByGuid = NULL;

// Ask the user for a ADsPath to start
_putws(L"This code binds to a directory object by ADsPath, retrieves the GUID,\n"
       L" then rebinds by GUID. \n\nSpecify the ADsPath of the object to bind to :\n");
_getws(pwszADsPathObject);


if (pwszADsPathObject[0] == NULL) 
    return;

wprintf(L"\nBinding to %s\n",pwszADsPathObject);

// Bind to initial object
hr = ADsGetObject( pwszADsPathObject,IID_IADs, (void **)& pIADsObject);
if (SUCCEEDED(hr))
{
    BSTR bsGuid = NULL;
    hr = pIADsObject->get_GUID(&bsGuid); 
    
    if (SUCCEEDED(hr))
    {	
        wprintf(L"\n The GUID for\n\n%s\n\nis\n\n%s\n",pwszADsPathObject,bsGuid);
	
        // Build a string for Binding to the object by GUID
        wsprintf(pwszBindByGuidStr,L"LDAP://<GUID=%s>",bsGuid);

        // Bind BACK to the Same object using the GUID
        hr = ADsGetObject( pwszBindByGuidStr,IID_IADs, (void **)& pIADsObjectByGuid);
         
        if (SUCCEEDED(hr))
        {	
            wprintf(L"\nSuccessfully RE bound to\n\n%s\n\nUsing the path:\n\n%s\n", pwszADsPathObject,pwszBindByGuidStr);

            // Release bind by GUID Object
            pIADsObjectByGuid->Release();
            pIADsObjectByGuid = NULL;
        }

        SysFreeString(bsGuid);
    }

    pIADsObject->Release();
    pIADsObject = NULL;
}

if (FAILED(hr))
    _putws(L"Failed");
CoUninitialize();    

}