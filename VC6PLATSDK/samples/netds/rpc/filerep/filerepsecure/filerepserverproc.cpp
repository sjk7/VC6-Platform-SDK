/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Server System Service

    FILE: FileRepServerProc.cpp
    
    PURPOSE: Remote procedures for server system service
    
    FUNCTIONS:
        RemoteOpen() - Open the file.  It also gets some
    some data from the file, and closes the file if all data
    has been read at once.  This enhances performance.
        RemoteRead() - Read a buffer's worth of the file.  It
    closes the file if EOF has been reached.

    COMMENTS:

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

// header file generated by MIDL compiler
#include "FileRepServer.h"

// Declarations for service routines.
#include "Service.h"

typedef struct {
    HANDLE hFile;
    // We use this byte to check if EOF has been
    // reached on read.  The byte is put into
    // the first position of the next buffer read if EOF
    // has not been reached.
    BYTE EOFCheck;
} FILE_CONTEXT_TYPE;

/*
  This is a procedure that actually reads file data.
  It performs the reading tasks common to RemoteOpen and RemoteRead.
  Notice that nToRead is the number of bytes to read.
*/
VOID ReadData(HANDLE hFile, VOID *pbBuf, unsigned long nToRead, unsigned long *cbRead, BOOL *bEOF, BYTE *EOFCheck) {

    if(!ReadFile(hFile, pbBuf, nToRead+1, cbRead, NULL)) {

	// We want to raise an exception but leave the context intact
	// so that subsequent reads may be attempted.  Later versions
        // may implement this feature.

	RpcRaiseException(GetLastError());
        return;	
    }
    
    // Check for EOF.
    *bEOF = FALSE;
    // If we read in the whole buffer, save the last byte.
    if(*cbRead == nToRead+1) {
	*EOFCheck = ((BYTE *)pbBuf)[(nToRead+1)-1];

	// return at most nToRead read bytes.
	*cbRead = nToRead;
    }
    // If we did not read the whole buffer then we reached the EOF.
    else{
	*bEOF = TRUE;
    }
}

/*
    FUNCTION: s_RemoteOpen

    PURPOSE: Opens a file on the server and returns some file data.

    PARAMETERS:
        hFileRepServer - RPC binding
        pphContext - the context handle associated with the open file
        pszFileName -  file to open
	pbBuf - buffer to read into
	cbRead - number of bytes read into the buffer

    RETURN VALUE:
        none

    COMMENTS:
*/
VOID s_RemoteOpen(handle_t hFileRepServer,
		  PCONTEXT_HANDLE_TYPE *pphContext,
		  LPTSTR pszFileName,
		  BYTE *pbBuf,
		  unsigned long *cbRead)
{
    HANDLE hFile;
    FILE_CONTEXT_TYPE *pFileContext;
    BOOL bEOF = FALSE;
    BYTE EOFCheck;
    INT status;
    RPC_STATUS rpcstatus;

    BOOL bImpersonating = FALSE;

    // We need to impersonate the user that has issued the
    // remote call.  If we impersonate here then we make sure that
    // the user has adequate permissions to open the file.
    if (!bImpersonating) {
        if ((rpcstatus = RpcImpersonateClient(hFileRepServer)) != RPC_S_OK) {      
            RpcRaiseException(rpcstatus);
	    return;
	}
	bImpersonating = TRUE;
    }

    // It is enough to impersonate while opening the file, since this is where all
    // the security checks are done.  We can later read from this handle
    // while not impersonating.
    if ((hFile = CreateFile(pszFileName,
			    GENERIC_READ,
			    FILE_SHARE_READ,
			    NULL,
			    OPEN_EXISTING,
			    FILE_ATTRIBUTE_NORMAL,
			    NULL)) == INVALID_HANDLE_VALUE) {

        if ((rpcstatus = RpcRevertToSelf()) != RPC_S_OK) {
	    RpcRaiseException(rpcstatus);
	    return;
	}

	RpcRaiseException(GetLastError());
        return;
    }

    // We can now revert to self, since file has been opened while
    // impersonating and hence the security requirements have been met.
    if (bImpersonating) {
        if ((rpcstatus = RpcRevertToSelf()) != RPC_S_OK) {
            RpcRaiseException(rpcstatus);
	    return;
	}
    }

    // Read data from file into the buffer.
    // This function may throw exceptions, but we would want
    // those to propagate out.
    ReadData(hFile, (VOID *)pbBuf, OPEN_BUFSIZE, cbRead, &bEOF, &EOFCheck);

    // Check if EOF has been reached.
    if(bEOF) {
	// If it has, we can simply return.
	
	// Since all of the read has completed, the [out] context handle
	// pointer is NULL.
	pFileContext = NULL;
	*pphContext = (PCONTEXT_HANDLE_TYPE) pFileContext;

	status = CloseHandle(hFile);
	ASSERTE(status != 0);

	return;
    }
    else {
	// Otherwise we need to allocate, initialize, and return the
	// context handle.
	if((pFileContext = (FILE_CONTEXT_TYPE *) midl_user_allocate(sizeof(FILE_CONTEXT_TYPE))) == NULL) {

	    status = CloseHandle(hFile);
	    ASSERTE(status != 0);
	    RpcRaiseException(ERROR_OUTOFMEMORY);	    
	    return;
	}

	// Initialize the context handle fields.
	pFileContext->hFile = hFile;

	pFileContext->EOFCheck = EOFCheck;
	
	*pphContext = (PCONTEXT_HANDLE_TYPE) pFileContext;

	return;
    }
}

