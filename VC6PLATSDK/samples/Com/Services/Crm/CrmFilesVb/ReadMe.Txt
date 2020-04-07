
			CrmFilesVB

This project is a sample Compensating Resource Manager (CRM) implemented in Visual Basic that creates and deletes files. It can be installed in a server application or in a library application. 

See CrmFiles for the Microsoft Visual C++ version.

The CRM Worker provides an interface for creating or deleting files.

The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications.

While the CRM Worker requires a transaction, the CRM Compensator should not have a transaction.


