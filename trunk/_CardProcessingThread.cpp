//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "_CardProcessingThread.h"
#include "_Ewclid-T.cpp"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CardProcessingThread::CardProcessingThread(int CRport, int CRtype,
                                                      int DeviceId_,
                                                      int KPPType_,
                                                      int Zone_NN_,
                                                      AnsiString PhotosPath_,
                                                      TIBDatabase *IBDatabase,
                                                      TLabel *lbStructure_,
                                                      TLabel *lbFName_,
                                                      TLabel *lbMName_,
                                                      TLabel *lbLName_,
                                                      TLabel *lbPassText1_,
                                                      TLabel *lbPassText2_,
                                                      TShape *shpCircle_,
                                                      TImage *imgPhoto_)
         : TThread(false)
{
 PassTime = 1;
 lastCard = -1;

 CR = new CardReader(CRport, CRtype);
 DeviceId   = DeviceId_;
 KPPType    = KPPType_;
 Zone_NN    = Zone_NN_;
 PhotosPath = PhotosPath_;

 if (DeviceId >= 0)
   hEwclidT = GetEwclidHandle();
 else
   hEwclidT = INVALID_HANDLE_VALUE;

 IBTransaction1 = new TIBTransaction(Application);
 IBTransaction1->DefaultDatabase = IBDatabase;

 IBSQL1 = new TIBSQL(Application);
 IBSQL1->Database = IBDatabase;
 IBSQL1->Transaction = IBTransaction1;

 lbStructure = lbStructure_;
 lbFName     = lbFName_;
 lbMName     = lbMName_;
 lbLName     = lbLName_;
 lbPassText1 = lbPassText1_;
 lbPassText2 = lbPassText2_;
 shpCircle   = shpCircle_;
 imgPhoto    = imgPhoto_;
}
//---------------------------------------------------------------------------
__fastcall CardProcessingThread::~CardProcessingThread()
{
 delete CR;

 delete IBTransaction1;
 delete IBSQL1;
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::UpdateForm()
{
 lbStructure->Caption = asStructure;
 lbFName    ->Caption = asFName;
 lbMName    ->Caption = asMName;
 lbLName    ->Caption = asLName;
 lbPassText1->Caption = asPassText1;
 lbPassText2->Caption = asPassText2;
 shpCircle->Brush->Color = clCircle;

 if (PhotoFileName == "")
   imgPhoto->Picture = NULL;
 else
   {
    try {
         imgPhoto->Picture->LoadFromFile(PhotosPath + PhotoFileName + ".jpg");
        }
    catch (const EFOpenError &Exception)
         {
          imgPhoto->Picture = NULL;
         }
   }
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::addEvent(int Object_NN, int Event)
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "INSERT INTO \
                                 Log (nn, zones_lnk, objects_lnk, eventtypes_lnk) \
                      VALUES \
                            (GEN_ID(gen_log,1)," + IntToStr(Zone_NN) + "," + IntToStr(Object_NN) + "," + IntToStr(Event) + ");";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();
 IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
int __fastcall CardProcessingThread::getLastKPPEvent(int Object_NN)
{
 int Event = evFirstUse;

 IBSQL1->Close();
 IBSQL1->SQL->Text = "SELECT                   \
                            Log.eventtypes_lnk \
                      FROM                     \
                          Log                  \
                      WHERE                    \
                           Log.objects_lnk = " + IntToStr(Object_NN) + " \
                       AND Log.nn = (          \
                                     SELECT    \
                                           MAX(Log.nn) \
                                     FROM      \
                                          Log  \
                                     WHERE     \
                                           Log.objects_lnk = " + IntToStr(Object_NN) + " \
                                       AND Log.zones_lnk = " + IntToStr(Zone_NN) + " \
                                       AND ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " or Log.eventtypes_lnk = " + IntToStr(evExit) + " \
                                      ));";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();

 if ( !IBSQL1->Eof )  // �� ������
   Event = IBSQL1->FieldByName("eventtypes_lnk")->AsInteger;

 IBTransaction1->Commit();

 return Event;
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::addLocation(int Object_NN)
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "INSERT INTO \
                                 Units_location (nn, zones_lnk, objects_lnk) \
                      VALUES \
                            (GEN_ID(gen_units_location,1)," + IntToStr(Zone_NN) + "," + IntToStr(Object_NN) + ");";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();
 IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::deleteLocation(int Object_NN)
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "DELETE FROM \
                                 Units_location \
                      WHERE  \
                           zones_lnk = " + IntToStr(Zone_NN) + " \
                       AND objects_lnk = " + IntToStr(Object_NN) + ";";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();
 IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::addSMSToQueue(int Object_NN, AnsiString Text)
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "INSERT INTO \
                                 SMS_Queue (nn, objects_lnk, text) \
                      VALUES \
                            (GEN_ID(gen_sms_queue,1)," + IntToStr(Object_NN) + ",'" + Text + "');";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();
 IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::processCardOnEntry()
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "SELECT                    \
                            Units.objects_lnk,  \
                            Units.enabled,      \
                            Units.expire,       \
                            Units.fname,        \
                            Units.mname,        \
                            Units.lname,        \
                            Units.sms_enabled,  \
                            Units.structure_name\
                       FROM                     \
                           Units                \
                       WHERE                    \
                            Units.card = " + IntToStr(curCard) + ";";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();

 if ( IBSQL1->Eof )  // ������
   {
    asStructure = "";
    asFName     = "";
    asMName     = "";
    asLName     = "";
    PhotoFileName = "";
    clCircle = clRed;
    asPassText1 = "�������� ��� � ��";
    asPassText2 = "";
   }
 else
   {
    asStructure = IBSQL1->FieldByName("structure_name")->AsString;
    asFName     = IBSQL1->FieldByName("fname")->AsString;
    asMName     = IBSQL1->FieldByName("mname")->AsString;
    asLName     = IBSQL1->FieldByName("lname")->AsString;
    curUnit_NN  = IBSQL1->FieldByName("objects_lnk")->AsInteger;
    PhotoFileName = IntToStr(curCard);

    if ( !IBSQL1->FieldByName("enabled")->AsInteger )
      {
       asPassText1 = "�������� ���������������";
       asPassText2 = "";
       clCircle = clRed;
       addEvent(curUnit_NN, evEntryWithDisabledCardAttempt);
      }
    else if (IBSQL1->FieldByName("expire")->AsDateTime < Now())
      {
       asPassText1 = "���� �������� �������� ����  " + IBSQL1->FieldByName("expire")->AsDateTime.FormatString("dd.mm.yyyy HH:mm");
       asPassText2 = "";
       clCircle = clRed;
       addEvent(curUnit_NN, evEntryWithExpiredCardAttempt);
      }
    else
      {
       if ( !IBSQL1->FieldByName("sms_enabled")->IsNull && IBSQL1->FieldByName("sms_enabled")->AsInteger )
         addSMSToQueue(curUnit_NN, "Vhod v shkolu v " + Time().FormatString("hh:nn") + Date().FormatString(" dd-mm-yyyy"));

       switch (getLastKPPEvent(curUnit_NN))
         {
          case evFirstUse: clCircle = clBlue;
                           asPassText1 = "���� ��������";
                           asPassText2 = "������ ������������� ��������";
                           addEvent(curUnit_NN, evFirstUse);
                           break;
          case evEntry   : clCircle = clYellow;
                           asPassText1 = "������������������� ����";
                           asPassText2 = "����� �� ��� ���������������";
                           addEvent(curUnit_NN, evNotRegisteredExit);
                           break;
          case evExit    : clCircle = clLime;
                           asPassText1 = "���� ��������";
                           asPassText2 = "";
                           break;
          default        : asPassText1 = "������-�� ������ ���� �� ������";
                           break;
         }

       addEvent(curUnit_NN, evEntry);
       addLocation(curUnit_NN);

       if (hEwclidT != INVALID_HANDLE_VALUE)
         {
          RelayControl(hEwclidT, DeviceId, 1);
          Sleep(100);
          RelayControl(hEwclidT, DeviceId, 0);
         }
      }
   }
  asPassText1 = TimeToStr(Time()) + "  " + asPassText1;
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::processCardOnExit()
{
 IBSQL1->Close();
 IBSQL1->SQL->Text = "SELECT                    \
                            Units.objects_lnk,  \
                            Units.enabled,      \
                            Units.expire,       \
                            Units.card_type,    \
                            Units.fname,        \
                            Units.mname,        \
                            Units.lname,        \
                            Units.sms_enabled,  \
                            Units.structure_name\
                       FROM                     \
                           Units                \
                       WHERE                    \
                            Units.card = " + IntToStr(curCard) + ";";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 IBSQL1->ExecQuery();

 if ( IBSQL1->Eof )  // ������
   {
    asStructure = "";
    asFName     = "";
    asMName     = "";
    asLName     = "";
    PhotoFileName = "";
    clCircle = clRed;
    asPassText1 = "�������� ��� � ��";
    asPassText2 = "";
   }
 else
   {
    asStructure = IBSQL1->FieldByName("structure_name")->AsString;
    asFName     = IBSQL1->FieldByName("fname")->AsString;
    asMName     = IBSQL1->FieldByName("mname")->AsString;
    asLName     = IBSQL1->FieldByName("lname")->AsString;
    curUnit_NN  = IBSQL1->FieldByName("objects_lnk")->AsInteger;
    PhotoFileName = IntToStr(curCard);

    if ( !IBSQL1->FieldByName("enabled")->AsInteger )
      {
       asPassText1 = "�������� ���������������";
       asPassText2 = "";
       clCircle = clRed;
       addEvent(curUnit_NN, evExitWithDisabledCardAttempt);
      }
    else if (IBSQL1->FieldByName("expire")->AsDateTime < Now())
      {
       asPassText1 = "���� �������� �������� ����  " + IBSQL1->FieldByName("expire")->AsDateTime.FormatString("dd.mm.yyyy HH:mm");
       asPassText2 = "";
       clCircle = clRed;
       addEvent(curUnit_NN, evExitWithExpiredCardAttempt);
      }
    else if (IBSQL1->FieldByName("card_type")->AsInteger == 2 && KPPType != 3)
      {
       asPassText1 = "��������! ����� �� �������� �����";
       asPassText2 = "�������� ����� � ������������";
       clCircle = clRed;
       addEvent(curUnit_NN, evExitWithGuestCardUsingWrongKPPAttempt);
      }
    else
      {
       if ( !IBSQL1->FieldByName("sms_enabled")->IsNull && IBSQL1->FieldByName("sms_enabled")->AsInteger )
         addSMSToQueue(curUnit_NN, "Vihod iz shkoli v " + Time().FormatString("hh:nn") + Date().FormatString(" dd-mm-yyyy"));

       switch (getLastKPPEvent(curUnit_NN))
         {
          case evFirstUse: clCircle = clBlue;
                           asPassText1 = "����� ��������";
                           asPassText2 = "������ ������������� ��������";
                           addEvent(curUnit_NN, evFirstUse);
                           break;
          case evExit    : clCircle = clYellow;
                           asPassText1 = "������������������� �����";
                           asPassText2 = "���� �� ��� ���������������";
                           addEvent(curUnit_NN, evNotRegisteredEntry);
                           break;
          case evEntry   : clCircle = clLime;
                           asPassText1 = "����� ��������";
                           asPassText2 = "";
                           break;
          default        : asPassText1 = "������-�� ������ ���� �� ������";
                           break;
         }

       addEvent(curUnit_NN, evExit);
       deleteLocation(curUnit_NN);

       if (hEwclidT != INVALID_HANDLE_VALUE)
         {
          RelayControl(hEwclidT, DeviceId, 1);
          Sleep(100);
          RelayControl(hEwclidT, DeviceId, 0);
         }
      }
   }
  asPassText1 = TimeToStr(Time()) + "  " + asPassText1;
}
//---------------------------------------------------------------------------
void __fastcall CardProcessingThread::Execute()
{
 if ( CR->isReady() )
   {
    clCircle = clGreen;
    asPassText1 = "�������� " + (KPPType == 1 ? AnsiString("����� ") : AnsiString("������ ")) + "�������";
   }
 else
   {
    clCircle = clRed;
    asPassText1 = "�������� " + (KPPType == 1 ? AnsiString("����� ") : AnsiString("������ ")) + "����������:";
    asPassText2 = CR->getErrorMessage();
    this->Terminate();
   }
 Synchronize(UpdateForm);

 while(!Terminated)
   {
    Sleep(200);
    curCard = CR->getNumber();
    if (curCard != 0)
      {
       if ( curCard == lastCard )
         {
          if ( (time(NULL) - PassTime) < 10 )
            continue;
         }

       PassTime = time(NULL);
       lastCard = curCard;

       if (KPPType == 1)  // ��� �� �����
         Synchronize(processCardOnEntry);
       else  // ��� �� ������
         Synchronize(processCardOnExit);

       Synchronize(UpdateForm);
      }
    else if ( (time(NULL) - PassTime) > 180 )
      {
       asStructure = "";
       asFName     = "";
       asMName     = "";
       asLName     = "";
       PhotoFileName = "";
       clCircle = clGreen;
       asPassText1 = "�������� " + (KPPType == 1 ? AnsiString("����� ") : AnsiString("������ ")) + "�������";
       asPassText2 = "";

       Synchronize(UpdateForm);
      }
   }
}
//---------------------------------------------------------------------------