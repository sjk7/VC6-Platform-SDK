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

/** @com.class(classid=F618C515-DFB8-11D1-A2CF-00805FC79235,DynamicCasts) 
    @com.interface(iid=6EB22871-8A19-11D0-81B6-00A0C9231C29, thread=AUTO, type=DUAL) */
public class COMAdminCatalogObject implements IUnknown,com.ms.com.NoAutoScripting,comadmin.ICatalogObject
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPGET, name="Value", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [type=VARIANT] return) */
  public native Variant getValue(String bstrPropName);

  /** @com.method(vtoffset=5, dispid=1, type=PROPPUT, name="Value", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [in,type=VARIANT] retval) */
  public native void setValue(String bstrPropName, Variant retval);

  /** @com.method(vtoffset=6, dispid=2, type=PROPGET, name="Key", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public native Variant getKey();

  /** @com.method(vtoffset=7, dispid=3, type=PROPGET, name="Name", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public native Variant getName();

  /** @com.method(vtoffset=8, dispid=4, type=METHOD, name="IsPropertyReadOnly", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [type=BOOLEAN] return) */
  public native boolean IsPropertyReadOnly(String bstrPropName);

  /** @com.method(vtoffset=9, dispid=5, type=PROPGET, name="Valid", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public native boolean getValid();

  /** @com.method(vtoffset=10, dispid=6, type=METHOD, name="IsPropertyWriteOnly", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [type=BOOLEAN] return) */
  public native boolean IsPropertyWriteOnly(String bstrPropName);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x6eb22871, (short)0x8a19, (short)0x11d0, (byte)0x81, (byte)0xb6, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x23, (byte)0x1c, (byte)0x29);

  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xf618c515, (short)0xdfb8, (short)0x11d1, (byte)0xa2, (byte)0xcf, (byte)0x0, (byte)0x80, (byte)0x5f, (byte)0xc7, (byte)0x92, (byte)0x35);
}
