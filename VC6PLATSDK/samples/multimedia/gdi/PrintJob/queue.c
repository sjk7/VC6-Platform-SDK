/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   Queue.c
* 
*   PURPOSE:    Data structure implementation.
* 

    FUNCTIONS:

    ReplaceString() - Utility function that reallocates string space and copies
                      the string to a target string pointer.

    FreeJob() - Frees and Initializes a JOBDATA structure.

    NewJob() - Creates a new JOBDATA structure given data from the spooler.

    FindJob() - Finds a job in the queue.

    AddChange() - Marks a part of a job's data as having changed.

    ClearChanges() - Clears all marked changes in a job's data.

    IsChanged() - Tests some part of a job's data for having changed.

    GetColumnData() - Returns a formatted string representing some part of
                      a job's data based upon presentation column.

    AllocQueueData() - Allocates or Reallocates a QUEUEDATA data structure.

    FreeQueueData() - Frees a QUEUEDATA data structure.

    FreeJobs() - Frees all of the jobs from a queue.

    SetPrinterQueueData() - Sets the printer information for a queue.

    AddJobData() - Adds a new job to the queue.

    SetJobData() - Finds or Adds a job and sets its data.

    UpdateJobData() - Processes a printer notification and updates an job that
                      is in the queue.

    UpdatePrinterData() - Processes a printer notification and updates the
                          printer data.

    COMMENTS:

            This module uses C Runtime memory allocation routines to allocate and
            or reallocate memory.

            This module simply implements a custom data structure for tracking
            printer queue information.

******************************************************************************/

#define STRICT
#include <Windows.h>
#include "Queue.h"
#include "QueCore.h"
#include "QueList.H"


/****************************************************************************
*                           Module private functions.
****************************************************************************/


/****************************************************************************

    FUNCTION:   ReplaceString( char **, char * )


    PURPOSE:   Copies the char * into the char * pointed to by the char **. 

    COMMENTS:

            *(char **) is freed and then allocated as appropriate to hold 
            char *. NULL is valid for *(char **) and simply causes an
            allocation.

****************************************************************************/

static BOOL ReplaceString(char **ppStr, char *pSrcStr)
{
    char *pNewStr;

    /*
     * OK, why not, propagate the NULL value.
     */
    if (pSrcStr == NULL)
    {
        free (*ppStr);
        *ppStr = NULL;
        return TRUE;
    }

    /* Make a copy of the source */
    pNewStr = (char *)malloc(lstrlen(pSrcStr)+1);
    /* bad thing happened, bail */
    if (pNewStr == NULL) 
        return FALSE;
    lstrcpyn(pNewStr, pSrcStr, lstrlen(pSrcStr)+1);

    /* cleanup previous String */
    free (*ppStr);
    
    /* send it back to caller */
    *ppStr = pNewStr;

    return TRUE;

} /* end of function ReplaceString */


/****************************************************************************

    FUNCTION:   FreeJob( JOBDATA * )


    PURPOSE:   Frees up the contents of JOBDATA * and initializes the 
               structure.

    COMMENTS:

            The resulting structure is clean (i.e. it is initialized to NULL.

****************************************************************************/

static void FreeJob(JOBDATA *pJob)
{
    free (pJob->pszDocument);
    free (pJob->pszOwner);
    free (pJob->pszStatus);
    ZeroMemory(pJob, sizeof(JOBDATA));
    
} /* end of function FreeJob */


/****************************************************************************

    FUNCTION:   NewJob( JOBDATA *, JOB_INFO_2 * )


    PURPOSE:   Given job data from the spooler it copies data into the JOBDATA
               structure.

    COMMENTS:

            This function allocates memory and attaches it to JOBDATA.

****************************************************************************/

