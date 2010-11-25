//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("About.cpp",             fAbout);
USEFORM("Cafeteria.cpp",         fCafeteria);
USEFORM("DBService.cpp",         fDBService);
USEFORM("GuestCardIssue.cpp",    fGuestCardIssue);
USEFORM("InputLine.cpp",         fInputLine);
USEFORM("KPP.cpp",               fKPP);
USEFORM("LicensingAgreement.cpp",fLicensingAgreement);
USEFORM("Login.cpp",             fLogin);
USEFORM("Main.cpp",              fMain);
USEFORM("ObjectsTree.cpp",       fObjectsTree);
USEFORM("OrganizationInfo.cpp",  fOrganizationInfo);
USEFORM("PrintCards.cpp",        fPrintCards);
USEFORM("Report.cpp",            fReport);
USEFORM("ReportChart.cpp",       fReportChart);
USEFORM("Schedules.cpp",         fSchedules);
USEFORM("UnitProperties.cpp",    fUnitProperties);
USEFORM("Zones.cpp",             fZones);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
 DecimalSeparator='.';
 ShortDateFormat = "yyyy-mm-dd";

 try
    {
     Application->Initialize();
     Application->CreateForm(__classid(TfMain), &fMain);
     Application->Run();
    }
 catch (Exception &Exception)
      {
       Application->ShowException(&Exception);
      }
 catch (...)
      {
       try
          {
           throw Exception("");
          }
       catch (Exception &Exception)
            {
             Application->ShowException(&Exception);
            }
      }
 return 0;
}
//---------------------------------------------------------------------------