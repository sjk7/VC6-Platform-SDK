//
// Auto-generated using JActiveX.EXE 5.00.3167.1
//   ("D:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe"   /w /xi /X:rkc /l "D:\DOCUME~1\a-joest\LOCALS~1\Temp\jvc6EA.tmp" /nologo /d "D:\Documents and Settings\a-joest\Desktop\Sunil" "A:\comadmin.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package comadmin;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

/** @com.class(classid=F618C514-DFB8-11D1-A2CF-00805FC79235,DynamicCasts) 
    @com.interface(iid=DD662187-DFC2-11D1-A2CF-00805FC79235, thread=AUTO, type=DUAL) */
public class COMAdminCatalog implements IUnknown,com.ms.com.NoAutoScripting,comadmin.ICOMAdminCatalog
{
  /** @com.method(vtoffset=4, dispid=1, type=METHOD, name="GetCollection", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrCollName, [iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object GetCollection(String bstrCollName);

  /** @com.method(vtoffset=5, dispid=2, type=METHOD, name="Connect", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrConnectString, [iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object Connect(String bstrConnectString);

  /** @com.method(vtoffset=6, dispid=3, type=PROPGET, name="MajorVersion", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getMajorVersion();

  /** @com.method(vtoffset=7, dispid=4, type=PROPGET, name="MinorVersion", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getMinorVersion();

  /** @com.method(vtoffset=8, dispid=5, type=METHOD, name="GetCollectionByQuery", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrCollName, [in,vt=16396,type=SAFEARRAY] aQuery, [iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object GetCollectionByQuery(String bstrCollName, com.ms.com.SafeArray aQuery);

  /** @com.method(vtoffset=9, dispid=6, type=METHOD, name="ImportComponent", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,type=STRING] bstrCLSIDOrProgId) */
  public native void ImportComponent(String bstrApplIdOrName, String bstrCLSIDOrProgId);

  /** @com.method(vtoffset=10, dispid=7, type=METHOD, name="InstallComponent", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,type=STRING] bstrDLL, [in,type=STRING] bstrTLB, [in,type=STRING] bstrPSDLL) */
  public native void InstallComponent(String bstrApplIdOrName, String bstrDLL, String bstrTLB, String bstrPSDLL);

  /** @com.method(vtoffset=11, dispid=8, type=METHOD, name="ShutdownApplication", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName) */
  public native void ShutdownApplication(String bstrApplIdOrName);

  /** @com.method(vtoffset=12, dispid=9, type=METHOD, name="ExportApplication", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,type=STRING] bstrApplicationFile, [in,type=I4] lOptions) */
  public native void ExportApplication(String bstrApplIdOrName, String bstrApplicationFile, int lOptions);

  /** @com.method(vtoffset=13, dispid=10, type=METHOD, name="InstallApplication", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplicationFile, [in,type=STRING] bstrDestinationDirectory, [in,type=I4] lOptions, [in,type=STRING] bstrUserId, [in,type=STRING] bstrPassword, [in,type=STRING] bstrRSN) */
  public native void InstallApplication(String bstrApplicationFile, String bstrDestinationDirectory, int lOptions, String bstrUserId, String bstrPassword, String bstrRSN);

  /** @com.method(vtoffset=14, dispid=11, type=METHOD, name="StopRouter", addFlagsVtable=4)
      @com.parameters() */
  public native void StopRouter();

  /** @com.method(vtoffset=15, dispid=12, type=METHOD, name="RefreshRouter", addFlagsVtable=4)
      @com.parameters() */
  public native void RefreshRouter();

  /** @com.method(vtoffset=16, dispid=13, type=METHOD, name="StartRouter", addFlagsVtable=4)
      @com.parameters() */
  public native void StartRouter();

  /** @com.method(vtoffset=17, dispid=14, type=METHOD, name="Reserved1", addFlagsVtable=4)
      @com.parameters() */
  public native void Reserved1();

  /** @com.method(vtoffset=18, dispid=15, type=METHOD, name="Reserved2", addFlagsVtable=4)
      @com.parameters() */
  public native void Reserved2();

  /** @com.method(vtoffset=19, dispid=16, type=METHOD, name="InstallMultipleComponents", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,vt=16396,type=SAFEARRAY] varFileNames, [in,vt=16396,type=SAFEARRAY] varCLSIDS) */
  public native void InstallMultipleComponents(String bstrApplIdOrName, com.ms.com.SafeArray varFileNames, com.ms.com.SafeArray varCLSIDS);