static BOOL NewJob(JOBDATA *pJob, JOB_INFO_2 *pJI)
{
    /* pJob assumed uninitilazed */
    ZeroMemory(pJob, sizeof(JOBDATA));
    
    
    /* Copy the data we want */
    pJob->JobId = pJI->JobId;
    
    if (!ReplaceString(&pJob->pszDocument, pJI->pDocument))
        goto Fail;
    if (!ReplaceString(&pJob->pszOwner, pJI->pUserName))
        goto Fail;
    if (!ReplaceString(&pJob->pszStatus, pJI->pStatus))
        goto Fail;

    pJob->dwStatus = pJI->Status;
    pJob->PagesPrinted = pJI->PagesPrinted;
    pJob->TotalPages = pJI->TotalPages;
    pJob->Size = pJI->Size;
    pJob->Submitted = pJI->Submitted;
    pJob->BytesPrinted = 0;
    
    /* Initialize the changed data to now chagnes */
    memset(&pJob->Changed, (char)TRUE, sizeof(pJob->Changed));

    return TRUE;

/* Bail when failure occurs */
Fail:
    FreeJob(pJob);

    return FALSE;

} /* end of function NewJob */


/****************************************************************************
*                           Module public functions.
****************************************************************************/


/****************************************************************************

    FUNCTION:   FindJob( QUEUEDATA *, DWORD, DWORD )


    PURPOSE:   Finds a job in the QUEUEDATA by job id.

    COMMENTS:
        
        Returns the position of the job in the queue in pAt.

****************************************************************************/

static BOOL FindJob(QUEUEDATA *pQueueData, DWORD JobId, DWORD *pAt)
{
    DWORD i;

    /* find the job in the queue */
    for (i=0; i < pQueueData->nJobs; i++)
    {
        if (pQueueData->pJobs[i].JobId == JobId)
            break;
    }

    if (i >= pQueueData->nJobs)
        return FALSE;       /* Not found in our queue data */

    *pAt = i;
    return TRUE;

} /* end of function FindJob */

/****************************************************************************

    FUNCTION:   AddChange( JOBDATA *, WORD )


    PURPOSE:   Marks the data in the JOBDATA that has changed.

    COMMENTS:
        
****************************************************************************/

void AddChange(JOBDATA *pJob, WORD Change)
{
    pJob->Changed[Change] = TRUE;

} /* end of function AddChange */


/****************************************************************************

    FUNCTION:   ClearChanges( JOBDATA * )


    PURPOSE:   Clears all of the changes marked in the JOBDATA.

    COMMENTS:
        
****************************************************************************/

void ClearChanges(JOBDATA *pJob)
{
    ZeroMemory(pJob->Changed, sizeof(pJob->Changed));

} /* end of function ClearChanges */


/****************************************************************************

    FUNCTION:   IsChanged( JOBDATA *, WORD Change )


    PURPOSE:   Tests to see if a part of the JOB has been changed.

    COMMENTS:
        
****************************************************************************/

BOOL IsChanged(JOBDATA *pJob, WORD Change)
{
    return pJob->Changed[Change];

} /* end of function IsChanged */


/****************************************************************************

    FUNCTION:   GetColumnData( JOBDATA *, unsigned short iCol )


    PURPOSE:   Returns a string representation of a part of the job which is
               to appear in a coloumn of the display.

    COMMENTS:
        
        iCol is the column index corresponding ot the columns created in the
        ListView control.

        The function allocates a string buffer and returns it to the caller.
        The caller is responsible for deleting the memory returned to it.
        
****************************************************************************/

char *GetColumnData(JOBDATA *pJob, unsigned short iCol)
{
    char *pStr = NULL;
    char Buffer[100];

    switch (iCol)
    {
        case DOCUMENTNAME:
        {
            ReplaceString(&pStr, pJob->pszDocument);
            break;
        }
        case OWNERNAME:
        {
            ReplaceString(&pStr, pJob->pszOwner);
            break;
        }
        case STATUS:
        {
            if (pJob->pszStatus != NULL && lstrlen(pJob->pszStatus))
            {
                ReplaceString(&pStr, pJob->pszStatus);
            }
            else 
            {
                MakeJobStatusStr(Buffer, sizeof(Buffer), pJob->dwStatus);
                ReplaceString(&pStr, Buffer);
            }
            break;
        }
        case SUBMITTED:
        {
            wsprintf(Buffer, 
                    "%02u/%02u/%u - %02u:%02u", 
                    pJob->Submitted.wMonth, 
                    pJob->Submitted.wDay,
                    (pJob->Submitted.wYear-((pJob->Submitted.wYear/100)*100)),
                    pJob->Submitted.wHour,
                    pJob->Submitted.wMinute);
            ReplaceString(&pStr, Buffer);
            break;
        }
        case PROGRESS:
        {
            if (pJob->PagesPrinted == 1)
                wsprintf(Buffer, "%u page of %u Pages, %u bytes of %u Total Bytes", pJob->PagesPrinted, pJob->TotalPages, pJob->BytesPrinted, pJob->Size);
            else
                wsprintf(Buffer, "%u pages of %u Pages, %u bytes of %u Total Bytes", pJob->PagesPrinted, pJob->TotalPages, pJob->BytesPrinted, pJob->Size);
            ReplaceString(&pStr, Buffer);
            break;
        }
        default:
        {
            ReplaceString(&pStr, "");
            break;
        }
    }

    return pStr;
    
} /* end of function GetColumnData */


