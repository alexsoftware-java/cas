//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "KPP.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfKPP *fKPP;
//---------------------------------------------------------------------------
__fastcall TfKPP::TfKPP(TComponent* Owner,
                        int CRport, int CRtype,
                        int DeviceId,
                        int KPPType,
                        AnsiString ZoneName,
                        int KPPNumber)
         : TForm(Owner)
{
 if ( fMain->userType == utUser )
   fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, fMain->cfgUser_NN, evKPPStart);

 if (KPPType == 1)
   this->Caption = "ÀÐÌ <ÊÏÏ>: '" + ZoneName + "', âõîä ¹ " + IntToStr(KPPNumber);
 else
   this->Caption = "ÀÐÌ <ÊÏÏ>: '" + ZoneName + "', âûõîä ¹ " + IntToStr(KPPNumber);

 CPT = new CardProcessingThread(CRport, CRtype,
                                DeviceId,
                                KPPType,
                                fMain->cfgZone_NN,
                                fMain->cfgPhotosPath,
                                fMain->IBDatabase1,
                                lbStructure,
                                lbFName,
                                lbMName,
                                lbLName,
                                lbPassText1,
                                lbPassText2,
                                shpCircle,
                                imgPhoto);
}
//---------------------------------------------------------------------------
__fastcall TfKPP::~TfKPP()
{
 Sleep(300);
 delete CPT;
}
//---------------------------------------------------------------------------
void __fastcall TfKPP::FormClose(TObject *Sender, TCloseAction &Action)
{
 CPT->Terminate();
 if ( fMain->userType == utUser )
   fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, fMain->cfgUser_NN, evKPPStop);
 Action = caFree;
}
//---------------------------------------------------------------------------