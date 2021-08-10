@rem To uninstall the MyStorageResource sample run this script.

@rem Unregister the MyStorageResource components.
regsvr32 /u /s %systemroot%\cluster\MyStorageResource.dll

@rem Reregister the ClCfgSrv.dll Physical Disk component.
regsvr32 /s %systemroot%\cluster\ClCfgSrv.dll
