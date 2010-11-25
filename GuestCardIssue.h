//---------------------------------------------------------------------------
#ifndef fGuestCardIssueH
#define fGuestCardIssueH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <IBDatabase.hpp>
#include <DB.hpp>
#include <IBCustomDataSet.hpp>
#include <IBQuery.hpp>
#include <jpeg.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <IBUpdateSQL.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfGuestCardIssue : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TDBGrid *DBGrid1;
        TImage *ImageArch;
        TPanel *Panel1;
        TButton *ButtonOk;
        TButton *ButtonCancel;
        TGroupBox *GroupBox2;
        TDBGrid *DBGrid2;
        TGroupBox *GroupBox3;
        TImage *ImageMain;
        TButton *ButtonScan;
        TLabeledEdit *EditFrom;
        TComboBox *ComboBox1;
        TButton *ButtonArch;
        TButton *ButtonQuery;
        TComboBox *ComboBox2;
        TComboBox *ComboBoxReas;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TIBTransaction *GuestTransaction;
        TComboBox *ComboBox1a;
        TIBQuery *Q1;
        TIBDataSet *Guests;
        TDataSource *DataSourceGuests;
        TComboBox *ComboBox2a;
        TLabeledEdit *EditMN;
        TLabeledEdit *EditFN;
        TLabeledEdit *EditLN;
        TDateTimePicker *DateTimePicker1;
        TIBDataSet *GuestsReq;
        TDataSource *DataSourceGuestsReq;
        TOpenPictureDialog *OpenJPGDialog;
        TIBDataSet *Units;
        TPopupMenu *DBGrid1PopupMenu;
        TMenuItem *N1;
        TMenuItem *N2;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ButtonOkClick(TObject *Sender);
        void __fastcall ButtonCancelClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ButtonArchClick(TObject *Sender);
        void __fastcall DBGrid1CellClick(TColumn *Column);
        void __fastcall ButtonScanClick(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall EditLNChange(TObject *Sender);
        void __fastcall EditFNKeyPress(TObject *Sender, char &Key);
        void __fastcall EditLNKeyPress(TObject *Sender, char &Key);
        void __fastcall EditMNKeyPress(TObject *Sender, char &Key);
        void __fastcall ButtonQueryClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall DBGrid1TitleClick(TColumn *Column);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
private:	// User declarations
        char buf[4096],sortfield[255],filter[255];
        TJPEGImage *jpPhoto;
        AnsiString unlink_fname;
        int QSeek(void);
        int From_Archive;
        void MakeSelectSQL(void);
public:		// User declarations
        __fastcall TfGuestCardIssue(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfGuestCardIssue *fGuestCardIssue;
//---------------------------------------------------------------------------
#endif