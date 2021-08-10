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

// VTable-only interface ADOCommandConstruction
/** @com.interface(iid=00000517-0000-0010-8000-00AA006D2EA4, thread=AUTO) */
public interface ADOCommandConstruction extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown getOLEDBCommand();

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] ppOLEDBCommand) */
  public void setOLEDBCommand(IUnknown ppOLEDBCommand);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x517, (short)0x0, (short)0x10, (byte)0x80, (byte)0x0, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x6d, (byte)0x2e, (byte)0xa4);
}
