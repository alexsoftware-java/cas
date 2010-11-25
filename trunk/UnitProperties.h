//---------------------------------------------------------------------------
#ifndef fUnitsListAddH
#define fUnitsListAddH
//---------------------------------------------------------------------------
#include "_CardReader.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ExtDlgs.hpp>
#include <Grids.hpp>
#include <IBCustomDataSet.hpp>
#include <IBDatabase.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TfUnitProperties : public TForm
{
__published:
        TToolBar *ToolBar1;
        TToolButton *tbAdd;
        TToolButton *tbAddCopy;
        TToolButton *tbChange;
        TToolButton *tbDelete;
        TToolButton *ToolButton1;
        TToolButton *tbSave;
        TToolButton *tbUndo;
        TToolButton *ToolButton2;
        TToolButton *tbPrior;
        TToolButton *tbNext;
        TOpenPictureDialog *OpenPictureDialog1;
        TPopupMenu *RightsScheme_PopupMenu;
        TMenuItem *pmGuard;
        TMenuItem *pmStatistician;
        TMenuItem *pmDirector;
        TIBDataSet *IBDataSet1;
        TIBTransaction *IBTransaction1;
        TDataSource *DataSource1;
        TOpenDialog *OpenDialog1;
        TPageControl *PageControl1;
        TTabSheet *pc1_tsGrid;
        TTabSheet *pc1_tsCard;
        TDBGrid *DBGrid1;
        TPanel *NamePanel;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TPanel *okCancelPanel;
        TButton *btOK;
        TButton *btCancel;
        TPageControl *PageControl2;
        TTabSheet *PageControl2_ts1;
        TGroupBox *gbPhoto;
        TImage *Image1;
        TButton *btLoadPhoto;
        TButton *btSavePhoto;
        TButton *btDeletePhoto;
        TLabel *Label2;
        TLabel *Label1;
        TGroupBox *GroupBox2;
        TLabeledEdit *LabeledEdit21;
        TLabeledEdit *LabeledEdit22;
        TLabeledEdit *LabeledEdit23;
        TLabeledEdit *LabeledEdit24;
        TLabeledEdit *LabeledEdit25;
        TGroupBox *GroupBox3;
        TLabeledEdit *LabeledEdit31;
        TLabeledEdit *LabeledEdit32;
        TLabeledEdit *LabeledEdit33;
        TLabeledEdit *LabeledEdit34;
        TLabeledEdit *LabeledEdit35;
        TDateTimePicker *DateTimePicker2;
        TLabeledEdit *LabeledEdit11;
        TLabeledEdit *LabeledEdit12;
        TLabeledEdit *LabeledEdit13;
        TButton *btPersonalRecord;
        TButton *btEventsList;
        TButton *btSetResidenceToday;
        TButton *Button7;
        TButton *btResidenceMonth;
        TComboBox *ComboBox1;
        TTabSheet *PageControl2_ts2;
        TGroupBox *GroupBox1;
        TCheckListBox *CheckListBox1;
        TLabeledEdit *LabeledEdit5;
        TLabeledEdit *LabeledEdit4;
        TCheckBox *chbEnabled;
        TDateTimePicker *DateTimePicker1;
        TButton *btGetCardNumber;
        TCheckBox *chbRenamePhoto;
        TCheckBox *chbMarkedForPrinting;
        TLabeledEdit *LabeledEdit6;
        TButton *btGetTemplateFilePath;
        TGroupBox *GroupBox4;
        TCheckBox *chbSMSEnabled;
        TLabeledEdit *LabeledEdit7;
        TComboBox *ComboBox2;
        TLabel *Label3;
        TGroupBox *GroupBox5;
        TLabeledEdit *LabeledEdit8;
        TLabeledEdit *LabeledEdit9;
        TButton *Button2;
        TTabSheet *PageControl2_ts3;
        TPrintDialog *PrintDialog1;
        TPanel *Panel3;
        TPaintBox *PaintBox1;
        TButton *btPrepareCardForPrinting;
        TButton *btPrintCard;

        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, const TPoint &MousePos, bool &Handled);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall IBDataSet1IsEmpyCheck(TDataSet *DataSet);
        void __fastcall IBDataSet1AfterChange(TDataSet *DataSet);
        void __fastcall IBDataSet1AfterDelete(TDataSet *DataSet);
        void __fastcall IBDataSet1AfterScroll(TDataSet *DataSet);
        void __fastcall tbAddClick(TObject *Sender);
        void __fastcall tbAddCopyClick(TObject *Sender);
        void __fastcall tbChangeClick(TObject *Sender);
        void __fastcall tbDeleteClick(TObject *Sender);
        void __fastcall tbSaveOrUndoClick(TObject *Sender);
        void __fastcall tbPriorClick(TObject *Sender);
        void __fastcall tbNextClick(TObject *Sender);
        void __fastcall DBGrid1DblClick(TObject *Sender);
        void __fastcall DBGrid1TitleClick(TColumn *Column);
        void __fastcall btEventsListClick(TObject *Sender);
        void __fastcall btSetResidenceTodayClick(TObject *Sender);
        void __fastcall RightsScheme_PopupMenuClick(TObject *Sender);
        void __fastcall btLoadPhotoClick(TObject *Sender);
        void __fastcall btSavePhotoClick(TObject *Sender);
        void __fastcall btDeletePhotoClick(TObject *Sender);
        void __fastcall btGetCardNumberClick(TObject *Sender);
        void __fastcall btGetTemplateFilePathClick(TObject *Sender);
        void __fastcall PaintBox1Paint(TObject *Sender);
        void __fastcall btPrepareCardForPrintingClick(TObject *Sender);
        void __fastcall btPrintCardClick(TObject *Sender);
        void __fastcall btOKClick(TObject *Sender);
        void __fastcall btCancelClick(TObject *Sender);
private:
        std::vector<int>  structuresList;
        Graphics::TBitmap *bmpCard;
        CardReader        *ControlCR;
        int               ActionType;
        int               ViewStyle;
        AnsiString        mbCaption;
        AnsiString        mbText;

        void __fastcall prepareForEditing();
        void __fastcall prepareForViewing();
public:
             __fastcall TfUnitProperties(TComponent* Owner, int ObjectID_ = 0, int ActionType_ = 1, int StructureNN_ = 0);
             __fastcall ~TfUnitProperties();
};
//---------------------------------------------------------------------------
extern PACKAGE TfUnitProperties *fUnitProperties;
//---------------------------------------------------------------------------
#endif