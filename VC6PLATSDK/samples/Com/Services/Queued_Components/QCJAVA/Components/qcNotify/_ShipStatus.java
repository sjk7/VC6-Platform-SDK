//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc24F.tmp" /nologo /d "D:\ComPlusSamples\Source\QCSample1" "D:\ComPlusSamples\Source\QCSample1\QCNotify.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package qcnotify;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Enum: _ShipStatus

public class _ShipStatus extends com.ms.wfc.core.Enum
{
  public static final short ssUnprocessed = 0;
  public static final short ssShipped = 1;
  public static final short ssBackOrdered = 2;
  public static final short ssNotStocked = 3;
  public static final short ssUnrecognizedItem = 4;
}
