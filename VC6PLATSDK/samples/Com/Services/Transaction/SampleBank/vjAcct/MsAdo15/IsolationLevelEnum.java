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

// Enum: IsolationLevelEnum

public class IsolationLevelEnum extends com.ms.wfc.core.Enum
{
  public static final int adXactUnspecified = -1;
  public static final int adXactChaos = 16;
  public static final int adXactReadUncommitted = 256;
  public static final int adXactBrowse = 256;
  public static final int adXactCursorStability = 4096;
  public static final int adXactReadCommitted = 4096;
  public static final int adXactRepeatableRead = 65536;
  public static final int adXactSerializable = 1048576;
  public static final int adXactIsolated = 1048576;
}
