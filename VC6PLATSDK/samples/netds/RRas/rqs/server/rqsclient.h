//+--------------------------------------------------------------------------
//
//      File:       RqsClient.h
//
//      Synopsis:   Object representing a client to the Quarantine engine
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#pragma once

class RqsEngine;

#define RQS_MESSAGE_LENGH_SIZE 4                             // "Size"
#define RQS_MESSAGE_PREFIX_SIZE (3 + RQS_MESSAGE_LENGH_SIZE) // "Size:1:"
#define RQS_MESSAGE_SIZE  (1024 + RQS_MESSAGE_PREFIX_SIZE)   // "Size:1:String"

//+--------------------------------------------------------------------------
//
// Synopsis: Defines the states a client goes through
//
//      Reading:            In the process of reading the client's message
//      ReceiveComplete:    Full client message received
//      Responding:         In the process of repsonding to the client
//      RespondComplete:    Completed a response to the client
//
//+--------------------------------------------------------------------------
enum RqsClientState
{
    Receiving,
    ReceiveComplete,
    Responding,
    RespondComplete,
    ClientError
};

//+--------------------------------------------------------------------------
//
// Synopsis: Client control block
//
//+--------------------------------------------------------------------------
class RqsClient
{
public:
    RqsClient();
    ~RqsClient();

    VOID SetEngine(IN RqsEngine* pEngine) {m_pEngine = pEngine;}
    VOID AssignSocket(IN RuSocket* pSocket); 

    HRESULT ReceiveMessage();
    HRESULT SendResponse(IN BOOL fOk);

    RqsClientState GetState() {return m_State;}
    CHAR* GetString() {return m_pszString;}
    CONST CHAR* GetUsername();

    DWORD GetAddressN();
    DWORD GetAddressH();
    CONST CHAR* GetAddressPsz();

private:
    RuSocket* m_pSocket;
    RqsEngine* m_pEngine;
    CHAR m_pszBuffer[RQS_MESSAGE_SIZE];
    CHAR m_pszAddress[32];
    UINT m_uiBytesRead;
    UINT m_uiMessageSize;
    CHAR* m_pszString;
    CHAR* m_pszUsername;
    RqsClientState m_State;
    DWORD m_dwAddressH;

    
};

