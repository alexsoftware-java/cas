#ifndef _SQL_Framework
#define _SQL_Framework

#include <IBQuery.hpp>

//--------------------------------------------------------------------------//

class SQL_Base
{
 public:
  TIBTransaction *IBTransaction;
  TIBSQL *IBSQL1;

   SQL_Base(TIBDatabase *IBDatabase);
  ~SQL_Base();
};

//--------------------------------------------------------------------------//

SQL_Base::SQL_Base(TIBDatabase *IBDatabase)
{
 IBTransaction = new TIBTransaction(Application);
 IBTransaction->DefaultDatabase = IBDatabase;
 IBTransaction->Params->Add("read_committed");
 IBTransaction->Params->Add("rec_version");
 IBTransaction->Params->Add("nowait");

 IBSQL1 = new TIBSQL(Application);
 IBSQL1->Database = IBDatabase;
 IBSQL1->Transaction = IBTransaction;
}

//--------------------------------------------------------------------------//

SQL_Base::~SQL_Base()
{
 delete IBSQL1;
 delete IBTransaction;
}

//==========================================================================//

class SQL_Framework : public SQL_Base
{
 public:
  SQL_Framework(TIBDatabase *IBDatabase) : SQL_Base(IBDatabase) {}

  void sqlInsert(TIBTransaction *IBTransaction_, char *tableName ...);
  void sqlUpdate(TIBTransaction *IBTransaction_, char *tableName, char *whereField, char *whereValue ...);
  void sqlDelete(TIBTransaction *IBTransaction_, char *tableName, char *whereField_1, char *whereValue_1, char *whereField_2 = NULL, char *whereValue_2 = NULL);
  void sqlExecute(TIBTransaction *IBTransaction_, AnsiString SQLCmd);

  int  getGenerator(AnsiString generatorName);

  void fillDictionary(AnsiString SQLCmd, AnsiString Key, AnsiString Value, std::vector<int>& KeyList, TComboBox *ComboBox, int cbInitialValue);

  int  getRecordsCount(TIBTransaction *IBTransaction_, AnsiString tableName, AnsiString whereField = "");

  void PhotoToDB(TIBDataSet *IBDataSet, AnsiString FileName);
  bool PhotoToFile(TIBDataSet *IBDataSet, AnsiString FileName);
  bool PhotoToBitmap(TIBDataSet *IBDataSet, Graphics::TBitmap *bmPhoto);

  void addEvent(int Zone_NN, int Object_NN, int Event);
};

//---------------------------------------------------------------------------

void SQL_Framework::sqlInsert(TIBTransaction *IBTransaction_, char *tableName ...)
{
 IBSQL1->Transaction = IBTransaction_;

 AnsiString fields, values;
 char       *p;

 va_list ap;
 va_start(ap, tableName);

#pragma warn -pia
 for (; p = va_arg(ap, char *); p != NULL)
#pragma warn .pia
    {
     fields += AnsiString(p) + ",";

     p = va_arg(ap, char *);
     if (strlen(p) == 0)
       values += "NULL,";
     else if (strstr(p,"GEN_ID(") == NULL)
       values += "'" + AnsiString(p) + "',";
     else
       values += AnsiString(p) + ",";
    }

 va_end(ap);

 fields[fields.Length()] = ')';  // Заменяем последнюю запятую на скобку
 values[values.Length()] = ')';

 IBSQL1->SQL->Text = "INSERT INTO " + AnsiString(tableName) + "(" + fields + " VALUES(" + values + ";";
 IBSQL1->ExecQuery();
 IBSQL1->Close();

 IBSQL1->Transaction = IBTransaction;
}

//---------------------------------------------------------------------------

void SQL_Framework::sqlUpdate(TIBTransaction *IBTransaction_, char *tableName, char *whereField, char *whereValue ...)
{
 IBSQL1->Transaction = IBTransaction_;

 AnsiString buf;
 char       *p;

 va_list ap;
 va_start(ap, whereValue);

#pragma warn -pia
 for (; p = va_arg(ap, char *); p != NULL)
#pragma warn .pia
    {
     buf += p;

     p = va_arg(ap, char *);
     if (strlen(p) == 0)
       buf += "=NULL,";
     else
       buf += "='" + AnsiString(p) + "',";
    }

 va_end(ap);

 buf.SetLength(buf.Length() - 1);       // Убиваем последнюю запятую

 IBSQL1->SQL->Text = "UPDATE " + AnsiString(tableName) + " SET " + buf + " WHERE " + AnsiString(whereField) + "='" + AnsiString(whereValue) + "';";
 IBSQL1->ExecQuery();
 IBSQL1->Close();

 IBSQL1->Transaction = IBTransaction;
}

//---------------------------------------------------------------------------

void SQL_Framework::sqlDelete(TIBTransaction *IBTransaction_, char *tableName, char *whereField_1, char *whereValue_1, char *whereField_2, char *whereValue_2)
{
 IBSQL1->Transaction = IBTransaction_;

 if (whereField_2 == NULL)
   IBSQL1->SQL->Text = "DELETE FROM " + AnsiString(tableName) + " WHERE " + AnsiString(whereField_1) + "='" + AnsiString(whereValue_1) + "';";
 else
   IBSQL1->SQL->Text = "DELETE FROM " + AnsiString(tableName) + " WHERE " + AnsiString(whereField_1) + "='" + AnsiString(whereValue_1) + "' AND "
                                                                          + AnsiString(whereField_2) + "='" + AnsiString(whereValue_2) + "';";

 IBSQL1->ExecQuery();
 IBSQL1->Close();

 IBSQL1->Transaction = IBTransaction;
}