/****************************************************************************

    FUNCTION:   AllocQueueData( QUEUEDATA *, DWORD nJobs )


    PURPOSE:   Allocates or Reallocates a QUEUEDATA data structure to hold
                Print QUEUE information.

    COMMENTS:
        
        AllocQueueData initializes the additional data space to all zeroes.
        
****************************************************************************/

BOOL AllocQueueData(QUEUEDATA *pQueueData, DWORD nJobs)
{
    QUEUEDATA   NewData;

    /* if we are to realloc, it should be expansion */
    if (nJobs < pQueueData->nAllocated)
        return FALSE;
    
    /* short cut the trivial */
    if (nJobs == pQueueData->nAllocated)
        return TRUE;
    
    /* Allocate a new Queue */
    ZeroMemory(&NewData, sizeof(NewData));
    NewData.pJobs = (JOBDATA *)realloc(pQueueData->pJobs, sizeof(JOBDATA) * nJobs);
    if (NewData.pJobs == NULL && nJobs)
    {
        return FALSE;
    }
    NewData.nJobs = pQueueData->nJobs;
    NewData.nAllocated = nJobs;
    NewData.Printer = pQueueData->Printer;
    
    /* Initialize the new allocated data space */
    ZeroMemory(&NewData.pJobs[NewData.nJobs], sizeof(JOBDATA)*(NewData.nAllocated-NewData.nJobs));

    *pQueueData = NewData;

    return TRUE;

} /* end of function AllocQueueData */


/****************************************************************************

    FUNCTION:   FreeQueueData( QUEUEDATA * )


    PURPOSE:   Deallocates a QUEUEDATA data structure.

    COMMENTS:
        
****************************************************************************/

void FreeQueueData(QUEUEDATA *pQueueData)
{
    FreeJobs(pQueueData);
    free (pQueueData->Printer.pszPrinterName);
    free (pQueueData->Printer.pszServerName);
    free (pQueueData->Printer.pszShareName);
    free (pQueueData->pJobs);
    ZeroMemory(pQueueData, sizeof(QUEUEDATA));
} /* end of function FreeQueueData */


/****************************************************************************

    FUNCTION:   FreeJobs( QUEUEDATA * )


    PURPOSE:   Deallocates the jobs contained in a QUEUEDATA data structure.

    COMMENTS:
        
****************************************************************************/

void FreeJobs(QUEUEDATA *pQueueData)
{
    DWORD   i;

    for (i=0; i < pQueueData->nJobs; i++)
    {
        FreeJob(&pQueueData->pJobs[i]);
    }
    free (pQueueData->pJobs);
    pQueueData->pJobs = NULL;
    pQueueData->nJobs = pQueueData->nAllocated = 0;
} /* end of function FreeJobs */


/****************************************************************************

    FUNCTION:   SetPrinterQueueData( QUEUEDATA *, PRINTER_INFO_2 * )


    PURPOSE:   Sets the printer data that is kept by the QUEUEDATA data 
                structure.

    COMMENTS:
        
****************************************************************************/

