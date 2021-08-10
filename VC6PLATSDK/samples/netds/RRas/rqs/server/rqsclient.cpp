//+--------------------------------------------------------------------------
//
//      File:       RqsClient.cpp
//
//      Synopsis:   Object representing a client to the Quarantine engine
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#include <rqs.h>

//+--------------------------------------------------------------------------
//
// Synopsis: Instantiate a client control block 
//
//+--------------------------------------------------------------------------
RqsClient::RqsClient() : m_pSocket(NULL), m_uiBytesRead(0), m_uiMessageSize(0),
                        m_pszString(NULL), m_pszUsername(NULL), m_State(Receiving), 
                        m_pEngine(NULL), m_dwAddressH(0)
{
    m_pszBuffer[0] = '\0';
    ZeroMemory(m_pszAddress, sizeof(m_pszAddress));
}

//+--------------------------------------------------------------------------
//
// Synopsis: Destroy a client control block 
//
//+--------------------------------------------------------------------------
RqsClient::~RqsClient()
{
    if (m_pSocket)
    {
        m_pSocket->Close();
        delete m_pSocket;
    }
}

//+--------------------------------------------------------------------------
//
// Synopsis: Assign ownership of a socket to a client control block.
//
//+--------------------------------------------------------------------------
VOID 
RqsClient::AssignSocket(
    IN RuSocket* pSocket)
{
    HRESULT hr;
    DWORD dwAddress = 0;
    
    m_pSocket = pSocket;

    hr = pSocket->GetAddress(&dwAddress);
    if (S_OK != hr)
    {
        m_pEngine->Trace("Unable to obtain client address. 0x%x", hr);
        m_State = ClientError;
        dwAddress = 0;
    }
    
    m_dwAddressH = ntohl(dwAddress);
    
    _snprintf(
        m_pszAddress, 
        sizeof(m_pszAddress) - 1, 
        "%d.%d.%d.%d",
        IP1(m_dwAddressH),
        IP2(m_dwAddressH),
        IP3(m_dwAddressH),
        IP4(m_dwAddressH));

}

//+--------------------------------------------------------------------------
//
// Synopsis: Receieve data from a client
//
//+--------------------------------------------------------------------------
HRESULT 
RqsClient::ReceiveMessage()
{
    HRESULT hr;
    UINT uiSize;
    CHAR* pszCur;
    INT iSize;

    // Sanity check that we haven't already read in too many bytes
    //
    if (m_uiBytesRead >= sizeof(m_pszBuffer))
    {
        m_pEngine->Trace(
            "Too many bytes read from client %s", 
            GetAddressPsz());
        m_State = ClientError;
        return E_FAIL;
    }

    // Read in whatever data is readily available
    //
    uiSize = sizeof(m_pszBuffer) - m_uiBytesRead;
    pszCur = &(m_pszBuffer[m_uiBytesRead]);
    hr = m_pSocket->Read((BYTE*)pszCur, &uiSize, FALSE);
    if (hr == HRESULT_FROM_WIN32(WSAEWOULDBLOCK))
    {
        return S_OK;
    }
    else if (S_OK != hr)
    {
        m_pEngine->Trace(
            "ClientError 0x%x while receiving message from %s",
            hr,
            GetAddressPsz());
            m_State = ClientError;
        return hr;
    }
    if (uiSize == 0)
    {
        // The client has disconnected this socket.  This should not happen
        //
        m_pEngine->Trace(
            "Dropping client because socket was closed remotely %s",
            GetAddressPsz());
        m_State = ClientError;
        return E_FAIL;            
    }

    // Update the total number of bytes read
    //
    m_uiBytesRead += uiSize;

    // The message is in the form "Size:1:username:String".
    // 
    // If we have Size, then remember it
    //
    if ((m_uiBytesRead >= RQS_MESSAGE_LENGH_SIZE) && (m_uiMessageSize == 0))
    {
        m_pszBuffer[RQS_MESSAGE_LENGH_SIZE] = '\0';
        iSize = atoi(m_pszBuffer);

        // iSize is the size of the rest of the buffer. i.e. strlen(":1:username:String")
        // Make sure that there is at least 1 character in String and that String
        // is no longer than 1024 bytes.
        //
        // 4 = strlen(":1:S")
        // 1027 = strlen(":1:username:String") if username:String is 1024 characters long
        // Note that the username string is optional.
        //
        if ((iSize < 4) || (iSize > 1027))
        {
            m_pEngine->Trace(
                "Client %s sent an out-of-range size", 
                GetAddressPsz());
            m_State = ClientError;
            return E_FAIL;
        }
        m_uiMessageSize = iSize;
    }

    // See if we're done reading yet
    //
    if (m_uiBytesRead >= (m_uiMessageSize + RQS_MESSAGE_LENGH_SIZE))
    {
        // First, remove the prefix
        //
        m_pszBuffer[RQS_MESSAGE_PREFIX_SIZE + m_uiMessageSize] = '\0';
        m_pszUsername = &(m_pszBuffer[RQS_MESSAGE_PREFIX_SIZE]);

        // Now check to see if there is a username
        //
        PCHAR pszColon = strchr(m_pszUsername, ':');
        if (pszColon)
        {
            m_pszString = pszColon + 1;
            *pszColon = '\0';

            // Make sure the username isn't longer than the username + domain + separator
            //
            if ((pszColon - m_pszUsername) > (UNLEN + DNLEN + 1))
            {
                m_pEngine->Trace(
                    "Client %s sent a larger than expected username", 
                    GetAddressPsz());
                m_State = ClientError;
                return E_FAIL;
            }
        }
        else
        {
           m_pszString = m_pszUsername;
           m_pszUsername = NULL;
        }

        // Finally save off the remaining as the string
        //
        m_State = ReceiveComplete;
    }
    
    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Send a response to a client
//
//+--------------------------------------------------------------------------
HRESULT 
RqsClient::SendResponse(
    IN BOOL fOk)
{
    UINT uiTot, uiSize;
    HRESULT hr;

    m_State = Responding;
    
    uiTot = uiSize = 3;
    hr = m_pSocket->Write(
            (BYTE*) ((fOk) ? "Ok" : "No"),
            &uiSize);
    if ((S_OK != hr) || (uiTot != uiSize))
    {
        m_pEngine->Trace(
            "Unable to respond to %s %x %d %d",
            GetAddressPsz(),
            hr,
            uiTot,
            uiSize);
    }

    m_State = RespondComplete;

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Retrieve the network-order address of the client
//
//+--------------------------------------------------------------------------
DWORD 
RqsClient::GetAddressN()
{
    return htonl(m_dwAddressH);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Retrieve the host-order address of the client
//
//+--------------------------------------------------------------------------
DWORD 
RqsClient::GetAddressH()
{
    return m_dwAddressH;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Retrieve the displayable string version of the client's address
//
//+--------------------------------------------------------------------------
CONST CHAR* 
RqsClient::GetAddressPsz()
{
    return m_pszAddress;
}

CONST CHAR*
RqsClient::GetUsername()
{
    if (m_pszUsername)
    {
        return m_pszUsername;
    }
    else
    {
        return "Unknown";
    }
}

