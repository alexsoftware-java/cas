//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "Cafeteria.h"
#include "DBService.h"
#include "GuestCardIssue.h"
#include "KPP.h"
#include "LicensingAgreement.h"
#include "Login.h"
#include "Main.h"
#include "ObjectsTree.h"
#include "OrganizationInfo.h"
#include "PrintCards.h"
#include "Report.h"
#include "Schedules.h"
#include "UnitProperties.h"
#include "Zones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMain *fMain;
//---------------------------------------------------------------------------
__fastcall TfMain::TfMain(TComponent* Owner) : TForm(Owner)
{
 Application->Title = programName;
 Caption = Application->Title;

// Лечение глюка BCB6 - непоказ иконок в меню
 mmWindows->Visible = false;
 mmWindows->Visible = true;

// Коннект к заданной в коммандной строке БД
 if (ParamCount() > 1)
   IBDatabase1->DatabaseName = ParamStr(2);
 else
   IBDatabase1->DatabaseName = "CAS.GDB";

 if (ParamCount() > 2)
   IBDatabase1->Params->Add("user_name=" + ParamStr(3));
 else
   IBDatabase1->Params->Add("user_name=sysdba");

 if (ParamCount() > 3)
   IBDatabase1->Params->Add("password=" + ParamStr(4));
 else
   IBDatabase1->Params->Add("password=masterkey");

 IBDatabase1->Connected = true;

 SQL_Fwk = new SQL_Framework(IBDatabase1);
 IBTransaction1->StartTransaction();

 // Считать версию БД
 Q1->SQL->Text = "SELECT * FROM Organization_Info WHERE nn=1;";
 Q1->ExecQuery();

 if ( Q1->FieldByName("DBVersion")->AsInteger != programDBVersion )
   {
    AnsiString mbCaption = Caption + " -- Критическая Ошибка",
               mbText    = "Версия выбранной базы данных - " + Q1->FieldByName("DBVersion")->AsString + ", в то время как для работы программы необходима версия " + IntToStr(programDBVersion) + ".\nРабота программы невозможна.\nПожалуйста, свяжитесь с Вашим поставщиком.";
    MessageBox(Handle, mbText.c_str(), mbCaption.c_str(), MB_OK | MB_ICONERROR);
    Application->Terminate();
   }

 if ( Q1->FieldByName("ServiceCard")->IsNull )
   cfgServiceCard = 11;
 else
   {
    int cfgCCode                = Q1->FieldByName("CCode")->AsInteger;
    AnsiString maybeServiceCard = Q1->FieldByName("ServiceCard")->AsString;

    if ( StrToInt(maybeServiceCard[3]) + StrToInt(maybeServiceCard[7]) * StrToInt(maybeServiceCard[1]) == cfgCCode)
      cfgServiceCard = StrToInt(maybeServiceCard);
    else
      cfgServiceCard = 11;
   }

// Считать параметры текущего компьютера
 Q1->Close();
 Q1->SQL->Text = "SELECT * FROM Zones_Cfg WHERE nn = " + ( ParamCount() > 0 ? ParamStr(1) : AnsiString("1") ) + ";";
 Q1->ExecQuery();

 if ( Q1->Eof )
   {
    AnsiString mbCaption = Caption + " -- Критическая Ошибка",
               mbText    = "Настройки данного компьютера не найдены в БД.\nРабота программы невозможна.\nПожалуйста, свяжитесь с Вашим поставщиком.";
    MessageBox(Handle, mbText.c_str(), mbCaption.c_str(), MB_OK | MB_ICONERROR);
    Application->Terminate();
   }

 cfgPhotosPath    = Q1->FieldByName("PhotosPath")   ->AsString;
 cfgControlCRType = Q1->FieldByName("CRType")       ->AsInteger;
 cfgControlCRPort = Q1->FieldByName("ControlCRPort")->AsInteger;

// Установить зону, в которой мы находимся
 Q1->Close();
 Q1->SQL->Text = "SELECT Objects_Links.left_lnk FROM Objects_Links WHERE Objects_Links.right_lnk = (SELECT Zones_Cfg.objects_lnk FROM Zones_Cfg WHERE Zones_Cfg.nn = " + ( ParamCount() > 0 ? ParamStr(1) : AnsiString("1") ) + ");";
 Q1->ExecQuery();

 cfgZone_NN = Q1->FieldByName("left_lnk")->AsInteger;

 IBTransaction1->Commit();

// Путь к exe'шнику - для отчётов
 ExePath = ParamStr(0);
 for (int i = ExePath.Length(); i > 1; i--)
    if (ExePath[i] == '\\')
      {
       ExePath.SetLength(i);
       break;
      }

 Timer1->Enabled = true;

#ifdef _DEBUG
 Timer1->Enabled = false;
 userType = utRoot;
 while ( userRights.Length() < userRightsLength )
      userRights += '1';
#endif
}
//---------------------------------------------------------------------------
void __fastcall TfMain::FormClose(TObject *Sender, TCloseAction &Action)
{
 for (int i = MDIChildCount-1; i >= 0; i--)
    MDIChildren[i]->Close();

 delete SQL_Fwk;
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmARMsKPPClick(TObject *Sender)
{
 bool fKPPfound = false;

 for (int i = MDIChildCount-1; i >= 0; i--)
   if (MDIChildren[i]->Caption.Pos("<КПП>") > 0)
     {
      MDIChildren[i]->Show();
      fKPPfound = true;
     }

 if (fKPPfound)
   return;

// Считать параметры текущего компьютера
 Q1->Close();
 Q1->SQL->Text = "SELECT * FROM Zones_Cfg WHERE nn = " + ( ParamCount() > 0 ? ParamStr(1) : AnsiString("1") ) + ";";
 if ( !IBTransaction1->Active )
   IBTransaction1->StartTransaction();
 Q1->ExecQuery();

 TfKPP *fKPPEntry1 = NULL,
       *fKPPExit1  = NULL,
       *fKPPEntry2 = NULL,
       *fKPPExit2  = NULL;

 if ( !Q1->FieldByName("Entry1_CRPort")->IsNull )
  fKPPEntry1 = new TfKPP(Application,
                         Q1->FieldByName("Entry1_CRPort")->AsInteger,
                         Q1->FieldByName("CRType")       ->AsInteger,
                         Q1->FieldByName("Entry1_Device")->IsNull ? -1 : Q1->FieldByName("Entry1_Device")->AsInteger,
                         1,
                         Q1->FieldByName("Name")         ->AsString,
                         1);

 if ( !Q1->FieldByName("Exit1_CRPort")->IsNull )
  fKPPExit1  = new TfKPP(Application,
                         Q1->FieldByName("Exit1_CRPort")->AsInteger,
                         Q1->FieldByName("CRType")      ->AsInteger,
                         Q1->FieldByName("Exit1_Device")->IsNull ? -1 : Q1->FieldByName("Exit1_Device")->AsInteger,
                         2,
                         Q1->FieldByName("Name")        ->AsString,
                         1);

 if ( !Q1->FieldByName("Entry2_CRPort")->IsNull )
   fKPPEntry2 = new TfKPP(Application,
                          Q1->FieldByName("Entry2_CRPort")->AsInteger,
                          Q1->FieldByName("CRType")       ->AsInteger,
                          Q1->FieldByName("Entry2_Device")->IsNull ? -1 : Q1->FieldByName("Entry2_Device")->AsInteger,
                          1,
                          Q1->FieldByName("Name")         ->AsString,
                          2);

 if ( !Q1->FieldByName("Exit2_CRPort")->IsNull )
   fKPPExit2 = new TfKPP(Application,
                         Q1->FieldByName("Exit2_CRPort")->AsInteger,
                         Q1->FieldByName("CRType")      ->AsInteger,
                         Q1->FieldByName("Exit2_Device")->IsNull ? -1 : Q1->FieldByName("Exit2_Device")->AsInteger,
                         2,
                         Q1->FieldByName("Name")        ->AsString,
                         2);

// Размеры и положение на экране
 if ( fKPPEntry1 != NULL)  // Если есть вход № 1
   {
    fKPPEntry1->Left   = 0;
    fKPPEntry1->Top    = 0;
    fKPPEntry1->Height = this->ClientHeight / 2;

    if ( fKPPEntry2 == NULL)
      {
       fKPPEntry1->Width = this->ClientWidth - 4;
      }
    else
      {
       fKPPEntry1->Width = this->ClientWidth / 2 - 8;

       fKPPEntry2->Left   = this->ClientWidth /2 - 4;
       fKPPEntry2->Top    = 0;
       fKPPEntry2->Height = this->ClientHeight / 2;
       fKPPEntry2->Width  = this->ClientWidth / 2 - 8;
      }
   }
 else if ( fKPPEntry2 != NULL)  // Если есть только вход № 2
   {
    fKPPEntry2->Left   = 0;
    fKPPEntry2->Top    = 0;
    fKPPEntry2->Height = this->ClientHeight / 2;
    fKPPEntry2->Width  = this->ClientWidth - 4;
   }

 if ( fKPPExit1 != NULL)  // Если есть выход № 1
   {
    fKPPExit1->Left   = 0;
    fKPPExit1->Top    = this->ClientHeight / 2;
    fKPPExit1->Height = this->ClientHeight / 2 - 4;

    if ( fKPPExit2 == NULL )
      {
       fKPPExit1->Width  = this->ClientWidth - 4;
      }
    else
      {
       fKPPExit1->Width  = this->ClientWidth / 2 - 8;

       fKPPExit2->Left   = this->ClientWidth / 2 - 4;
       fKPPExit2->Top    = this->ClientHeight / 2;
       fKPPExit2->Height = this->ClientHeight / 2 - 4;
       fKPPExit2->Width  = this->ClientWidth / 2 - 8;
      }
   }
 else if ( fKPPExit2 != NULL)  // Если есть только выход № 2
   {
    fKPPExit2->Left   = 0;
    fKPPExit2->Top    = this->ClientHeight / 2;
    fKPPExit2->Height = this->ClientHeight / 2 - 4;
    fKPPExit2->Width  = this->ClientWidth - 4;

    fKPPEntry2->Left = 0;
    fKPPEntry2->Top  = 0;
    fKPPEntry2->Height = this->ClientHeight / 2;
    fKPPEntry2->Width  = this->ClientWidth - 4;
   }

 IBTransaction1->Commit();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmARMsCafeteriaClick(TObject *Sender)
{
 TfCafeteria *fCafeteria = new TfCafeteria(Application, fMain->cfgControlCRPort, fMain->cfgControlCRType);

// Размеры и положение на экране
 fCafeteria->Left = 0;
 fCafeteria->Top  = 0;
 fCafeteria->Height = this->ClientHeight / 2;
 fCafeteria->Width  = this->ClientWidth - 4;
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmObjectsTreeClick(TObject *Sender)
{
 TfObjectsTree *fObjectsTree = new TfObjectsTree(Application);

 fObjectsTree->Left = 0;
 fObjectsTree->Top  = 0;
 fObjectsTree->Width  = this->ClientWidth / 3 + 60;
 fObjectsTree->Height = this->ClientHeight - 4;
}
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmUnitsClick(TObject *Sender)
{
 TfUnitProperties *fUnitProperties = new TfUnitProperties(Application);
}
#pragma warn .aus
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmOrganizationInfoClick(TObject *Sender)
{
 TfOrganizationInfo *fOrganizationInfo = new TfOrganizationInfo(Application);
}
#pragma warn .aus
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmZonesClick(TObject *Sender)
{
 TfZones *fZones = new TfZones(Application);
}
#pragma warn .aus
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmSchedulesClick(TObject *Sender)
{
 TfSchedules *fSchedules = new TfSchedules(Application);
}
#pragma warn .aus
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmGuestCardIssueClick(TObject *Sender)
{
// TfGuestCardIssue *fGuestCardIssue = new TfGuestCardIssue(Application);
 if (fGuestCardIssue==NULL) Application->CreateForm(__classid(TfGuestCardIssue), &fGuestCardIssue);
 else fGuestCardIssue->Show();
}
#pragma warn .aus
//---------------------------------------------------------------------------
void __fastcall TfMain::mmReportSelectionClick(TObject *Sender)
{
 TfObjectsTree *fObjectsTree = new TfObjectsTree(Application);

 fObjectsTree->Left = 0;
 fObjectsTree->Top  = 0;
 fObjectsTree->Width  = this->ClientWidth / 3 + 60;
 fObjectsTree->Height = this->ClientHeight - 4;

 fObjectsTree->tbReportSelectionClick(this);
 fObjectsTree->tbReportSelection->Down = true;
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmReportWhoHereClick(TObject *Sender)
{
 TfReport *fReport = new TfReport(Application, Date(), Time().FormatString("hh:nn"), Date(), "");
 fReport->PrepareData(200, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmReportHavedDinnerClick(TObject *Sender)
{
 TfReport *fReport = new TfReport(Application, Date(), "08:00", Date(), Time().FormatString("hh:nn"));
 fReport->PrepareData(500, 0, 2509);
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmLoginClick(TObject *Sender)
{
 if (Timer1->Enabled) // первая авторизация после запуска
   Timer1->Enabled = false;
 else
   {
    for (int i = MDIChildCount-1; i >= 0; i--)
       MDIChildren[i]->Close();
    Application->ProcessMessages();
    if (MDIChildCount > 0)
      return;
   }

 TfLogin *fLogin = new TfLogin(Application);

 if (fLogin->ShowModal() == mrCancel)
   {
    delete fLogin;
    Application->Terminate();
   }
 else
   {
    delete fLogin;

    mmARMs             ->Visible = ( userRights[1]  == '1' || userRights[18] == '1' );
    mmARMsKPP          ->Visible = ( userRights[1]  == '1' );
    mmARMsCafeteria    ->Visible = ( userRights[18] == '1' );
    mmOrganization     ->Visible = ( userRights[2]  == '1' );
    mmUnits            ->Visible = ( userRights[6]  == '1' );
    mmReports          ->Visible = ( userRights[10] == '1' || userRights[13] == '1' );
    mmReportSelection  ->Visible = ( userRights[10] == '1' );
    mmReportWhoHere    ->Visible = ( userRights[13] == '1' );
    mmService          ->Visible = ( userRights[14] == '1' || userRights[15] == '1' || userRights[16] == '1' );
    mmServiceDB        ->Visible = ( userRights[14] == '1' || userRights[15] == '1' );
    mmServicePrintCards->Visible = ( userRights[16] == '1' );
    mmSystemCommands   ->Visible = ( userRights[17] == '1' );

    mmSchedules     ->Visible = ( userType != utUser );
    mmGuestCardIssue->Visible = ( userType != utUser );

    if (userRights[1] == '1' && userType == utUser)
      mmARMsKPPClick(Sender);

    else if (userRights[18] == '1' && userType == utUser)
      mmARMsCafeteriaClick(Sender);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmShutdownClick(TObject *Sender)
{
 fMain->SQL_Fwk->addEvent(cfgZone_NN, cfgUser_NN, evPCShutdown);

 OSVERSIONINFO osvi;
 osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
 GetVersionEx(&osvi);
 if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT)
   {
    STARTUPINFO         si;   ZeroMemory(&si, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;

    CreateProcess(NULL,                       // name of executable module
                  "rundll32 user,ExitWindows",// command line string
                  NULL,                       // process security attributes
                  NULL,                       // thread security attributes
                  false,                      // handle inheritance flag
                  NULL,                       // creation flags
                  NULL,                       // new environment block
                  NULL,                       // current directory name
                  &si,                        // STARTUPINFO
                  &pi);                       // PROCESS_INFORMATION
   }
 else
   {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return;

    if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
      {
       CloseHandle(hToken);
       return;
      }

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, false, &tkp, NULL, NULL, NULL);
    CloseHandle(hToken);
    ExitWindowsEx(EWX_POWEROFF, NULL);
   }
}
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmServiceDBClick(TObject *Sender)
{
 TfDBService *fDBService = new TfDBService(Application);

 if ( !ListBox1->Visible)
   mmWindowsMessagesWindowClick(Sender);
}
#pragma warn .aus
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmServicePrintCardsClick(TObject *Sender)
{
 TfPrintCards *fPrintCards = new TfPrintCards(Application);
}
#pragma warn .aus
//---------------------------------------------------------------------------
void __fastcall TfMain::mmWindowsCascadeClick(TObject *Sender)
{
 Cascade();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmWindowsTileVerticalClick(TObject *Sender)
{
 TileMode = tbVertical;
 Tile();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmWindowsTileHorizontalClick(TObject *Sender)
{
 TileMode = tbHorizontal;
 Tile();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmWindowsMessagesWindowClick(TObject *Sender)
{
 StatusBar1->Visible = !StatusBar1->Visible;

 mmWindowsMessagesWindow->Checked = !mmWindowsMessagesWindow->Checked;
 ListBox1->Visible = !ListBox1->Visible;
}
//---------------------------------------------------------------------------
#pragma warn -aus
void __fastcall TfMain::mmInformationAboutClick(TObject *Sender)
{
 TfAbout *fAbout = new TfAbout(Application);
}
#pragma warn .aus
//---------------------------------------------------------------------------
void __fastcall TfMain::mmInformationLicensingAgreementClick(TObject *Sender)
{
 TfLicensingAgreement *fLicensingAgreement = new TfLicensingAgreement(Application);
 fLicensingAgreement->RichEdit1->Lines->LoadFromFile(fMain->ExePath + "LicensingAgreement.rtf");
}
//---------------------------------------------------------------------------
void __fastcall TfMain::mmInformationSiteClick(TObject *Sender)
{
 ShellExecute(Handle, "open", "http://www.kp-voshod.ru", NULL, NULL, SW_RESTORE);
}
//---------------------------------------------------------------------------
void __fastcall TfMain::addMessage(AnsiString Message)
{
 StatusBar1->SimpleText = Message;

 ListBox1->Items->Add(Message);
 ListBox1->Perform(WM_KEYDOWN,VK_END,0);
 Application->ProcessMessages();
}
//---------------------------------------------------------------------------