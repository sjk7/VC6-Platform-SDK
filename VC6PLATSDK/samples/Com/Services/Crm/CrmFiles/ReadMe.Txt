
                            CrmFiles

This project is a sample Compensating Resource Manager (CRM) that creates and deletes files. It can be installed in a server application or in a library application. The CRM Worker provides an interface for creating or deleting files. The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications
and ICrmFormatLogRecords to support monitoring. While the CRM Worker requires a transaction, the CRM Compensator should not have a transaction.


