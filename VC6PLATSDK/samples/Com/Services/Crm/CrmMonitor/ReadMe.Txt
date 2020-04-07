
			CrmMonitor

This sample shows how CRM clerks in a specified transaction can be found and queried.

This directory contains the CrmMonComp project plus a Visual Basic project that demonstrates the use of the Compensating Resource Manager (CRM) monitoring interfaces.

CrmMonComp.dll is a component which should be installed in the application to be monitored. It does not require a transaction.

CrmMonComp shows the use of the following interfaces:

ICrmMonitor
ICrmMonitorLogRecords
ICrmMonitorClerks
ICrmFormatLogRecords

Monitor.vbp is a Visual Basic project that provides a simple user interface to CrmMonComp. Monitor.vbp builds Monitor.exe.

To use Monitor.exe, install CrmMonComp.dll into the application where you want to monitor the CRMs, and run Monitor.exe. Copy the transaction Unit Of Work (UOW) identifier for the transaction you want to monitor from the COM+ Explorer (Transaction List), paste it into Monitor.exe, then click the Go button. This will list details of all the CRMs currently involved in that transaction. The transaction can optionally be aborted by selecting the Abort Transaction check box prior to clicking Go.




