//---------------------------------------------------------------------------
#include <vcl.h>
#include <comobj.hpp>
#include <FileCtrl.hpp>
#pragma hdrstop

#include "DBService.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define xlCenter        3
//---------------------------------------------------------------------------
TfDBService *fDBService;
//---------------------------------------------------------------------------
__fastcall TfDBService::TfDBService(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void __fastcall TfDBService::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfDBService::btDBCreateClick(TObject *Sender)
{
 if (LabeledEdit4->Text.IsEmpty())
   {
    if (SaveDialog1->Execute())
      LabeledEdit4->Text = SaveDialog1->FileName;
    else
      return;
   }

 IBDatabase1->Close();

 if (LabeledEdit3->Text.IsEmpty())
   {
    DeleteFile(LabeledEdit4->Text.c_str());
    IBDatabase1->DatabaseName = LabeledEdit4->Text;
   }
 else
   IBDatabase1->DatabaseName = LabeledEdit3->Text + ":" + LabeledEdit4->Text;

 IBDatabase1->Params->Clear();
 IBDatabase1->Params->Add("USER '" + LabeledEdit1->Text + "' PASSWORD '" + LabeledEdit2->Text + "'");
 IBDatabase1->Params->Add("PAGE_SIZE 4096");
 IBDatabase1->Params->Add("DEFAULT CHARACTER SET WIN1251;");
 IBDatabase1->CreateDatabase();
 IBDatabase1->Close();

 fMain->addMessage("Создан файл базы данных " + LabeledEdit4->Text);

 if ( !openDB() )
   return;

 const char *sqlCmd[] =
 {
  "CREATE TABLE AUX_YESNO (               \
       NN    INTEGER NOT NULL PRIMARY KEY,\
       NAME  CHAR(3) NOT NULL             \
   );",

  "INSERT INTO AUX_YESNO (nn, name) VALUES (0, 'Нет');",
  "INSERT INTO AUX_YESNO (nn, name) VALUES (1, 'Да');",


  "CREATE TABLE EVENTTYPES (                      \
       NN            INTEGER NOT NULL PRIMARY KEY,\
       NAME          VARCHAR(100),                \
       INTERNALNAME  VARCHAR(100)                 \
   );",

  "INSERT INTO EventTypes (nn, name, internalname) VALUES (-13, 'Выход не был зарегистрирован',                        'evNotRegisteredExit');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (-12, 'Попытка выхода при истёкшем сроке действия карточки', 'evExitWithExpiredCardAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (-2,  'Ручное открытие турникета на выход',                  'evManualExitDeviceOpening');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (-1,  'Регистрация выхода',                                  'evExit');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (0,   'Первое использование карточки',                       'evFirstUse');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (1,   'Регистрация входа',                                   'evEntry');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (2,   'Ручное открытие турникета на вход',                   'evManualEntryDeviceOpening');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (11,  'Попытка входа с недействительной карточкой',          'evEntryWithDisabledCardAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (12,  'Попытка входа при истёкшем сроке действия карточки',  'evEntryWithExpiredCardAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (13,  'Вход не был зарегистрирован',                         'evNotRegisteredEntry');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (21,  'Неудачная попытка входа в систему',                   'evUnsuccessfullyLoginAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (22,  'Успешная авторизация',                                'evLogon');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (23,  'Выключение компьютера',                               'evPCShutdown');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (24,  'Запуск АРМ <КПП>',                                    'evKPPStart');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (25,  'Завершение АРМ <КПП>',                                'evKPPStop');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (30,  'Выдана гостевая карта',                               'evGuestCardIssue');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (31,  'Попытка выхода с гостевой картой через неверный КПП', 'evExitWithGuestCardUsingWrongKPPAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (40,  'Отправлено SMS',                                      'evSMSSent');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (41,  'Не удалось отправить SMS',                            'evSMSSendingError');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (50,  'Регистрация скидки в столовой',                                 'evMealDiscount');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (51,  'Попытка скидки в столовой',                                     'evMealDiscountAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (52,  'Попытка скидки в столовой с недействительной карточкой',         'evMealDiscountWithDisabledCardAttempt');",
  "INSERT INTO EventTypes (nn, name, internalname) VALUES (53,  'Попытка скидки в столовой при истёкшем сроке действия карточки', 'evMealDiscountWithExpiredCardAttempt');",


  "CREATE TABLE ORGANIZATION_INFO (               \
       NN            INTEGER NOT NULL PRIMARY KEY,\
       DBVERSION     INTEGER,                     \
       SERVICECARD   INTEGER,                     \
       CCODE         INTEGER,                     \
       ORGANIZATION  VARCHAR(256),                \
       DIRECTOR      VARCHAR(256),                \
       PHONE         VARCHAR(100)                 \
   );",

  "INSERT INTO Organization_Info (nn, dbversion) VALUES (1, 197);",


  "CREATE TABLE OBJECTS (                        \
       NN           INTEGER NOT NULL PRIMARY KEY,\
       NAME         VARCHAR(256),                \
       DESCRIPTION  VARCHAR(256),                \
       OTYPE        INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE,           \
       DELETED      INTEGER                      \
   );",


  "CREATE TABLE OBJECTS_LINKS (         \
       LINK_TYPE  INTEGER NOT NULL      \
                  REFERENCES OBJECTS(NN)\
                  ON DELETE CASCADE     \
                  ON UPDATE CASCADE,    \
       LEFT_LNK   INTEGER NOT NULL      \
                  REFERENCES OBJECTS(NN)\
                  ON DELETE CASCADE     \
                  ON UPDATE CASCADE,    \
       RIGHT_LNK  INTEGER NOT NULL      \
                  REFERENCES OBJECTS(NN)\
                  ON DELETE CASCADE     \
                  ON UPDATE CASCADE,    \
       PRIMARY KEY (LINK_TYPE, LEFT_LNK, RIGHT_LNK) \
   );",


  "CREATE TABLE SCHEDULES_DAYS (                 \
       NN           INTEGER NOT NULL PRIMARY KEY,\
       OBJECTS_LNK  INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE,           \
       DAY_DATE     DATE NOT NULL,               \
       DAY_TYPE     INTEGER NOT NULL             \
   );",
                                                   
  "CREATE TABLE SCHEDULES_WHOURS (               \
       NN           INTEGER NOT NULL PRIMARY KEY,\
       OBJECTS_LNK  INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE,           \
       DAY_DATE     DATE NOT NULL,               \
       BEGIN_TIME   TIME NOT NULL,               \
       END_TIME     TIME NOT NULL                \
   );",

  "CREATE TABLE SCHEDULES_BREAKS (               \
       NN           INTEGER NOT NULL PRIMARY KEY,\
       OBJECTS_LNK  INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE,           \
       DAY_DATE     DATE NOT NULL,               \
       BEGIN_TIME   TIME NOT NULL,               \
       END_TIME     TIME NOT NULL                \
   );",


  "CREATE TABLE ZONES_CFG (                        \
       NN             INTEGER NOT NULL PRIMARY KEY,\
       OBJECTS_LNK    INTEGER NOT NULL             \
                      REFERENCES OBJECTS(NN)       \
                      ON DELETE CASCADE            \
                      ON UPDATE CASCADE,           \
       NAME           COMPUTED BY ((SELECT Objects.name FROM Objects WHERE Objects.nn = Zones_Cfg.objects_lnk)),\
       PHOTOSPATH     VARCHAR(256),                \
       CRTYPE         INTEGER,                     \
       CONTROLCRPORT  INTEGER,                     \
       ENTRY1_CRPORT  INTEGER,                     \
       ENTRY1_DEVICE  INTEGER,                     \
       EXIT1_CRPORT   INTEGER,                     \
       EXIT1_DEVICE   INTEGER,                     \
       ENTRY2_CRPORT  INTEGER,                     \
       ENTRY2_DEVICE  INTEGER,                     \
       EXIT2_CRPORT   INTEGER,                     \
       EXIT2_DEVICE   INTEGER                      \
   );",


  "CREATE TABLE UNITS (                                  \
       NN                   INTEGER NOT NULL PRIMARY KEY,\
       CARD                 INTEGER,                     \
       CARD_TYPE            INTEGER,                     \
       ENABLED              INTEGER,                     \
       EXPIRE               TIMESTAMP,                   \
       RIGHTS               VARCHAR(100),                \
       PASSWRD              VARCHAR(100),                \
       TEMPLATE             VARCHAR(256),                \
       MARKED_FOR_PRINTING  INTEGER,                     \
       WEB_LOGIN            VARCHAR(100),                \
       WEB_PASSWORD         VARCHAR(100),                \
       OBJECTS_LNK          INTEGER NOT NULL             \
                            REFERENCES OBJECTS(NN)       \
                            ON DELETE CASCADE            \
                            ON UPDATE CASCADE,           \
       STRUCTURE_NAME       COMPUTED BY ((SELECT Objects.name FROM Objects WHERE Objects.nn = (SELECT Objects_links.left_lnk FROM Objects_links WHERE Objects_links.right_lnk = Units.objects_lnk))),\
       STRUCTURES_LNK       COMPUTED BY ((SELECT Objects_links.left_lnk FROM Objects_links WHERE Objects_links.right_lnk = Units.objects_lnk)),\
       FNAME                VARCHAR(256),                \
       MNAME                VARCHAR(256),                \
       LNAME                VARCHAR(256),                \
       PHOTO                BLOB,                        \
       SMS_ENABLED          INTEGER,                     \
       SMS_PHONE            VARCHAR(20),                 \
       BIRTHDAY             TIMESTAMP,                   \
       HOME_ADDRESS         VARCHAR(256),                \
       MEDICAL_POLICY       VARCHAR(256),                \
       PHONE                VARCHAR(256),                \
       FATHER_FIO           VARCHAR(256),                \
       FATHER_EMPLOYMENT    VARCHAR(256),                \
       FATHER_POST          VARCHAR(256),                \
       FATHER_PHONE         VARCHAR(256),                \
       FATHER_INFO          VARCHAR(256),                \
       MOTHER_FIO           VARCHAR(256),                \
       MOTHER_EMPLOYMENT    VARCHAR(256),                \
       MOTHER_POST          VARCHAR(256),                \
       MOTHER_PHONE         VARCHAR(256),                \
       MOTHER_INFO          VARCHAR(256)                 \
   );",


  "CREATE TABLE SMS_QUEUE (                      \
       NN           INTEGER NOT NULL PRIMARY KEY,\
       OBJECTS_LNK  INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE,           \
       TEXT         VARCHAR(100)                 \
   );",


  "CREATE TABLE GUESTS (                                                   \
       NN              INTEGER NOT NULL PRIMARY KEY,                       \
       FNAME           VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       MNAME           VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       LNAME           VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       DOCUMENT_PHOTO  BLOB,                                               \
       STRUCTURES_LNK  INTEGER NOT NULL                                    \
                       REFERENCES OBJECTS(NN)                              \
                       ON DELETE CASCADE                                   \
                       ON UPDATE CASCADE,                                  \
       VISIT_FROM      VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       VISIT_REASON    VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       VISIT_DATE      TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL        \
   );",

  "CREATE TABLE GUESTS_REQUEST (                                           \
       NN              INTEGER NOT NULL PRIMARY KEY,                       \
       FNAME           VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       MNAME           VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       LNAME           VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       STRUCTURES_LNK  INTEGER NOT NULL                                    \
                       REFERENCES OBJECTS(NN)                              \
                       ON DELETE CASCADE                                   \
                       ON UPDATE CASCADE,                                  \
       VISIT_FROM      VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       VISIT_REASON    VARCHAR(255) CHARACTER SET WIN1251 COLLATE PXW_CYRL,\
       VISIT_DATE      TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,       \
       FINISHED        INTEGER DEFAULT 0 NOT NULL                          \
   );",


  "CREATE TABLE LOG (                                               \
       NN              INTEGER NOT NULL PRIMARY KEY,                \
       DATETIME        TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\
       ZONES_LNK       INTEGER NOT NULL                             \
                       REFERENCES OBJECTS(NN)                       \
                       ON DELETE CASCADE                            \
                       ON UPDATE CASCADE,                           \
       OBJECTS_LNK     INTEGER NOT NULL                             \
                       REFERENCES OBJECTS(NN)                       \
                       ON DELETE CASCADE                            \
                       ON UPDATE CASCADE,                           \
       EVENTTYPES_LNK  INTEGER NOT NULL                             \
                       REFERENCES EVENTTYPES(NN)                    \
                       ON DELETE CASCADE                            \
                       ON UPDATE CASCADE                            \
   );",

  "CREATE INDEX LOG_INDEX1 ON LOG (DATETIME);",


  "CREATE TABLE UNITS_LOCATION (                 \
       NN           INTEGER NOT NULL PRIMARY KEY,\
       DATETIME     TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL,\
       ZONES_LNK    INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE,           \
       OBJECTS_LNK  INTEGER NOT NULL             \
                    REFERENCES OBJECTS(NN)       \
                    ON DELETE CASCADE            \
                    ON UPDATE CASCADE            \
   );",


  "CREATE GENERATOR GEN_GUESTS;",
  "CREATE GENERATOR GEN_GUESTS_ORDERS;",
  "CREATE GENERATOR GEN_GUESTS_REQUEST;",
  "CREATE GENERATOR GEN_LOG;",
  "CREATE GENERATOR GEN_OBJECTS;",
  "CREATE GENERATOR GEN_SCHEDULES_DAYS;",
  "CREATE GENERATOR GEN_SCHEDULES_BREAKS;",
  "CREATE GENERATOR GEN_SCHEDULES_WHOURS;",
  "CREATE GENERATOR GEN_SMS_QUEUE;",
  "CREATE GENERATOR GEN_UNITS;",
  "CREATE GENERATOR GEN_UNITS_LOCATION;",
  "CREATE GENERATOR GEN_ZONES_CFG;",


  "INSERT INTO Objects (nn, otype, name) VALUES (0,    0,    'Meta-object; also well known link_type');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-101, 0,    'Тип: cтруктурные единицы - корневая папка');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-102, 0,    'Тип: структурные единицы - папка');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-103, 0,    'Тип: структурные единицы - юнит');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-1,   -101, 'Структурные единицы');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-111, 0,    'Тип: зоны доступа - корневая папка');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-112, 0,    'Тип: зоны доступа - зона');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-113, 0,    'Тип: зоны доступа - рабочее место в зоне');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-2,   -111, 'Зоны доступа');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-121, 0,    'Тип: графики работы - корневая папка');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-122, 0,    'Тип: графики работы - папка');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-123, 0,    'Тип: графики работы - график');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-3,   -121, 'Графики работы');",
  "INSERT INTO Objects (nn, otype, name) VALUES (-100, 0,    'Корень дерева ;-)');",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, -100, (SELECT objects.nn FROM objects WHERE objects.name = 'Структурные единицы'));",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, -100, (SELECT objects.nn FROM objects WHERE objects.name = 'Зоны доступа'));",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, -100, (SELECT objects.nn FROM objects WHERE objects.name = 'Графики работы'));",

  "INSERT INTO Objects (nn, otype, name) VALUES (GEN_ID(gen_objects,1), -112, 'Здание охраняемого объекта');",
  "INSERT INTO Objects (nn, otype, name) VALUES (GEN_ID(gen_objects,1), -113, 'ПК охраны без турникетов');",
  "INSERT INTO Objects (nn, otype, name) VALUES (GEN_ID(gen_objects,1), -113, 'ПК охраны с турникетами');",
  "INSERT INTO Objects (nn, otype, name) VALUES (GEN_ID(gen_objects,1), -113, 'ПК завуча');",
  "INSERT INTO Objects (nn, otype, name) VALUES (GEN_ID(gen_objects,1), -113, 'ПК для печати карточек');",
  "INSERT INTO Zones_Cfg (nn, objects_lnk, photospath, crtype, controlcrport, entry1_crport, exit1_crport) VALUES (GEN_ID(gen_zones_cfg,1), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК охраны без турникетов'), 'C:\\CAS\\Photos\\', 1, 1, 1, 2);",
  "INSERT INTO Zones_Cfg (nn, objects_lnk, photospath, crtype, controlcrport, entry1_crport, entry1_device, exit1_crport, exit1_device, entry2_crport, entry2_device, exit2_crport, exit2_device) VALUES (GEN_ID(gen_zones_cfg,1), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК охраны с турникетами'), 'C:\\CAS\\Photos\\', 1, 1, 1, 0, 2, 1, 3, 2, 4, 3);",
  "INSERT INTO Zones_Cfg (nn, objects_lnk, photospath) VALUES (GEN_ID(gen_zones_cfg,1), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК завуча'), '\\192.168.16.170\\CAS_Photos\');",
  "INSERT INTO Zones_Cfg (nn, objects_lnk, photospath, crtype, controlcrport) VALUES (GEN_ID(gen_zones_cfg,1), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК для печати карточек'), '::db', 1, 1);",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT objects.nn FROM objects WHERE objects.name = 'Зоны доступа'), (SELECT objects.nn FROM objects WHERE objects.name = 'Здание охраняемого объекта'));",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT objects.nn FROM objects WHERE objects.name = 'Здание охраняемого объекта'), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК охраны без турникетов'));",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT objects.nn FROM objects WHERE objects.name = 'Здание охраняемого объекта'), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК охраны с турникетами'));",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT objects.nn FROM objects WHERE objects.name = 'Здание охраняемого объекта'), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК завуча'));",
  "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT objects.nn FROM objects WHERE objects.name = 'Здание охраняемого объекта'), (SELECT objects.nn FROM objects WHERE objects.name = 'ПК для печати карточек'));",
