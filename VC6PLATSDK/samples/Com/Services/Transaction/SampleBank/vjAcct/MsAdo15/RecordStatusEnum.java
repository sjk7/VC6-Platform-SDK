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

// Enum: RecordStatusEnum

public class RecordStatusEnum extends com.ms.wfc.core.Enum
{
  public static final int adRecOK = 0;
  public static final int adRecNew = 1;
  public static final int adRecModified = 2;
  public static final int adRecDeleted = 4;
  public static final int adRecUnmodified = 8;
  public static final int adRecInvalid = 16;
  public static final int adRecMultipleChanges = 64;
  public static final int adRecPendingChanges = 128;
  public static final int adRecCanceled = 256;
  public static final int adRecCantRelease = 1024;
  public static final int adRecConcurrencyViolation = 2048;
  public static final int adRecIntegrityViolation = 4096;
  public static final int adRecMaxChangesExceeded = 8192;
  public static final int adRecObjectOpen = 16384;
  public static final int adRecOutOfMemory = 32768;
  public static final int adRecPermissionDenied = 65536;
  public static final int adRecSchemaViolation = 131072;
  public static final int adRecDBDeleted = 262144;
}
