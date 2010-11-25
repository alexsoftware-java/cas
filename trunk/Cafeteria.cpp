//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Cafeteria.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfCafeteria *fCafeteria;
//---------------------------------------------------------------------------
__fastcall TfCafeteria::TfCafeteria(TComponent* Owner, int CRport, int CRtype) : TForm(Owner)
{
 CR = new CardReader(CRport, CRtype);

 lbStructure->Caption = "";
 lbFName    ->Caption = "";
 lbMName    ->Caption = "";
 lbLName    ->Caption = "";

  if ( CR->isReady() )
   {
    shpCircle->Brush->Color = clGreen;
    lbPassText1->Caption    = "Программа учёта скидок активирована";
    lbPassText2->Caption    = "";
   }
 else
   {
    shpCircle->Brush->Color = clRed;
    lbPassText1->Caption    = "Учёт скидок невозможен:";
    lbPassText2->Caption    = CR->getErrorMessage();
    Timer1->Enabled         = false;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfCafeteria::FormClose(TObject *Sender, TCloseAction &Action)
{
 delete CR;

 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfCafeteria::Timer1Timer(TObject *Sender)
{
 int curCard,
     curUnit_NN;

 curCard = CR->getNumber();

 if ( curCard == 0 )
   return;

 IBTransaction1->StartTransaction();
 IBSQL1->SQL->Text = "SELECT                     \
                            Units.objects_lnk,   \
                            Units.enabled,       \
                            Units.expire,        \
                            Units.structure_name,\
                            Units.fname,         \
                            Units.mname,         \
                            Units.lname          \
                       FROM                      \
                           Units                 \
                       WHERE                     \
                            Units.card = " + IntToStr(curCard) + ";";
 IBSQL1->ExecQuery();

 if ( IBSQL1->Eof )  // пустая
   {
    lbStructure->Caption = "";
    lbFName    ->Caption = "";
    lbMName    ->Caption = "";
    lbLName    ->Caption = "";
    lbPassText1->Caption = "Карточки нет в БД";
    lbPassText2->Caption = "";
    imgPhoto->Picture = NULL;
    shpCircle->Brush->Color = clRed;
   }
 else
   {
    curUnit_NN           = IBSQL1->FieldByName("objects_lnk")->AsInteger;
    lbStructure->Caption = IBSQL1->FieldByName("structure_name")->AsString;
    lbFName    ->Caption = IBSQL1->FieldByName("fname")->AsString;
    lbMName    ->Caption = IBSQL1->FieldByName("mname")->AsString;
    lbLName    ->Caption = IBSQL1->FieldByName("lname")->AsString;

    try {
         imgPhoto->Picture->LoadFromFile(fMain->cfgPhotosPath + IntToStr(curCard) + ".jpg");
        }
    catch (const EFOpenError &Exception)
         {
          imgPhoto->Picture = NULL;
         }

    if ( !IBSQL1->FieldByName("enabled")->AsInteger )
      {
       lbPassText1->Caption = "Карточка недействительна";
       lbPassText2->Caption = "";
       shpCircle->Brush->Color = clRed;
       fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, curUnit_NN, evMealDiscountWithDisabledCardAttempt);
      }
    else if ( IBSQL1->FieldByName("expire")->AsDateTime < Now() )
      {
       lbPassText1->Caption = "Срок действия карточки истёк  " + IBSQL1->FieldByName("expire")->AsDateTime.FormatString("dd.mm.yyyy HH:mm");
       lbPassText2->Caption = "";
       shpCircle->Brush->Color = clRed;
       fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, curUnit_NN, evMealDiscountWithExpiredCardAttempt);
      }
    else
      {
       IBTransaction1->Commit();
       IBSQL1->Close();
       IBSQL1->SQL->Text = "SELECT * FROM GC(2509) WHERE o_nn = " + IntToStr(curUnit_NN) + ";";
       IBTransaction1->StartTransaction();
       IBSQL1->ExecQuery();

       if ( !IBSQL1->Eof )
         {
          lbStructure->Caption = "ОАО \"КП\" - " + lbStructure->Caption;

          if ( fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Log", "Log.eventtypes_lnk = " + IntToStr(evMealDiscount) +
                                                                 " AND Log.objects_lnk = " + IntToStr(curUnit_NN) +
                                                                 " AND Log.datetime LIKE '" +  Date().DateString() + "%'") == 0 )
            {
             shpCircle->Brush->Color = clLime;
             lbPassText1->Caption = "Скидка предоставлена";
             lbPassText2->Caption = "";
             fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, curUnit_NN, evMealDiscount);
            }
          else
            {
             shpCircle->Brush->Color = clYellow;
             lbPassText1->Caption = "Скидка сегодня уже была предоставлена";
             lbPassText2->Caption = "";
             fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, curUnit_NN, evMealDiscountAttempt);
            }
         }
       else
         {
          shpCircle->Brush->Color = clRed;
          lbPassText1->Caption = "Скидка только для работников";
          lbPassText2->Caption = "";
          fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, curUnit_NN, evMealDiscountAttempt);
         }
      }
   }
 lbPassText1->Caption = TimeToStr(Time()) + "  " + lbPassText1->Caption;

 IBTransaction1->Commit();
 IBSQL1->Close();
}
//---------------------------------------------------------------------------