//  "INSERT INTO Structures (nn, name) VALUES (GEN_ID(gen_structures,1), 'Сотрудники (встроенная)');",
//  "INSERT INTO Units (nn, card, lname, mname, fname, rights, passwrd, enabled, expire, structures_lnk) VALUES (GEN_ID(gen_units,1), 1, 'Директор',  NULL,     NULL,    '01110110011010001', '1', 1, '2006-08-31', 1);",
//  "INSERT INTO Units (nn, card, lname, mname, fname, rights, passwrd, enabled, expire, structures_lnk) VALUES (GEN_ID(gen_units,1), 2, 'Охранник',  'первая', 'смена', '10000000000010001', '2', 1, '2006-08-31', 1);",
//  "INSERT INTO Units (nn, card, lname, mname, fname, rights, passwrd, enabled, expire, structures_lnk) VALUES (GEN_ID(gen_units,1), 3, 'Охранник',  'вторая', 'смена', '10000000000010001', '3', 1, '2006-08-31', 1);",
//  "INSERT INTO Units (nn, card, lname, mname, fname, rights, passwrd, enabled, expire, structures_lnk) VALUES (GEN_ID(gen_units,1), 4, 'Статистик', NULL,     NULL,    '01000100011010000', '4', 1, '2006-08-31', 1);",
  NULL
 };

 for (int i = 0; sqlCmd[i] != NULL; i++)
    {
     IBTransaction1->StartTransaction();
     IBSQL1->SQL->Text = sqlCmd[i];
     try
        {
         IBSQL1->ExecQuery();
        }
     catch (...)
          {
           fMain->addMessage("Не удалось выполнить: " + AnsiString(sqlCmd[i]));
          }
     IBTransaction1->Commit();
    }

 fMain->addMessage("Созданы таблицы в базе данных");
}
//---------------------------------------------------------------------------
void __fastcall TfDBService::btExcelExportClick(TObject *Sender)
{
 if ( !SaveDialog2->Execute() )
   return;

 if ( chbExportLog->Checked )
   if ( !SaveDialog3->Execute() )
     return;

 if ( !openDB() )
   return;

 DeleteFile(SaveDialog2->FileName.c_str());

 // Считать версию БД
 int DBVersion;
 try
    {
     IBTransaction1->StartTransaction();
     IBSQL1->SQL->Text = "SELECT * FROM Organization_Info WHERE nn=1;";
     IBSQL1->ExecQuery();
     IBSQL1->Close();

     DBVersion = IBSQL1->FieldByName("DBVersion")->AsInteger;
    }
 catch (...)
    {
     IBSQL1->Close();
     DBVersion = 180;
    }

 Variant v_Excel, v_ExcelSheet;
 v_Excel = CreateOleObject("Excel.Application");
 v_Excel.OlePropertySet("Visible", chbExcelVisible->Checked);
 v_Excel.OlePropertyGet("Workbooks").OleProcedure("Add");

 // Список групп
   // Лист
 v_ExcelSheet = v_Excel.OlePropertyGet("Worksheets", 2);
 v_ExcelSheet.OleProcedure("Select");
   // Заголовок
 v_ExcelSheet.OlePropertyGet("Rows", "1:1").OlePropertySet("HorizontalAlignment", xlCenter);
 v_ExcelSheet.OlePropertyGet("Rows", "1:1").OlePropertyGet("Font").OlePropertySet("Bold", true);
 v_ExcelSheet.OlePropertyGet("Columns","A:A").OlePropertySet("ColumnWidth", 35);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 1).OlePropertySet("Value", "Наименование подразделения");
   // Данные
 if ( DBVersion < 190 )
   IBSQL1->SQL->Text = "SELECT * FROM Structures ORDER BY name;";
 else
   IBSQL1->SQL->Text = "SELECT name FROM Objects WHERE otype != 0 AND otype != -123 AND otype != -113 AND otype != -103 ORDER BY name";
 IBSQL1->ExecQuery();
 for (int i = 2; !IBSQL1->Eof; IBSQL1->Next(), i++)
    {
     fMain->addMessage("Список групп - " + IntToStr(i - 1));

     v_ExcelSheet.OlePropertyGet("Cells", i, 1).OlePropertySet("Value", IBSQL1->FieldByName("name")->AsString.c_str());
    }
 IBSQL1->Close();

 // Списочный состав групп
   // Лист
 v_ExcelSheet = v_Excel.OlePropertyGet("Worksheets", 1);
 v_ExcelSheet.OleProcedure("Select");
   // Заголовок
 v_ExcelSheet.OlePropertyGet("Rows", "1:1").OlePropertySet("HorizontalAlignment", xlCenter);
 v_ExcelSheet.OlePropertyGet("Rows", "1:1").OlePropertySet("VerticalAlignment", xlCenter);
 v_ExcelSheet.OlePropertyGet("Rows", "1:1").OlePropertySet("WrapText", true); // переносить по словам
 v_ExcelSheet.OlePropertyGet("Rows", "1:1").OlePropertyGet("Font").OlePropertySet("Bold", true);
 v_ExcelSheet.OlePropertyGet("Columns","A:A").OlePropertySet("ColumnWidth", 18);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 1).OlePropertySet("Value", "Фамилия");
 v_ExcelSheet.OlePropertyGet("Columns","B:B").OlePropertySet("ColumnWidth", 18);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 2).OlePropertySet("Value", "Имя");
 v_ExcelSheet.OlePropertyGet("Columns","C:C").OlePropertySet("ColumnWidth", 18);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 3).OlePropertySet("Value", "Отчество");
 v_ExcelSheet.OlePropertyGet("Columns","D:D").OlePropertySet("ColumnWidth", 15);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 4).OlePropertySet("Value", "Название подразделения");
 v_ExcelSheet.OlePropertyGet("Columns","E:E").OlePropertySet("ColumnWidth", 12);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 5).OlePropertySet("Value", "Карточка");
 v_ExcelSheet.OlePropertyGet("Columns","F:F").OlePropertySet("ColumnWidth", 12);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 6).OlePropertySet("Value", "Шаблон для печати");
 v_ExcelSheet.OlePropertyGet("Columns","G:G").OlePropertySet("ColumnWidth", 10);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 7).OlePropertySet("Value", "Помечена для печати");
 v_ExcelSheet.OlePropertyGet("Columns","H:H").OlePropertySet("ColumnWidth", 36);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 8).OlePropertySet("Value", "Фото");
 v_ExcelSheet.OlePropertyGet("Columns","I:I").OlePropertySet("ColumnWidth", 11);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 9).OlePropertySet("Value", "Домашний адрес");
 v_ExcelSheet.OlePropertyGet("Columns","J:J").OlePropertySet("ColumnWidth", 9);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 10).OlePropertySet("Value", "Телефон");
 v_ExcelSheet.OlePropertyGet("Columns","K:K").OlePropertySet("ColumnWidth", 14);
 v_ExcelSheet.OlePropertyGet("Cells", 1, 11).OlePropertySet("Value", "Полис медицинского страхования");

   // Данные
 IBDataSet1->InsertSQL->Text = "";

 if ( DBVersion < 190 )
   IBDataSet1->SelectSQL->Text = "SELECT                                     \
                                        Units.*,                             \
                                        Structures.name AS structure_name    \
                                  FROM                                       \
                                      Units, Structures                      \
                                  WHERE                                      \
                                        Units.structures_lnk = Structures.nn \
                                  ORDER BY                                   \
                                          structure_name, Units.lname, Units.fname, Units.mname;";
 else
   IBDataSet1->SelectSQL->Text = "SELECT    \
                                        nn, lname, fname, mname, card, template, marked_for_printing, structure_name, enabled, expire, photo, home_address, phone, medical_policy \
                                  FROM      \
                                      Units \
                                  ORDER BY  \
                                          structure_name, Units.lname, Units.fname, Units.mname;";

 IBDataSet1->Prepare();  IBDataSet1->Open();
 AnsiString PhotoFileName = fMain->ExePath + "Photos";
 CreateDirectory(PhotoFileName.c_str(), NULL);
 for (int i = 2; !IBDataSet1->Eof; IBDataSet1->Next(), i++)
    {
     fMain->addMessage("Списочный состав групп - " + IntToStr(i - 1));

     v_ExcelSheet.OlePropertyGet("Cells", i, 1).OlePropertySet("Value", IBDataSet1->FieldByName("lname"         )->AsString.c_str());
     v_ExcelSheet.OlePropertyGet("Cells", i, 2).OlePropertySet("Value", IBDataSet1->FieldByName("fname"         )->AsString.c_str());
     v_ExcelSheet.OlePropertyGet("Cells", i, 3).OlePropertySet("Value", IBDataSet1->FieldByName("mname"         )->AsString.c_str());
     v_ExcelSheet.OlePropertyGet("Cells", i, 4).OlePropertySet("Value", IBDataSet1->FieldByName("structure_name")->AsString.c_str());
     v_ExcelSheet.OlePropertyGet("Cells", i, 5).OlePropertySet("Value", IBDataSet1->FieldByName("card"          )->AsString.c_str());
     try
        {
         v_ExcelSheet.OlePropertyGet("Cells", i, 6).OlePropertySet("Value", IBDataSet1->FieldByName("template"           )->AsString.c_str());
         v_ExcelSheet.OlePropertyGet("Cells", i, 7).OlePropertySet("Value", IBDataSet1->FieldByName("marked_for_printing")->AsString.c_str());
         v_ExcelSheet.OlePropertyGet("Cells", i, 9).OlePropertySet("Value", IBDataSet1->FieldByName("home_address"       )->AsString.c_str());
         v_ExcelSheet.OlePropertyGet("Cells", i, 10).OlePropertySet("Value",IBDataSet1->FieldByName("phone"              )->AsString.c_str());
         v_ExcelSheet.OlePropertyGet("Cells", i, 11).OlePropertySet("Value",IBDataSet1->FieldByName("medical_policy"     )->AsString.c_str());

         if ( IBDataSet1->FieldByName("card")->AsInteger > 0)
           PhotoFileName = fMain->ExePath + "Photos\\" + IBDataSet1->FieldByName("card")->AsString + ".jpg";
         else
           PhotoFileName = fMain->ExePath + "Photos\\" + IBDataSet1->FieldByName("nn")->AsString + ".jpg";

         if ( fMain->SQL_Fwk->PhotoToFile(IBDataSet1, PhotoFileName) )
           v_ExcelSheet.OlePropertyGet("Cells", i, 8).OlePropertySet("Value", PhotoFileName.c_str());
       }
     catch (...) { }
    }
 IBDataSet1->Close();
 IBTransaction1->Commit();

 v_ExcelSheet.OleProcedure("SaveAs", SaveDialog2->FileName.c_str());
 v_Excel.OleProcedure("Quit");

 // События
 if ( chbExportLog->Checked )
   {
    IBTransaction1->StartTransaction();

    if ( DBVersion < 197 )
      IBSQL1->SQL->Text = "SELECT                    \
                                 Log.datetime,       \
                                 Log.zones_lnk,      \
                                 Log.eventtypes_lnk, \
                                 Units.card AS ucard \
                           FROM                      \
                               Log, Units            \
                           WHERE                     \
                                Units.card > 0       \
                            AND Log.units_lnk = Units.nn;";
    else
      IBSQL1->SQL->Text = "SELECT                    \
                                 Log.datetime,       \
                                 Log.zones_lnk,      \
                                 Log.objects_lnk,    \
                                 Log.eventtypes_lnk, \
                                 Units.card AS ucard \
                           FROM                      \
                               Log, Units            \
                           WHERE                     \
                                Units.card > 0       \
                            AND Log.objects_lnk = Units.objects_lnk;";

    IBSQL1->ExecQuery();

    if ( !IBSQL1->Eof )
      {
       FILE *outFile = fopen(SaveDialog3->FileName.c_str(), "w");
       AnsiString S1;

       for (int i = 1; !IBSQL1->Eof ; IBSQL1->Next(), i++)
          {
           fMain->addMessage("События - " + IntToStr(i));
           S1 = "INSERT INTO Log(nn, datetime, zones_lnk, objects_lnk, eventtypes_lnk) VALUES(GEN_ID(gen_log,1),'" +
                                 IBSQL1->FieldByName("datetime")->AsString + "'," +
                                 IBSQL1->FieldByName("zones_lnk")->AsString +
                                 ",(SELECT Units.objects_lnk FROM Units WHERE Units.card = '" + IBSQL1->FieldByName("ucard")->AsString + "')," +
                                 IBSQL1->FieldByName("eventtypes_lnk")->AsString + ");\n";
           fputs(S1.c_str(), outFile);
          }

       fclose(outFile);
      }
    IBSQL1->Close();
   }

 fMain->addMessage("Экспорт завершен");
}
//---------------------------------------------------------------------------
void __fastcall TfDBService::btExcelImportClick(TObject *Sender)
{
 if ( !OpenDialog2->Execute() )
   return;

 if ( RadioGroup1->ItemIndex == 1 && Edit1->Text.IsEmpty() )
   {
    AnsiString PhotosPath;
    if ( !SelectDirectory("Выберите папку для копирования фотографий", "", PhotosPath) )
      return;

    if (PhotosPath[PhotosPath.Length()] != '\\')
      PhotosPath += '\\';
     Edit1->Text = PhotosPath;
   }

 if ( !openDB() )
   return;

 AnsiString S1, S2, Cell, newNN, newName;
 Variant    v_Excel, v_ExcelSheet;

 v_Excel = CreateOleObject("Excel.Application");
 v_Excel.OlePropertySet("Visible", chbExcelVisible->Checked);
 v_Excel.OlePropertyGet("Workbooks").OlePropertyGet("Open", OpenDialog2->FileName.c_str());

 // Список групп
 v_ExcelSheet = v_Excel.OlePropertyGet("Worksheets", 2); // "Лист2");
 v_ExcelSheet.OleProcedure("Select");
 for (int i = 2; ; i++)
    {
     Cell = "A" + IntToStr(i); S1 = v_ExcelSheet.OlePropertyGet("Range", Cell.c_str());
     if (S1.IsEmpty())
       break;

     fMain->addMessage("Список групп - " + IntToStr(i - 1));

     IBTransaction1->StartTransaction();
     IBSQL1->SQL->Text = "SELECT GEN_ID(gen_objects, 1) AS gv FROM rdb$database;";
     IBSQL1->ExecQuery();
     newNN = IBSQL1->FieldByName("gv")->AsString;
     IBSQL1->Close();

     IBSQL1->SQL->Text = "INSERT INTO Objects (nn, name, otype) VALUES (" + newNN + ", '" + S1.TrimRight() +"', -102);";
     IBSQL1->ExecQuery();
     IBTransaction1->Commit();

     IBTransaction1->StartTransaction();
     IBSQL1->SQL->Text = "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT MIN(objects.nn) FROM objects WHERE objects.name = 'Структурные единицы'), " + newNN + ");";
     IBSQL1->ExecQuery();
     IBTransaction1->Commit();
   }

 // Списочный состав групп
 IBDataSet1->InsertSQL->Text = "INSERT INTO \
                                           Units (nn, lname, fname, mname, card, template, marked_for_printing, objects_lnk, enabled, expire, photo, home_address, phone, medical_policy) \
                                VALUES \
                                      (:nn, :lname, :fname, :mname, :card, :template, :marked_for_printing, :objects_lnk, :enabled, :expire, :photo, :home_address, :phone, :medical_policy);";
 IBDataSet1->SelectSQL->Text = "SELECT    \
                                      nn, lname, fname, mname, card, template, marked_for_printing, objects_lnk, structure_name, enabled, expire, photo, home_address, phone, medical_policy \
                                  FROM      \
                                      Units;";

 v_ExcelSheet = v_Excel.OlePropertyGet("Worksheets", 1); // "Лист1");
 v_ExcelSheet.OleProcedure("Select");

 for (int i = 2; ; i++)
    {
     fMain->addMessage("Списочный состав групп - " + IntToStr(i - 1));

     if (v_ExcelSheet.OlePropertyGet("Cells", i, 1).OlePropertyGet("Value").IsEmpty())
       break;

     IBTransaction1->StartTransaction();
     IBSQL1->SQL->Text = "SELECT GEN_ID(gen_objects, 1) AS gv FROM rdb$database;";
     IBSQL1->ExecQuery();
     newNN = IBSQL1->FieldByName("gv")->AsString;
     IBSQL1->Close();

     newName = v_ExcelSheet.OlePropertyGet("Cells", i, 1).OlePropertyGet("Value") +
               ( v_ExcelSheet.OlePropertyGet("Cells", i, 2).OlePropertyGet("Value").IsEmpty() ? AnsiString("") : AnsiString(" " + v_ExcelSheet.OlePropertyGet("Cells", i, 2).OlePropertyGet("Value"))) +
               ( v_ExcelSheet.OlePropertyGet("Cells", i, 3).OlePropertyGet("Value").IsEmpty() ? AnsiString("") : AnsiString(" " + v_ExcelSheet.OlePropertyGet("Cells", i, 3).OlePropertyGet("Value")));

     IBSQL1->SQL->Text = "INSERT INTO Objects (nn, name, otype) VALUES (" + newNN + ", '" + newName +"', -103);";
     IBSQL1->ExecQuery();
     IBTransaction1->Commit();

     IBTransaction1->StartTransaction();
     IBSQL1->SQL->Text = "INSERT INTO Objects_Links (link_type, left_lnk, right_lnk) VALUES (0, (SELECT MIN(objects.nn) FROM objects WHERE objects.name = '" + v_ExcelSheet.OlePropertyGet("Cells", i, 4).OlePropertyGet("Value") + "'), " + newNN + ");";
     IBSQL1->ExecQuery();
     IBTransaction1->Commit();

     IBDataSet1->Open();
     IBDataSet1->Append();
     IBDataSet1->FieldByName("lname"              )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 1).OlePropertyGet("Value");
     IBDataSet1->FieldByName("fname"              )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 2).OlePropertyGet("Value");
     IBDataSet1->FieldByName("mname"              )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 3).OlePropertyGet("Value");
     IBDataSet1->FieldByName("card"               )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 5).OlePropertyGet("Value");
     IBDataSet1->FieldByName("template"           )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 6).OlePropertyGet("Value");
     IBDataSet1->FieldByName("marked_for_printing")->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 7).OlePropertyGet("Value");
     IBDataSet1->FieldByName("home_address"       )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 9).OlePropertyGet("Value");
     IBDataSet1->FieldByName("phone"              )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 10).OlePropertyGet("Value");
     IBDataSet1->FieldByName("medical_policy"     )->AsString = v_ExcelSheet.OlePropertyGet("Cells", i, 11).OlePropertyGet("Value");
     IBDataSet1->FieldByName("objects_lnk"        )->AsString = newNN;
     IBDataSet1->FieldByName("enabled"            )->AsInteger  = 1;
     IBDataSet1->FieldByName("expire"             )->AsDateTime = TDateTime(2010, 9, 1);

     if ( RadioGroup1->ItemIndex == 0 )
       {
        try {
             fMain->SQL_Fwk->PhotoToDB(IBDataSet1, v_ExcelSheet.OlePropertyGet("Cells", i, 8).OlePropertyGet("Value"));
            }
        catch (const EFOpenError &Exception)
             {
              fMain->addMessage("Списочный состав групп - " + IntToStr(i - 1) + ": " + Exception.Message);
             }
       }
     else
       {
        AnsiString PictureOldFileName = (AnsiString) v_ExcelSheet.OlePropertyGet("Cells", i, 8).OlePropertyGet("Value"),
                   PictureNewFileName = Edit1->Text + v_ExcelSheet.OlePropertyGet("Cells", i, 5).OlePropertyGet("Value") + ".jpg";
        CopyFile(PictureOldFileName.c_str(), PictureNewFileName.c_str(), false);
       }

     IBDataSet1->Post();
     IBTransaction1->Commit();
   }

 v_Excel.OleProcedure("Quit");
 fMain->addMessage("Импорт завершен");
}
//---------------------------------------------------------------------------
bool __fastcall TfDBService::openDB()
{
 if (LabeledEdit4->Text.IsEmpty())
   {
    if (OpenDialog1->Execute())
      {
       LabeledEdit4->Text = OpenDialog1->FileName;
      }
    else
      return false;
   }

 IBDatabase1->Close();

 if (LabeledEdit3->Text.IsEmpty())
   IBDatabase1->DatabaseName = LabeledEdit4->Text;
 else
   IBDatabase1->DatabaseName = LabeledEdit3->Text + ":" + LabeledEdit4->Text;

 IBDatabase1->Params->Clear();
 IBDatabase1->Params->Add("user_name=" + LabeledEdit1->Text);
 IBDatabase1->Params->Add("password="  + LabeledEdit2->Text);
 IBDatabase1->Params->Add("lc_ctype=WIN1251");

 IBDatabase1->Open();

 if ( !IBDatabase1->Connected )
   {
    fMain->addMessage("Операция остановлена: не удалось подсоединиться к созданной базе данных");
    return false;
   }
 else
   {
    fMain->addMessage("Успешно подключена база данных " + IBDatabase1->DatabaseName);
    return true;
   }
}
//---------------------------------------------------------------------------