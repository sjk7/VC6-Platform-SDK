#ifndef _ACUser_h_
#define _ACUser_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IAgentCtlUserInput wrapper class

class CAgentCtlUserInput : public COleDispatchDriver
{
public:
	CAgentCtlUserInput() {}		// Calls COleDispatchDriver default constructor
	CAgentCtlUserInput(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAgentCtlUserInput(const CAgentCtlUserInput& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	short GetCount();
	CString GetName();
	CString GetCharacterID();
	long GetConfidence();
	CString GetVoice();
	CString GetAlt1Name();
	long GetAlt1Confidence();
	CString GetAlt1Voice();
	CString GetAlt2Name();
	long GetAlt2Confidence();
	CString GetAlt2Voice();
};


#endif
