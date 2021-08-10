/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   Queue.h
* 
*   PURPOSE:    Data structure declaration.
* 
*
*   PUBLIC FUNCTIONS:   
*       AddChange () - Marks that field in the jobs as changed.
*       ClearChanges () - Clears all of the fields flags.
*       IsChanged () - Test for a fields state of change.
*       GetColumnData () - Returns a string representation of the field
*                          data for use in the ListView. 
*       FreeJobs () - Toss the current job list.
*       SetPrinterQueueData () - Update the printer data in the data structure.
*       AddJobData () - Add a new Job to the list.
*       SetJobData () - Update and existing job.
*       UpdateQueue () - Apply the change notification as appropriate. 
*
*   HELPER FUNCTIONS:   
*       AllocQueueData () - Data structure init.
*       FreeQueueData () - Data structure destroy.
*       UpdateJobData () - Apply a Job change notification to the data structure.
*       UpdatePrinterData () - Apply a Printer change notification to the data structure.
*
*   COMMENTS:
*
*           See the actual source file for most comments.
*
******************************************************************************/

/*
 * Indices for the fields of interest
 * These indices correspond directly to the column position of the 
 * data as it is shown in the derived ListView control: QueList.
 * They are also the index parameter to GetColumnData().
 */
#define DOCUMENTNAME    0
#define OWNERNAME       1
#define STATUS          2
#define SUBMITTED       3
#define PROGRESS        4
#define NFIELDS         5


/*
 * Current state of the Printer Queue we are watching
 */
typedef struct _Printer
{
    LPTSTR  pszPrinterName; // The shell "friendly" name
    LPTSTR  pszServerName;  // The server of the printer
    LPTSTR  pszShareName;   // The share for the printer
    DWORD   dwStatus;       // Current status of the printer
    DWORD   cJobs;          // # of jobs currently in the printer
    HANDLE  hPrinter;       // An open handle to the printer
} PRINTERDATA;

/*
 * Current state of a particular job in the queue.
 */
typedef struct _Job
{
    // members of the JOB_INFO_* structure we are interested in.
    // Copy them here for safekeeping between updates
    DWORD       JobId;
    LPTSTR      pszDocument;    //DOCUMENTNAME
    LPTSTR      pszOwner;       //OWNERNAME

    LPTSTR      pszStatus;      //STATUS
    DWORD       dwStatus;

    DWORD       PagesPrinted;   //PROGRESS
    DWORD       TotalPages;
    DWORD       Size;
    DWORD       BytesPrinted;

    SYSTEMTIME  Submitted;      //SUBMITTED

    // Keep track of what parts change on each update.
    // Usefull for altering only that piece of data
    // in the ListView control
    BOOL        Changed[NFIELDS];
} JOBDATA;


/*
 * Top of the data structure
 */
typedef struct _Queue
{
    PRINTERDATA Printer;
    DWORD       nJobs;
    DWORD       nAllocated;
    JOBDATA     *pJobs;
} QUEUEDATA;


/*
 * Functions for recording changes in the data structure
 */
void AddChange(JOBDATA *pJob, WORD Change);
void ClearChanges(JOBDATA *pJob);
BOOL IsChanged(JOBDATA *pJob, WORD Change);

/*
 * Accessing the data by Columnal semantic meaning
 */
char *GetColumnData(JOBDATA *pJob, unsigned short iCol);

/*
 * Basic data structure manipulation
 */
BOOL AllocQueueData(QUEUEDATA *pQueueData, DWORD nJobs);
void FreeQueueData(QUEUEDATA *pQueueData);
void FreeJobs(QUEUEDATA *pQueueData);
BOOL SetPrinterQueueData(QUEUEDATA *pQueueData, PRINTER_INFO_2 *pPI);
BOOL AddJobData(QUEUEDATA *pQueueData, JOB_INFO_2 *pJI);
BOOL SetJobData(QUEUEDATA *pQueueData, JOB_INFO_2 *pJI);

/*
 * Process Printer Notifictions.
 */
BOOL UpdateJobData(QUEUEDATA *pQueueData, PRINTER_NOTIFY_INFO_DATA *pPNID);
BOOL UpdatePrinterData(QUEUEDATA *pQueueData, PRINTER_NOTIFY_INFO_DATA *pPNID);
BOOL UpdateQueue(QUEUEDATA *pQueueData, PRINTER_NOTIFY_INFO *pPNI);

/* end of header file Queue.h */