/*
    FUNCTION: s_RemoteRead

    PURPOSE: Opens a file on the server and returns some file data.

    PARAMETERS:
        hFileRepServer - RPC binding
        pphContext - the context handle associated with the open file
	pbBuf - buffer to read into
	cbRead - number of bytes read into the buffer

    RETURN VALUE:
        none

    COMMENTS:
*/
VOID s_RemoteRead(handle_t hFileRepServer,
		  PCONTEXT_HANDLE_TYPE *pphContext,
		  BYTE *pbBuf,
		  unsigned long *cbRead)
{
    FILE_CONTEXT_TYPE *pFileContext;
    BOOL bEOF = FALSE;
    BYTE EOFCheck;
    INT status;

    // Clients have already been authenticated in RemoteOpen.
    // Here we operate on the context handle generated in RemoteOpen,
    // hence no additional security precations need to be taken.

    // Make sure that the provided context handle is not NULL.
    if(*pphContext == NULL) {
	
	RpcRaiseException(RPC_X_SS_IN_NULL_CONTEXT);
        return;	
    }

    pFileContext = (FILE_CONTEXT_TYPE *) *pphContext;

    // Remember that we have a byte left over from RemoteOpen EOF check.
    pbBuf[0] = pFileContext->EOFCheck;

    // Read the following bytes from file, but remember that we now only
    // have space for READ_BUFSIZE-1 bytes and we write starting
    // from the 1st index.  We will let possible exceptions propagate out.
    ReadData(pFileContext->hFile, (VOID *)&(pbBuf[1]), READ_BUFSIZE-1, cbRead, &bEOF, &EOFCheck);
    
    // Since we had the first byte left over from the previous read, pretend
    // that we read it.
    (*cbRead)++;

    if(bEOF){
        // If it has, we can destroy the context handle, close 
        // the file and return.
	status = CloseHandle(pFileContext->hFile);
        ASSERTE(status != 0);

	midl_user_free(*pphContext);
      
	// Return NULL context handle to signify that the file has
	// been completely read.
	pFileContext = NULL;
	*pphContext = (PCONTEXT_HANDLE_TYPE) pFileContext;

	return;
    }

    // Memorize the last byte read for the next read.
    pFileContext->EOFCheck = EOFCheck;

    // Otherwise we just return the number of symbols read in cbRead.
    return;
}

// The rundown routine is associated with the context handle type.
// When a connection breaks, the server stub and the run-time 
// library will call this routine.
void __RPC_USER PCONTEXT_HANDLE_TYPE_rundown(PCONTEXT_HANDLE_TYPE phContext) {
    FILE_CONTEXT_TYPE *pFileContext;
    INT status;

    // We need to try and close the file associated with the
    // context handle...

    // Context handle can not be NULL in this section, so we can
    // go ahead and try closing the file.
    pFileContext = (FILE_CONTEXT_TYPE *) phContext;
    
    // Also, we do not need to worry about pFileContext->hFile's being
    // null since we checked for it when we opened the file.
    status = CloseHandle(pFileContext->hFile);
    ASSERTE(status != 0);
    
    // And then free the memory taken up by it.
    midl_user_free(phContext);
}

// end FileRepServerProc.cpp
