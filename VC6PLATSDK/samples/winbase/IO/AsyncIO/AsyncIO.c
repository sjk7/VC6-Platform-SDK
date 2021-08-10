/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1992 - 2000.  Microsoft Corporation.  All rights reserved.

Module Name:

    AsyncIO.c

Abstract:

    This is the main source file for the AsyncIO API demonstration
    program.  This program demonstrates how to use many of the advanced
    operating system features provided by the Win32 API set on Windows/NT.

    This file and its corresponding header file, AsyncIO.h, can be found
    in the sample programs directory of the Platform SDK.

    This program has a real purpose, although the implementation is
    somewhat contrived in order to demonstrate the various operating
    system features of Windows/NT.

    The features that this program demonstrate are:

        - Creating multiple threads, using critical sections
          and semaphores for synchronization.

        - Thread termination.

        - Virtual memory, commitment vs reservation.

        - Structured exception handling, including finally
          clauses and an exception filter procedure.

        - Enumeration of directory entries.

        - Mapped file I/O

        - Asynchronous file I/O via completion routine.

        - Synchronous file I/O

    AsyncIO is a character mode program for searching the files in a
    directory tree for a match against a pattern.  It uses multiple
    threads to do its work, with each thread processing a file at a
    time, accumulating its matches and outputting them to standard
    output contiguously when it is done searching a file.

    The command line syntax is:

        Usage: AsyncIO [-h] [-v] [-y] [-a | -s | -m] [-t n] SearchString [DirectoryPath]

        where:

            -h - prints this message.

            -v - generates verbose output.

            -y - ignores case when doing comparisons.

            -a - specifies that the program should use asynchronous file
                 I/O to read the files being searched.

            -s - specifies that the program should use synchronous file
                 I/O to read the files being searched.

            -m - specifies that the program should use mapped file I/O
                 to read the files being searched.

            -t - specifies the number of threads to use when doing the
                 search.  Default is 4 * the number of processors. The 
                 number never exceeds MAXIMUM_WORKER_THREADS, which is
                 currently defined to be 128.

            SearchString - specifies the text to search for.  Enclose in
                           quotes if it contains spaces or punctuation.

            DirectoryPath - specifies the root of the tree to begin the
                            search at.  Defaults to the current directory.


--*/

#ifdef _IA64_
#pragma warning(disable:4100 4127 4702 4706)
#endif

#include "AsyncIO.h"

int
main(
    int argc,
    char *argv[]
    )

/*++

Routine Description:

    This is the main procedure for the AsyncIO program, and is called by
    the C Runtime startup code when the program starts.

Arguments:

    argc - number of argumments in the argv array.

    argv - pointer to an array of null terminated string pointers.

Return Value:

    Process exit status.  The value returned by this function will
    be used as the exit code parameter passed to ExitProcess.

--*/

{
   SYSTEM_INFO SystemInformation;
   PWORK_QUEUE WorkQueue;

   //
   // Query the number of processors from the system and set the default
   // number of worker threads to 4 times the number of processors or
   // MAXIMUM_WORKER_THREADS, whichever is smaller.
   //

   GetSystemInfo( &SystemInformation );
   NumberOfWorkerThreads = SystemInformation.dwNumberOfProcessors * 4;
   if (NumberOfWorkerThreads > MAXIMUM_WORKER_THREADS)
   {
       NumberOfWorkerThreads = MAXIMUM_WORKER_THREADS;
   }

   //
   // Process the arguments given on the command line.
   //

   if (!ProcessCommandLineArguments( argc, argv ))
   {
      exit( 1 );
   }

   //
   // Allocate a thread local storage slot for use by our worker
   // thread routine (ProcessRequest).  This call reserves a
   // 32-bit slot in the thread local storage array for every
   // thread in this process.  Remember the slot index in a global
   // variable for use by our worker thread routine.
   //

   TlsIndex = TlsAlloc();
   if (TlsIndex == TLS_OUT_OF_INDEXES)
   {
      fprintf( stderr, "AsyncIO: Unable to allocated thread local storage.\n" );
      exit( 1 );
   }

   //
   // If asynchronous I/O is used, create an event that will be signalled
   // when there are no more outstanding I/O requests. The event is a
   // manual reset event, that once signalled via SetEvent, will remain
   // signalled until ResetEvent is called.
   //

   if (ASyncIO)
   {
      IoCompletedEvent = CreateEvent( NULL,   // Not inherited
                                      TRUE,   // Manual reset
                                      FALSE,  // Initially reset
                                      NULL    // No name
                                     );
      if (IoCompletedEvent == NULL)
      {
         fprintf( stderr, "AsyncIO: Unable to create the event needed for asynchronous I/O.\n");
         exit( 1 );
      }
   }

   //
   // Create a work queue and the specified number of threads which will
   // process the work items in the queue and the routine which will do
   // the processing.
   //

   WorkQueue = CreateWorkQueue( NumberOfWorkerThreads, ProcessRequest );
   if (WorkQueue == NULL)
   {
      fprintf( stderr, "AsyncIO: Unable to create %u worker threads.\n", NumberOfWorkerThreads );
      exit( 1 );
   }

   //
   // Now walk the directory tree, which will call our procedure
   // QueueSearchFile for each directory and file in the tree.
   //

   if (EnumerateDirectoryTree( DirectoryPath,
                               QueueSearchFile,
                               WorkQueue
                             ) == FALSE)
   {
      //
      // The search failed for some reason. Destroy the work queue.
      // The system will close the IoCompletedEvent handle when we
      // exit.
      //
      
      DestroyWorkQueue ( WorkQueue );
      exit(1);
   }
       
   //
   // Done walking the tree.  If asynchronous I/O is used, wait for all
   // all the outstanding I/O requests to be completed.
   //

   if (ASyncIO)
   {
      //
      // We use an alertable wait in a loop. I/O completion will 
      // terminate the wait, even through the event we are waiting
      // on is not signalled.
      //

      while (WaitForSingleObjectEx( IoCompletedEvent, // Event waited on
                                    INFINITE,         // No timeout
                                    TRUE              // Alertable
                                  ) == WAIT_IO_COMPLETION
            )
      {
         NOTHING;
      }
   }

   //
   // All done, destroy the work queue. This function will wait until
   // the work queue is empty and all the worker threads have exited
   // and then it will destroy the queue.
   //

   DestroyWorkQueue( WorkQueue );

   if (Verbose && MatchedLineCount)
   {
      fprintf( stderr,
               "Found %u lines with matches in %u files, out of %u files searched.\n",
               MatchedLineCount,
               MatchedFileCount,
               SearchedFileCount
             );
   }

   return 0;
}


VOID
QueueSearchFile(
               LPSTR Path,
               PWIN32_FIND_DATA FindFileData,
               PVOID EnumerateParameter
               )

