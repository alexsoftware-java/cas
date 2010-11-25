#ifndef _CardReaderH
#define _CardReaderH
//---------------------------------------------------------------------------
#include <stdio.h>
#include <vcl.h>
//--------------------------------------------------------------------------//
class CardReader
{
 private:
  HANDLE hComPort;
  DWORD  dwBytes;
  int    type;
  char   str[15];
  AnsiString ErrorText;
  void fillErrorMessage();

 public:
             CardReader(int port, int readerType);
             ~CardReader();
        bool isReady();
  AnsiString getErrorMessage();
         int getNumber();
};
//--------------------------------------------------------------------------//
#endif