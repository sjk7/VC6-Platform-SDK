THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999.  Microsoft Corporation.  All rights reserved.

ENUMSTREAMS is a console application listing the name and size of 
the streams in a file.  ENUMSTREAMS uses the Backup APIs 
BackupRead and BackupSeek to do its work.

To run, pass as the first argument the name a file.  This file is 
opened for reading and shared read/write access.  If the file is 
already opened in a conflicting mode, then enumerating streams 
cannot be done.

The application contains a set of functions to get the stream 
information using FindFirstStream/FindNextStream/FindCloseStream
method.

ENUMSTREAMS works on any version of Windows NT.  On file system
which dot not have native support for streams, Windows simulates
the default (unnamed) stream that includes the file contents.  
The unnamed stream does not exist unless there is some contents in
it.

To build the sample insure the platform SDK paths are set.  Simply 
executing nmake builds the final executable ENUMSTREAMS.EXE.  You 
can use nmake nodebug=1 to build without debug information.
