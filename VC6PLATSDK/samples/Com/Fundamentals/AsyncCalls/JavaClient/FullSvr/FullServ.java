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

/** @com.class(classid=F03BE175-A8DE-40D1-9161-A36BCBE1FEA6,DynamicCasts) 
    @com.interface(iid=D3140112-D43F-4718-9119-EF62D631F2AB, thread=AUTO) */
public class FullServ implements IUnknown,com.ms.com.NoAutoScripting,fullsvr.IFullServ,fullsvr.ICallFactory
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=I4] i, [in,type=I4] j, [type=I4] return) */
  public native int Sum(int i, int j);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xd3140112, (short)0xd43f, (short)0x4718, (byte)0x91, (byte)0x19, (byte)0xef, (byte)0x62, (byte)0xd6, (byte)0x31, (byte)0xf2, (byte)0xab);
  /** @com.method()
      @hidden */
  public native void CreateCall(com.ms.com._Guid riid, IUnknown pCtrlUnk, com.ms.com._Guid riid2, IUnknown[] ppv);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xf03be175, (short)0xa8de, (short)0x40d1, (byte)0x91, (byte)0x61, (byte)0xa3, (byte)0x6b, (byte)0xcb, (byte)0xe1, (byte)0xfe, (byte)0xa6);
}
