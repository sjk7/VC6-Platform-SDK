;//+--------------------------------------------------------------------------
;//
;//      File:       rqsmsg.mc
;//
;//      Synopsis:   Event log definitions
;//
;//      Copyright   (c) Microsoft Corporation
;//
;//+--------------------------------------------------------------------------

MessageId=900
Severity=Success
SymbolicName=RQS_LOG_SUCCESS
Language=English
A remote access client at IP address %1 connected by %2 has successfully removed its quarantine by presenting this string: %3.

.

MessageId=1000
Severity=Warning
SymbolicName=RQS_LOG_SUCCESS_BUT_NO_QUARANTINE
Language=English
A remote access client at IP address %1 connected by %2 attempted to remove its quarantine by presenting this string: %3.  Quarantine removal failed as the user was either never quarantined or was already removed from quarantine.

.

MessageId=1001
Severity=Warning
SymbolicName=RQS_LOG_REJECT
Language=English
A remote access client at IP address %1 connected by %2 has been rejected because it presented the following unrecognized quarantine string: %3.

.

MessageId=1100
Severity=Error
SymbolicName=RQS_LOG_SUCCESS_BUT_PROBLEM_ENCOUNTERED
Language=English
A remote access client at IP address %1 connected by %2 has presented this recognized string: %3.  However, there was an error encountered when attempting to remove the quarantine.

.