  /** @com.method(vtoffset=20, dispid=17, type=METHOD, name="GetMultipleComponentsInfo", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,vt=16396,type=SAFEARRAY] varFileNames, [out,vt=16396,type=SAFEARRAY] varCLSIDS, [out,vt=16396,type=SAFEARRAY] varClassNames, [out,vt=16396,type=SAFEARRAY] varFileFlags, [out,vt=16396,type=SAFEARRAY] varComponentFlags) */
  public native void GetMultipleComponentsInfo(String bstrApplIdOrName, com.ms.com.SafeArray varFileNames, com.ms.com.SafeArray varCLSIDS, com.ms.com.SafeArray varClassNames, com.ms.com.SafeArray varFileFlags, com.ms.com.SafeArray varComponentFlags);

  /** @com.method(vtoffset=21, dispid=18, type=METHOD, name="RefreshComponents", addFlagsVtable=4)
      @com.parameters() */
  public native void RefreshComponents();

  /** @com.method(vtoffset=22, dispid=19, type=METHOD, name="BackupREGDB", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrBackupFilePath) */
  public native void BackupREGDB(String bstrBackupFilePath);

  /** @com.method(vtoffset=23, dispid=20, type=METHOD, name="RestoreREGDB", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrBackupFilePath) */
  public native void RestoreREGDB(String bstrBackupFilePath);

  /** @com.method(vtoffset=24, dispid=21, type=METHOD, name="QueryApplicationFile", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplicationFile, [out,size=1,elementType=STRING,type=ARRAY] bstrApplicationName, [out,size=1,elementType=STRING,type=ARRAY] bstrApplicationDescription, [out,size=1,elementType=BOOLEAN,type=ARRAY] bHasUsers, [out,size=1,elementType=BOOLEAN,type=ARRAY] bIsProxy, [out,vt=16396,type=SAFEARRAY] varFileNames) */
  public native void QueryApplicationFile(String bstrApplicationFile, String[] bstrApplicationName, String[] bstrApplicationDescription, boolean[] bHasUsers, boolean[] bIsProxy, com.ms.com.SafeArray varFileNames);

  /** @com.method(vtoffset=25, dispid=22, type=METHOD, name="StartApplication", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName) */
  public native void StartApplication(String bstrApplIdOrName);

  /** @com.method(vtoffset=26, dispid=23, type=METHOD, name="ServiceCheck", addFlagsVtable=4)
      @com.parameters([in,type=I4] lService, [type=I4] return) */
  public native int ServiceCheck(int lService);

  /** @com.method(vtoffset=27, dispid=24, type=METHOD, name="InstallMultipleEventClasses", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,vt=16396,type=SAFEARRAY] varFileNames, [in,vt=16396,type=SAFEARRAY] varCLSIDS) */
  public native void InstallMultipleEventClasses(String bstrApplIdOrName, com.ms.com.SafeArray varFileNames, com.ms.com.SafeArray varCLSIDS);

  /** @com.method(vtoffset=28, dispid=25, type=METHOD, name="InstallEventClass", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrApplIdOrName, [in,type=STRING] bstrDLL, [in,type=STRING] bstrTLB, [in,type=STRING] bstrPSDLL) */
  public native void InstallEventClass(String bstrApplIdOrName, String bstrDLL, String bstrTLB, String bstrPSDLL);

  /** @com.method(vtoffset=29, dispid=26, type=METHOD, name="GetEventClassesForIID", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrIID, [out,vt=16396,type=SAFEARRAY] varCLSIDS, [out,vt=16396,type=SAFEARRAY] varProgIDs, [out,vt=16396,type=SAFEARRAY] varDescriptions) */
  public native void GetEventClassesForIID(String bstrIID, com.ms.com.SafeArray varCLSIDS, com.ms.com.SafeArray varProgIDs, com.ms.com.SafeArray varDescriptions);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xdd662187, (short)0xdfc2, (short)0x11d1, (byte)0xa2, (byte)0xcf, (byte)0x0, (byte)0x80, (byte)0x5f, (byte)0xc7, (byte)0x92, (byte)0x35);

  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xf618c514, (short)0xdfb8, (short)0x11d1, (byte)0xa2, (byte)0xcf, (byte)0x0, (byte)0x80, (byte)0x5f, (byte)0xc7, (byte)0x92, (byte)0x35);
}
