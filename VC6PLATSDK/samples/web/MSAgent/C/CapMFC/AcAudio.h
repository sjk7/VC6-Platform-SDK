#ifndef _ACAudio_h_
#define _ACAudio_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CAgentCtlAudioObject wrapper class

class CAgentCtlAudioObject : public COleDispatchDriver
{
public:
	CAgentCtlAudioObject() {}		// Calls COleDispatchDriver default constructor
	CAgentCtlAudioObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAgentCtlAudioObject(const CAgentCtlAudioObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetEnabled();
	BOOL GetSoundEffects();
};


#endif