/*++

Routine Description:

    This is the directory enumeration function.  It is called by the
    EnumerateDirectoryTree function once for each file and directory
    in the tree.

    This function, if it decides it wants to search the file, will 
    open the file and then, depending upon the I/O method selected via
    the command line, will:

        - map the file PAGE_READONLY for mapped file I/O,

        - read the file into an allocated buffer for synchronous
          I/O, or

        - for asynchronous I/O, allocate a buffer and start a read 
          operation to read the entire file into the buffer.  A 
          completion routine will be invoked when the read completes, 
          possibly in another thread context.

    Finally it will queue a search request to the work queue, with the
    relevant information contained in the request.  For asynchronous
    I/O, the search request is allocated and initialized here but is
    not actually queued to the work queue until the I/O completion
    routine has been called.

Arguments:

    Path - Supplies a pointer to a null terminated string that contains
        the fully qualified path of the file or directory.

    FindFileData - Supplies the directory information associated
        with the file or directory specified by the Path argument.

    EnumerateParameter - Uninterpreted 32-bit value. 

Return Value:

    None.

--*/

{
   PWORK_QUEUE WorkQueue = (PWORK_QUEUE)EnumerateParameter;
   PSEARCH_REQUEST SearchRequest;
   HANDLE File;
   HANDLE Mapping;
   LPVOID FileData;
   DWORD FileSize;
   SIZE_T PathLength;

   //
   // Ignore directories or zero length files, as there 
   // is nothing to search in these cases.
   //

   if ((FindFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ||
       !(FileSize = FindFileData->nFileSizeLow)
      )
   {
      return;
   }

   //
   // Open the file using the fully qualified path.  Specify the
   // sequential scan hint to the cache manager and GENERIC_READ 
   // access to the file. If asynchronous I/O is used, specify 
   // file overlapped flag.
   //

   File = CreateFile( Path,
                      GENERIC_READ,
                      FILE_SHARE_READ,
                      NULL,
                      OPEN_EXISTING,
                      FILE_FLAG_SEQUENTIAL_SCAN |
                      (ASyncIO ? FILE_FLAG_OVERLAPPED : 0),
                      NULL
                    );

   //
   // Since NULL might be a valid file object handle, failure
   // is indicated by a special return value.
   //

   if (File == INVALID_HANDLE_VALUE)
   {
      fprintf( stderr, "%s(0) : error %u: Unable to open file.\n",
               Path,
               GetLastError()
             );

      return;
   }

   //
   // File successfully opened for read access.
   //

   if (MappedFileIO)
   {
      //
      // If mapped file I/O, create a file mapping object, backed by
      // the file we just opened.  Make the default page protection
      // for the mapping be read only.
      //

      Mapping = CreateFileMapping( File,
                                   NULL,
                                   PAGE_READONLY,
                                   0,
                                   0,
                                   NULL
                                 );

      //
      // Okay to close the file handle now, since the mapping object
      // has a reference to the file that will cause the open file
      // object to remain until the reference is destroyed. Note that
      // any sharing information is lost at this point, so somebody
      // could come in and open it for write access.
      //

      CloseHandle( File );

      //
      // Here, a null value indicates an error.
      //

      if (Mapping == NULL)
      {
         fprintf( stderr, "%s(0) : error %u: Unable to create mapping object.\n",
                  Path,
                  GetLastError()
                );
         return;
      }

      //
      // Finally, map a view of the file, using the mapping object
      // just created, into the address space of this process. 
      // The offset and size are zero, which means to map the
      // entire file.
      //

      FileData = MapViewOfFile( Mapping,
                                FILE_MAP_READ,
                                0,
                                0,
                                0
                              );

      //
      // Okay to close the mapping object handle now, it will remained
      // referenced as long as the view remains mapped.
      //

      CloseHandle( Mapping );

      //
      // A null value indicates the map operation failed.
      //

      if (FileData == NULL)
      {
         fprintf( stderr, "%s(0) : error %u: Unable to map file.\n",
                  Path,
                  GetLastError()
                );
         return;
      }

      //
      // All done mapping the file.  Set the File handle to NULL as 
      // it has been closed already.  Both the file object and mapping
      // objects created above will be freed when the map view is
      // unmapped.
      //

      File = NULL;
   }
   else
   {
      //
      // Mapped I/O will not be used. So allocate a buffer big enough 
      // to contain the entire file.
      //

      FileData = VirtualAlloc( NULL,
                               FileSize,
                               MEM_COMMIT,
                               PAGE_READWRITE
                             );
      if (FileData == NULL)
      {
         fprintf( stderr, "%s(0) : error %u: Unable to allocate memory to contain file.\n",
                  Path,
                  GetLastError()
                );
         CloseHandle( File );
         return;
      }
   }

   //
   // Note that Path points to a null terminated string produced
   // by our function EnumerateDirectoryTree. We can find the 
   // length of the string safely using strlen. 
   //

   PathLength = strlen( Path );

   //
   // We have successfully opened the file and are ready to go.
   // Allocate space for a search request and fill it in with
   // the information needed by the ProcessSearchFile function
   // when it runs. 
   // 
   // The space for SearchRequest->FullNameName[0] is provided 
   // within SearchRequest. An additional space of PathLength 
   // characters suffices for Path and null termination. 
   //

   SearchRequest = LocalAlloc( LMEM_ZEROINIT,
                               sizeof( *SearchRequest ) + PathLength
                             );
   if (SearchRequest == NULL)
   {
      fprintf( stderr, "AsyncIO: Out of memory\n" );
      exit( 1 );
   }

   SearchRequest->WorkItem.Reason = WORK_ITEM;
   SearchRequest->File = File;
   SearchRequest->FileSize = FileSize;
   SearchRequest->FileData = FileData;
   strncpy( SearchRequest->FullPathName, Path, PathLength );
   SearchRequest->FullPathName[ PathLength ] = '\0';

   if (!ASyncIO)
   {
      
      //
      // Asynchronous I/O is not used. Queue the search
      // request to the work queue.
      //

      QueueWorkItem( WorkQueue, &SearchRequest->WorkItem );
   }
   else
   {
      //
      // Asynchronous I/O is used. Queue the read operation.
      // The file handle must remain open while the read 
      // operation is pending.
      //

      if (!ReadFileEx( File,
                       FileData,
                       FileSize,
                       &SearchRequest->OverlappedIO,
                       (LPOVERLAPPED_COMPLETION_ROUTINE) ProcessReadFileCompletion
                     )
         )
      {
         fprintf( stderr, "%s(0) : error %u: Unable to queue read of file.\n",
                  Path,
                  GetLastError()
                );

         VirtualFree( FileData, 0, MEM_RELEASE );
         CloseHandle( File );
         LocalFree( SearchRequest );
         return;
      }

      //
      // Successfully queued the read operation.  Keep a count
      // of outstanding read operations so we know when it is
      // okay to terminate.
      //

      OutstandingIOOperations += 1;
   }

   //
   // Return back to the EnumerateDirectoryTree function so that it
   // can call us with the next file or directrry.
   //

   return;
}


VOID
ProcessRequest(
              IN PWORK_QUEUE_ITEM WorkItem
              )

/*++

Routine Description:

    This function is called whenever a work item is removed from
    the work queue by one of the worker threads.  Which worker
    thread context this function is called in is arbitrary.

    This functions keeps a pointer to state information in
    thread local storage.

    This function is called once at the beginning with a
    special initialization call.  During this call, this
    function allocates space for state information and
    remembers the pointer to the state information in
    a Thread Local Storage (TLS) slot.

    This function is called once at the end with a special
    termination call.  During this call, this function
    frees the state information allocated during the
    initialization call.

    In between these two calls are zero or more calls to
    handle a work item.  The work item is a search request
    which is handled by the ProcessSearchFile function.

Arguments:

    WorkItem - Supplies a pointer to the work item just removed
        from the work queue.  It is the responsibility of this
        routine to free the memory used to hold the work item.

Return Value:

    None.

--*/

{
   DWORD BytesWritten;
   PSEARCH_REQUEST_STATE State;
   PSEARCH_REQUEST SearchRequest;
   CHAR MessageBuffer[ 2 * MAX_PATH ];

   if (WorkItem->Reason == WORK_INITIALIZE_ITEM)
   {
      //
      // First time initialization call.  Allocate space for
      // state information.
      //

      State = LocalAlloc( LMEM_ZEROINIT,
                          sizeof( *State )
                        );

      if (State != NULL)
      {
         //
         // Now create a virtual buffer, with an initial commitment
         // of zero and a maximum commitment of 128KB.  This buffer
         // will be used to accumulate the matched strings output
         // during the search of a single file.  This is so the
         // output can be written to standard output with a single
         // write call, thus insuring that it remains contiguous
         // in the output stream, and is not intermingled with the
         // output of the other worker threads.
         //

         if (CreateVirtualBuffer( &State->Buffer, (SIZE_T) 0, (SIZE_T) (2 * 64 * 1024) ))
         {
            //
            // The CurrentOutput field of the state block is
            // a pointer to where the next output goes in the
            // buffer.  It is initialized here and reset each
            // time the buffer is flushed to standard output.
            //

            State->CurrentOutput = State->Buffer.Base;
         }
         else
         {
            LocalFree( State );
            State = NULL;
         }
      }

      //
      // Remember the pointer to the state information
      // thread local storage.
      //

      TlsSetValue( TlsIndex, State );
      return;
   }

   //
   // Here to handle a work item or special terminate call.
   // Get the state pointer from thread local storage.
   //

   State = (PSEARCH_REQUEST_STATE)TlsGetValue( TlsIndex );
   if (State == NULL)
   {
      return;
   }

   //
   // If this is the special terminate work item, free the virtual
   // buffer and state block allocated above and set the thread
   // local storage value to NULL.  Return to caller.
   //

   if (WorkItem->Reason == WORK_TERMINATE_ITEM)
   {
      FreeVirtualBuffer( &State->Buffer );
      LocalFree( State );
      TlsSetValue( TlsIndex, NULL );
      return;
   }

   //
   // If not an initialize or terminate work item, then must be a
   // search request.  Calculate the address of the search request
   // block, based on the position of the WorkItem field in the
   // SEARCH_REQUEST structure.
   //

   SearchRequest = CONTAINING_RECORD( WorkItem, SEARCH_REQUEST, WorkItem );

   //
   // Actual search operation is protected by a try ... except
   // block so that any attempts to store into the virtual buffer
   // will be handled correctly by extending the virtual buffer.
   //

   _try {
      //
      // Perform the search against this file.
      //

      ProcessSearchFile( SearchRequest, State );

      //
      // Done with this file.  If asynchronous I/O is used, decrement 
      // the count of outstanding I/O operations. If the count becomes
      // zero, signal the IoCompletedEvent as there are no more outstanding
      // I/O operations.
      //

      if (ASyncIO && InterlockedDecrement( &OutstandingIOOperations ) == 0)
      {
         SetEvent( IoCompletedEvent );
      }

      //
      // If any output was written to the virtual buffer, flush the 
      // output to standard output.  Trim the virtual buffer back to 
      // zero committed pages.
      //

      if (State->CurrentOutput > (LPSTR)State->Buffer.Base)
      {
         WriteFile( GetStdHandle( STD_OUTPUT_HANDLE ),
                    State->Buffer.Base,
                    (DWORD)(State->CurrentOutput - (LPSTR)State->Buffer.Base),
                    &BytesWritten,
                    NULL
                  );

         TrimVirtualBuffer( &State->Buffer );
         State->CurrentOutput = (LPSTR)State->Buffer.Base;
      }
   }

   _except( VirtualBufferExceptionFilter( GetExceptionCode(),
                                          GetExceptionInformation(),
                                          &State->Buffer
                                        )
          )
   {

      //
      // We will get here if the exception filter was unable to
      // commit the memory.
      //
      // Note that FullPathName was generated by our function 
      // QuerySearchFile. It points to a null terminated path 
      // name. 
      //

      WriteFile( GetStdHandle( STD_OUTPUT_HANDLE ),
                 MessageBuffer,
                 sprintf( MessageBuffer,
                          "%s(0) : error 0: too many matches for file\n",
                          SearchRequest->FullPathName
                        ),
                 &BytesWritten,
                 NULL
               );
   }

   //
   // Free the storage used by the SearchRequest
   //

   LocalFree( SearchRequest );

   //
   // All done with this request.  Return to the worker thread that
   // called us.
   //

   return;
}



VOID
ProcessReadFileCompletion(
                         DWORD dwErrorCode,
                         DWORD dwNumberOfBytesTransfered,
                         LPOVERLAPPED lpOverlapped
                         )

/*++

Routine Description:

    This function is called whenever an asynchronous read operation,
    queued by the function QueueSearchFile, completes. This function
    calulates the address of the search request block and then
    queue the request to the work queue, now that the data is
    in memory.

Arguments:

    dwErrorCode - Supplies the error code that the I/O completed with.

    dwNumberOfBytesTransfered - Supplies the actual number of bytes
        transferred.

    lpOverlapped - Supplies a pointer to the structure given to
        ReadFileEx when the I/O operation was queued.

Return Value:

    None.

--*/

{
   PSEARCH_REQUEST SearchRequest;

   //
   // Since the data we need is now in memory, queue the search
   // request to the work queue.
   //

   SearchRequest = CONTAINING_RECORD( lpOverlapped, SEARCH_REQUEST, OverlappedIO );
   QueueWorkItem( SearchRequest->WorkItem.WorkQueue, &SearchRequest->WorkItem );
}



VOID
ProcessSearchFile(
                 IN PSEARCH_REQUEST SearchRequest,
                 IN PSEARCH_REQUEST_STATE State
                 )

/*++

Routine Description:

    This function performs the actual search of the contents of the
    passed file for the search string given on the command line.
    If we are using synchronous I/O, then do the read operation
    now.

    Search the contents of the file for any matches, and accumulate
    the match output in the virtual buffer using sprintf, which is
    multi-thread safe, even with the single threaded version of
    the libraries. 

    Note that this function is called within an exception block. Our
    function VirtualBufferExceptionFilter will be called if uncommitted 
    memory is referenced. That function will either commit additional
    memory and then repeat the faulting instruction or execute the
    caller's exception handler, depending whether additional pages
    can be committed. Therefore, sprintf can be safely used here.

Arguments:

    SearchRequest - Supplies a pointer to the search request which
        contains the relevant information.

    State - Supplies a pointer to state information for the current
        thread.

Return Value:

    None.

--*/

{
   LPSTR FileData, s, s1, BegLine, EndLine, EndOfFile;
   DWORD LineNumber;
   DWORD MatchesFound;
   DWORD BytesRead;

   // Get a pointer to the beginning of the file data in memory
   // and calculate the address of the end of file point in
   // memory.
   //

   FileData = SearchRequest->FileData;
   EndOfFile = FileData + SearchRequest->FileSize;

   //
   // If synchronous I/O is used, then we have not read in the
   // file contents yet, so issue the synchronous read to get
   // the data into memory.
   //

   if (SyncIO)
   {
      if (!ReadFile( SearchRequest->File,
                     FileData,
                     SearchRequest->FileSize,
                     &BytesRead,
                     NULL
                   ) ||
          BytesRead != SearchRequest->FileSize
         )
      {

         State->CurrentOutput += sprintf( State->CurrentOutput,
                                          "%s(0) : error %u: Unable to read file contents.\n",
                                          SearchRequest->FullPathName,
                                          GetLastError()
                                        );

         CloseHandle( SearchRequest->File );
         return;
      }
   }

   //
   // Close any open file handle associated with this request.
   //

   if (SearchRequest->File != NULL)
   {
      CloseHandle( SearchRequest->File );
   }

   //
   // Search the file contents, keeping track of line breaks
   // so we can tell the line number of each match.
   //

   s = FileData;
   LineNumber = 0;
   MatchesFound = 0;
   while (s < EndOfFile)
   {
      BegLine = s;
      while (s < EndOfFile && *s != '\n')
      {
         s++;
      }

      if (*s == '\n')
      {
         LineNumber += 1;
         EndLine = s - 1;
         if (EndLine > BegLine && EndLine[ -1 ] == '\r')
         {
            EndLine -= 1;
         }

         s1 = BegLine;
         while (s1 < (EndLine - SearchStringLength))
         {
            if (!(SearchFunction)( s1, SearchString, SearchStringLength ))
            {
               //
               // We have a match for this line.  Append the
               // output to the virtual buffer and update the
               // current output pointer.
               //

               State->CurrentOutput += sprintf( State->CurrentOutput,
                                                "%s(%u) : %.*s\n",
                                                SearchRequest->FullPathName,
                                                LineNumber,
                                                EndLine - BegLine,
                                                BegLine
                                              );
               MatchesFound += 1;
               break;
            }

            s1++;
         }

         s++;
      }
   }
  
   if (MatchesFound)
   {

      //
      // Increment the global variables that summarize the result
      // of the search. Since these variables may be incremented
      // by multiple worker threads, use atomic add and increment.
      //

      InterlockedExchangeAdd( &MatchedLineCount, MatchesFound );
      InterlockedIncrement( &MatchedFileCount );
   }
   InterlockedIncrement( &SearchedFileCount );

   //
   // All done with the file contents.  Discard it either by
   // unmapping the view of the file in the case of mapped file
   // I/O or free the virtual memory for other types of I/O
   //

   if (MappedFileIO)
   {
      if (!UnmapViewOfFile( FileData ))
      {
         State->CurrentOutput += sprintf( State->CurrentOutput,
                                          "%s(%u) : UnmapViewOfFile( %p ) failed, error == %u\n",
                                          SearchRequest->FullPathName,
                                          LineNumber,
                                          FileData,
                                          GetLastError()
                                        );
      }
   }
   else
   {
      VirtualFree( FileData, 0, MEM_RELEASE );
   }
}


PWORK_QUEUE
CreateWorkQueue(
               IN DWORD NumberOfWorkerThreads,
               IN PWORKER_ROUTINE WorkerRoutine
               )

/*++

Routine Description:

    This function creates a work queue, with the specified number of
    threads to service work items placed in the queue.  Work items
    are removed from the queue in the same order that they are placed
    in the queue.

Arguments:

    NumberOfWorkerThreads - Specifies how many threads this function
        should create to process work items placed in the queue.
        The number must be no greater than MAXIMUM_WORKER_THREAD 
        and greater than 0.

    WorkerRoutine - Specifies the address of a routine to call
        for each work item as it is removed from the queue.  The
        thread context the routine is called in is undefined.

Return Value:

    A pointer to the work queue.  Returns NULL if unable to create
    the work queue and its worker threads.  Extended error information
    is available from GetLastError()

--*/

{
   PWORK_QUEUE WorkQueue;
   HANDLE Thread;
   DWORD ThreadId;
   DWORD i;

   //
   // Allocate space for the work queue, which includes an
   // array of thread handles.
   //

   WorkQueue = LocalAlloc( LMEM_ZEROINIT,
                           sizeof( *WorkQueue ) +
                           (NumberOfWorkerThreads * sizeof( HANDLE ))
                         );
   if (WorkQueue == NULL)
   {
      return NULL;
   }

   //
   // Mutual exclusion between the worker threads accessing the work
   // queue is done with a critical section. Initialize the critical 
   // section and preallocate the event that will be used later by 
   // EnterCriticalSection(). Set spin count to 0, so when the critical 
   // section is unavailable, a calling thread will not spin before wait.
   //

   if (!InitializeCriticalSectionAndSpinCount( &WorkQueue->CriticalSection, 0))
   {
      LocalFree( WorkQueue);
      return NULL;
   }

   //
   // The work queue is controlled by a counting semaphore that
   // is incremented each time a work item is placed in the queue
   // and decremented each time a worker thread wakes up to remove
   // an item from the queue.
   //

   if (WorkQueue->Semaphore = CreateSemaphore( NULL, 0, 100000, NULL ))
   {
   
      //
      // The queue itself is just a doubly linked list, where
      // items are placed in the queue at the tail of the list
      // and removed from the queue from the head of the list.
      //

      InitializeListHead( &WorkQueue->Queue );

      //
      // Capture the address of the supplied worker function in 
      // the work queue structure.
      //

      WorkQueue->WorkerRoutine = WorkerRoutine;

      //
      // Now create the requested number of worker threads. The
      // handle to each thread is remembered in an array of thread 
      // handles in the work queue structure.
      //

      for (i=0; i<NumberOfWorkerThreads; i++)
      {
         Thread = CreateThread( NULL,
                                0,
                                (LPTHREAD_START_ROUTINE) WorkerThread,
                                WorkQueue,
                                0,
                                &ThreadId
                              );
         if (Thread == NULL)
         {
            break;
         }
         else
         {
            WorkQueue->NumberOfWorkerThreads++;
            WorkQueue->WorkerThreads[ i ] = Thread;
            SetThreadPriority( Thread, THREAD_PRIORITY_ABOVE_NORMAL );
         }
      }

      //
      // If we successfully created all of the worker threads
      // then return the address of the work queue structure
      // to indicate success.
      //

      if (i == NumberOfWorkerThreads)
      {
         return WorkQueue;
      }
   }

   //
   // Failed for some reason.  Destroy whatever we managed
   // to create and return failure to the caller.
   //

   DestroyWorkQueue( WorkQueue );
   return NULL;
}



VOID
DestroyWorkQueue(
                IN OUT PWORK_QUEUE WorkQueue
                )

/*++

Routine Description:

    This function first sets the terminating flag of the specified work 
    queue. It then shuts down the worker threads associated with work
    queue cleanly after the threads complete processing all the work 
    items in the queue and exit. After all the threads have exited, the
    function destroys `the work queue. 

Arguments:

    WorkQueue - Supplies a pointer to the work queue to destroy.

Return Value:

    None.

--*/

{
   DWORD i;
   DWORD rc;

   //
   // If the semaphore handle field is not NULL, then there
   // may be threads to terminate.
   //

   if (WorkQueue->Semaphore != NULL)
   {
      //
      // Set the terminating flag in the work queue and
      // signal the counting semaphore by the number of
      // worker threads so they will all wake up and
      // notice the terminating flag and exit. 
      //

      EnterCriticalSection( &WorkQueue->CriticalSection );
      _try {
         WorkQueue->Terminating = TRUE;
         ReleaseSemaphore( WorkQueue->Semaphore,
                           WorkQueue->NumberOfWorkerThreads,
                           NULL
                         );
         //
         // The count of the semaphore at this time is equal to the 
         // number of work items remaining in the work queue plus 
         // the number of worker threads. This ensures that all threads 
         // will be awakened to run.
         //
      }
      _finally {
         LeaveCriticalSection( &WorkQueue->CriticalSection );
      }

      //
      // Wait for all worker threads to run, see that the terminating
      // flag is set, and then exit when the work queue is empty. This
      // will occur eventually unless the system malfunctions. So do 
      // not timeout. 
      // 

      while (TRUE)
      {
         rc = WaitForMultipleObjectsEx( WorkQueue->NumberOfWorkerThreads,
                                        WorkQueue->WorkerThreads,
                                        TRUE,
                                        INFINITE,    // No timeout
                                        TRUE         // Alertable
                                      );
         if (rc == WAIT_IO_COMPLETION)
         {
            //
            // If we came out of the wait because an I/O
            // completion routine was called, reissue the
            // wait.
            //
            continue;
         }
         else
         {
            break;
         }
      }

      //
      // Now all the worker threads have terminated. Close the thread 
      // handles so the thread objects will eventually be deleted by 
      // the object manager. 
      //

      for (i=0; i<WorkQueue->NumberOfWorkerThreads; i++)
      {    
         CloseHandle( WorkQueue->WorkerThreads[ i ] );
      }

      //
      // All threads stopped, all thread handles closed.  Now
      // delete the critical section and close the semaphore
      // handle.
      //

      DeleteCriticalSection( &WorkQueue->CriticalSection );
      CloseHandle( WorkQueue->Semaphore );
   }

   //
   // Everything is done, now free the memory used by the work queue.
   //

   LocalFree( WorkQueue );
   return;
}



BOOL
QueueWorkItem(
             IN OUT PWORK_QUEUE WorkQueue,
             IN PWORK_QUEUE_ITEM WorkItem
             )

/*++

Routine Description:

    This function queues a work item to the passed work queue that is
    processed by one of the worker threads associated with the queue.

Arguments:

    WorkQueue - Supplies a pointer to the work queue that is to
        receive the work item.

    WorkItem - Supplies a pointer to the work item to add to the queue.
        The work item structure contains a doubly linked list entry, the
        address of a routine to call and a parameter to pass to that
        routine.  It is the routine's responsibility to reclaim the
        storage occupied by the WorkItem structure.

Return Value:

    TRUE if operation was successful.  Otherwise returns FALSE and
    extended error information is available from GetLastError()

--*/

{
   BOOL Result;

   //
   // Acquire the work queue critical section and insert the work item
   // in the queue and release the semaphore if the work item is not
   // already in the list.
   //

   EnterCriticalSection( &WorkQueue->CriticalSection );
   Result = TRUE;
   _try {
      WorkItem->WorkQueue = WorkQueue;
      InsertTailList( &WorkQueue->Queue, &WorkItem->List );
      Result = ReleaseSemaphore( WorkQueue->Semaphore, 1, NULL );
   }
   _finally {
      LeaveCriticalSection( &WorkQueue->CriticalSection );
   }

   return Result;
}


VOID
WorkerThread(
            LPVOID lpThreadParameter
            )

/*++

Routine Description:

    This is the routine executed by each worker thread. Upon the 
    creation of the thread, the routine allocates and initializes 
    the state information and virtual buffer of the thread. It then 
    continuously processes work items inserted in the queue whenever
    the thread is released to run. Upon termination, the routine 
    calls ExitThread, which cleanly terminates the thread.

Arguments:

    lpThreadParameter - Supplies a pointer to the work queue 
        associated with this thread.

Return Value:

    None

--*/

{
   PWORK_QUEUE WorkQueue = (PWORK_QUEUE)lpThreadParameter;
   DWORD rc;
   WORK_QUEUE_ITEM InitWorkItem;
   PWORK_QUEUE_ITEM WorkItem;

   //
   // Call the worker routine with an initialize work item
   // to give it a chance to initialize some per thread
   // state that will passed to it for each subsequent
   // work item.
   //

   InitWorkItem.Reason = WORK_INITIALIZE_ITEM;
   (WorkQueue->WorkerRoutine)( &InitWorkItem );
   while ( TRUE )
   {
      _try {

         //
         // Wait until something is put in the queue (semaphore is
         // released), remove the item from the queue, mark it not
         // inserted, and execute the specified routine.
         //

         rc = WaitForSingleObjectEx( WorkQueue->Semaphore, INFINITE, TRUE );
         if (rc == WAIT_IO_COMPLETION)
         {
            continue;
         }

         EnterCriticalSection( &WorkQueue->CriticalSection );
         _try {
            if (WorkQueue->Terminating && IsListEmpty( &WorkQueue->Queue ))
            {
               break;
            }

            WorkItem = (PWORK_QUEUE_ITEM)RemoveHeadList( &WorkQueue->Queue );
         }
         _finally {
            LeaveCriticalSection( &WorkQueue->CriticalSection );
         }

         //
         // Execute the worker routine for this work item.
         //

         (WorkQueue->WorkerRoutine)( WorkItem );
      }
      _except( EXCEPTION_EXECUTE_HANDLER )
      {
         //
         // Ignore any exceptions from worker routine.
         //

      }
   }

   //
   // We reach this point when the terminating flag of the work queue 
   // is set and work queue is empty. Call the worker routine to free
   // the search request state and set the TlsIndex of the thread to
   // NULL. 
   //

   InitWorkItem.Reason = WORK_TERMINATE_ITEM;
   (WorkQueue->WorkerRoutine)( &InitWorkItem );

   //
   // Call ExitThread to deallocate its own stack and then terminate. 
   //

   ExitThread( 0 );

   //
   // The state of this thread becomes signaled.
   //
}


BOOL
CreateVirtualBuffer(
                   OUT PVIRTUAL_BUFFER Buffer,
                   IN SIZE_T CommitSize,
                   IN SIZE_T ReserveSize OPTIONAL
                   )

/*++

Routine Description:

    This function is called to create a virtual buffer.  A virtual
    buffer is a contiguous range of virtual memory, where some initial
    prefix portion of the memory is committed and the remainder is only
    reserved virtual address space.  A routine is provided to extend the
    size of the committed region incrementally or to trim the size of
    the committed region back to some specified amount.

Arguments:

    Buffer - Pointer to the virtual buffer control structure that is
        filled in by this function.

    CommitSize - Size of the initial committed portion of the buffer.
        May be zero.

    ReserveSize - Amount of virtual address space to reserve for the
        buffer.  May be zero, in which case amount reserved is the
        committed size plus one, rounded up to the next 64KB boundary.

Return Value:

    TRUE if operation was successful.  Otherwise returns FALSE and
    extended error information is available from GetLastError()

--*/

{
   SYSTEM_INFO SystemInformation;

   //
   // Query the page size from the system for rounding
   // our memory allocations.
   //

   GetSystemInfo( &SystemInformation );
   Buffer->PageSize = SystemInformation.dwPageSize;

   //
   // If the reserve size was not specified, default it by
   // rounding up the initial committed size to a 64KB
   // boundary.  This is because the Win32 Virtual Memory
   // API calls always allocate virtual address space on
   // 64KB boundaries, so we might well have it available
   // for commitment.
   //

   if (!ARGUMENT_PRESENT( ReserveSize ))
   {
      ReserveSize = ROUND_UP( CommitSize + 1, 0x10000 );
   }

   //
   // Attempt to reserve the address space.
   //

   Buffer->Base = VirtualAlloc( NULL,
                                ReserveSize,
                                MEM_RESERVE,
                                PAGE_READWRITE
                              );
   if (Buffer->Base == NULL)
   {
      //
      // Unable to reserve address space, return failure.
      //

      return FALSE;
   }

   //
   // Attempt to commit some initial portion of the reserved region.
   //
   //

   CommitSize = ROUND_UP( CommitSize, Buffer->PageSize );
   if (CommitSize == 0 ||
       VirtualAlloc( Buffer->Base,
                     CommitSize,
                     MEM_COMMIT,
                     PAGE_READWRITE
                   ) != NULL
      )
   {
      //
      // Either the size of the committed region was zero or the
      // commitment succeeded.  In either case calculate the
      // address of the first byte after the committed region
      // and the address of the first byte after the reserved
      // region and return successs.
      //

      Buffer->CommitLimit = (LPVOID)
                            ((char *)Buffer->Base + CommitSize);

      Buffer->ReserveLimit = (LPVOID)
                             ((char *)Buffer->Base + ReserveSize);

      return TRUE;
   }

   //
   // If unable to commit the memory, release the virtual address
   // range allocated above and return failure.
   //

   VirtualFree( Buffer->Base, 0, MEM_RELEASE );
   return FALSE;
}



BOOL
ExtendVirtualBuffer(
                   IN PVIRTUAL_BUFFER Buffer,
                   IN LPVOID Address
                   )

/*++

Routine Description:

    This function is called to extend the committed portion of a virtual
    buffer.

Arguments:

    Buffer - Pointer to the virtual buffer control structure.

    Address - Byte at this address is committed, along with all memory
        from the beginning of the buffer to this address.  If the
        address is already within the committed portion of the virtual
        buffer, then this routine does nothing.  If the address is 
        outside the reserved portion of the virtual buffer, then this 
        routine returns an error.

        Otherwise enough pages are committed so that the memory from the
        base of the buffer to the passed address is a contiguous region
        of committed memory.


Return Value:

    TRUE if operation was successful.  Otherwise returns FALSE and
    extended error information is available from GetLastError()

--*/

{
   SIZE_T NewCommitSize;
   LPVOID NewCommitLimit;

   //
   // See if address is within the buffer.
   //

   if (Address >= Buffer->Base && Address < Buffer->ReserveLimit)
   {
      //
      // See if the address is within the committed portion of
      // the buffer.  If so return success immediately.
      //

      if (Address < Buffer->CommitLimit)
      {
         return TRUE;
      }

      //
      // Address is within the reserved portion.  Determine how many
      // bytes are between the address and the end of the committed
      // portion of the buffer.  Round this size to a multiple of
      // the page size and this is the amount we will attempt to
      // commit.
      //

      NewCommitSize =
		ROUND_UP( (SIZE_T) Address + 1, Buffer->PageSize ) - (SIZE_T) Buffer->CommitLimit;

      //
      // Attempt to commit the memory.
      //

      NewCommitLimit = VirtualAlloc( Buffer->CommitLimit,
                                     NewCommitSize,
                                     MEM_COMMIT,
                                     PAGE_READWRITE
                                   );
      if (NewCommitLimit != NULL)
      {
         //
         // Successful, so update the upper limit of the committed
         // region of the buffer and return success.
         //

         Buffer->CommitLimit = (LPVOID)
                               ((SIZE_T)NewCommitLimit + NewCommitSize);

         return TRUE;
      }
   }

   //
   // Address is outside of the buffer, return failure.
   //

   return FALSE;
}


BOOL
TrimVirtualBuffer(
                 IN PVIRTUAL_BUFFER Buffer
                 )

/*++

Routine Description:

    This function is called to decommit any memory that has been
    committed for this virtual buffer.

Arguments:

    Buffer - Pointer to the virtual buffer control structure.

Return Value:

    TRUE if operation was successful.  Otherwise returns FALSE and
    extended error information is available from GetLastError()

--*/

{
   Buffer->CommitLimit = Buffer->Base;
   return VirtualFree( Buffer->Base, 0, MEM_DECOMMIT );
}



BOOL
FreeVirtualBuffer(
                 IN PVIRTUAL_BUFFER Buffer
                 )
/*++

Routine Description:

    This function is called to free all the memory that is associated
    with this virtual buffer.

Arguments:

    Buffer - Pointer to the virtual buffer control structure.

Return Value:

    TRUE if operation was successful.  Otherwise returns FALSE and
    extended error information is available from GetLastError()

--*/

{
   //
   // Decommit and release all virtual memory associated with
   // this virtual buffer.
   //

   return VirtualFree( Buffer->Base, 0, MEM_RELEASE );
}



int
VirtualBufferExceptionFilter(
                            IN DWORD ExceptionCode,
                            IN PEXCEPTION_POINTERS ExceptionInfo,
                            IN OUT PVIRTUAL_BUFFER Buffer
                            )

/*++

Routine Description:

    This function is an exception filter that handles exceptions that
    referenced uncommitted but reserved memory contained in the passed
    virtual buffer.  It this filter routine is able to commit the
    additional pages needed to allow the memory reference to succeed,
    then it will re-execute the faulting instruction.  If it is unable
    to commit the pages, it will execute the callers exception handler.

    If the exception is not an access violation or is an access
    violation but does not reference memory contained in the reserved
    portion of the virtual buffer, then this filter passes the exception
    on up the exception chain.

Arguments:

    ExceptionCode - Reason for the exception.

    ExceptionInfo - Information about the exception and the context
        that it occurred in.

    Buffer - Points to a virtual buffer control structure that defines
        the reserved memory region that is to be committed whenever an
        attempt is made to access it.

Return Value:

    Exception disposition code that tells the exception dispatcher what
    to do with this exception.  One of three values is returned:

        EXCEPTION_EXECUTE_HANDLER - execute the exception handler
            associated with the exception clause that called this filter
            procedure.

        EXCEPTION_CONTINUE_SEARCH - Continue searching for an exception
            handler to handle this exception.

        EXCEPTION_CONTINUE_EXECUTION - Dismiss this exception and return
            control to the instruction that caused the exception.


--*/

{
   LPVOID FaultingAddress;

   //
   // If this is an access violation touching memory within
   // our reserved buffer, but outside of the committed portion
   // of the buffer, then we are going to take this exception.
   //

   if (ExceptionCode == STATUS_ACCESS_VIOLATION)
   {
      //
      // Get the virtual address that caused the access violation
      // from the exception record.  Determine if the address
      // references memory within the reserved but uncommitted
      // portion of the virtual buffer.
      //

      FaultingAddress = (LPVOID)ExceptionInfo->ExceptionRecord->ExceptionInformation[ 1 ];
      if (FaultingAddress >= Buffer->CommitLimit &&
          FaultingAddress <= Buffer->ReserveLimit
         )
      {
         //
         // This is our exception.  Try to extend the buffer
         // to including the faulting address.
         //

         if (ExtendVirtualBuffer( Buffer, FaultingAddress ))
         {
            //
            // Buffer successfully extended, so re-execute the
            // faulting instruction.
            //

            return EXCEPTION_CONTINUE_EXECUTION;
         }
         else
         {
            //
            // Unable to extend the buffer.  Stop searching
            // for exception handlers and execute the caller's
            // handler.
            //

            return EXCEPTION_EXECUTE_HANDLER;
         }
      }
   }

   //
   // Not an exception we care about, so pass it up the chain.
   //

   return EXCEPTION_CONTINUE_SEARCH;
}


BOOL
EnumerateDirectoryTree(
                      LPSTR DirectoryPath,
                      PDIRECTORY_ENUMERATE_ROUTINE EnumerateRoutine,
                      PVOID EnumerateParameter
                      )

/*++

Routine Description:

    This function walks a directory tree, depth first, calling the
    passed enumeration routine for each directory and file found
    in the tree.  The enumeration routine is passed the full path
    of the file, the directory information associated with the file
    and an enumeration parameter that is uninterpreted by this
    function.

Arguments:

    DirectoryPath - Absolute or relative path to the directory that
        is the root of the tree to enumerate.

    EnumerateRoutine - Pointer to an enumeration routine to call
        for each file and directory found.

    EnumerateParameter - Uninterpreted 32-bit value that is passed
        to the EnumerationRoutine each time it is called.

Return Value:

    TRUE if operation was successful.  Otherwise returns FALSE and
    extended error information is available from GetLastError()

--*/

{
   BOOL Result;
   VIRTUAL_BUFFER Buffer;
   PENUMERATE_DIRECTORY_STATE State;
   PENUMERATE_DIRECTORY_STACK Stack;
   WIN32_FIND_DATA FindFileData;

   //
   // Create a virtual buffer with an initial committed size of
   // our directory state buffer, and a maximum reserved size of
   // the longest possible full path based on the maximum depth
   // we handle and the maximum length of each path component.
   //

   if (!CreateVirtualBuffer( &Buffer,
                             (SIZE_T)  sizeof( ENUMERATE_DIRECTORY_STATE ),
							 (SIZE_T)  (sizeof( ENUMERATE_DIRECTORY_STATE ) +
										MAX_DEPTH * MAX_PATH)
                           )
      )
   {
      return FALSE;
   }

   //
   // This buffer will be used to maintain a stack of directory
   // search handles, as well as accumulate the full path string
   // as we descend the directory tree.
   //

   State = (PENUMERATE_DIRECTORY_STATE)Buffer.Base;
   State->Depth = 0;
   Stack = &State->Stack[ 0 ];

   //
   // Enter a try ... finally block so we can insure that we clean
   // up after ourselves on exit.
   //

   _try {
      //
      // First translate the passed in DirectoryPath into a fully
      // qualified path.  This path will be the initial value in
      // our path buffer.  The initial allocation of the path buffer
      // is big enough for this initial request, so does not need
      // to be guarded by a try ... except clause.
      //

      if (GetFullPathName( DirectoryPath, MAX_PATH, State->Path, &Stack->PathEnd ))
      {
         //
         // Now enter a try ... except block that will be used to
         // manage the commitment of space in the path buffer as
         // we append subdirectory names and file names to it.
         // Using the virtual buffer allows us to handle full
         // path names up to 16KB in length, with an initial
         // allocation of 4KB.
         //

         _try {
            //
            // Walk the directory tree.  The outer loop is executed
            // once for each directory in the tree.
            //

            while (TRUE)
            {
               startDirectorySearch:
               //
               // Find the end of the current path, and make sure
               // there is a trailing path separator.
               //

               Stack->PathEnd = strchr( State->Path, '\0' );
               if (Stack->PathEnd > State->Path && Stack->PathEnd[ -1 ] != '\\')
               {
                  *(Stack->PathEnd)++ = '\\';
               }

               //
               // Now append the wild card specification that will
               // let us enumerate all the entries in this directory.
               // Call FindFirstFile to find the first entry in the
               // directory.
               //

               strcpy( Stack->PathEnd, "*.*" );
               Stack->FindHandle = FindFirstFile( State->Path,
                                                  &FindFileData
                                                );
               if (Stack->FindHandle != INVALID_HANDLE_VALUE)
               {
                  //
                  // Entry found.  Now loop through the entire
                  // directory processing each entry found,
                  // including the first one.
                  //
                  do
                  {
                     //
                     // Ignore bogus pseudo-directories that are
                     // returned by some file systems (e.g. FAT).
                     //

                     if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&
                         (!strcmp( FindFileData.cFileName, "." ) ||
                          !strcmp( FindFileData.cFileName, ".." )
                         )
                        )
                     {
                        continue;
                     }

                     //
                     // Copy the file name portion from the current
                     // directory entry to the last component in the
                     // path buffer.
                     //
                     // We can use strcpy here because we know that 
                     // the source is a null terminated string.
                     //

                     strcpy( Stack->PathEnd, FindFileData.cFileName );

                     //
                     // Call the supplied enumeration routine with the
                     // full path we have built up in the path buffer,
                     // the directory information for this directory
                     // entry and the supplied enumeration parameter.
                     //

                     (*EnumerateRoutine)( State->Path, &FindFileData, EnumerateParameter );

                     //
                     // If this entry is a subdirectory, then it is
                     // time to recurse.  Do this by incrementing the
                     // stack pointer and depth and jumping to the top
                     // of the outer loop to process current contents
                     // of the path buffer as a fully qualified name of
                     // a directory.
                     //

                     if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                     {
                        Stack++;
                        State->Depth++;
                        goto startDirectorySearch;
                        restartDirectorySearch:         ;
                     }

                     //
                     // Here to find the next entry in the current directory.
                     //
                  }

                  while ( FindNextFile( Stack->FindHandle, &FindFileData ) );

                  //
                  // No more entries in the current directory, so close
                  // the search handle and fall into the code that will
                  // pop our stack of directory seacrh handles.

                  FindClose( Stack->FindHandle );
               }

               //
               // Here when done with a directory.  See if we are pushed
               // inside another directory.  If not, then we are done
               // enumerating the whole tree, so break out of the loop.
               //

               if (!State->Depth)
               {
                  Result = TRUE;
                  break;
               }

               //
               // We were pushed within another directory search,
               // so pop the stack to restore its search handle
               // and path buffer position and resume the search
               // within that directory.

               State->Depth--;
               --Stack;
               goto restartDirectorySearch;
            }
         }

         //
         // Any of the code that appends to the path buffer within
         // the above try ... except clause can cause an access
         // violation if the path buffer becomes longer than its
         // current committed size.  This exception filter
         // will dynamically commit additional pages as needed
         // and resume execution.
         //

         _except( VirtualBufferExceptionFilter( GetExceptionCode(),
                                                GetExceptionInformation(),
                                                &Buffer
                                              )
                )
         {
            //
            // We will get here if the exception filter was unable to
            // commit the memory.
            //

            Result = FALSE;
         }
      }
      else
      {
         //
         // Initial GetFullPathName failed, so return a failure.
         //

         Result = FALSE;
      }
   }
   _finally {
      //
      // Here on our way out of the outer try ... finally block.
      // Make sure all our search handles have been closed and then
      // free the virtual buffer.  The only way this code is not
      // executed is if code within the try ... finally block
      // called ExitThread or ExitProcess, or an external thread
      // or process terminated this thread or process.
      //
      // In the case of process death, this is not a problem, because
      // process terminate closes all open handles attached to the process
      // and frees all private virtual memory that is part of the address
      // space of the process.
      //
      // In the case ot thread death, the code below is not executed if
      // the thread terminates via ExitThread in the context of the
      // try .. finally or if an external thread, either in this process
      // or another process called TerminateThread on this thread.
      //

      while (State->Depth--)
      {
         --Stack;
         FindClose( Stack->FindHandle );
      }

      FreeVirtualBuffer( &Buffer );
   }

   return Result;
}


