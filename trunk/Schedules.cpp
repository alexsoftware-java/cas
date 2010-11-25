//---------------------------------------------------------------------------
#include <vcl.h>
#include <DateUtils.hpp>
#pragma hdrstop

#include "InputLine.h"
#include "Main.h"
#include "Schedules.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfSchedules *fSchedules;
//---------------------------------------------------------------------------
__fastcall TfSchedules::TfSchedules(TComponent* Owner) : TForm(Owner)
{
 TStringGrid *Calendars[] = { StringGrid1, StringGrid2, StringGrid3, StringGrid4, StringGrid5, StringGrid6, StringGrid7, StringGrid8, StringGrid9, StringGrid10, StringGrid11, StringGrid12, NULL };
 for (int i = 0; Calendars[i] != NULL; i++)
    Calendars[i]->DefaultDrawing = false;

 selectedCalendar = StringGrid1;

 if (!IBTransaction1->Active)
   IBTransaction1->StartTransaction();

// Корневой элемент TreeView
 TTreeNode *z = TreeView1->Items->AddObject(NULL, "Графики", (void *) -3);
 z->ImageIndex = 0;
 if (fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Objects_links", "left_lnk = -3"))
   z->HasChildren = true;

 IBSQL1->Close();

 TreeView1->TopItem->Expand(false);
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 if ( tbSave->Enabled )
   {
    AnsiString mbCaption = Caption + " -- Предупреждение";
    switch(MessageBox(Handle, "Вы изменяли информацию в базе данных.\nСохранить изменения?", mbCaption.c_str(), MB_YESNOCANCEL | MB_ICONWARNING))
      {
       case IDCANCEL: CanClose = false;
                      break;
       case IDYES   : IBTransaction1->Commit();
                      break;
       case IDNO    : IBTransaction1->Rollback();
                      break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbAddClick(TObject *Sender)
{
 TfInputLine *fInputLine = new TfInputLine(this, "Добавление графика");

 if (fInputLine->ShowModal() == mrOk)
   {
    TTreeNode *tnWhereToAdd = TreeView1->Selected->ImageIndex == 1 ? TreeView1->Selected->Parent : TreeView1->Selected;

    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");

    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  fInputLine->LabeledEdit1->Text.c_str(),
                              "otype", "-123",
                              NULL);
    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects_Links",
                              "link_type", "0",
                              "left_lnk",  IntToStr((int) tnWhereToAdd->Data),
                              "right_lnk", IntToStr(newNN),
                              NULL);

    TreeView1->Items->AddChildObject(tnWhereToAdd, fInputLine->LabeledEdit1->Text, (void *) newNN)->ImageIndex = 1;
    if ( !tnWhereToAdd->Expanded)
      tnWhereToAdd->Expand(false);

    tbSave->Enabled = true;
    tbUndo->Enabled = true;
   }

 delete fInputLine;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbAddFolderClick(TObject *Sender)
{
 TfInputLine *fInputLine = new TfInputLine(this, "Добавление папки графиков");

 if (fInputLine->ShowModal() == mrOk)
   {
    TTreeNode *tnWhereToAdd = TreeView1->Selected->ImageIndex == 1 ? TreeView1->Selected->Parent : TreeView1->Selected;
    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");

    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  fInputLine->LabeledEdit1->Text.c_str(),
                              "otype", "-122",
                              NULL);
    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects_Links",
                              "link_type", "0",
                              "left_lnk",  IntToStr((int) tnWhereToAdd->Data),
                              "right_lnk", IntToStr(newNN),
                              NULL);

    TreeView1->Items->AddChildObject(tnWhereToAdd, fInputLine->LabeledEdit1->Text, (void *) newNN)->ImageIndex = 0;
    if ( !tnWhereToAdd->Expanded)
      tnWhereToAdd->Expand(false);

    tbSave->Enabled = true;
    tbUndo->Enabled = true;
   }

 delete fInputLine;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbAddCopyClick(TObject *Sender)
{
 TfInputLine *fInputLine;
 int OType;

 if ( TreeView1->Selected->ImageIndex == 1 )
   {
    OType = -123;
    fInputLine = new TfInputLine(this, "Добавление графика");
   }
 else
   {
    OType = -122;
    fInputLine = new TfInputLine(this, "Добавление папки графиков");
   }

 if (fInputLine->ShowModal() == mrOk)
   {
    TTreeNode *tnWhereToAdd = TreeView1->Selected->ImageIndex == 1 ? TreeView1->Selected->Parent : TreeView1->Selected;
    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");

    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  fInputLine->LabeledEdit1->Text.c_str(),
                              "otype", IntToStr(OType),
                              NULL);
    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects_Links",
                              "link_type", "0",
                              "left_lnk",  IntToStr((int) tnWhereToAdd->Data),
                              "right_lnk", IntToStr(newNN),
                              NULL);

    TreeView1->Items->AddChildObject(tnWhereToAdd, fInputLine->LabeledEdit1->Text, (void *) newNN)->ImageIndex = (  OType == -122 ? 0 : 1 );
    if ( !tnWhereToAdd->Expanded)
      tnWhereToAdd->Expand(false);

    tbSave->Enabled = true;
    tbUndo->Enabled = true;
   }

 delete fInputLine;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbChangeClick(TObject *Sender)
{
 TfInputLine *fInputLine = new TfInputLine(this, "Изменение названия для   '" + TreeView1->Selected->Text + "'", TreeView1->Selected->Text);

 if (fInputLine->ShowModal() == mrOk)
   {

    fMain->SQL_Fwk->sqlUpdate(IBTransaction1, "Objects",
                              "nn", IntToStr((int) TreeView1->Selected->Data).c_str(),
                              "name", fInputLine->LabeledEdit1->Text.c_str(),
                              NULL);
    TreeView1->Selected->Text = fInputLine->LabeledEdit1->Text;
    tbSave->Enabled = true;
    tbUndo->Enabled = true;
   }

 delete fInputLine;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbDeleteClick(TObject *Sender)
{
 fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Objects", "nn", IntToStr((int) TreeView1->Selected->Data).c_str());
 TreeView1->Items->Delete(TreeView1->Selected);

 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbSaveClick(TObject *Sender)
{
 IBTransaction1->Commit();
 IBTransaction1->StartTransaction();

 TreeView1->Selected = TreeView1->TopItem;
 TreeView1->TopItem->DeleteChildren();
 TreeView1->TopItem->HasChildren = true;
 TreeView1->TopItem->Expand(false);

 tbSave->Enabled = false;
 tbUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::tbUndoClick(TObject *Sender)
{
 IBTransaction1->Rollback();
 IBTransaction1->StartTransaction();

 TreeView1->Selected = TreeView1->TopItem;
 TreeView1->TopItem->DeleteChildren();
 TreeView1->TopItem->HasChildren = true;
 TreeView1->TopItem->Expand(false);

 tbSave->Enabled = false;
 tbUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::TreeView1DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 Accept = (Sender == Source);
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::TreeView1DragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
 TTreeNode *DestinationNode = TreeView1->GetNodeAt(X, Y);  // Куда вешать перетащенное
 if (DestinationNode == NULL)  // а тащат-то в пустоту
   return;

 if (DestinationNode->ImageIndex == 1)  // Юзер тащит в объект, а не папку
   DestinationNode = DestinationNode->Parent;

 for (unsigned int i = 0; i < TreeView1->SelectionCount; i++)
    {
     // Проверяем, что тащат не внутрь самого себя, и что притащили не туда же, откуда тащат
     if ( !DestinationNode->HasAsParent(TreeView1->Selections[i]) && TreeView1->Selections[i]->Parent != DestinationNode )
       {
        IBSQL1->SQL->Text = "UPDATE              \
                                   Objects_links \
                                SET      \
                                   left_lnk = " + IntToStr((int) DestinationNode->Data) + " \
                                WHERE      \
                                     left_lnk = " + IntToStr((int) TreeView1->Selections[i]->Parent->Data) + " \
                                 AND right_lnk = " + IntToStr((int) TreeView1->Selections[i]->Data) + ";";
        IBSQL1->ExecQuery();
        TreeView1->Selections[i]->MoveTo(DestinationNode, naAddChild);

        tbSave->Enabled = true;
        tbUndo->Enabled = true;
       }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::TreeView1Expanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
 if (Node->Count > 0)
   return;

 IBSQL1->SQL->Text = "SELECT                     \
                            Objects.nn,          \
                            Objects.name,        \
                            Objects.description, \
                            Objects.otype        \
                      FROM                       \
                          Objects, Objects_links \
                      WHERE                      \
                           (Objects.otype = -122 OR Objects.otype = -123) \
                       AND Objects.nn = Objects_links.right_lnk \
                       AND Objects_links.left_lnk = " + IntToStr((int) Node->Data) + " \
                      ORDER BY                   \
                              Objects.otype, Objects.name;";
 IBSQL1->ExecQuery();

 for (; !IBSQL1->Eof; IBSQL1->Next())
    {
     TTreeNode *z = TreeView1->Items->AddChildObject(Node,
                                                     IBSQL1->FieldByName("name")->AsString,
                                                     (void *)IBSQL1->FieldByName("nn")->AsInteger);
     z->ImageIndex = IBSQL1->FieldByName("otype")->AsInteger + 123;

     if (IBSQL1->FieldByName("otype")->AsInteger == -122)
       {
        z->ImageIndex = 0;
        if (fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Objects_links", "left_lnk = " + IBSQL1->FieldByName("nn")->AsString))
         z->HasChildren = true;
       }
     else
       z->ImageIndex = 1;
    }

 IBSQL1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
 if (Node == TreeView1->TopItem)
   {
    tbAddCopy->Enabled = false;
    tbChange ->Enabled = false;
    tbDelete ->Enabled = false;
   }
 else
   {
    tbAddCopy->Enabled = true;
    tbChange ->Enabled = true;
    tbDelete ->Enabled = true;
   }

 if ( Node->ImageIndex != 1 ) // папка
   GroupBox1->Visible = false;
 else
   {
    TStringGrid *Calendars[] = { StringGrid1, StringGrid2, StringGrid3, StringGrid4, StringGrid5, StringGrid6, StringGrid7, StringGrid8, StringGrid9, StringGrid10, StringGrid11, StringGrid12, NULL };
    for (int i = 0; Calendars[i] != NULL; i++)
       fillCalendar(Calendars[i], StrToInt(Date().FormatString("yyyy")), i+1);
    GroupBox1->Visible = true;
    updateSelectedInCalendarDay();
    this->ActiveControl = TreeView1; // Если график показывается 1-й раз после загрузки формы, то из-за особенностей setFirstDayInMonthSelected() нужно вернуть ActiveControl
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::TreeView1Changing(TObject *Sender, TTreeNode *Node, bool &AllowChange)
{
 if ( Node->ImageIndex == 0 )
   Node->SelectedIndex = 2;
 else
   Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::TreeView1Editing(TObject *Sender, TTreeNode *Node, bool &AllowEdit)
{
 AllowEdit = false;
 tbChangeClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::Button1Click(TObject *Sender)
{
 if (RadioGroup1->ItemIndex == 0)
   {
    setWeekendsHoliday(selectedCalendar);
    selectedCalendar->Repaint();
   }
 else if (RadioGroup1->ItemIndex == 1)
   {
    TStringGrid *Calendars[] = { StringGrid1, StringGrid2, StringGrid3, StringGrid4, StringGrid5, StringGrid6, StringGrid7, StringGrid8, StringGrid9, StringGrid10, StringGrid11, StringGrid12, NULL };

    for (int i = 0; Calendars[i] != NULL; i++)
       {
        setWeekendsHoliday(Calendars[i]);
        Calendars[i]->Repaint();
       }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::Button2Click(TObject *Sender)
{
 if (RadioGroup1->ItemIndex == 0)
   {
    setTimeForMonth(selectedCalendar);
   }
 else if (RadioGroup1->ItemIndex == 1)
   {
    TStringGrid *Calendars[] = { StringGrid1, StringGrid2, StringGrid3, StringGrid4, StringGrid5, StringGrid6, StringGrid7, StringGrid8, StringGrid9, StringGrid10, StringGrid11, StringGrid12, NULL };
    for (int i = 0; Calendars[i] != NULL; i++)
       setTimeForMonth(Calendars[i]);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::btNavigateCalendarClick(TObject *Sender)
{
 TButton *Button = (TButton *) Sender;

 TStringGrid *Calendars[] = { StringGrid1, StringGrid2, StringGrid3, StringGrid4, StringGrid5, StringGrid6, StringGrid7, StringGrid8, StringGrid9, StringGrid10, StringGrid11, StringGrid12, NULL };

 for (int i = 0; Calendars[i] != NULL; i++)
    {
     if (Button->Name == "btMonthBack")
       fillCalendar(Calendars[i], StrToInt(Calendars[i]->Cells[1][0]), StrToInt(Calendars[i]->Cells[2][0]) - 1);
     else if (Button->Name == "btYearBack")
       fillCalendar(Calendars[i], StrToInt(Calendars[i]->Cells[1][0]) - 1, StrToInt(Calendars[i]->Cells[2][0]));
     else if (Button->Name == "btMonthForward")
       fillCalendar(Calendars[i], StrToInt(Calendars[i]->Cells[1][0]), StrToInt(Calendars[i]->Cells[2][0]) + 1);
     else if (Button->Name == "btYearForward")
       fillCalendar(Calendars[i], StrToInt(Calendars[i]->Cells[1][0]) + 1, StrToInt(Calendars[i]->Cells[2][0]));

     Calendars[i]->Repaint();
    }
 updateSelectedInCalendarDay();
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::sgMonthCalendarSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
 TStringGrid *sgMonthCalendar = (TStringGrid *) Sender;

 if ( ARow > 1 && !sgMonthCalendar->Cells[ACol][ARow].IsEmpty())
   {
    CanSelect = true;

    switch (getDayType(sgMonthCalendar->Cells[1][0],
                       sgMonthCalendar->Cells[2][0],
                       sgMonthCalendar->Cells[ACol][ARow]))
          {
           case 0: cur_gbDayType = 0;
                   rbDayType1->Checked = true;
                   break;
           case 2: cur_gbDayType = 2;
                   rbDayType2->Checked = true;
                   break;
           case 3: cur_gbDayType = 3;
                   rbDayType3->Checked = true;
                   break;
          }

    loadTimeInValueListEditor(vleWorkTime,
                              sgMonthCalendar->Cells[1][0],
                              sgMonthCalendar->Cells[2][0],
                              sgMonthCalendar->Cells[ACol][ARow]);
    cur_vleWorkTime = vleWorkTime->Strings->Text;

    loadTimeInValueListEditor(vleBreaks,
                              sgMonthCalendar->Cells[1][0],
                              sgMonthCalendar->Cells[2][0],
                              sgMonthCalendar->Cells[ACol][ARow]);
    cur_vleBreaks = vleBreaks->Strings->Text;
   }
 else
   {
    CanSelect = false;
    setFirstDayInMonthSelected();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::sgMonthCalendarEnter(TObject *Sender)
{
 if (((TStringGrid *) Sender) != selectedCalendar)
   sgMonthCalendarExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::sgMonthCalendarExit(TObject *Sender)
{
 while ( !this->ActiveControl ) // Пока значение ActiveControl не перестанет быть NULL
   Application->ProcessMessages();

 // Если перешли на StringGrid, то на старом нужно погасить курсор
 if (this->ActiveControl->Name.Pos("StringGrid"))
   {
    TRect CellRect = selectedCalendar->CellRect(selectedCalendar->Col, selectedCalendar->Row);
    sgMonthCalendarDrawCell(selectedCalendar,
                            selectedCalendar->Col,
                            selectedCalendar->Row,
                            CellRect,
                            TGridDrawState());
    selectedCalendar = (TStringGrid *) Sender;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::sgMonthCalendarDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
 TStringGrid *sgMonthCalendar = (TStringGrid *) Sender;

 if ( ARow == 0 ) // название месяца
   {
    Rect.left   = sgMonthCalendar->CellRect(0, 0).left;           // задаём размер прямоугольника
    Rect.top    = sgMonthCalendar->CellRect(6, 0).top;
    Rect.right  = sgMonthCalendar->CellRect(6, 0).right;
    Rect.bottom = sgMonthCalendar->CellRect(6, 0).bottom;
    sgMonthCalendar->Canvas->Brush->Color = clActiveCaption;      // задаём цвет заливки

    sgMonthCalendar->Canvas->Font->Color = clCaptionText;         // задаём параметры шрифта
    sgMonthCalendar->Canvas->Font->Style = TFontStyles()<<fsBold;

    ACol = 0;
  }
 else if ( ARow == 1 ) // название дня
   {
    sgMonthCalendar->Canvas->Brush->Color = clBtnFace;
    sgMonthCalendar->Canvas->Font->Color = clWindowText;
    sgMonthCalendar->Canvas->Font->Style = TFontStyles();
   }
 else  // числа
   {
    switch (getDayType(sgMonthCalendar->Cells[1][0],
                       sgMonthCalendar->Cells[2][0],
                       sgMonthCalendar->Cells[ACol][ARow]))
          {
           case 2:  sgMonthCalendar->Canvas->Brush->Color = TColor (0x008080FF);
                    break;
           case 3:  sgMonthCalendar->Canvas->Brush->Color = clSkyBlue;
                    break;
           default: // пустая клетка (-1), день не значится в БД (0)
                    sgMonthCalendar->Canvas->Brush->Color = clWindow;
                    break;
          }

    sgMonthCalendar->Canvas->Font->Color = clWindowText;

    if (State.Contains(gdFocused) && State.Contains(gdSelected))     // если курсор сейчас на ячейке
      {
       // sgMonthCalendar->Canvas->Brush->Color = clHighlight;
       // sgMonthCalendar->Canvas->Font->Color = clHighlightText;
       sgMonthCalendar->Canvas->Font->Style = TFontStyles()<<fsBold;
      }
    else
      sgMonthCalendar->Canvas->Font->Style = TFontStyles();
   }

 sgMonthCalendar->Canvas->TextRect(Rect,     // пишем текст посередине прямоугольника, не выходя за его границы
                                   Rect.left + ( Rect.right  - Rect.left - sgMonthCalendar->Canvas->TextWidth  ( sgMonthCalendar->Cells[ACol][ARow] ) ) /2,
                                   Rect.top  + ( Rect.bottom - Rect.top  - sgMonthCalendar->Canvas->TextHeight ( sgMonthCalendar->Cells[ACol][ARow] ) ) /2,
                                   sgMonthCalendar->Cells[ACol][ARow]);

 if ( State.Contains(gdSelected) && sgMonthCalendar == selectedCalendar) // если ячейка выбрана
   sgMonthCalendar->Canvas->DrawFocusRect(Rect);
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::rbDayTypeClick(TObject *Sender)
{
 int DayType;

 if ( rbDayType1->Checked )
   DayType = 0;
 else if ( rbDayType2->Checked )
   DayType = 2;
 else if ( rbDayType3->Checked )
   DayType = 3;

 if ( DayType == cur_gbDayType )
   return;
 else
   cur_gbDayType = DayType;

 AnsiString DayDate = selectedCalendar->Cells[1][0] + "-" + selectedCalendar->Cells[2][0] + "-" + selectedCalendar->Cells[selectedCalendar->Col][selectedCalendar->Row];

 fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Schedules_days", "objects_lnk", IntToStr((int) TreeView1->Selected->Data).c_str(),
                                                             "day_date",    DayDate.c_str());
 if ( DayType > 1 )
   fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Schedules_days",
                             "nn",           "GEN_ID(gen_Schedules_days,1)",
                             "objects_lnk",  IntToStr((int) TreeView1->Selected->Data).c_str(),
                             "day_date",     DayDate.c_str(),
                             "day_type",     IntToStr(DayType),
                             NULL);

 TRect CellRect = selectedCalendar->CellRect(selectedCalendar->Col, selectedCalendar->Row);
 sgMonthCalendarDrawCell(selectedCalendar,
                         selectedCalendar->Col,
                         selectedCalendar->Row,
                         CellRect,
                         TGridDrawState() << gdSelected);

 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::ValueListEditorGetEditMask(TObject *Sender, int ACol, int ARow, AnsiString &Value)
{
// Value="90:00;1;_";
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::ValueListEditorValidate(TObject *Sender, int ACol, int ARow, const AnsiString KeyName, const AnsiString KeyValue)
{
// Не проверяется:
// - введено значение только одной колонки
// - курсор передвигали клавишами <-, ->
// - введены буквы
// - кол-во введённых символов большее нужного 
 if (ACol == 0)
   {
    if ( StrToInt(KeyName.SubString(1,2)) > 24 || StrToInt(KeyName.SubString(4,6)) > 59 || KeyName[3] != ':' )
      {
       throw Exception("Время '" + KeyName + "' - некорректно");
      }
   }
 else
   {
    if ( StrToInt(KeyValue.SubString(1,2)) > 24 || StrToInt(KeyValue.SubString(4,6)) > 59 || KeyName[3] != ':' )
      {
       throw Exception("Время '" + KeyValue + "' - некорректно");
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::ValueListEditorExit(TObject *Sender)
{
 TValueListEditor *ValueListEditor = (TValueListEditor *) Sender;

 if ( ValueListEditor->Name == "vleWorkTime" )
   {
    if ( vleWorkTime->Strings->Text == cur_vleWorkTime )
      return;
   }
 else
   {
     if ( vleBreaks->Strings->Text == cur_vleBreaks )
       return;
   }

 saveTimeFromValueListEditor((TValueListEditor *) Sender,
                             selectedCalendar->Cells[1][0],
                             selectedCalendar->Cells[2][0],
                             selectedCalendar->Cells[selectedCalendar->Col][selectedCalendar->Row]);
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::fillCalendar(TStringGrid *sgMonthCalendar, int Year, int Month)
{
 if (Month == 0)       // если в вызывающей функции на единицу уменьшили январь
   {
    Month = 12;
    Year--;
   }
 else if (Month == 13) // или увеличили декабрь
   {
    Month = 1;
    Year++;
   }

 int DaysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

 if (Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0))  // не високосный ли год
   DaysInMonth[2]++;

 for (int i = 0; i < sgMonthCalendar->ColCount; i++)
    for (int j = 0; j < sgMonthCalendar->RowCount; j++)
       sgMonthCalendar->Cells[i][j] = "";

 sgMonthCalendar->Cells[0][0] = LongMonthNames[Month - 1] + "  (" + Year + ")";

 sgMonthCalendar->Cells[1][0] = Year;
 sgMonthCalendar->Cells[2][0] = Month;

 sgMonthCalendar->Cells[0][1] = ShortDayNames[1].UpperCase();
 sgMonthCalendar->Cells[1][1] = ShortDayNames[2].UpperCase();
 sgMonthCalendar->Cells[2][1] = ShortDayNames[3].UpperCase();
 sgMonthCalendar->Cells[3][1] = ShortDayNames[4].UpperCase();
 sgMonthCalendar->Cells[4][1] = ShortDayNames[5].UpperCase();
 sgMonthCalendar->Cells[5][1] = ShortDayNames[6].UpperCase();
 sgMonthCalendar->Cells[6][1] = ShortDayNames[0].UpperCase();

 int curDate = 1,
     X       = DayOfTheWeek(EncodeDate(Year,Month,1)) - 1;

 for (int Y = 1; curDate <= DaysInMonth[Month]; Y++)
    {
     for (; X < 7 && curDate <= DaysInMonth[Month]; X++)
        {
         sgMonthCalendar->Cells[X][Y+1] = IntToStr(curDate);
         curDate++;
        }
     X = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::setFirstDayInMonthSelected()
{
// Обработка дурацкого глюка StringGrid - если на нём никогда не выделяли ячейку,
// то выделить её программно иным способом не получается
 TPoint NewPoint,
        OldPoint = Mouse->CursorPos;

 TRect CellRect = selectedCalendar->CellRect(DayOfTheWeek( EncodeDate( StrToInt(selectedCalendar->Cells[1][0]), StrToInt(selectedCalendar->Cells[2][0]), 1 ) ) - 1, 2);
 NewPoint.x = CellRect.Left + 5;
 NewPoint.y = CellRect.Top + 5;

 NewPoint = selectedCalendar->ClientToScreen(NewPoint);

 Mouse->CursorPos = NewPoint;
 mouse_event( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ); // нажали левую кнопку
 mouse_event( MOUSEEVENTF_LEFTUP,   0, 0, 0, 0 ); // отжали левую кнопку

 Mouse->CursorPos = OldPoint;
 Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::updateSelectedInCalendarDay()
{
 if ( selectedCalendar->Cells[selectedCalendar->Col][selectedCalendar->Row].IsEmpty() ) // Выделеная ячейка теперь пустая
   {
    selectedCalendar->Col = DayOfTheWeek( EncodeDate( StrToInt(selectedCalendar->Cells[1][0]), StrToInt(selectedCalendar->Cells[2][0]), 1 ) ) - 1;
    selectedCalendar->Row = 2;
   }
 else // Просто загрузили новый график - нужно обновить тип дня и времена
   {
    bool CanSelect = true;
    sgMonthCalendarSelectCell(selectedCalendar, selectedCalendar->Col, selectedCalendar->Row, CanSelect);
   }
}
//---------------------------------------------------------------------------
int __fastcall TfSchedules::getDayType(AnsiString Year, AnsiString Month, AnsiString Day)
{
 // -1: пустая клетка
 //  0: день не значится в БД
 //  2: выходной
 //  3: праздник
 if ( Day.IsEmpty() )
   return -1;

 int DayType;
 IBSQL1->SQL->Text = "SELECT                        \
                            Schedules_days.day_type \
                      FROM                          \
                          Schedules_days            \
                      WHERE                         \
                           Schedules_days.day_date = '" + Year + "-" + Month + "-" + Day + "' \
                       AND Schedules_days.objects_lnk = " + IntToStr((int) TreeView1->Selected->Data) + ";";
 IBSQL1->ExecQuery();

 if ( IBSQL1->FieldByName("day_type")->IsNull )
   DayType = 0;
 else
   DayType = IBSQL1->FieldByName("day_type")->AsInteger;

 IBSQL1->Close();

 return DayType;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::setWeekendsHoliday(TStringGrid *sgMonthCalendar)
{
 AnsiString Day_date;

 for (int i = 2; i < sgMonthCalendar->RowCount; i++)
    for (int j = 5; j < sgMonthCalendar->ColCount; j++)
       if ( !sgMonthCalendar->Cells[j][i].IsEmpty() )
         {
          Day_date = sgMonthCalendar->Cells[1][0] + "-" + sgMonthCalendar->Cells[2][0] + "-" + sgMonthCalendar->Cells[j][i];
          fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Schedules_days", "objects_lnk", IntToStr((int) TreeView1->Selected->Data).c_str(),
                                                                      "day_date",    Day_date.c_str());
          fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Schedules_days",
                                    "nn",          "GEN_ID(gen_Schedules_days,1)",
                                    "objects_lnk", IntToStr((int) TreeView1->Selected->Data).c_str(),
                                    "day_date",    Day_date.c_str(),
                                    "day_type",    "2",
                                    NULL);
         }
 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::loadTimeInValueListEditor(TValueListEditor *ValueListEditor, AnsiString Year, AnsiString Month, AnsiString Day)
{
 AnsiString Table = ValueListEditor->Name == "vleWorkTime" ? "Schedules_whours" : "Schedules_breaks";

 ValueListEditor->Strings->Clear();

 IBSQL1->SQL->Text = "SELECT            \
                            begin_time, \
                            end_time    \
                      FROM              \
                           " + Table + "\
                      WHERE             \
                           day_date = '" + Year + "-" + Month + "-" + Day + "' \
                       AND objects_lnk = " + IntToStr((int) TreeView1->Selected->Data) + ";";
 IBSQL1->ExecQuery();

 for (; !IBSQL1->Eof; IBSQL1->Next())
    {
     ValueListEditor->Strings->Add(IBSQL1->FieldByName("begin_time")->AsString.SubString(1,5)
                                   + "="
                                   + IBSQL1->FieldByName("end_time")->AsString.SubString(1,5));
    }

 IBSQL1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::saveTimeFromValueListEditor(TValueListEditor *ValueListEditor, AnsiString Year, AnsiString Month, AnsiString Day)
{
 AnsiString Day_date = Year + "-" + Month + "-" + Day,
            Table    = ValueListEditor->Name == "vleWorkTime" ? "Schedules_whours" : "Schedules_breaks",
            TableGen = "GEN_ID(gen_" + Table + ",1)";

 fMain->SQL_Fwk->sqlDelete(IBTransaction1, Table.c_str(), "objects_lnk", IntToStr((int) TreeView1->Selected->Data).c_str(),
                                                          "day_date",    Day_date.c_str());

 for (int i = 1; i < ValueListEditor->RowCount; i++)
    {
     fMain->SQL_Fwk->sqlInsert(IBTransaction1, Table.c_str(),
                               "nn",           TableGen.c_str(),
                               "objects_lnk",  IntToStr((int) TreeView1->Selected->Data).c_str(),
                               "day_date",     Day_date.c_str(),
                               "begin_time",   ValueListEditor->Cells[0][i].c_str(),
                               "end_time",     ValueListEditor->Cells[1][i].c_str(),
                               NULL);
    }

 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfSchedules::setTimeForMonth(TStringGrid *sgMonthCalendar)
{
 for (int i = 2; i < sgMonthCalendar->RowCount; i++)
    for (int j = 0; j < sgMonthCalendar->ColCount; j++)
       if ( !sgMonthCalendar->Cells[j][i].IsEmpty() )
         {
          saveTimeFromValueListEditor(vleWorkTime,
                                      sgMonthCalendar->Cells[1][0],
                                      sgMonthCalendar->Cells[2][0],
                                      sgMonthCalendar->Cells[j][i]);
          saveTimeFromValueListEditor(vleBreaks,
                                      sgMonthCalendar->Cells[1][0],
                                      sgMonthCalendar->Cells[2][0],
                                      sgMonthCalendar->Cells[j][i]);
         }
 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------