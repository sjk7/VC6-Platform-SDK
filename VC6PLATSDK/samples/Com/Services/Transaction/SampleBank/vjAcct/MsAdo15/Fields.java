//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("D:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /wfc  /w /xi /X:rkc /l "D:\DOCUME~1\erica\LOCALS~1\Temp\jvc22.tmp" /nologo /d "D:\mssdk\samples\Com\Services\Transaction\SampleBank\vjacct" "D:\Program Files\Common Files\System\ado\msado15.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package msado15;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dual interface Fields
/** @com.interface(iid=00000564-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface Fields extends msado15.Fields20
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=PROPGET, name="Count", name2="getCount", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCount();

  /** @com.method(vtoffset=5, dispid=4294967292, type=METHOD, name="_NewEnum", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown _NewEnum();

  /** @com.method(vtoffset=6, dispid=1610743810, type=METHOD, name="Refresh", addFlagsVtable=4)
      @com.parameters() */
  public void Refresh();

  /** @com.method(vtoffset=7, dispid=0, type=PROPGET, name="Item", name2="getItem", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [iid=0000054C-0000-0010-8000-00AA006D2EA4,thread=AUTO,type=DISPATCH] return) */
  public msado15.Field getItem(Variant Index);

  /** @com.method(vtoffset=8, dispid=1610874880, type=METHOD, name="_Append", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Name, [in,type=I4] Type, [in,type=I4] DefinedSize, [in,type=I4] Attrib) */
  public void _Append(String Name, int Type, int DefinedSize, int Attrib);

  /** @com.method(vtoffset=9, dispid=1610874881, type=METHOD, name="Delete", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index) */
  public void Delete(Variant Index);

  /** @com.method(vtoffset=10, dispid=1610940416, type=METHOD, name="Append", addFlagsVtable=4)
      @com.parameters([in,type=STRING] Name, [in,type=I4] Type, [in,type=I4] DefinedSize, [in,type=I4] Attrib, [in,type=VARIANT] FieldValue) */
  public void Append(String Name, int Type, int DefinedSize, int Attrib, Variant FieldValue);

  /** @com.method(vtoffset=11, dispid=1610940417, type=METHOD, name="Update", addFlagsVtable=4)
      @com.parameters() */
  public void Update();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x564, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
