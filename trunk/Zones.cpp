//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "InputLine.h"
#include "Main.h"
#include "Zones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfZones *fZones;
//---------------------------------------------------------------------------
__fastcall TfZones::TfZones(TComponent* Owner) : TForm(Owner)
{
 if (!IBTransaction1->Active)
   IBTransaction1->StartTransaction();

// Корневой элемент TreeView
 TTreeNode *z = TreeView1->Items->AddObject(NULL, "Зоны доступа", (void *) -2);
 z->ImageIndex = 0;
 if (fMain->SQL_Fwk->getRecordsCount(IBTransaction1, "Objects_links", "left_lnk = -2"))
   z->HasChildren = true;

 IBSQL1->Close();

 TreeView1->TopItem->Expand(false);
}
//---------------------------------------------------------------------------
void __fastcall TfZones::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfZones::FormCloseQuery(TObject *Sender, bool &CanClose)
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
void __fastcall TfZones::tbAddClick(TObject *Sender)
{
 TfInputLine *fInputLine = new TfInputLine(this, "Добавление рабочего места в зоне доступа");

 if (fInputLine->ShowModal() == mrOk)
   {
    TTreeNode *tnWhereToAdd = TreeView1->Selected->ImageIndex == 1 ? TreeView1->Selected->Parent : TreeView1->Selected;

    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");

    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  fInputLine->LabeledEdit1->Text.c_str(),
                              "otype", "-113",
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
void __fastcall TfZones::tbAddFolderClick(TObject *Sender)
{
 TfInputLine *fInputLine = new TfInputLine(this, "Добавление зоны доступа");

 if (fInputLine->ShowModal() == mrOk)
   {
    TTreeNode *tnWhereToAdd = TreeView1->Selected->ImageIndex == 1 ? TreeView1->Selected->Parent : TreeView1->Selected;
    int newNN = fMain->SQL_Fwk->getGenerator("gen_objects");

    fMain->SQL_Fwk->sqlInsert(IBTransaction1, "Objects",
                              "nn",    IntToStr(newNN),
                              "name",  fInputLine->LabeledEdit1->Text.c_str(),
                              "otype", "-112",
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
void __fastcall TfZones::tbAddCopyClick(TObject *Sender)
{
 TfInputLine *fInputLine;
 int OType;

 if ( TreeView1->Selected->ImageIndex == 1 )
   {
    OType = -113;
    fInputLine = new TfInputLine(this, "Добавление рабочего места в зоне доступа");
   }
 else
   {
    OType = -112;
    fInputLine = new TfInputLine(this, "Добавление зоны доступа");
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

    TreeView1->Items->AddChildObject(tnWhereToAdd, fInputLine->LabeledEdit1->Text, (void *) newNN)->ImageIndex = (  OType == -112 ? 0 : 1 );
    if ( !tnWhereToAdd->Expanded)
      tnWhereToAdd->Expand(false);

    tbSave->Enabled = true;
    tbUndo->Enabled = true;
   }

 delete fInputLine;
}
//---------------------------------------------------------------------------
void __fastcall TfZones::tbChangeClick(TObject *Sender)
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
void __fastcall TfZones::tbDeleteClick(TObject *Sender)
{
 fMain->SQL_Fwk->sqlDelete(IBTransaction1, "Objects", "nn", IntToStr((int) TreeView1->Selected->Data).c_str());
 TreeView1->Items->Delete(TreeView1->Selected);

 tbSave->Enabled = true;
 tbUndo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfZones::tbSaveClick(TObject *Sender)
{
 IBTransaction1->Commit();
 IBTransaction1->StartTransaction();

 TreeView1->TopItem->DeleteChildren();
 TreeView1->TopItem->HasChildren = true;
 TreeView1->TopItem->Expand(false);

 tbSave->Enabled = false;
 tbUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfZones::tbUndoClick(TObject *Sender)
{
 IBTransaction1->Rollback();
 IBTransaction1->StartTransaction();

 TreeView1->TopItem->DeleteChildren();
 TreeView1->TopItem->HasChildren = true;
 TreeView1->TopItem->Expand(false);

 tbSave->Enabled = false;
 tbUndo->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TfZones::TreeView1DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
 Accept = (Sender == Source);
}
//---------------------------------------------------------------------------
void __fastcall TfZones::TreeView1DragDrop(TObject *Sender, TObject *Source, int X, int Y)
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
void __fastcall TfZones::TreeView1Expanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion)
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
                           (Objects.otype = -112 OR Objects.otype = -113) \
                       AND Objects.nn = Objects_links.right_lnk \
                       AND Objects_links.left_lnk = " + IntToStr((int) Node->Data) + " \
                      ORDER BY                   \
                              Objects.otype DESC, Objects.name;";
 IBSQL1->ExecQuery();

 for (; !IBSQL1->Eof; IBSQL1->Next())
    {
     TTreeNode *z = TreeView1->Items->AddChildObject(Node,
                                                     IBSQL1->FieldByName("name")->AsString,
                                                     (void *)IBSQL1->FieldByName("nn")->AsInteger);

     if (IBSQL1->FieldByName("otype")->AsInteger == -112)
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
void __fastcall TfZones::TreeView1Change(TObject *Sender, TTreeNode *Node)
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
    IBSQL1->SQL->Text = "SELECT * FROM Zones_cfg WHERE objects_lnk = " + IntToStr((int) Node->Data) + ";";
    IBSQL1->ExecQuery();

    if ( !IBSQL1->Eof )  // не пустая
      {
       lbeNN        ->Text = IBSQL1->FieldByName("nn")           ->AsString;
       lbePhotosPath->Text = IBSQL1->FieldByName("photospath")   ->AsString;
       RadioGroup1  ->ItemIndex = IBSQL1->FieldByName("crtype")  ->AsInteger - 1;
       LabeledEdit1 ->Text = IBSQL1->FieldByName("controlcrport")->AsString;
       LabeledEdit2 ->Text = IBSQL1->FieldByName("entry1_crport")->AsString;
       LabeledEdit3 ->Text = IBSQL1->FieldByName("exit1_crport") ->AsString;
       LabeledEdit4 ->Text = IBSQL1->FieldByName("entry2_crport")->AsString;
       LabeledEdit5 ->Text = IBSQL1->FieldByName("exit2_crport") ->AsString;
       LabeledEdit6 ->Text = IBSQL1->FieldByName("entry1_device")->AsString;
       LabeledEdit7 ->Text = IBSQL1->FieldByName("exit1_device") ->AsString;
       LabeledEdit8 ->Text = IBSQL1->FieldByName("entry2_device")->AsString;
       LabeledEdit9 ->Text = IBSQL1->FieldByName("exit2_device") ->AsString;
      }

    IBSQL1->Close();
    GroupBox1->Visible = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfZones::TreeView1Changing(TObject *Sender, TTreeNode *Node, bool &AllowChange)
{
 if (Node->ImageIndex == 0)
   Node->SelectedIndex = 2;
 else
   Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TfZones::TreeView1Editing(TObject *Sender, TTreeNode *Node, bool &AllowEdit)
{
 AllowEdit = false;
 tbChangeClick(Sender);
}
//---------------------------------------------------------------------------