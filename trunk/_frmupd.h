#ifndef _MN_FORM_UPDATE_FUNCTIONS
#define _MN_FORM_UPDATE_FUNCTIONS

#include <StdCtrls.hpp>
#include <IBQuery.hpp>

void QUpdateFromAnsiString(TIBQuery *Q1,AnsiString Text,char *field);
void QUpdateDoubleFromAnsiString(TIBQuery *Q1,AnsiString Text,char *field);
void QUpdateFromInt(TIBQuery *Q1,int value,char *field);
void QUpdateFromIntNM(TIBQuery *Q1,int value,char *field);
void QUpdateFromCombo(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,char *field);
void FormCombosFromTable(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,char *table,int value);
void FormCombosFromTable_Ex(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,char *table,char *field,char *cond,char *order_by,int value);
void FormCombosFromPersons(TIBQuery *Q1,TComboBox *Box1,TComboBox *Box2,int value);
void QInsertText(AnsiString Text,char *fff,char *vvv,char *field);
void QInsertInt(int i,char *fff,char *vvv,char *field);
void QInsertIntNM(int i,char *fff,char *vvv,char *field);
void QInsertIntFromText(AnsiString Text,char *fff,char *vvv,char *field);
void QInsertDoubleFromText(AnsiString Text,char *fff,char *vvv,char *field);
void QInsertDoubleZFromText(AnsiString Text,char *fff,char *vvv,char *field);
void QInsertIntFromCombo(TComboBox *Box1,TComboBox *Box2,char *fff,char *vvv,char *field);
int QCheckExist(TIBQuery *Q1,char *table,char *where);
int QGetStatus(TIBQuery *Q1,char *table,char *where);
void QLookupNNFromVal(TIBQuery *Q1,char *table,char *field,char *val,int *nn);
void QLookupValFromNN(TIBQuery *Q1,char *table,char *field,char *val,int nn);
int QSeek(TIBQuery *Q1,char *field_name,int NN);
#endif