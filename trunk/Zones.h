//---------------------------------------------------------------------------
#ifndef fZonesH
#define fZonesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <ImgList.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TfZones : public TForm
{
__published:
        TIBTransaction *IBTransaction1;
        TIBSQL *IBSQL1;
        TToolBar *ToolBar1;
        TToolButton *tbAdd;
        TToolButton *tbAddFolder;
        TToolButton *tbAddCopy;
        TToolButton *tbChange;
        TToolButton *tbDelete;
        TToolButton *ToolButton1;
        TToolButton *tbSave;
        TToolButton *tbUndo;
        TTreeView *TreeView1;
        TImageList *ImageList1;
        TGroupBox *GroupBox1;
        TLabeledEdit *lbeNN;
        TLabeledEdit *lbePhotosPath;
        TGroupBox *GroupBox2;
        TLabeledEdit *LabeledEdit2;
        TUpDown *UpDown11;
        TLabeledEdit *LabeledEdit3;
        TUpDown *UpDown2;
        TLabeledEdit *LabeledEdit1;
        TUpDown *UpDown1;
        TLabeledEdit *LabeledEdit4;
        TUpDown *UpDown3;
        TLabeledEdit *LabeledEdit5;
        TUpDown *UpDown4;
        TRadioGroup *RadioGroup1;
        TGroupBox *GroupBox3;
        TLabeledEdit *LabeledEdit6;
        TUpDown *UpDown5;
        TLabeledEdit *LabeledEdit7;
        TUpDown *UpDown6;
        TLabeledEdit *LabeledEdit8;
        TUpDown *UpDown8;
        TLabeledEdit *LabeledEdit9;
        TUpDown *UpDown9;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall tbAddClick(TObject *Sender);
        void __fastcall tbAddFolderClick(TObject *Sender);
        void __fastcall tbAddCopyClick(TObject *Sender);
        void __fastcall tbChangeClick(TObject *Sender);
        void __fastcall tbDeleteClick(TObject *Sender);
        void __fastcall tbSaveClick(TObject *Sender);
        void __fastcall tbUndoClick(TObject *Sender);
        void __fastcall TreeView1Expanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall TreeView1Changing(TObject *Sender, TTreeNode *Node, bool &AllowChange);
        void __fastcall TreeView1Editing(TObject *Sender, TTreeNode *Node, bool &AllowEdit);
        void __fastcall TreeView1DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
        void __fastcall TreeView1DragDrop(TObject *Sender, TObject *Source, int X, int Y);
private:
public:
             __fastcall TfZones(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfZones *fZones;
//---------------------------------------------------------------------------
#endif