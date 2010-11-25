//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Report.h"
#include "ReportChart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pr_Classes"
#pragma link "pr_Common"
#pragma resource "*.dfm"
TfReport *fReport;
//---------------------------------------------------------------------------
__fastcall TfReport::TfReport(TComponent* Owner, TDateTime BeginDate_, AnsiString BeginTimeInWords_, TDateTime EndDate_, AnsiString EndTimeInWords_) : TForm(Owner)
{
 BeginDate = BeginDate_;
 EndDate   = EndDate_;
 BeginTimeInWords = BeginTimeInWords_;
 EndTimeInWords   = EndTimeInWords_;

 prIniFileName = fMain->ExePath + "Reports\\pr.ini";
}
//---------------------------------------------------------------------------
void __fastcall TfReport::PrepareData(int ReportType, int ReportMode, int ParentObject, AnsiString dopInfo)
{
 switch (ReportType)
 {
  case 100: // ������� ������� ��� ����������� Unit'�
            IBQuery1->SQL->Text = "\
SELECT \
      Log.datetime, \
      Eventtypes.name AS event_name \
FROM     \
    Log  \
JOIN     \
    Eventtypes ON Log.eventtypes_lnk = Eventtypes.nn \
WHERE    \
     Log.objects_lnk = " + IntToStr(ParentObject) + "\
ORDER BY \
        Log.datetime;";
            IBQuery1->Prepare();  IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\unit_log.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "������� ������� ��� " + dopInfo;
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("(������ �� dddd, dd mmmm yyyy ����)");
            break;
  case 200: // ��������� ������� � ��� �� ������� � �������
            IBQuery1->SQL->Text = "\
SELECT DISTINCT \
               Units.fname, \
               Units.mname, \
               Units.lname, \
               Units.structure_name \
FROM \
    Units \
JOIN \
    Units_location ON Units.objects_lnk = Units_location.objects_lnk \
WHERE \
     Units_location.zones_lnk = " + IntToStr(fMain->cfgZone_NN) + "\
 AND Units_location.datetime LIKE '" +  BeginDate.DateString() + "%' \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname;";
            IBQuery1->Prepare(); IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\who_here.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "����������� �� ���������� � " + BeginTimeInWords;
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("� dddd, dd mmmm yyyy ����");
            break;
  case 210: // ���������������
            IBQuery1->SQL->Text = "\
SELECT \
      Units.fname, \
      Units.mname, \
      Units.lname, \
      Units.structure_name \
FROM \
    Units \
WHERE \
     Units.enabled = 1 \
 AND Units.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
 AND Units.objects_lnk NOT IN ( \
                               SELECT DISTINCT \
                                      Log.objects_lnk \
                               FROM \
                                   Log \
                               WHERE \
                                  ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evManualEntry) + " )\
                                 AND Log.datetime BETWEEN '" + BeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + EndDate.DateString() + " " + EndTimeInWords + "' \
                              ) \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname;";
            IBQuery1->Prepare(); IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\who_here.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "���������������";
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + BeginTimeInWords + EndDate.FormatString("  --  dddd, dd mmmm yyyy ���� ") + EndTimeInWords;
            break;
  case 250: // ���������� ����������� ������
            IBQuery1->SQL->Text = "\
SELECT \
      Units.lname || ' ' || Units.fname || ' ' || Units.mname AS full_name, \
      Units.structure_name, \
      Log.datetime, Eventtypes.name AS event_name \
FROM           \
    Units, Log \
JOIN           \
    Eventtypes ON Log.eventtypes_lnk = Eventtypes.nn \
WHERE          \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evNotRegisteredEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evNotRegisteredExit) + " ) \
 AND Log.datetime BETWEEN '" + BeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + EndDate.DateString() + " " + EndTimeInWords + "' \
 AND Log.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname, \
        Log.datetime;";
            IBQuery1->Prepare(); IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\arrived_exited.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "���������� ����������� ������";
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + BeginTimeInWords + EndDate.FormatString("  --  dddd, dd mmmm yyyy ���� ") + EndTimeInWords;
            break;
  case 300: // ����� � ������ �� ������
            IBQuery1->SQL->Text = "\
SELECT \
      Units.lname || ' ' || Units.fname || ' ' || Units.mname AS full_name, \
      Units.structure_name, \
      Log.datetime, \
      Eventtypes.name AS event_name \
FROM           \
    Units, Log \
JOIN           \
    Eventtypes ON Log.eventtypes_lnk = Eventtypes.nn \
WHERE          \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evManualEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evExit) + " OR Log.eventtypes_lnk = " + IntToStr(evManualExit) + " )\
 AND Log.datetime BETWEEN '" + BeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + EndDate.DateString() + " " + EndTimeInWords + "' \
 AND Log.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname, \
        Log.datetime;";
            IBQuery1->Prepare(); IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\arrived_exited.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "����� � ������";
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + BeginTimeInWords + EndDate.FormatString("  --  dddd, dd mmmm yyyy ���� ") + EndTimeInWords;
            break;
  case 310:{// ��������� � ���������� ������� �� ������
            AnsiString S;
            TDateTime cBeginDate = BeginDate;
                       
            for (S = ""; cBeginDate <= EndDate; cBeginDate++)
               S += "Log.datetime BETWEEN '" + cBeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + cBeginDate.DateString() + " " + EndTimeInWords + "' OR ";
            S.SetLength(S.Length()-3);

            IBQuery1->SQL->Text = "\
SELECT \
      Units.lname || ' ' || Units.fname || ' ' || Units.mname AS full_name, \
      Units.structure_name, \
      Log.datetime, \
      Eventtypes.name AS event_name \
FROM           \
    Units, Log \
JOIN           \
    Eventtypes ON Log.eventtypes_lnk = Eventtypes.nn \
WHERE          \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evManualEntry) + " )\
 AND (" + S + ") \
 AND Log.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname, \
        Log.datetime;";
            IBQuery1->Prepare();  IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\arrived_exited.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "��������� ����� " + BeginTimeInWords + " � " + EndTimeInWords;
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + EndDate.FormatString("  --  dddd, dd mmmm yyyy ����");
           }break;
  case 320:{// ������� � ���������� ������� �� ������
            AnsiString S;
            TDateTime cBeginDate = BeginDate;
                       
            for (S = ""; cBeginDate <= EndDate; cBeginDate++)
               S += "Log.datetime BETWEEN '" + cBeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + cBeginDate.DateString() + " " + EndTimeInWords + "' OR ";
            S.SetLength(S.Length()-3);

            IBQuery1->SQL->Text = "\
SELECT \
      Units.lname || ' ' || Units.fname || ' ' || Units.mname AS full_name, \
      Units.structure_name, \
      Log.datetime, \
      Eventtypes.name AS event_name \
FROM           \
    Units, Log \
JOIN           \
    Eventtypes ON Log.eventtypes_lnk = Eventtypes.nn \
WHERE          \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evExit) + " OR Log.eventtypes_lnk = " + IntToStr(evManualExit) + " )\
 AND (" + S + ") \
 AND Log.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname, \
        Log.datetime;";
            IBQuery1->Prepare();  IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\arrived_exited.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "������� ����� " + BeginTimeInWords + " � " + EndTimeInWords;
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + EndDate.FormatString("  --  dddd, dd mmmm yyyy ����");
           }break;
  case 400:{ // ���������
            IBQuery1->SQL->Text = "\
SELECT \
      Units.structure_name,  \
      COUNT(DISTINCT Units.nn) \
FROM      \
    Units \
WHERE     \
     Units.enabled = 1 \
 AND Units.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
GROUP BY  \
        Units.structure_name \
ORDER BY  \
        Units.structure_name DESC;";
            IBQuery2->SQL->Text = "\
SELECT DISTINCT \
               Units.structure_name, \
               COUNT(DISTINCT Log.objects_lnk) \
FROM \
    Log, Units \
WHERE \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evManualEntry) + " )\
 AND Log.datetime LIKE '" +  BeginDate.DateString() + "%' \