//---------------------------------------------------------------------------

void SQL_Framework::sqlExecute(TIBTransaction *IBTransaction_, AnsiString SQLCmd)
{
 IBSQL1->Transaction = IBTransaction_;

 IBSQL1->SQL->Text = SQLCmd;
 IBSQL1->ExecQuery();
 IBSQL1->Close();

 IBSQL1->Transaction = IBTransaction;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int  SQL_Framework::getGenerator(AnsiString generatorName)
{
 if ( !IBSQL1->Transaction->Active )
   IBSQL1->Transaction->StartTransaction();

 IBSQL1->SQL->Text = "SELECT GEN_ID(" + generatorName + ", 1) AS gv FROM rdb$database;";
 IBSQL1->ExecQuery();

 int result = IBSQL1->FieldByName("gv")->AsInteger;

 IBSQL1->Close();
 IBSQL1->Transaction->Commit();

 return result;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void SQL_Framework::fillDictionary(AnsiString SQLCmd, AnsiString Key, AnsiString Value, std::vector<int>& KeyList, TComboBox *ComboBox, int cbInitialValue)
{
 if ( !IBSQL1->Transaction->Active )
   IBSQL1->Transaction->StartTransaction();

 IBSQL1->SQL->Text = SQLCmd;
 IBSQL1->ExecQuery();

 for (; !IBSQL1->Eof; IBSQL1->Next())
    {
     ComboBox->Items->Add( IBSQL1->FieldByName(Value)->AsString  );
     KeyList.push_back   ( IBSQL1->FieldByName(Key)  ->AsInteger );
    }

 IBSQL1->Close();
 IBSQL1->Transaction->Commit();

 if (cbInitialValue != -1 )
   for (unsigned int i = 0; i < KeyList.size(); i++)
      if (KeyList[i] == cbInitialValue)
        {
         ComboBox->ItemIndex = i;
         break;
        }
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

int SQL_Framework::getRecordsCount(TIBTransaction *IBTransaction_, AnsiString tableName, AnsiString whereField)
{
 if ( IBTransaction_ != NULL) 
   IBSQL1->Transaction = IBTransaction_;

 if ( !IBSQL1->Transaction->Active )
   IBSQL1->Transaction->StartTransaction();

 if (whereField == "")
   IBSQL1->SQL->Text = "SELECT COUNT(*) AS rc FROM "+ tableName + ";";
 else
   IBSQL1->SQL->Text = "SELECT COUNT(*) AS rc FROM "+ tableName + " WHERE " + whereField + ";";

 IBSQL1->ExecQuery();

 int result = IBSQL1->FieldByName("rc")->AsInteger;

 IBSQL1->Close();

 if ( IBTransaction_ != NULL) 
   IBSQL1->Transaction = IBTransaction;

 return result;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void SQL_Framework::PhotoToDB(TIBDataSet *IBDataSet, AnsiString FileName)
{
 if ( FileName.IsEmpty() )
   return;

 TFileStream *fs = new TFileStream(FileName, fmOpenRead || fmShareCompat);
 TStream     *bs = IBDataSet->CreateBlobStream(IBDataSet->FieldByName("photo"), bmWrite);

 bs->CopyFrom(fs, fs->Size);

 delete fs;
 delete bs;
}

//---------------------------------------------------------------------------

bool SQL_Framework::PhotoToFile(TIBDataSet *IBDataSet, AnsiString FileName)
{
 if ( IBDataSet->FieldByName("photo")->IsNull )
   return false;

 TFileStream *fs = new TFileStream(FileName, fmCreate);
 TStream     *bs = IBDataSet->CreateBlobStream(IBDataSet->FieldByName("photo"), bmRead);

 fs->CopyFrom(bs, bs->Size);

 delete fs;
 delete bs;

 return true;
}

//---------------------------------------------------------------------------

bool SQL_Framework::PhotoToBitmap(TIBDataSet *IBDataSet, Graphics::TBitmap *bmPhoto)
{
 if ( IBDataSet->FieldByName("photo")->IsNull )
   return false;

 TJPEGImage *jpgPhoto = new TJPEGImage();
 TStream    *bs = IBDataSet->CreateBlobStream(IBDataSet->FieldByName("photo"), bmRead);

 jpgPhoto->LoadFromStream(bs);
 bmPhoto->Assign(jpgPhoto);

 delete jpgPhoto;
 delete bs;

 return true;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void SQL_Framework::addEvent(int Zone_NN, int Object_NN, int Event)
{
 IBSQL1->Transaction->StartTransaction();
 IBSQL1->SQL->Text = "INSERT INTO Log(nn, zones_lnk, objects_lnk, eventtypes_lnk) VALUES(GEN_ID(gen_log,1)," + IntToStr(Zone_NN) + "," + IntToStr(Object_NN) + "," + IntToStr(Event) + ");";
 IBSQL1->ExecQuery();
 IBSQL1->Transaction->Commit();
}

//==========================================================================//
#endif