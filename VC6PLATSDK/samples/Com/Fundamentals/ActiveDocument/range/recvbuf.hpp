// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

// ===========================================================================
//                     RecvBuf utility class
// ===========================================================================
class RecvBuf
{
    DWORD  m_cbBufSize; // size of buffer
    PBYTE  m_pbBufBeg;  // start of buffer
    PBYTE  m_pbBufEnd;  // end of buffer

public:

    PBYTE  m_pbDataBeg; // start of data
    PBYTE  m_pbDataEnd; // end of data

    RecvBuf()
    {
        m_pbBufBeg = NULL;
    }

    ~RecvBuf()
    {
        if (m_pbBufBeg)
            LocalFree ((HLOCAL) m_pbBufBeg);
    }

    PBYTE BufBeg(void)   { return m_pbBufBeg; }
    DWORD BufSpace(void) { return (DWORD)(m_pbBufEnd - m_pbDataEnd); }
    DWORD BufSize(void)  { return m_cbBufSize; }

    void  BufReset(void)
    {
        m_pbDataBeg = m_pbBufBeg;
        m_pbDataEnd = m_pbBufBeg;
    }

    void BufShift (void)
    {    
        if (m_pbDataBeg > m_pbBufBeg)
        {
            // Shift the data to front of buffer.
            DWORD cbData = (DWORD)(m_pbDataEnd - m_pbDataBeg);
            MoveMemory (m_pbBufBeg, m_pbDataBeg, cbData);
            m_pbDataBeg  = m_pbBufBeg;
            m_pbDataEnd  = m_pbBufBeg + cbData;
        }
    }

    BOOL BufAlloc (DWORD dwSize);
    BOOL BufScanStr (PSTR pszSearch, DWORD cbSearch);
    BOOL BufScanInt (DWORD *pdwRet, BYTE cDelimit);
};

