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

// VTable-only interface ICallFactory
/** @com.interface(iid=1C733A30-2A1C-11CE-ADE5-00AA0044773D, thread=AUTO) */
public interface ICallFactory extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] riid, [in,iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] pCtrlUnk, [in,type=PTR] riid2, [out,size=1,type=ARRAY] ppv) */
  public void CreateCall(com.ms.com._Guid riid, IUnknown pCtrlUnk, com.ms.com._Guid riid2, IUnknown[] ppv);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x1c733a30, (short)0x2a1c, (short)0x11ce, (byte)0xad, (byte)0xe5, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x44, (byte)0x77, (byte)0x3d);
}
