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

// Dual interface Error
/** @com.interface(iid=00000500-0000-0010-8000-00AA006D2EA4, thread=AUTO, type=DUAL) */
public interface Error extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=PROPGET, name="Number", name2="getNumber", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getNumber();

  /** @com.method(vtoffset=5, dispid=1610743809, type=PROPGET, name="Source", name2="getSource", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getSource();

  /** @com.method(vtoffset=6, dispid=0, type=PROPGET, name="Description", name2="getDescription", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getDescription();

  /** @com.method(vtoffset=7, dispid=1610743811, type=PROPGET, name="HelpFile", name2="getHelpFile", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getHelpFile();

  /** @com.method(vtoffset=8, dispid=1610743812, type=PROPGET, name="HelpContext", name2="getHelpContext", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getHelpContext();

  /** @com.method(vtoffset=9, dispid=1610743813, type=PROPGET, name="SQLState", name2="getSQLState", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getSQLState();

  /** @com.method(vtoffset=10, dispid=1610743814, type=PROPGET, name="NativeError", name2="getNativeError", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getNativeError();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x500, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