GROUP BY \
        Units.structure_name;";
            TfReportChart *fReportChart = new TfReportChart(Application);
            fReportChart->dt = BeginDate;
            fReportChart->Chart1->Title->Text->Text = BeginDate.FormatString("��������� ������������ � dddd, dd mmmm yyyy ����");

            std::vector<AnsiString> structureName;
            std::vector<int> countTotal;
            std::vector<int> countHere;

            IBQuery1->Prepare();  IBQuery1->Open();
            while (!IBQuery1->Eof)
              {
               structureName.push_back(IBQuery1->FieldByName("structure_name")->AsString);
               countTotal.push_back(IBQuery1->FieldByName("count")->AsInteger);
               countHere.push_back(0);
               IBQuery1->Next();
              }
            IBQuery1->Close();  IBQuery1->UnPrepare();

            IBQuery2->Prepare();  IBQuery2->Open();
            while (!IBQuery2->Eof)
              {
               for (unsigned int i = 0; i < structureName.size(); i++)
                  if (structureName[i] == IBQuery2->FieldByName("structure_name")->AsString)
                    {
                     countHere[i] = IBQuery2->FieldByName("count")->AsInteger;
                     break;
                    }
               IBQuery2->Next();
              }
            IBQuery2->Close();  IBQuery2->UnPrepare();

            int cTotal = 0, cHere = 0;
            for (unsigned int i = 0; i < structureName.size(); i++)
               {
                cTotal += countTotal[i];
                cHere += countHere[i];
               }
            fReportChart->Series1->Add(cTotal, "����� �����");
            fReportChart->Series2->Add(cHere, "����� �����");

            for (unsigned int i = 0; i < structureName.size(); i++)
               {
                fReportChart->Series1->Add(countTotal[i], structureName[i]);
                fReportChart->Series2->Add(countHere[i], structureName[i]);
               }

            this->Close();
            return;
           }
  case 401: // ������������� � �������������� � ���������� ������ �� ���������
            IBQuery1->SQL->Text = "\
SELECT DISTINCT \
               Units.lname, Units.fname, Units.mname, Units.structure_name \
FROM \
    Log, Units \
WHERE \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evManualEntry) + " )\
 AND Units.structure_name = '" + dopInfo + "' \
 AND Log.datetime LIKE '" + BeginDate.DateString() + "%' \
