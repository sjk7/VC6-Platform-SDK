// VCSecuritySampleClass.cpp : Implementation of CVCSecuritySampleClass
#include "stdafx.h"
#include "VCSecuritySample.h"
#include "VCSecuritySampleClass.h"
// If targeting COM+ uncomment the following line:
// #define _complus
#include <comsvcs.h>

/////////////////////////////////////////////////////////////////////////////
// CVCSecuritySampleClass


STDMETHODIMP CVCSecuritySampleClass::AmIAnAdministrator(short * retval)
{
IObjectContext * pObjCtx;
HRESULT hr;
int fIsInRole;


hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjCtx);
if(FAILED(hr))
{
	*retval = 2;
	return S_OK;
}

if(NULL == pObjCtx)
{
    //Return Error Code
	*retval = 2;
	return S_OK;
}

if(!pObjCtx->IsSecurityEnabled())
{
    //Return Error Code
	*retval = 2;
	return S_OK;
}

BSTR strAdminRole = SysAllocString(L"Administrator");
hr = pObjCtx->IsCallerInRole(strAdminRole, &fIsInRole);
SysFreeString(strAdminRole);

//An error will be caused if the Administrator role does
//not exist.
if(CONTEXT_E_ROLENOTFOUND == hr)
{
	*retval = 0;
	return S_OK;
}

if(FAILED(hr))
{
	*retval = 2;
	return S_OK;
}

if (fIsInRole) 
	*retval = 1;
else
	*retval = 0;

return S_OK;

}


STDMETHODIMP CVCSecuritySampleClass::WhoAmI(BSTR * retval)
{
IObjectContext * pIObjCtx = NULL;
ISecurityProperty* pISecurityProperty = NULL;
DWORD			cbDomain = 20;
DWORD			cbUserName = 20 ;
OLECHAR			lpwstrDomain[20 + 20 + 2] = _T("");
OLECHAR			lpwstrUserName[20] = _T("");
PSID			pSID = NULL;
SID_NAME_USE	peUse;


if(FAILED(CoGetObjectContext(IID_IObjectContext, (void**)&pIObjCtx)))
	goto error;

if(NULL == pIObjCtx)
	goto error;

if(!pIObjCtx->IsSecurityEnabled())
	goto error;

if(FAILED(pIObjCtx->QueryInterface(IID_ISecurityProperty,
	(void**)&pISecurityProperty)))
	goto error;

if(FAILED(pISecurityProperty->GetDirectCallerSID(&pSID)))
	goto error;

if(!LookupAccountSid(NULL, pSID,lpwstrUserName,&cbUserName, 
	lpwstrDomain, &cbDomain, &peUse))
	goto error;
			
if((!cbDomain) || (!cbUserName))
	goto error;

_tcsncat(lpwstrDomain, _T("\\"),1);
_tcsncat(lpwstrDomain, lpwstrUserName, _tcslen(lpwstrUserName));
*retval = SysAllocString(lpwstrDomain);
goto cleanup;

error:
*retval = SysAllocString(L"");
goto cleanup;

cleanup:
if(pSID)
	pISecurityProperty->ReleaseSID(pSID);
if(pIObjCtx)
	pIObjCtx->Release();
if(pISecurityProperty)
	pISecurityProperty->Release();
return S_OK;
}