BOOL
ProcessCommandLineArguments(
                           int argc,
                           char *argv[]
                           )
{
   BOOL Result;
   LPSTR s;

   Result = FALSE;
   _try {
      if (argc < 1)
      {
         return Result;
      }

      while (--argc)
      {
         s = *++argv;
         if (*s == '-' || *s == '/')
         {
            while (*++s)
            {
               switch ( tolower( *s ) )
               {
               case 'm':
                  MappedFileIO = TRUE;
                  break;

               case 'a':
                  ASyncIO = TRUE;
                  break;

               case 's':
                  SyncIO = TRUE;
                  break;

               case 'v':
                  Verbose = TRUE;
                  break;

               case 'y':
                  IgnoreCase = TRUE;
                  break;

               case 't':
                  if (--argc)
                  {
                     NumberOfWorkerThreads = atoi( *++argv );
                     if (NumberOfWorkerThreads > 0)
                     {
                        if (NumberOfWorkerThreads > MAXIMUM_WORKER_THREADS)
                        {
                           NumberOfWorkerThreads = MAXIMUM_WORKER_THREADS;
                        }
                        break;
                     }
                  }

                  // fall through if -t argument missing.

               case '?':
               case 'h':
               default:
                  return Result;
               }
            }
         }
         else
            if (SearchString == NULL)
         {
            SearchString = s;
         }
         else
            if (DirectoryPath == NULL)
         {
            DirectoryPath = s;
         }
         else
         {
            return Result;
         }
      }

      if (SearchString == NULL)
      {
         return Result;
      }

      SearchStringLength = (DWORD)strlen(SearchString);
      if (SearchStringLength == 0)
      {
         return Result;
      }

      if (IgnoreCase)
      {
         SearchFunction = _strnicmp;
      }
      else
      {
         SearchFunction = strncmp;
      }

      if (DirectoryPath == NULL)
      {
         DirectoryPath = ".";
      }

      //
      // If the command line specifies neither asynchronous nor
      // synchronous I/O, use mapped file I/O.
      //

      if (!(ASyncIO || SyncIO))
      {
         MappedFileIO = TRUE;

      } else {

         MappedFileIO = FALSE;
      }

      if (Verbose)
      {
         fprintf( stderr, "Directory Tree: %s\n", DirectoryPath );
         fprintf( stderr, "Search String: '%s'\n", SearchString );
         fprintf( stderr, "Case %ssensitive\n", IgnoreCase ? "in" : "" );
         fprintf( stderr, "Number of Worker Threads: %u\n", NumberOfWorkerThreads );

         if (MappedFileIO)
         {
            fprintf( stderr, "Using Mapped File I/O\n" );
         }
         else
            if (ASyncIO)
         {  
            fprintf( stderr, "Using ASynchronous File I/O\n" );
         }
         else
            if (SyncIO)
         {
            fprintf( stderr, "Using Synchronous File I/O\n" );
         }
      }

      Result = TRUE;

   }
   _finally {
      if (!Result)
      {
         fprintf( stderr, "usage: AsyncIO [-h] [-v] [-y] [-a | -s | -m] [-t n] SearchString [DirectoryPath]\n" );
         fprintf( stderr, "Where...\n" );
         fprintf( stderr, "    -h - prints this message\n" );
         fprintf( stderr, "    -v - generates verbose output\n" );
         fprintf( stderr, "    -y - ignores case when doing comparision\n" );
         fprintf( stderr, "    -t - specifies the number of threads to use (defaults to 4 * number of processors)\n" );
         fprintf( stderr, "    -a - uses asynchronous file I/O\n" );
         fprintf( stderr, "    -s - uses synchronous file I/O\n" );
         fprintf( stderr, "    -m - uses mapped file I/O (default)\n" );
         fprintf( stderr, "    SearchString - specifies the text to search for\n" );
         fprintf( stderr, "    DirectoryPath - specifies the directory to start from (defaults to .)\n" );
      }
   }

   return Result;
}
