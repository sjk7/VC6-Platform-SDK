
/*

    ADSIHelpers.h

    General helper rountines for Debugging ADSI applications


*/


#ifndef __ADSIHELLPERS_H
#define __ADSIHELLPERS_H

#include <activeds.h>
#include <adsiid.h>


// Function declarations
void			CheckHRESULT(HRESULT hr, const char *pszCause);
const char *	GetVariantStyle(VARTYPE vt);
HRESULT			GetIADsPropertyValueAsBSTR(BSTR * pbsRet,IADsPropertyValue * pAdsPV);
WCHAR*          CrackADError(HRESULT hResult);
void            ADErrMsgBox(HRESULT passedhr);
const char *    QueryAllInterfaces(IUnknown * pUnk);
char *          GetCharFromGUID(GUID idtofind);


// Macros

// Simple Macro to simplyfy reading a bitflag
#define HAS_BIT_STYLE(val, style) \
((val & style) == style)


// Inline functions

// Will display ADSI or COM error messages
// when passed a BAD Hresult
inline void CheckADHRESULT(HRESULT hr)
{
    if (FAILED(hr))
        ADErrMsgBox(hr);

}

#endif
