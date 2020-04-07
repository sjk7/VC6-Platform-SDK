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

/** @com.class(classid=F618C516-DFB8-11D1-A2CF-00805FC79235,DynamicCasts) 
    @com.interface(iid=6EB22872-8A19-11D0-81B6-00A0C9231C29, thread=AUTO, type=DUAL) */
public class COMAdminCatalogCollection implements IUnknown,com.ms.com.NoAutoScripting,comadmin.ICatalogCollection
{
  /** @com.method(vtoffset=4, dispid=4294967292, type=PROPGET, name="_NewEnum", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public native IUnknown get_NewEnum();

  /** @com.method(vtoffset=5, dispid=1, type=PROPGET, name="Item", addFlagsVtable=4)
      @com.parameters([in,type=I4] lIndex, [iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object getItem(int lIndex);

  /** @com.method(vtoffset=6, dispid=1610743810, type=PROPGET, name="Count", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getCount();

  /** @com.method(vtoffset=7, dispid=1610743811, type=METHOD, name="Remove", addFlagsVtable=4)
      @com.parameters([in,type=I4] lIndex) */
  public native void Remove(int lIndex);

  /** @com.method(vtoffset=8, dispid=1610743812, type=METHOD, name="Add", addFlagsVtable=4)
      @com.parameters([iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object Add();

  /** @com.method(vtoffset=9, dispid=2, type=METHOD, name="Populate", addFlagsVtable=4)
      @com.parameters() */
  public native void Populate();

  /** @com.method(vtoffset=10, dispid=3, type=METHOD, name="SaveChanges", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int SaveChanges();

  /** @com.method(vtoffset=11, dispid=4, type=METHOD, name="GetCollection", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrCollName, [in,type=VARIANT] varObjectKey, [iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object GetCollection(String bstrCollName, Variant varObjectKey);

  /** @com.method(vtoffset=12, dispid=6, type=PROPGET, name="Name", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public native Variant getName();

  /** @com.method(vtoffset=13, dispid=7, type=PROPGET, name="AddEnabled", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public native boolean getAddEnabled();

  /** @com.method(vtoffset=14, dispid=8, type=PROPGET, name="RemoveEnabled", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public native boolean getRemoveEnabled();

  /** @com.method(vtoffset=15, dispid=9, type=METHOD, name="GetUtilInterface", addFlagsVtable=4)
      @com.parameters([iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] return) */
  public native Object GetUtilInterface();

  /** @com.method(vtoffset=16, dispid=10, type=PROPGET, name="DataStoreMajorVersion", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getDataStoreMajorVersion();

  /** @com.method(vtoffset=17, dispid=11, type=PROPGET, name="DataStoreMinorVersion", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public native int getDataStoreMinorVersion();

  /** @com.method(vtoffset=18, dispid=12, type=METHOD, name="PopulateByKey", addFlagsVtable=4)
      @com.parameters([in,vt=12,type=SAFEARRAY] aKeys) */
  public native void PopulateByKey(com.ms.com.SafeArray aKeys);

  /** @com.method(vtoffset=19, dispid=13, type=METHOD, name="PopulateByQuery", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrQueryString, [in,type=I4] lQueryType) */
  public native void PopulateByQuery(String bstrQueryString, int lQueryType);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x6eb22872, (short)0x8a19, (short)0x11d0, (byte)0x81, (byte)0xb6, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x23, (byte)0x1c, (byte)0x29);

  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xf618c516, (short)0xdfb8, (short)0x11d1, (byte)0xa2, (byte)0xcf, (byte)0x0, (byte)0x80, (byte)0x5f, (byte)0xc7, (byte)0x92, (byte)0x35);
}