BOOL SetPrinterQueueData(QUEUEDATA *pQueueData, PRINTER_INFO_2 *pPI)
{
    PRINTERDATA pd;

    if (pPI == NULL)
        return FALSE;
    
    /* Initialize and copy pertinent data */
    ZeroMemory(&pd, sizeof(pd));

    ReplaceString(&pd.pszPrinterName, pPI->pPrinterName);
    ReplaceString(&pd.pszServerName, pPI->pServerName);
    ReplaceString(&pd.pszShareName, pPI->pShareName);

    pd.dwStatus = pPI->Status;
    pd.cJobs = pPI->cJobs;
    pd.hPrinter = pQueueData->Printer.hPrinter;

    /* Cleanup previous printer data */
    free (pQueueData->Printer.pszPrinterName);
    free (pQueueData->Printer.pszServerName);
    free (pQueueData->Printer.pszShareName);

    /* copy it */
    pQueueData->Printer = pd;
    return TRUE;
    
} /* end of function SetPritnerQueueData */


/****************************************************************************

    FUNCTION:   AddJobData( QUEUEDATA *, JOB_INFO_2 * )


    PURPOSE:   Appends the job to the queue data structure.

    COMMENTS:
        
****************************************************************************/

BOOL AddJobData(QUEUEDATA *pQueueData, JOB_INFO_2 *pJI)
{

    /* allocated more space if necessary */
    if (pQueueData->nJobs == pQueueData->nAllocated)
        if (!AllocQueueData(pQueueData, pQueueData->nAllocated+1))
            return FALSE;
    
    /* Add the Job at the end */
    if (!NewJob(&pQueueData->pJobs[pQueueData->nJobs], pJI))
        return FALSE;

    pQueueData->nJobs++;

    return TRUE;

} /* end of function AddJobData */


/****************************************************************************

    FUNCTION:   SetJobData( QUEUEDATA *, JOB_INFO_2 * )


    PURPOSE:   Locates the job in the queue and updates its data.

    COMMENTS:
                If the job is not located in the queue the function returns
                FALSE;
        
****************************************************************************/

BOOL SetJobData(QUEUEDATA *pQueueData, JOB_INFO_2 *pJI)
{
    DWORD i;
    JOBDATA jd;

    if (!FindJob(pQueueData, pJI->JobId, &i))
        return FALSE;

    /* make a new one */
    if (!NewJob(&jd, pJI))
        return FALSE;
    
    /* cleanup previous version */
    FreeJob(&pQueueData->pJobs[i]);
    
    /* copy new data */
    pQueueData->pJobs[i] = jd;

    return TRUE;

} /* end of function SetJobData */


/****************************************************************************

    FUNCTION:   UpdateJobData( QUEUEDATA *, PRINTER_NOTIFY_INFO_DATA * )


    PURPOSE:   Updates the job data identified by the notify information.

    COMMENTS:
                This function checks for the right notification data and 
                returns FALSE if it is not correct.

                If the job in the notification information is not found,
                a new one is created in the queue.

                As each piece of a Job's data is updates it is marked in 
                the data structure as having been changed.
        
****************************************************************************/

