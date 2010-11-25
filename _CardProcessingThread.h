//---------------------------------------------------------------------------
#ifndef _CardProcessingThreadH
#define _CardProcessingThreadH
//---------------------------------------------------------------------------
#include <time.h>
#include <Classes.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include "_structures.h"
#include "_CardReader.h"
//---------------------------------------------------------------------------
class CardProcessingThread : public TThread
{
 private:
  TIBTransaction *IBTransaction1;
  TIBSQL *IBSQL1;
  time_t PassTime;

  CardReader *CR;
  HANDLE     hEwclidT;
         int DeviceId,
             KPPType,
             Zone_NN,
             curCard,
             curUnit_NN,
             lastCard;
  AnsiString PhotosPath,
             PhotoFileName,
             asStructure,
             asFName,
             asMName,
             asLName,
             asPassText1,
             asPassText2;
      TColor clCircle;
      TLabel *lbStructure,
             *lbFName,
             *lbMName,
             *lbLName,
             *lbPassText1,
             *lbPassText2;
      TShape *shpCircle;
      TImage *imgPhoto;

  void __fastcall addEvent(int Object_NN, int Event);
   int __fastcall getLastKPPEvent(int Object_NN);
  void __fastcall addLocation(int Object_NN);
  void __fastcall deleteLocation(int Object_NN);
  void __fastcall addSMSToQueue(int Object_NN, AnsiString Text);
  void __fastcall processCardOnEntry();
  void __fastcall processCardOnExit();

 protected:
  void __fastcall Execute();

 public:
       __fastcall CardProcessingThread(int CRport, int CRtype,
                                       int DeviceId_,
                                       int KPPType_,
                                       int Zone_NN_,
                                       AnsiString PhotosPath_,
                                       TIBDatabase *IBDatabase,
                                       TLabel *lbStructure_, TLabel *lbFName_, TLabel *lbMName_, TLabel *lbLName_, TLabel *lbPassText1_, TLabel *lbPassText2_, TShape *shpCircle_, TImage *imgPhoto_);
       __fastcall ~CardProcessingThread();
  void __fastcall UpdateForm();
};
//---------------------------------------------------------------------------
#endif