@rem To install the MyStorageResource sample copy MyStorageResource.dll
@rem into the cluster directory (%systemroot%\cluster) then run
@rem this script.

@rem Delete the ClCfgSrv.dll Physical Disk component registration.
@rem This needs to be done to avoid conflicts because both components
@rem would try to do the same things, with unpredictable results.
reg delete HKCR\CLSID\{71D13B29-4667-41FB-B4E3-F26418895CDA} /f

@rem Register the MyStorageResource dll sample.
regsvr32 /s %systemroot%\cluster\MyStorageResource.dll
