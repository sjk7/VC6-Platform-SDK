//
// Auto-generated using JActiveX.EXE 5.00.3167.1
//   ("D:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe"   /w /xi /X:rkc /l "D:\DOCUME~1\a-joest\LOCALS~1\Temp\jvc958.tmp" /nologo /d "D:\mssdk\Samples\COM\Fundamentals\AsyncCalls\JavaClient" "D:\mssdk\Samples\COM\Fundamentals\AsyncCalls\FullSvr\Debug\FullSvr.exe")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package fullsvr;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// VTable-only interface ISynchronize
/** @com.interface(iid=00000030-0000-0000-C000-000000000046, thread=AUTO) */
public interface ISynchronize extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwFlags, [in,type=U4] dwMilliseconds) */
  public void Wait(int dwFlags, int dwMilliseconds);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters() */
  public void Signal();

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters() */
  public void Reset();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x30, (short)0x0, (short)0x0, (byte)0xc0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x0, (byte)0x46);
}
