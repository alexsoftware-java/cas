//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InputLine.h"
#include "Main.h"
#include "Report.h"
#include "ObjectsTree.h"
#include "UnitProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfObjectsTree *fObjectsTree;
//---------------------------------------------------------------------------
__fastcall TfObjectsTree::TfObjectsTree(TComponent* Owner) : TForm(Owner)
{
 selectedNodeNN = 0;

 if (fMain->userType == utUser) // Применение параметров безопасности
   {
    tbChange         ->Visible = ( fMain->userRights[3] == '1' || fMain->userRights[7] == '1' );
    tbAdd            ->Visible = ( fMain->userRights[4] == '1' || fMain->userRights[8] == '1' );
    tbAddCopy        ->Visible = ( fMain->userRights[4] == '1' || fMain->userRights[8] == '1' );
    tbDelete         ->Visible = ( fMain->userRights[5] == '1' || fMain->userRights[9] == '1' );
    tbReportSelection->Visible = ( fMain->userRights[10] == '1' );

    if ( fMain->userRights[7] == '0' )
      {
       TreeView1->OnDragDrop = NULL;
       TreeView1->OnDragOver = NULL;
      }

    if (!tbChange->Visible && !tbAdd->Visible && !tbDelete->Visible)
      {
       tbSave->Visible = false;
       tbUndo->Visible = false;
      }

    rgReportMode->Controls[1]->Enabled = ( fMain->userRights[11] == '1' );
    rgReportMode->Controls[2]->Enabled = ( fMain->userRights[12] == '1' );
   }

 mcBeginDate->Date = Date();
 mcEndDate  ->Date = Date();

 rgReportModeClick(this);

 tbReportSelectionClick(this);

 if (!IBTransaction1->Active)
   IBTransaction1->StartTransaction();

// Корневой элемент TreeView
 IBSQL1->SQL->Text = "SELECT             \
                            Objects.name \
                      FROM               \
                          Objects        \
                      WHERE              \
                           Objects.nn = -100;";
 IBSQL1->ExecQuery();

 TTreeViewDataItem *tnItem = new TTreeViewDataItem (-100, 0);
 TTreeNode         *z      = TreeView1->Items->AddObject(NULL,
                                                         IBSQL1->FieldByName("name")->AsString,
                                                         (void *)tnItem);
 z->ImageIndex  = 0;
 z->HasChildren = true;
 IBSQL1->Close();

 TreeView1->Items->GetFirstNode()->Expand(false);
 TreeView1->Selected = TreeView1->Items->GetFirstNode();
 updateStatusBar();
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::FormCloseQuery(TObject *Sender, bool &CanClose)
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
void __fastcall TfObjectsTree::tbAddClick(TObject *Sender)
{
 int OType;
 TTreeNode *tnWhereToAdd;
 AnsiString ilCaption;

 switch ( ((TTreeViewDataItem *) TreeView1->Selected->Data)->OType )
       {
        case -121: //Тип: графики работы - корневая папка
        case -122: //Тип: графики работы - папка
                   tnWhereToAdd = TreeView1->Selected;
                   if (((TToolButton *)Sender)->Name == "tbAdd")
                     {
                      OType     = -123;
                      ilCaption = "Добавление графика работы";
                     }
                   else
                     {
                      OType     = -122;
                      ilCaption = "Добавление папки графиков работы";
                     }
                   break;
        case -123: //Тип: графики работы - график
                   tnWhereToAdd = TreeView1->Selected->Parent;
                   if (((TToolButton *)Sender)->Name == "tbAdd")
                     {
                      OType     = -123;
                      ilCaption = "Добавление графика работы";
                     }
                   else
                     {
                      OType     = -122;
                      ilCaption = "Добавление папки графиков работы";
                     }
                   break;
        ////
        case -111: //Тип: зоны доступа - корневая папка
        case -112: //Тип: зоны доступа - зона
                   tnWhereToAdd = TreeView1->Selected;
                   if (((TToolButton *)Sender)->Name == "tbAdd")
                     {
                      OType     = -113;
                      ilCaption = "Добавление рабочего места в зоне доступа";
                     }
                   else
                     {
                      OType     = -112;
                      ilCaption = "Добавление папки в зоне доступа";
                     }
                   break;
        case -113: //Тип: зоны доступа - рабочее место в зоне
                   tnWhereToAdd = TreeView1->Selected->Parent;
                   if (((TToolButton *)Sender)->Name == "tbAdd")
                     {
                      OType     = -113;
                      ilCaption = "Добавление рабочего места в зоне доступа";
                     }
                   else
                     {
                      OType     = -112;
                      ilCaption = "Добавление папки в зоне доступа";
                     }
                   break;
        ////
        case -101: //Тип: cтруктурные единицы - корневая папка
        case -102: //Тип: структурные единицы - папка
                   tnWhereToAdd = TreeView1->Selected;
                   if (((TToolButton *)Sender)->Name == "tbAdd")
                     {
                      OType     = -103;
                      ilCaption = "Добавление сотрудника";
                     }
                   else
                     {
                      OType     = -102;
                      ilCaption = "Добавление папки сотрудников";
                     }
                   break;
        case -103: //Тип: структурные единицы - юнит
                   tnWhereToAdd = TreeView1->Selected->Parent;
                   if (((TToolButton *)Sender)->Name == "tbAdd")
                     {
                      OType     = -103;
                      ilCaption = "Добавление сотрудника";
                     }
                   else
                     {
                      OType     = -102;
                      ilCaption = "Добавление папки сотрудников";
                     }
                   break;
        default  :
                   break;
       }


 if ( OType == -103 ) // Костыль для Units
   {
    #pragma warn -aus
    TfUnitProperties *fUnitProperties = new TfUnitProperties(Application, 0, 11, ((TTreeViewDataItem *) tnWhereToAdd->Data)->NN);
    return;
   }

 TfInputLine *fInputLine = new TfInputLine(this, ilCaption);
     #pragma warn .aus
 if ( fInputLine->ShowModal() == mrOk )
   {
    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");

    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  fInputLine->LabeledEdit1->Text.c_str(),
                              "otype", IntToStr(OType),
                              NULL);
    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects_Links",
                              "link_type", "0",
                              "left_lnk",  IntToStr(((TTreeViewDataItem *) tnWhereToAdd->Data)->NN),
                              "right_lnk", IntToStr(newNN),
                              NULL);

    selectedNodeNN = newNN;
    tnWhereToAdd->HasChildren = true;
    tnWhereToAdd->Expand(false);

    tbSave->Enabled = true;
    tbUndo->Enabled = true;
   }

 delete fInputLine;

 updateStatusBar();
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::tbAddCopyClick(TObject *Sender)
{
/*   */
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::tbChangeClick(TObject *Sender)
{
 if ( ((TTreeViewDataItem *) TreeView1->Selected->Data)->OType == -103 ) // Юниты
   {
    if (fMain->userRights[7] == '1')
      {
       #pragma warn -aus
       TfUnitProperties *fUnitProperties = new TfUnitProperties(Application, ((TTreeViewDataItem *) TreeView1->Selected->Data)->NN, 13);
      }
      #pragma warn .aus
    else
      {
       #pragma warn -aus
       TfUnitProperties *fUnitProperties = new TfUnitProperties(Application, ((TTreeViewDataItem *) TreeView1->Selected->Data)->NN, 2);
      }
      #pragma warn .aus
   }
 else
   {
    TfInputLine *fInputLine = new TfInputLine(this, "Изменение названия для   '" + TreeView1->Selected->Text + "'", TreeView1->Selected->Text);

    if (fInputLine->ShowModal() == mrOk)
      {
       fMain->SQL_Fwk->sqlUpdate(IBTransaction1, "Objects",
                                 "nn", IntToStr(((TTreeViewDataItem *) TreeView1->Selected->Data)->NN).c_str(),
                                 "name", fInputLine->LabeledEdit1->Text.c_str(),
                                 NULL);
       TreeView1->Selected->Text = fInputLine->LabeledEdit1->Text;
       tbSave->Enabled = true;
       tbUndo->Enabled = true;
      }

    delete fInputLine;
   }

 updateStatusBar();
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::tbDeleteClick(TObject *Sender)
{
 TreeView1->Selected->Expand(true);
 deleteChildren(TreeView1->Selected);

 updateStatusBar();

 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::tbSaveClick(TObject *Sender)
{
 IBTransaction1->Commit();
 IBTransaction1->StartTransaction();

 tbSave->Enabled = false;
 tbUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::tbUndoClick(TObject *Sender)
{
 IBTransaction1->Rollback();
 IBTransaction1->StartTransaction();

 TreeView1->Items->GetFirstNode()->DeleteChildren();
 TreeView1->Items->GetFirstNode()->HasChildren = true;
 TreeView1->Items->GetFirstNode()->Expand(false);

 updateStatusBar();

 tbSave->Enabled = false;
 tbUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::tbReportSelectionClick(TObject *Sender)
{
 if ( !gbReportSelection->Visible )
   {
    TreeView1->Align = alLeft;
    TreeView1->Width = 313;
    this->ClientWidth = 840;
   }
 else
   {
    TreeView1->Align = alClient;
   }

 gbReportSelection->Visible = !gbReportSelection->Visible;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 Accept = (Sender == Source);
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1DragDrop(TObject *Sender, TObject *Source, int X, int Y)
{
 TTreeNode *DestinationNode = TreeView1->GetNodeAt(X, Y);  // Куда вешать перетащенное
 if (DestinationNode == NULL)  // а тащат-то в пустоту
   return;

 switch ( ((TTreeViewDataItem *) DestinationNode->Data)->OType )  // Юзер тащит в объект, а не папку
       {
        case -123: //Тип: графики работы - график
        case -113: //Тип: зоны доступа - рабочее место в зоне
        case -103: //Тип: структурные единицы - юнит
                   DestinationNode = DestinationNode->Parent;
                   break;
       }

 for (unsigned int i = 0; i < TreeView1->SelectionCount; i++)
    {
     // Проверяем, что:
     //  - тащат не внутрь самого себя
     //  - притащили не туда же, откуда тащат
     if ( !DestinationNode->HasAsParent(TreeView1->Selections[i]) && TreeView1->Selections[i]->Parent != DestinationNode )
       {
        IBSQL1->SQL->Text = "UPDATE              \
                                   Objects_links \
                                SET      \
                                   left_lnk = "    + IntToStr(((TTreeViewDataItem *) DestinationNode->Data)->NN) + " \
                                WHERE      \
                                     left_lnk = "  + IntToStr(((TTreeViewDataItem *) TreeView1->Selections[i]->Parent->Data)->NN) + " \
                                 AND right_lnk = " + IntToStr(((TTreeViewDataItem *) TreeView1->Selections[i]->Data)->NN) + ";";
        IBSQL1->ExecQuery();

        TreeView1->Selections[i]->Delete();
        DestinationNode->HasChildren = true;
        DestinationNode->Expand(false);

        tbSave->Enabled = true;
        tbUndo->Enabled = true;
       }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1Expanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
{
 if (Node->Count > 0)  // Если уже есть дети - сначала удалить их всех
   Node->DeleteChildren();

 IBSQL1->SQL->Text = "SELECT                     \
                            Objects.nn,          \
                            Objects.name,        \
                            Objects.otype        \
                      FROM                       \
                          Objects, Objects_links \
                      WHERE                      \
                           Objects_links.left_lnk  = " + IntToStr(((TTreeViewDataItem *) Node->Data)->NN) + " \
                       AND Objects_links.right_lnk = Objects.nn \
                      ORDER BY                   \
                              Objects.otype DESC, Objects.name;";
 IBSQL1->ExecQuery();

 for (; !IBSQL1->Eof; IBSQL1->Next())
    {
     TTreeViewDataItem *tnItem = new TTreeViewDataItem (IBSQL1->FieldByName("nn")->AsInteger,
                                                        IBSQL1->FieldByName("otype")->AsInteger);
     TTreeNode *z = TreeView1->Items->AddChildObject(Node,
                                                     IBSQL1->FieldByName("name")->AsString,
                                                     (void *)tnItem);
     if (fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Objects_links", "left_lnk = " + AnsiString(tnItem->NN)))
       z->HasChildren = true;

     // Картинка
     switch ( tnItem->OType )
           {
            case -121: //Тип: графики работы - корневая папка
                       z->ImageIndex    = 5;
                       z->SelectedIndex = 5;
                       break;
            case -122: //Тип: графики работы - папка
                       z->ImageIndex    = 5;
                       z->SelectedIndex = 5;
                       break;
            case -123: //Тип: графики работы - график
                       z->ImageIndex    = 5;
                       z->SelectedIndex = 5;
                       break;
            ////
            case -111: //Тип: зоны доступа - корневая папка
                       z->ImageIndex    = 4;
                       z->SelectedIndex = 4;
                       break;
            case -112: //Тип: зоны доступа - зона
                       z->ImageIndex    = 4;
                       z->SelectedIndex = 4;
                       break;
            case -113: //Тип: зоны доступа - рабочее место в зоне
                       z->ImageIndex    = 4;
                       z->SelectedIndex = 4;
                       break;
            ////
            case -101: //Тип: cтруктурные единицы - корневая папка
                       z->ImageIndex    = 2;
                       z->SelectedIndex = 2;
                       break;
            case -102: //Тип: структурные единицы - папка
                       z->ImageIndex    = 0;
                       z->SelectedIndex = 1;
                       break;
            case -103: //Тип: структурные единицы - юнит
                       z->ImageIndex    = 3;
                       z->SelectedIndex = 3;
                       break;
        }

     if ( tnItem->NN == selectedNodeNN )
       {
        TreeView1->Selected = z;
        selectedNodeNN = 0;
       }
    }

 IBSQL1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1Deletion(TObject *Sender, TTreeNode *Node)
{
 delete Node->Data;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1Change(TObject *Sender, TTreeNode *Node)
{
 if ( ((TTreeViewDataItem *) TreeView1->Selected->Data)->NN == -100 ) // Корень дерева
   {
    tbAdd      ->Enabled = false;
    tbAddFolder->Enabled = false;
    tbAddCopy  ->Enabled = false;
    tbChange   ->Enabled = false;
    tbDelete   ->Enabled = false;
   }
 else if (   ((TTreeViewDataItem *) TreeView1->Selected->Data)->OType == -121
          || ((TTreeViewDataItem *) TreeView1->Selected->Data)->OType == -111
          || ((TTreeViewDataItem *) TreeView1->Selected->Data)->OType == -101)
   {
    tbAdd      ->Enabled = true;
    tbAddFolder->Enabled = true;
    tbAddCopy  ->Enabled = false;
    tbChange   ->Enabled = false;
    tbDelete   ->Enabled = false;
   }
 else
   {
    tbAdd      ->Enabled = true;
    tbAddFolder->Enabled = true;
    tbAddCopy  ->Enabled = true;
    tbChange   ->Enabled = true;
    tbDelete   ->Enabled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1Changing(TObject *Sender, TTreeNode *Node, bool &AllowChange)
{
// Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::TreeView1Editing(TObject *Sender, TTreeNode *Node, bool &AllowEdit)
{
 AllowEdit = false;
 tbChangeClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::pmChildrenCountClick(TObject *Sender)
{
 ShowMessage(getChildrenCount(TreeView1->Selected));
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::pmExpandAllClick(TObject *Sender)
{
 TreeView1->Selected->Expand(true);
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::rgReportModeClick(TObject *Sender)
{
 switch (rgReportMode->ItemIndex)
   {
    case 0: btShowReport->Caption = "Просмотр";
            break;
    case 1: btShowReport->Caption = "Печать";
            break;
    case 2: btShowReport->Caption = "Редактирование";
            break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::btShowReportClick(TObject *Sender)
{
 int ReportType;

 switch (rgReportType->ItemIndex)
   {
    case -1:
             return;
    case  0: ReportType = 300;
             break;
    case  1: ReportType = 310;
             break;
    case  2: ReportType = 320;
             break;
    case  3: ReportType = 210;
             break;
    case  4: ReportType = 250;
             break;
    case  5: ReportType = 400;
             break;
    case  6: ReportType = 500;
             break;
    case  7: ReportType = 501;
             break;
   }

 TfReport *fReport = new TfReport(Application,
                                  mcBeginDate->Date, dtpBeginTime->Date.FormatString("hh:nn"),
                                  mcEndDate->Date,   dtpEndTime->Date.FormatString("hh:nn"));
 fReport->PrepareData(ReportType,
                      rgReportMode->ItemIndex,
                      ((TTreeViewDataItem *) TreeView1->Selected->Data)->NN);
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::updateStatusBar()
{
 StatusBar1->Panels->Items[0]->Text = "Подразделений: " + AnsiString(fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Objects", "otype = -102"));
 StatusBar1->Panels->Items[1]->Text = "Сотрудников: " + AnsiString(fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Objects", "otype = -103"));
}
//---------------------------------------------------------------------------
int __fastcall TfObjectsTree::getChildrenCount(TTreeNode *z)
{
 int j = 0;
 for (int i = 0; i < z->Count; i++)
    if ( z->Item[i]->HasChildren )
      j += getChildrenCount(z->Item[i]);
    else
      j++;
 return j;
}
//---------------------------------------------------------------------------
void __fastcall TfObjectsTree::deleteChildren(TTreeNode *z)
{
 while ( z->Count > 0)
   {
    if ( z->Item[0]->HasChildren )
      {
       deleteChildren(z->Item[0]);
      }
    else
      {
       fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Objects", "nn", IntToStr(((TTreeViewDataItem *) z->Item[0]->Data)->NN).c_str());
       TreeView1->Items->Delete(z->Item[0]);
      }
   }

 fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Objects", "nn", IntToStr(((TTreeViewDataItem *) z->Data)->NN).c_str());
 TreeView1->Items->Delete(z);
}
//---------------------------------------------------------------------------