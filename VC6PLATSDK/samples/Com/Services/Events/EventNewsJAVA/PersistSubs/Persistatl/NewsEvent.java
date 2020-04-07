//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc2.tmp" /nologo /d "D:\ComPlusSamples\Source\LCE\PersistSubs" "D:\ComPlusSamples\Source\LCE\PersistSubs\PersistATL.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package persistatl;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

/** @com.register(clsid=6B834DA0-A5D3-11D2-AD4D-0080C7BFF6DB, typelib=04A47040-A5D3-11D2-AD4D-0080C7BFF6DB, version="1.0", description="NewsEvent Class")*/
public class NewsEvent implements IUnknown,com.ms.com.NoAutoScripting,persistatl.INewsEventDefault
{
  public void NewsFlash(double dtTimeStamp, String Symbol, String Headline, String URL) 
  {
	  com.ms.win32.User32.MessageBox (0,Headline,Symbol,0);
	  
  }

  public void ShortQuote(String Symbol, double BidPrice, double AskPrice, double LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow) 
  {
  }

  public void LongQuote(String Symbol, double BidPrice, double AskPrice, String LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow, int AskSize, int BidSize, double OpenPrice, double ClosePrice, String CloseDate) 
  {
  }

}
