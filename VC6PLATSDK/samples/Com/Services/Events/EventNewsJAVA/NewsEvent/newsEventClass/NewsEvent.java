//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /xh /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc147.tmp" /nologo /d "D:\ComPlusSamples\Source\LCE\NewsEvent" "D:\ComPlusSamples\Source\LCE\NewsEvent\NewsEventClass.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package newseventclass;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

/** @com.register(clsid=997FF9C0-0F01-11D3-9257-0080C7C30D72, typelib=94007C90-0F00-11D3-9257-0080C7C30D72, version="1.0", description="NewsEvent Class")*/
public class NewsEvent implements IUnknown,com.ms.com.NoAutoScripting,newseventclass.INewsEventDefault
{
  public void NewsFlash(double dtTimeStamp, String Symbol, String Headline, String URL) 
  {
  }

  public void ShortQuote(String Symbol, double BidPrice, double AskPrice, double LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow) 
  {
  }

  public void LongQuote(String Symbol, double BidPrice, double AskPrice, String LastTradeTime, double LastTradePrice, double NetChange, double DailyHigh, double DailyLow, int AskSize, int BidSize, double OpenPrice, double ClosePrice, String CloseDate) 
  {
  }

}
