//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Report.h"
#include "PrintCards.h"
#include "UnitProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfUnitProperties *fUnitProperties;
//---------------------------------------------------------------------------
__fastcall TfUnitProperties::TfUnitProperties(TComponent* Owner,
                                              int ObjectID_,   /* = 0 */
                                              int ActionType_, /* = 1 */
                                              int StructureNN_ /* = 0 */) : TForm(Owner)
// actionType:
// 1 - Просмотр таблицей, 2 - Просмотр карточкой
// 11 - Добавление, 12 - Добавление копированием, 13 - Изменение
{
 ControlCR = NULL;
 bmpCard   = NULL;
 ViewStyle = 1;

 if ( fMain->cfgPhotosPath == "::db" ) // Если фото в БД, то переименовывать при загрузке не надо
   {
    chbRenamePhoto->Checked = false;
    chbRenamePhoto->Enabled = false;
   }

 if (fMain->userType == utUser)
   {
//    PageControl2_ts2->TabVisible = false;
//    btLoadPhoto   ->Visible = false;
//    btDeletePhoto ->Visible = false;
//    chbRenamePhoto->Visible = false;

    tbChange ->Visible = ( fMain->userRights[7] == '1' );
    tbAdd    ->Visible = ( fMain->userRights[8] == '1' );
    tbAddCopy->Visible = ( fMain->userRights[8] == '1' );
    tbDelete ->Visible = ( fMain->userRights[9] == '1' );
   }

 IBDataSet1->Prepare();  IBDataSet1->Open();

 if (ActionType_ == 11)
   {
    fMain->SQL_Fwk->fillDictionary("SELECT * FROM Objects WHERE otype != 0 AND otype != -123 AND otype != -113 AND otype != -103 ORDER BY name",
                                   "nn",
                                   "name",
                                   structuresList,
                                   ComboBox1,
                                   StructureNN_);
   }
 else // Если не "Добавление", то ищем соответствующую запись в базе
   {
    while (!IBDataSet1->Eof && IBDataSet1->FieldByName("objects_lnk")->AsInteger != ObjectID_)
         IBDataSet1->Next();

    fMain->SQL_Fwk->fillDictionary("SELECT * FROM Objects WHERE otype != 0 AND otype != -123 AND otype != -113 AND otype != -103 ORDER BY name",
                                   "nn",
                                   "name",
                                   structuresList,
                                   ComboBox1,
                                   -1);
    IBDataSet1AfterScroll(IBDataSet1);
   }

 IBDataSet1->AfterScroll = IBDataSet1AfterScroll;

 switch (ActionType_)
   {
    case  1: PageControl1->ActivePage = pc1_tsGrid;
             prepareForViewing();
             break;
    case  2: PageControl1->ActivePage = pc1_tsCard;
             prepareForViewing();    
             break;
    case 11: tbAddClick(this);
             break;
    case 12: tbAddCopyClick(this);
             break;
    case 13: tbChangeClick(this);
             break;
   }
}
//---------------------------------------------------------------------------
__fastcall TfUnitProperties::~TfUnitProperties()
{
 if ( bmpCard != NULL )
   delete bmpCard;

 if ( ControlCR != NULL )
   delete ControlCR;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, const TPoint &MousePos, bool &Handled)
{
 if ( WheelDelta > 0 )
   tbPriorClick(Sender);
 else
   tbNextClick(Sender);

 Handled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::FormCloseQuery(TObject *Sender, bool &CanClose)
{
 mbCaption = Caption + " -- Предупреждение";

 if (tbSave->Enabled)
   switch(MessageBox(Handle, "Вы изменяли информацию в базе данных.\nСохранить изменения?\n", mbCaption.c_str(), MB_YESNOCANCEL | MB_ICONWARNING))
     {
      case IDCANCEL: CanClose = false;
                     break;
      case IDYES   : IBTransaction1->Commit();
                     break;
      case IDNO    : IBTransaction1->Rollback();
                     break;
     }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::IBDataSet1IsEmpyCheck(TDataSet *DataSet)
{
 if (IBDataSet1->IsEmpty())
   {
    tbAddCopy->Enabled = false;
    tbChange ->Enabled = false;
    tbDelete ->Enabled = false;
    tbPrior  ->Enabled = false;
    tbNext   ->Enabled = false;
    DBGrid1->OnDblClick = NULL;
   }
 else
   {
    tbAddCopy->Enabled = true;
    tbChange ->Enabled = true;
    tbDelete ->Enabled = true;
    DBGrid1->OnDblClick = DBGrid1DblClick;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::IBDataSet1AfterChange(TDataSet *DataSet)
{
 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::IBDataSet1AfterDelete(TDataSet *DataSet)
{
 IBDataSet1IsEmpyCheck(IBDataSet1);
 IBDataSet1AfterChange(IBDataSet1);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::IBDataSet1AfterScroll(TDataSet *DataSet)
{
 LabeledEdit4   ->Text     = IBDataSet1->FieldByName("card")             ->AsString;
 ComboBox2      ->ItemIndex= IBDataSet1->FieldByName("card_type")        ->AsInteger;
 chbEnabled     ->Checked  = IBDataSet1->FieldByName("enabled")          ->AsInteger;
 DateTimePicker1->DateTime = IBDataSet1->FieldByName("expire")           ->AsDateTime;
 LabeledEdit5   ->Text     = IBDataSet1->FieldByName("passwrd")          ->AsString;
 LabeledEdit6   ->Text     = IBDataSet1->FieldByName("template")         ->AsString;
 chbMarkedForPrinting->Checked= IBDataSet1->FieldByName("marked_for_printing")->AsInteger;
 LabeledEdit8   ->Text     = IBDataSet1->FieldByName("web_login")        ->AsString;
 LabeledEdit9   ->Text     = IBDataSet1->FieldByName("web_password")     ->AsString;
 LabeledEdit1   ->Text     = IBDataSet1->FieldByName("lname")            ->AsString;
 LabeledEdit2   ->Text     = IBDataSet1->FieldByName("fname")            ->AsString;
 LabeledEdit3   ->Text     = IBDataSet1->FieldByName("mname")            ->AsString;
 chbSMSEnabled->Checked    = IBDataSet1->FieldByName("sms_enabled")      ->AsInteger;
 LabeledEdit7   ->Text     = IBDataSet1->FieldByName("sms_phone")        ->AsString;
 DateTimePicker2->DateTime = IBDataSet1->FieldByName("birthday")         ->AsDateTime;
 LabeledEdit11  ->Text     = IBDataSet1->FieldByName("home_address")     ->AsString;
 LabeledEdit12  ->Text     = IBDataSet1->FieldByName("phone")            ->AsString;
 LabeledEdit13  ->Text     = IBDataSet1->FieldByName("medical_policy")   ->AsString;
 LabeledEdit21  ->Text     = IBDataSet1->FieldByName("father_fio")       ->AsString;
 LabeledEdit22  ->Text     = IBDataSet1->FieldByName("father_employment")->AsString;
 LabeledEdit23  ->Text     = IBDataSet1->FieldByName("father_post")      ->AsString;
 LabeledEdit24  ->Text     = IBDataSet1->FieldByName("father_phone")     ->AsString;
 LabeledEdit25  ->Text     = IBDataSet1->FieldByName("father_info")      ->AsString;
 LabeledEdit31  ->Text     = IBDataSet1->FieldByName("mother_fio")       ->AsString;
 LabeledEdit32  ->Text     = IBDataSet1->FieldByName("mother_employment")->AsString;
 LabeledEdit33  ->Text     = IBDataSet1->FieldByName("mother_post")      ->AsString;
 LabeledEdit34  ->Text     = IBDataSet1->FieldByName("mother_phone")     ->AsString;
 LabeledEdit35  ->Text     = IBDataSet1->FieldByName("mother_info")      ->AsString;

 if (IBDataSet1->FieldByName("rights")->IsNull)
   for (int i = 0; i < CheckListBox1->Items->Count; i++)
      CheckListBox1->Checked[i] = false;
 else
   {
    AnsiString Rights = IBDataSet1->FieldByName("rights")->AsString;
    for (int i = 0; i < Rights.Length(); i++)
       CheckListBox1->Checked[i] = ( Rights[i+1] == '0' ? false : true );
   }

 for (unsigned int i = 0, j = IBDataSet1->FieldByName("structures_lnk")->AsInteger; i < structuresList.size(); i++)
#pragma warn -csu
    if (structuresList[i] == j)
#pragma warn .csu
      {
       ComboBox1->ItemIndex = i;
       break;
      }

 if ( fMain->cfgPhotosPath == "::db" )
   {
    Image1->Tag = 0;
    if ( !fMain->SQL_Fwk->PhotoToBitmap(IBDataSet1, Image1->Picture->Bitmap) )
      Image1->Picture = NULL;
   }
 else
   {
    try {
         Image1->Picture->LoadFromFile(fMain->cfgPhotosPath + IBDataSet1->FieldByName("card")->AsString + ".jpg");
        }
    catch (const EFOpenError &Exception)
         {
          Image1->Picture = NULL;
         }
   }


 delete bmpCard;
 bmpCard = NULL;
 PaintBox1->Repaint();

 tbPrior->Enabled = !IBDataSet1->Bof;
 tbNext ->Enabled = !IBDataSet1->Eof;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbAddClick(TObject *Sender)
{
 Caption = "Списочный состав организации  --  Добавление";
 LabeledEdit1 ->Text = "";
 LabeledEdit2 ->Text = "";
 LabeledEdit3 ->Text = "";
 LabeledEdit4 ->Text = "";
 LabeledEdit5 ->Text = "";
 LabeledEdit6 ->Text = "";
 LabeledEdit7 ->Text = "";
 LabeledEdit8 ->Text = "";
 LabeledEdit9 ->Text = "";
 LabeledEdit11->Text = "";
 LabeledEdit12->Text = "";
 LabeledEdit13->Text = "";
 LabeledEdit21->Text = "";
 LabeledEdit22->Text = "";
 LabeledEdit23->Text = "";
 LabeledEdit24->Text = "";
 LabeledEdit25->Text = "";
 LabeledEdit31->Text = "";
 LabeledEdit32->Text = "";
 LabeledEdit33->Text = "";
 LabeledEdit34->Text = "";
 LabeledEdit35->Text = "";
 ComboBox2->ItemIndex = 0;
 chbEnabled->Checked = true;
 DateTimePicker1->DateTime = TDateTime(2008, 9, 1);
 chbSMSEnabled->Checked = false;
 chbMarkedForPrinting->Checked = false;
 Image1->Picture = NULL;

 ActionType = 11;

 prepareForEditing();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbAddCopyClick(TObject *Sender)
{
 Caption = "Списочный состав организации  --  Добавление";
 Image1->Picture = NULL;
 ActionType = 12;

 prepareForEditing();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbChangeClick(TObject *Sender)
{
 Caption = "Списочный состав организации  --  Изменение";

 ActionType = 13;

 prepareForEditing();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbDeleteClick(TObject *Sender)
{
 int nn = IBDataSet1->FieldByName("objects_lnk")->AsInteger;
 IBDataSet1->Delete();
 fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Objects", "nn", IntToStr(nn).c_str());
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbSaveOrUndoClick(TObject *Sender)
{
 if (((TToolButton *)Sender)->Name == "tbSave")
   IBTransaction1->Commit();
 else
   IBTransaction1->Rollback();

 IBTransaction1->StartTransaction();

 tbSave->Enabled = false;
 tbUndo->Enabled = false;

 IBDataSet1->Prepare();  IBDataSet1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbPriorClick(TObject *Sender)
{
 IBDataSet1->Prior();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::tbNextClick(TObject *Sender)
{
 IBDataSet1->Next();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::DBGrid1TitleClick(TColumn *Column)
{
 if (IBDataSet1->SelectSQL->Strings[IBDataSet1->SelectSQL->Count - 1] != Column->FieldName + ";")
   {
    IBDataSet1->SelectSQL->Strings[IBDataSet1->SelectSQL->Count - 1] = Column->FieldName + ";";
    IBDataSet1->Prepare();  IBDataSet1->Open();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::DBGrid1DblClick(TObject *Sender)
{
 if (fMain->userRights[7] == '1')
   tbChangeClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::PaintBox1Paint(TObject *Sender)
{
 if ( bmpCard != NULL )
   PaintBox1->Canvas->StretchDraw(PaintBox1->ClientRect, bmpCard);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btEventsListClick(TObject *Sender)
{
 TfReport *fReport = new TfReport(Application, Date());
 fReport->PrepareData(100, 0, IBDataSet1->FieldByName("objects_lnk")->AsInteger,
                              IBDataSet1->FieldByName("lname")->AsString + " "  +
                              IBDataSet1->FieldByName("fname")->AsString + " "  +
                              IBDataSet1->FieldByName("mname")->AsString + ", " +
                              ComboBox1->Items->Strings[ComboBox1->ItemIndex]);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btSetResidenceTodayClick(TObject *Sender)
{
 fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, IBDataSet1->FieldByName("objects_lnk")->AsInteger, evManualEntry);
 fMain->SQL_Fwk->addEvent(fMain->cfgZone_NN, IBDataSet1->FieldByName("objects_lnk")->AsInteger, evManualExit);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btLoadPhotoClick(TObject *Sender)
{
 if ( LabeledEdit4->Text.IsEmpty() && fMain->cfgPhotosPath != "::db" )
   {
    mbCaption = Caption + " -- Ошибка",
    MessageBox(Handle, "Загрузка фотографии возможна только после ввода номера карточки.\n", mbCaption.c_str(), MB_OK | MB_ICONERROR);
    return;
   }

 if (OpenPictureDialog1->Execute())
   {
    if ( fMain->cfgPhotosPath == "::db" )
      {
       Image1->Tag = 1; // Устанавливаем признак того, что фотку нужно будет загрузить
      }
    else
      {
       AnsiString PictureNewFileName = fMain->cfgPhotosPath + LabeledEdit4->Text + ".jpg";
       CopyFile(OpenPictureDialog1->FileName.c_str(), PictureNewFileName.c_str(), false);
      }

    Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btSavePhotoClick(TObject *Sender)
{
 if ( IBDataSet1->FieldByName("card")->AsInteger <= 0 )
   {
    mbCaption = Caption + " -- Ошибка",
    MessageBox(Handle, "Невозможно сохранить фотографию в файл пока не зарегистрирована карточка.\n", mbCaption.c_str(), MB_OK | MB_ICONERROR);
    return;
   }

 AnsiString PhotoFileName = fMain->ExePath + "Photos\\" + IBDataSet1->FieldByName("card")->AsString + ".jpg";

 if ( fMain->SQL_Fwk->PhotoToFile(IBDataSet1, PhotoFileName) )
   {
    mbCaption = Caption + " -- Информация",
    MessageBox(Handle, "Фотография сохранена в файл.\n", mbCaption.c_str(), MB_OK | MB_ICONINFORMATION);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btDeletePhotoClick(TObject *Sender)
{
 if ( Image1->Picture == NULL )
   return;

 Image1->Picture = NULL;

 if ( fMain->cfgPhotosPath == "::db" )
   Image1->Tag = 2;
 else
   {
    AnsiString PictureNewFileName = fMain->cfgPhotosPath + LabeledEdit4->Text + ".jpg";
    DeleteFile(PictureNewFileName.c_str());
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btGetCardNumberClick(TObject *Sender)
{
 if ( !fMain->cfgControlCRPort )
   {
    mbCaption = Caption + " -- Ошибка";
    MessageBox(Handle, "В настройках Вашего рабочего места не установлен порт считывателя.\n", mbCaption.c_str(), MB_OK | MB_ICONERROR);
    return;
   }
 
 if ( !ControlCR )
   ControlCR = new CardReader(fMain->cfgControlCRPort, fMain->cfgControlCRType);

 if ( ControlCR->isReady() )
   {
    LabeledEdit4->Text = ControlCR->getNumber();
    if (LabeledEdit4->Text == "0")
      LabeledEdit4->Text = ControlCR->getNumber();
   }
 else
   {
    mbCaption = Caption + " -- Ошибка";
    mbText    = "Не удалось инициализировать считыватель:  " + ControlCR->getErrorMessage();
    MessageBox(Handle, mbText.c_str(), mbCaption.c_str(), MB_OK | MB_ICONERROR);
    delete ControlCR;
    ControlCR = NULL;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btGetTemplateFilePathClick(TObject *Sender)
{
 OpenDialog1->InitialDir = fMain->ExePath + "Templates\\";

 if (OpenDialog1->Execute())
   LabeledEdit6->Text = ExtractFileName(OpenDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::RightsScheme_PopupMenuClick(TObject *Sender)
{
 for (int i = 0; i < CheckListBox1->Items->Count; i++)
    CheckListBox1->Checked[i] = false;

 if (((TMenuItem*)Sender)->Name == "pmGuard")
   {
    CheckListBox1->Checked[0] = true;
    CheckListBox1->Checked[12]= true;
    CheckListBox1->Checked[16]= true;
   }
 else if (((TMenuItem*)Sender)->Name == "pmStatistician")
   {
    CheckListBox1->Checked[1] = true;
    CheckListBox1->Checked[5] = true;
    CheckListBox1->Checked[9] = true;
    CheckListBox1->Checked[10]= true;
    CheckListBox1->Checked[12]= true;
   }
 else
   {
    CheckListBox1->Checked[1] = true;
    CheckListBox1->Checked[2] = true;
    CheckListBox1->Checked[3] = true;
    CheckListBox1->Checked[5] = true;
    CheckListBox1->Checked[6] = true;
    CheckListBox1->Checked[9] = true;
    CheckListBox1->Checked[10]= true;
    CheckListBox1->Checked[12]= true;
    CheckListBox1->Checked[16]= true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btOKClick(TObject *Sender)
{
 if ( ComboBox1->ItemIndex == -1 )
   {
    mbCaption = Caption + " -- Ошибка",
    MessageBox(Handle, "Для внесения изменений необходимо выбрать \"Структурную единицу\".\n", mbCaption.c_str(), MB_OK | MB_ICONERROR);
    return;
   }

 AnsiString PictureOldFileName = fMain->cfgPhotosPath + IBDataSet1->FieldByName("card")->AsString + ".jpg";

 if (ActionType == 13)
   IBDataSet1->Edit();
 else
   {
    IBDataSet1->AfterScroll = NULL;
    IBDataSet1->Append();
    IBDataSet1->AfterScroll = IBDataSet1AfterScroll;
   }

 AnsiString Rights;
 for (int i = 0; i < CheckListBox1->Items->Count; i++)
    Rights += CheckListBox1->Checked[i] ? '1' : '0';
 if (Rights.Pos("1") == 0)
   Rights = "";

 IBDataSet1->FieldByName("card")               ->AsString   = LabeledEdit4->Text;
 IBDataSet1->FieldByName("card_type")          ->AsInteger  = ComboBox2->ItemIndex;
 IBDataSet1->FieldByName("enabled")            ->AsInteger  = chbEnabled->Checked;
 IBDataSet1->FieldByName("expire")             ->AsDateTime = DateTimePicker1->DateTime;
 IBDataSet1->FieldByName("rights")             ->AsString   = Rights;
 IBDataSet1->FieldByName("passwrd")            ->AsString   = LabeledEdit5->Text;
 IBDataSet1->FieldByName("template")           ->AsString   = LabeledEdit6->Text;
 IBDataSet1->FieldByName("marked_for_printing")->AsInteger  = chbMarkedForPrinting->Checked;
 IBDataSet1->FieldByName("web_login")          ->AsString   = LabeledEdit8->Text;
 IBDataSet1->FieldByName("web_password")       ->AsString   = LabeledEdit9->Text;
 IBDataSet1->FieldByName("lname")              ->AsString   = LabeledEdit1->Text;
 IBDataSet1->FieldByName("fname")              ->AsString   = LabeledEdit2->Text;
 IBDataSet1->FieldByName("mname")              ->AsString   = LabeledEdit3->Text;
 IBDataSet1->FieldByName("sms_enabled")        ->AsInteger  = chbSMSEnabled->Checked;
 IBDataSet1->FieldByName("sms_phone")          ->AsString   = LabeledEdit7->Text;
 IBDataSet1->FieldByName("birthday")           ->AsDateTime = DateTimePicker2->DateTime;
 IBDataSet1->FieldByName("home_address")       ->AsString   = LabeledEdit11->Text;
 IBDataSet1->FieldByName("phone")              ->AsString   = LabeledEdit12->Text;
 IBDataSet1->FieldByName("medical_policy")     ->AsString   = LabeledEdit13->Text;
 IBDataSet1->FieldByName("father_fio")         ->AsString   = LabeledEdit21->Text;
 IBDataSet1->FieldByName("father_employment")  ->AsString   = LabeledEdit22->Text;
 IBDataSet1->FieldByName("father_post")        ->AsString   = LabeledEdit23->Text;
 IBDataSet1->FieldByName("father_phone")       ->AsString   = LabeledEdit24->Text;
 IBDataSet1->FieldByName("father_info")        ->AsString   = LabeledEdit25->Text;
 IBDataSet1->FieldByName("mother_fio")         ->AsString   = LabeledEdit31->Text;
 IBDataSet1->FieldByName("mother_employment")  ->AsString   = LabeledEdit32->Text;
 IBDataSet1->FieldByName("mother_post")        ->AsString   = LabeledEdit33->Text;
 IBDataSet1->FieldByName("mother_phone")       ->AsString   = LabeledEdit34->Text;
 IBDataSet1->FieldByName("mother_info")        ->AsString   = LabeledEdit35->Text;

 // Добавление в таблицы Objects и Objects_Links
 AnsiString newName = IBDataSet1->FieldByName("lname")->AsString +
                    ( IBDataSet1->FieldByName("fname")->IsNull ? AnsiString("") : AnsiString(" " + IBDataSet1->FieldByName("fname")->AsString)) +
                    ( IBDataSet1->FieldByName("mname")->IsNull ? AnsiString("") : AnsiString(" " + IBDataSet1->FieldByName("mname")->AsString));
 if (ActionType == 13)
   {
    fMain->SQL_Fwk->sqlUpdate(IBTransaction1, "Objects",
                              "nn",   IBDataSet1->FieldByName("objects_lnk")->AsString.c_str(),
                              "name", newName.c_str(),
                              NULL);
    fMain->SQL_Fwk->sqlExecute(IBTransaction1, "UPDATE              \
                                                      Objects_links \
                                                SET                 \
                                                   left_lnk = "    + IntToStr(structuresList[ComboBox1->ItemIndex]) + " \
                                                WHERE               \
                                                     left_lnk = "  + IBDataSet1->FieldByName("structures_lnk")->AsString + " \
                                                 AND right_lnk = " + IBDataSet1->FieldByName("objects_lnk")->AsString + ";");
   }
 else
   {
    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");
    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  newName.c_str(),
                              "otype", "-103",
                              NULL);
    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects_Links",
                              "link_type", "0",
                              "left_lnk",  IntToStr(structuresList[ComboBox1->ItemIndex]).c_str(),
                              "right_lnk", IntToStr(newNN).c_str(),
                              NULL);
    IBDataSet1->FieldByName("objects_lnk")->AsInteger = newNN;
   }

 if (Image1->Tag == 1)      // фотку надо сохранять
   fMain->SQL_Fwk->PhotoToDB(IBDataSet1, OpenPictureDialog1->FileName);
 else if (Image1->Tag == 2) // фотку удалили или не трогали
   IBDataSet1->FieldByName("photo")->Clear();

 IBDataSet1->Post();

 if ( chbRenamePhoto->Checked )
   {
    AnsiString PictureNewFileName = fMain->cfgPhotosPath + LabeledEdit4->Text + ".jpg";
    MoveFile(PictureOldFileName.c_str(), PictureNewFileName.c_str());
   }

 prepareForViewing();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btCancelClick(TObject *Sender)
{
 prepareForViewing();
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::prepareForEditing()
{
 if ( PageControl1->Pages[PageControl1->TabIndex]->Name == "pc1_tsGrid" )
   ViewStyle = 1;
 else
   ViewStyle = 2;

 // Вкладка "Личные данные"
 for (int i = 0; i < PageControl2_ts1->ControlCount; i++)
    PageControl2_ts1->Controls[i]->Enabled = true;
 btLoadPhoto->Enabled = true;
 btDeletePhoto->Enabled = true;

 // Остальные компоненты
 PageControl2_ts2->Enabled = true;
 NamePanel       ->Enabled = true;
 pc1_tsGrid->TabVisible = false;
 ToolBar1     ->Visible = false;
 okCancelPanel->Visible = true;

 this->OnMouseWheel = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::prepareForViewing()
{
 Caption = "Списочный состав организации  --  Просмотр";

 // Вкладка "Личные данные"
 for (int i = 0; i < PageControl2_ts1->ControlCount; i++)
    PageControl2_ts1->Controls[i]->Enabled = false;
 btEventsList ->Enabled = true;
 gbPhoto      ->Enabled = true;
 btLoadPhoto  ->Enabled = false;
 btSavePhoto  ->Enabled = true;
 btDeletePhoto->Enabled = false;

 // Остальные компоненты
 PageControl2_ts2->Enabled = false;
 NamePanel       ->Enabled = false;
 pc1_tsGrid->TabVisible = true;
 ToolBar1     ->Visible = true;
 okCancelPanel->Visible = false;

 IBDataSet1AfterScroll(IBDataSet1);

 if ( ViewStyle == 1 )
   PageControl1->ActivePageIndex = 0;

 this->OnMouseWheel = TfUnitProperties::FormMouseWheel;
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btPrepareCardForPrintingClick(TObject *Sender)
{
 if ( bmpCard != NULL )
   delete bmpCard;
 bmpCard = new Graphics::TBitmap();

 fPrintCards->fillCard(bmpCard, IBDataSet1->FieldByName("template")->AsString, IBDataSet1, PaintBox1);
}
//---------------------------------------------------------------------------
void __fastcall TfUnitProperties::btPrintCardClick(TObject *Sender)
{
 if ( !PrintDialog1->Execute() )
   return;

 TPrinter *Prn = Printer();
 Prn->BeginDoc();
 Prn->Title = "Карточка " + LabeledEdit1->Text + " " + LabeledEdit2->Text + " " + LabeledEdit3->Text;

 // Количество точек на сантиметр
 const double prn_dpi_x = GetDeviceCaps(Prn->Canvas->Handle, LOGPIXELSX) / 2.54,
              prn_dpi_y = GetDeviceCaps(Prn->Canvas->Handle, LOGPIXELSY) / 2.54;

 // Расположение карточек на листе
 const double CardWidth  = 8.6,
              CardHeight = 5.5,
              Left1 = 0,
              Top1 = 0;

 TRect CardRect = Rect (Left1 * prn_dpi_x, Top1 * prn_dpi_y, (Left1 + CardWidth) * prn_dpi_x, (Top1 + CardHeight) * prn_dpi_y);

 Prn->Canvas->StretchDraw(CardRect, bmpCard);
 Prn->EndDoc();
}
//---------------------------------------------------------------------------