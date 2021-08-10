/*++

Copyright (c) Microsoft Corporation


--*/

void ReleaseObj(IUnknown* pInterface);

void PrintErrorText(HRESULT hr);

void SafeStrCopy(TCHAR* src, TCHAR* dst, size_t srcBufLen);

// For Invoke Action 
HRESULT HrCreateSafeArray(VARTYPE vt, int nArgs, SAFEARRAY **ppsa);
HRESULT HrCreateArgVariants(DWORD dwArgs, VARIANT*** pppVars);
HRESULT HrDestroyArgVariants(DWORD dwArgs, VARIANT*** pppVars);
void VariantSetVar(VARIANT* pvarToSet, VARIANT& va);
void VariantSetArray(SAFEARRAY* psa, VARIANT& va);
HRESULT HrGetSafeArrayBounds(SAFEARRAY *psa, long* plLBound, long* plUBound);
HRESULT HrGetVariantElement(SAFEARRAY *psa, int lPosition, VARIANT* pvar);
