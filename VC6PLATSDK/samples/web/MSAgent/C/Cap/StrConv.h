#ifndef _StrConv_h_
#define _StrConv_h_


LPWSTR WINAPI A2WHelper(LPWSTR pwsz, LPCSTR psz, UINT cch) {

	_ASSERTE(psz);
	_ASSERTE(pwsz);

	pwsz[0] = '\0';

	MultiByteToWideChar(CP_ACP, 0, psz, -1, pwsz, cch);

	return pwsz;
}


LPSTR WINAPI W2AHelper(LPSTR psz, LPCWSTR pwsz, UINT cch) {

	_ASSERTE(psz);
	_ASSERTE(pwsz);

	psz[0] = '\0';

	WideCharToMultiByte(CP_ACP, 0, pwsz, -1, psz, cch, NULL, NULL);

	return psz;
}


#ifndef _DEBUG
#define USES_CONVERSION int _convert; _convert
#else
#define USES_CONVERSION int _convert = 0
#endif


#ifndef A2WHELPER
#define A2WHELPER	A2WHelper
#define W2AHELPER	W2AHelper
#endif


#define A2W(psz) (\
	((LPCSTR)psz == NULL) ? NULL : (\
		_convert = (lstrlenA(psz)+1),\
		A2WHELPER((LPWSTR)alloca(_convert*2), psz, _convert)))

#define W2A(pwsz) (\
	((LPCWSTR)pwsz == NULL) ? NULL : (\
		_convert = (lstrlenW(pwsz)+1)*2,\
		W2AHELPER((LPSTR)alloca(_convert), pwsz, _convert)))


#define A2CW(psz)		((LPCWSTR)A2W(psz))
#define W2CA(pwsz)		((LPCSTR)W2A(pwsz))


#ifdef _UNICODE
	#define T2A W2A
	#define A2T A2W
	inline LPWSTR T2W(LPTSTR lp) { return lp; }
	inline LPTSTR W2T(LPWSTR lp) { return lp; }
	#define T2CA W2CA
	#define A2CT A2CW
	inline LPCWSTR T2CW(LPCTSTR lp) { return lp; }
	inline LPCTSTR W2CT(LPCWSTR lp) { return lp; }
#else
	#define T2W A2W
	#define W2T W2A
	inline LPSTR T2A(LPTSTR lp) { return lp; }
	inline LPTSTR A2T(LPSTR lp) { return lp; }
	#define T2CW A2CW
	#define W2CT W2CA
	inline LPCSTR T2CA(LPCTSTR lp) { return lp; }
	inline LPCTSTR A2CT(LPCSTR lp) { return lp; }
#endif


#endif
