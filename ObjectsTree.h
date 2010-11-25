//---------------------------------------------------------------------------
#ifndef fObjectsTreeH
#define fObjectsTreeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TfObjectsTree : public TForm
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
        TToolButton *ToolButton2;
        TToolButton *tbReportSelection;
        TImageList *ImageList1;
        TTreeView *TreeView1;
        TPopupMenu *PopupMenu1;
        TMenuItem *pmChildrenCount;
        TMenuItem *N1;
        TMenuItem *pmExpandAll;
        TGroupBox *gbReportSelection;
        TGroupBox *GroupBox1;
        TMonthCalendar *mcBeginDate;
        TDateTimePicker *dtpBeginTime;
        TGroupBox *GroupBox2;
        TMonthCalendar *mcEndDate;
        TDateTimePicker *dtpEndTime;
        TRadioGroup *rgReportType;
        TRadioGroup *rgReportMode;
        TButton *btShowReport;
        TStatusBar *StatusBar1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall tbAddClick(TObject *Sender);
        void __fastcall tbAddCopyClick(TObject *Sender);
        void __fastcall tbChangeClick(TObject *Sender);
        void __fastcall tbDeleteClick(TObject *Sender);
        void __fastcall tbSaveClick(TObject *Sender);
        void __fastcall tbUndoClick(TObject *Sender);
        void __fastcall tbReportSelectionClick(TObject *Sender);
        void __fastcall TreeView1Expanding(TObject *Sender, TTreeNode *Node, bool &AllowExpansion);
        void __fastcall TreeView1Deletion(TObject *Sender, TTreeNode *Node);
        void __fastcall TreeView1Change(TObject *Sender, TTreeNode *Node);
        void __fastcall TreeView1Changing(TObject *Sender, TTreeNode *Node, bool &AllowChange);
        void __fastcall TreeView1Editing(TObject *Sender, TTreeNode *Node, bool &AllowEdit);
        void __fastcall TreeView1DragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
        void __fastcall TreeView1DragDrop(TObject *Sender, TObject *Source, int X, int Y);
        void __fastcall pmChildrenCountClick(TObject *Sender);
        void __fastcall pmExpandAllClick(TObject *Sender);
        void __fastcall rgReportModeClick(TObject *Sender);
        void __fastcall btShowReportClick(TObject *Sender);
private:
        int selectedNodeNN;
        void __fastcall updateStatusBar();
        int  __fastcall getChildrenCount(TTreeNode *z);
        void __fastcall deleteChildren(TTreeNode *z);
public:
             __fastcall TfObjectsTree(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfObjectsTree *fObjectsTree;
//---------------------------------------------------------------------------
#endif