ORDER BY \
        Units.lname, Units.fname, Units.mname;";
            IBQuery1->Prepare();  IBQuery1->Open();
            IBQuery2->SQL->Text = "\
SELECT \
      Units.lname, \
      Units.fname, \
      Units.mname  \
FROM \
    Units \
WHERE \
     Units.enabled = 1 \
 AND Units.structure_name = '" + dopInfo + "' \
 AND Units.objects_lnk NOT IN ( \
                               SELECT DISTINCT \
                                               Units.objects_lnk \
                               FROM \
                                   Log, Units  \
                               WHERE \
                                    Units.objects_lnk = Log.objects_lnk \
                                AND ( Log.eventtypes_lnk = " + IntToStr(evEntry) + " OR Log.eventtypes_lnk = " + IntToStr(evManualEntry) + " )\
                                AND Units.structure_name = '" + dopInfo + "' \
                                AND Log.datetime LIKE '" + BeginDate.DateString() + "%' \
                               ) \
ORDER BY \
        Units.lname, \
        Units.fname, \
        Units.mname;";
            IBQuery2->Prepare();  IBQuery2->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\chart_1.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "������������� � �������������� � " + dopInfo;
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ����");
            break;
  case 500: // ���������� ������ � �������� � ���������� �������
            IBQuery1->SQL->Text = "\
SELECT \
      Units.lname || ' ' || Units.fname || ' ' || Units.mname AS full_name, \
      Units.structure_name, \
      COUNT (*) AS rc \
FROM \
    Units, Log \
WHERE \
     Units.objects_lnk = Log.objects_lnk \
 AND Log.eventtypes_lnk = " + IntToStr(evMealDiscount) + " \
 AND Log.datetime BETWEEN '" + BeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + EndDate.DateString() + " " + EndTimeInWords + "' \
 AND Log.objects_lnk IN (SELECT o_nn FROM GC ("+ IntToStr(ParentObject) +")) \
GROUP BY \
        full_name, Units.structure_name \
ORDER BY \
        Units.structure_name, full_name;";
            IBQuery1->Prepare(); IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\haved_dinner.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "���������� ������ � ��������";
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + BeginTimeInWords + EndDate.FormatString("  --  dddd, dd mmmm yyyy ���� ") + EndTimeInWords;
            break;
  case 501: // ���������� �������� ������ � �������� � ���������� �������
            IBQuery1->SQL->Text = "\
SELECT \
      Units.lname || ' ' || Units.fname || ' ' || Units.mname AS full_name, \
      Units.structure_name, \
      Log.datetime, Eventtypes.name AS event_name \
FROM \
    Units, Log \
JOIN \
    Eventtypes ON Log.eventtypes_lnk = Eventtypes.nn \
WHERE          \
     Units.objects_lnk = Log.objects_lnk \
 AND ( Log.eventtypes_lnk = " + IntToStr(evMealDiscountAttempt) + " OR Log.eventtypes_lnk = " + IntToStr(evMealDiscountWithDisabledCardAttempt) + " OR Log.eventtypes_lnk = " + IntToStr(evMealDiscountWithExpiredCardAttempt) + " ) \
 AND Log.datetime BETWEEN '" + BeginDate.DateString() + " " + BeginTimeInWords + "' AND '" + EndDate.DateString() + " " + EndTimeInWords + "' \
ORDER BY \
        Units.structure_name, \
        Units.lname, \
        Units.fname, \
        Units.mname, \
        Log.datetime;";
            IBQuery1->Prepare(); IBQuery1->Open();
            prReport1->LoadTemplateFromFile(fMain->ExePath + "Reports\\arrived_exited.prt",false);
            prReport1->Variables->ByName["ReportTitle"]->AsString = "���������� �������� ������ � ��������";
            prReport1->Variables->ByName["ReportPeriod"]->AsString = BeginDate.FormatString("������:  dddd, dd mmmm yyyy ���� ") + BeginTimeInWords + EndDate.FormatString("  --  dddd, dd mmmm yyyy ���� ") + EndTimeInWords;
            break;

 }

 prReport1->Title = prReport1->Variables->ByName["ReportTitle"]->AsString;

 switch (ReportMode)
 {
  case  0: if (prReport1->PrepareReport())
             prReport1->PreviewPreparedReport(false);
           break;
  case  1: if (prReport1->PrepareReport())
             prReport1->PrintPreparedReport();
           break;
  case  2: prReport1->DesignReport(false);
           break;
 }
 this->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfReport::prReport1DestroyPreview(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------