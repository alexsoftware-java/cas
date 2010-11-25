//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <stdio.h>
#include <string>
#include <vector>
#include "_structures.h"
#include "_SQL_Framework.cpp"
//---------------------------------------------------------------------------
class TfMain : public TForm
{
__published:
        TIBDatabase *IBDatabase1;
        TIBTransaction *IBTransaction1;
        TIBSQL *Q1;
        TTimer *Timer1;
        TImageList *ImageList;
        TImageList *ImageList1;
        TImageList *ImageList2;
        TMainMenu *MainMenu1;
        TMenuItem *mmARMs;
        TMenuItem *mmARMsKPP;
        TMenuItem *mmARMsCafeteria;
        TMenuItem *mmOrganization;
        TMenuItem *mmObjectsTree;
        TMenuItem *mmOrganizationN1;
        TMenuItem *mmUnits;
        TMenuItem *mmOrganizationN2;
        TMenuItem *mmOrganizationInfo;
        TMenuItem *mmOrganizationN3;
        TMenuItem *mmZones;
        TMenuItem *mmOrganizationN4;
        TMenuItem *mmSchedules;
        TMenuItem *mmOrganizationN5;
        TMenuItem *mmGuestCardIssue;
        TMenuItem *mmReports;
        TMenuItem *mmReportSelection;
        TMenuItem *mmReportWhoHere;
        TMenuItem *mmReportHavedDinner;
        TMenuItem *mmLogin;
        TMenuItem *mmSystemCommands;
        TMenuItem *mmShutdown;
        TMenuItem *mmService;
        TMenuItem *mmServiceDB;
        TMenuItem *mmServicePrintCards;
        TMenuItem *mmWindows;
        TMenuItem *mmWindowsCascade;
        TMenuItem *mmWindowsTileVertical;
        TMenuItem *mmWindowsTileHorizontal;
        TMenuItem *mmWindowsN1;
        TMenuItem *mmWindowsMessagesWindow;
        TMenuItem *mmInformation;
        TMenuItem *mmInformationAbout;
        TMenuItem *mmInformationLicensingAgreement;
        TMenuItem *mmInformationSite;
        TListBox *ListBox1;
        TStatusBar *StatusBar1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall mmARMsKPPClick(TObject *Sender);
        void __fastcall mmARMsCafeteriaClick(TObject *Sender);
        void __fastcall mmObjectsTreeClick(TObject *Sender);
        void __fastcall mmUnitsClick(TObject *Sender);
        void __fastcall mmOrganizationInfoClick(TObject *Sender);
        void __fastcall mmZonesClick(TObject *Sender);
        void __fastcall mmSchedulesClick(TObject *Sender);
        void __fastcall mmGuestCardIssueClick(TObject *Sender);
        void __fastcall mmReportSelectionClick(TObject *Sender);
        void __fastcall mmReportWhoHereClick(TObject *Sender);
        void __fastcall mmReportHavedDinnerClick(TObject *Sender);
        void __fastcall mmLoginClick(TObject *Sender);
        void __fastcall mmShutdownClick(TObject *Sender);
        void __fastcall mmServiceDBClick(TObject *Sender);
        void __fastcall mmServicePrintCardsClick(TObject *Sender);
        void __fastcall mmWindowsCascadeClick(TObject *Sender);
        void __fastcall mmWindowsTileVerticalClick(TObject *Sender);
        void __fastcall mmWindowsTileHorizontalClick(TObject *Sender);
        void __fastcall mmWindowsMessagesWindowClick(TObject *Sender);
        void __fastcall mmInformationAboutClick(TObject *Sender);
        void __fastcall mmInformationLicensingAgreementClick(TObject *Sender);
        void __fastcall mmInformationSiteClick(TObject *Sender);
private:
public:
        SQL_Framework *SQL_Fwk;
        int        cfgZone_NN,
                   cfgUser_NN,
                   userType,
                   cfgServiceCard,
                   cfgControlCRType,
                   cfgControlCRPort;
        AnsiString cfgPhotosPath,
                   userRights,
                   ExePath;
             __fastcall TfMain(TComponent* Owner);
        void __fastcall addMessage(AnsiString Message);
};
//---------------------------------------------------------------------------
extern PACKAGE TfMain *fMain;
//---------------------------------------------------------------------------
#endif