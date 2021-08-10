The MyStorageResource sample demonstrates a Cluster Configuration Wizard
extension dll.  It is heavily based on the Physical Disk code in the
wizard that detects shared disks and creates resources for them.

Compile the sample and copy MyStorageResource.dll to the cluster directory
(%systemroot%\cluster) then run Install.cmd.  To uninstall the sample
run Uninstall.cmd.  This must be done for all nodes that will participate
in the cluster.
