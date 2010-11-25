#include "_CardReader.h"

//--------------------------------------------------------------------------//

CardReader::CardReader(int port, int readerType)
{
 type = readerType;
 sprintf(str, "\\\\.\\COM%d", port);

 hComPort = CreateFile(str, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

 if (hComPort == INVALID_HANDLE_VALUE)
   {
    fillErrorMessage();
    return;
   }

 if (!SetupComm(hComPort,2048,2048))
   {
    fillErrorMessage();
    return;
   }

 COMMTIMEOUTS ctmo;   ZeroMemory(&ctmo, sizeof(COMMTIMEOUTS));
// ctmo.ReadIntervalTimeout = 200;
 ctmo.ReadIntervalTimeout = 300;
 ctmo.ReadTotalTimeoutMultiplier = 0;
// ctmo.ReadTotalTimeoutConstant = 150;
 ctmo.ReadTotalTimeoutConstant = 200;
 ctmo.WriteTotalTimeoutMultiplier = 0;
 ctmo.WriteTotalTimeoutConstant = 200;
 if (!SetCommTimeouts(hComPort, &ctmo))
   {
    fillErrorMessage();
    return;
   }

 DCB dcb;   ZeroMemory(&dcb, sizeof(DCB));
 dcb.DCBlength = sizeof(DCB);
 dcb.BaudRate = type == 1 ? CBR_9600 : CBR_1200;
 dcb.ByteSize = 8;
 dcb.Parity = NOPARITY;
 dcb.StopBits = ONESTOPBIT;
 dcb.fDtrControl = DTR_CONTROL_DISABLE;
 dcb.fRtsControl = RTS_CONTROL_DISABLE;

 if (!SetCommState(hComPort, &dcb))
   {
    fillErrorMessage();
    return;
   }
}

//--------------------------------------------------------------------------//

CardReader::~CardReader()
{
 CloseHandle(hComPort);
}

//--------------------------------------------------------------------------//

bool CardReader::isReady()
{
 return ErrorText.IsEmpty();
}

//--------------------------------------------------------------------------//

AnsiString CardReader::getErrorMessage()
{
 return ErrorText;
}

//--------------------------------------------------------------------------//

void CardReader::fillErrorMessage()
{
 char *buf;
 FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
               NULL,
               GetLastError(),
               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
               (LPTSTR) &buf,
               0,
               NULL);
 ErrorText = buf;
 LocalFree(buf);
}

//--------------------------------------------------------------------------//

int CardReader::getNumber()
{
 *str = '\0';

 if (type == 1)  // shs
   {
    WriteFile(hComPort, "k", 1, &dwBytes, NULL);
    ReadFile(hComPort, &str, 14, &dwBytes, NULL);

    if (*str == ' ')
      return 0;

    int a = 0;
    sscanf(str, "%8X", &a);
    return a;
   }
 else  // китайские
   {
    ReadFile(hComPort, &str, 10, &dwBytes, NULL);

    if (*str == ' ')
      return 0;

    int a = 0;
    sscanf(str, "%10X", &a);
    return a;
   }
}

//--------------------------------------------------------------------------//