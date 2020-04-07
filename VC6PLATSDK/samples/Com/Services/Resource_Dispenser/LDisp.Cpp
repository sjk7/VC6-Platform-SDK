// LDisp.cpp : Implementation of CLDisp
#include "stdafx.h"
#include "Disp1.h"
#include "LDisp.h"

/////////////////////////////////////////////////////////////////////////////
// CLDisp


//Alloc & DeAlloc are the two members of the ILDisp interface, which is what
//a COM+ object would actually use.  The other functions later in this file are
//used by the Resource Dispenser Manager.

//Alloc takes a pointer to a RESID and sets the RESID equal to the id of 
//a newly allocated resource.
//We obtain this pointer by calling the AllocResource method provided
//by the Resource Dispenser Manager.
STDMETHODIMP CLDisp::Alloc(long * pJAustin)
{
	//if we don't have a valid pointer to the Dispenser Manager, fail.
	if(m_pDispMan)
	{
		*pJAustin = NULL;
		//We pass the pointer to JAustin to alloc Resource.
		//Once it returns to us, the dispenser manager has set
		//JAustin equal to a specific RESID.  We return this to the
		//client, and which time the client has a RESID.
		return m_pHolder->AllocResource((RESID)1, (RESID *)pJAustin);
	}

	return E_FAIL;

}

//DeAlloc takes a RESID and deallocates it by calling the FreeResource
//method provided by the dispenser manager.
STDMETHODIMP CLDisp::DeAlloc(long JAustin)
{
	//If we don't have a valid pointer to a dispenser manager, fail.
 if(m_pDispMan)
	{
	 //call free resource, specifying which resource to free.
	 return m_pHolder->FreeResource((RESID)JAustin);
	}
	else return E_FAIL;

}

//CreateResource allocates an integer and returns a RESID uniquely specifying
//that piece of memory back to the resource dispenser manager.
HRESULT CLDisp::CreateResource(const RESTYPID ResTypId,
									RESID * pResId,
									TIMEINSECS* pSecsFreeBeforeDestroy)
{

	if(1 != ResTypId)
		return E_FAIL;

	int * j = new int; //allocate an integer
	*pResId = (RESID)j; //convert the pointer to the integer to a RESID.
	*pSecsFreeBeforeDestroy = 20;

	return S_OK;
}

//RateResource tells the caller (the Resource Dispenser Manager) how easy
//it will be to use the specified resource.  In our
//case we always say that the integer is perfectly suited (100) to any
//caller, since integers are non-transactional resources.
HRESULT CLDisp::RateResource(const RESTYPID ResTypId,
							const RESID ResId,
								const BOOL fRequiresTransactionEnlistment,
								RESOURCERATING* pRating)
{
	*pRating = 100; //perfectly suited.
	return S_OK;
}

//EnlistResource enlists a resource in a transaction.  Our integers are 
//non-transactional, so we always return E_FAIL.  
HRESULT CLDisp::EnlistResource(const RESID ResId, const TRANSID TransId)
{return E_FAIL;}


//EnlistResource un-enlists a resource from a transaction.  Our integers are 
//non-transactional, so we always return E_FAIL.
HRESULT CLDisp::ResetResource(const RESID ResId)
{return S_OK;}

//DestroyResource is called by the Resource Dispenser Manager and tells a 
//dispenser to de-allocate a resource.  Our resources are just integers,
//so we just use delete.
HRESULT CLDisp::DestroyResource(const RESID ResId)
{ 
	delete (int *)ResId; 
	return S_OK;
}

//We don't implement DestroyResourceS.
HRESULT CLDisp::DestroyResourceS(constSRESID ResId)
{return E_FAIL;}

