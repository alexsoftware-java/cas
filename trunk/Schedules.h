//---------------------------------------------------------------------------
#ifndef fSchedulesH
#define fSchedulesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <IBDatabase.hpp>
#include <IBSQL.hpp>
#include <ImgList.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include <ValEdit.hpp>
//---------------------------------------------------------------------------
class TfSchedules : public TForm
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
        TLabel *Label1;
        TLabel *Label2;
        TGroupBox *GroupBox2;
        TStringGrid *StringGrid1;
        TStringGrid *StringGrid2;
        TStringGrid *StringGrid3;
        TStringGrid *StringGrid4;
        TStringGrid *StringGrid5;
        TStringGrid *StringGrid6;
        TStringGrid *StringGrid7;
        TStringGrid *StringGrid8;
        TStringGrid *StringGrid9;
        TStringGrid *StringGrid10;
        TStringGrid *StringGrid11;
        TStringGrid *StringGrid12;
        TGroupBox *gbDayType;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TRadioButton *rbDayType1;
        TRadioButton *rbDayType2;
        TRadioButton *rbDayType3;
        TValueListEditor *vleWorkTime;
        TValueListEditor *vleBreaks;
        TButton *btYearBack;
        TButton *btMonthBack;
        TButton *btMonthForward;
        TButton *btYearForward;
        TButton *Button2;
        TButton *Button1;
        TRadioGroup *RadioGroup1;
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
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall btNavigateCalendarClick(TObject *Sender);
        void __fastcall sgMonthCalendarSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
        void __fastcall sgMonthCalendarEnter(TObject *Sender);
        void __fastcall sgMonthCalendarExit(TObject *Sender);
        void __fastcall sgMonthCalendarDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall rbDayTypeClick(TObject *Sender);
        void __fastcall ValueListEditorGetEditMask(TObject *Sender, int ACol, int ARow, AnsiString &Value);
        void __fastcall ValueListEditorValidate(TObject *Sender, int ACol, int ARow, const AnsiString KeyName, const AnsiString KeyValue);
        void __fastcall ValueListEditorExit(TObject *Sender);
private:
        TStringGrid *selectedCalendar;
        int         cur_gbDayType;
        AnsiString  cur_vleWorkTime,
                    cur_vleBreaks;
        void __fastcall fillCalendar(TStringGrid *sgMonthCalendar, int Year, int Month);
        void __fastcall setFirstDayInMonthSelected();
        void __fastcall updateSelectedInCalendarDay();
         int __fastcall getDayType(AnsiString Year, AnsiString Month, AnsiString Day);
        void __fastcall setWeekendsHoliday(TStringGrid *sgMonthCalendar);
        void __fastcall loadTimeInValueListEditor(TValueListEditor *ValueListEditor, AnsiString Year, AnsiString Month, AnsiString Day);
        void __fastcall saveTimeFromValueListEditor(TValueListEditor *ValueListEditor, AnsiString Year, AnsiString Month, AnsiString Day);
        void __fastcall setTimeForMonth(TStringGrid *sgMonthCalendar);
public:
             __fastcall TfSchedules(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfSchedules *fSchedules;
//---------------------------------------------------------------------------
#endif