BOOL UpdateJobData(QUEUEDATA *pQueueData, PRINTER_NOTIFY_INFO_DATA *pPNID)
{
    DWORD       i;
    BOOL        fSuccess = FALSE;
    JOB_INFO_2  ji;

    /* check for the right notification type */
    if (pPNID->Type != JOB_NOTIFY_TYPE)
        return FALSE;

    if (!FindJob(pQueueData, pPNID->Id, &i))
    {
        /* didn't find job so possibly a new one */
        /* add an entry that can be updated now and later */
        ZeroMemory(&ji, sizeof(ji));
        ji.JobId = pPNID->Id;
        if (!AddJobData(pQueueData, &ji))
            return FALSE;
        if (!FindJob(pQueueData, pPNID->Id, &i))
            return FALSE;
    }

    /* Update members based on the advertised change */
    switch (pPNID->Field)
    {
        case JOB_NOTIFY_FIELD_STATUS:
        {
            pQueueData->pJobs[i].dwStatus = pPNID->NotifyData.adwData[0];
            fSuccess = TRUE;
            AddChange(&pQueueData->pJobs[i], STATUS);
            break;
        }
        case JOB_NOTIFY_FIELD_STATUS_STRING:
        {
            fSuccess = ReplaceString(&pQueueData->pJobs[i].pszStatus, pPNID->NotifyData.Data.pBuf);
            AddChange(&pQueueData->pJobs[i], STATUS);
            break;
        }
        case JOB_NOTIFY_FIELD_USER_NAME:
        {
            fSuccess = ReplaceString(&pQueueData->pJobs[i].pszOwner, pPNID->NotifyData.Data.pBuf);
            AddChange(&pQueueData->pJobs[i], OWNERNAME);
            break;
        }
        case JOB_NOTIFY_FIELD_DOCUMENT:
        {
            fSuccess = ReplaceString(&pQueueData->pJobs[i].pszDocument, pPNID->NotifyData.Data.pBuf);
            AddChange(&pQueueData->pJobs[i], DOCUMENTNAME);
            break;
        }
        case JOB_NOTIFY_FIELD_PAGES_PRINTED:
        {
            pQueueData->pJobs[i].PagesPrinted = pPNID->NotifyData.adwData[0];
            AddChange(&pQueueData->pJobs[i], PROGRESS);
            break;
        }
        case JOB_NOTIFY_FIELD_TOTAL_PAGES:
        {
            pQueueData->pJobs[i].TotalPages = pPNID->NotifyData.adwData[0];
            AddChange(&pQueueData->pJobs[i], PROGRESS);
            break;
        }
        case JOB_NOTIFY_FIELD_TOTAL_BYTES:
        {
            pQueueData->pJobs[i].Size = pPNID->NotifyData.adwData[0];
            AddChange(&pQueueData->pJobs[i], PROGRESS);
            break;
        }
        case JOB_NOTIFY_FIELD_BYTES_PRINTED:
        {
            pQueueData->pJobs[i].BytesPrinted = pPNID->NotifyData.adwData[0];
            AddChange(&pQueueData->pJobs[i], PROGRESS);
            break;
        }
        case JOB_NOTIFY_FIELD_SUBMITTED:
        {
            pQueueData->pJobs[i].Submitted = *(SYSTEMTIME*) pPNID->NotifyData.Data.pBuf;
            AddChange(&pQueueData->pJobs[i], SUBMITTED);
            break;
        }
    }

    return fSuccess;

} /* end of function UpdateJobData */


/****************************************************************************

    FUNCTION:   UpdatePrinterData( QUEUEDATA *, PRINTER_NOTIFY_INFO_DATA * )


    PURPOSE:   Updates the printer data identified by the notify information.

    COMMENTS:
                This function checks for the right notification data and 
                returns FALSE if it is not correct.

****************************************************************************/

BOOL UpdatePrinterData(QUEUEDATA *pQueueData, PRINTER_NOTIFY_INFO_DATA *pPNID)
{
    BOOL    fSuccess = FALSE;

    /* make sure we are processing printer data */
    if (pPNID->Type != PRINTER_NOTIFY_TYPE)
        return FALSE;

    /* update the change as advertised */
    switch (pPNID->Field)
    {
        case PRINTER_NOTIFY_FIELD_PRINTER_NAME:
        {
            fSuccess = ReplaceString(&pQueueData->Printer.pszPrinterName, pPNID->NotifyData.Data.pBuf);
            break;
        }
        case PRINTER_NOTIFY_FIELD_SHARE_NAME:
        {
            fSuccess = ReplaceString(&pQueueData->Printer.pszShareName, pPNID->NotifyData.Data.pBuf);
            break;
        }
        case PRINTER_NOTIFY_FIELD_SERVER_NAME:
        {
            fSuccess = ReplaceString(&pQueueData->Printer.pszServerName, pPNID->NotifyData.Data.pBuf);
            break;
        }
        case PRINTER_NOTIFY_FIELD_STATUS:
        {
            pQueueData->Printer.dwStatus = pPNID->NotifyData.adwData[0];
            fSuccess = TRUE;
            break;
        }
        case PRINTER_NOTIFY_FIELD_CJOBS:
        {
            pQueueData->Printer.cJobs = pPNID->NotifyData.adwData[0];
            fSuccess = TRUE;
            break;
        }
    }

    return fSuccess;

} /* end of function UpdatePrinterData */

/* end of source file Queue.C */
