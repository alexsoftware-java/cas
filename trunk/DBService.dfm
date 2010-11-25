object fDBService: TfDBService
  Left = 342
  Top = 179
  Caption = #1054#1087#1077#1088#1072#1094#1080#1080' '#1089' '#1073#1072#1079#1086#1081' '#1076#1072#1085#1085#1099#1093
  ClientHeight = 302
  ClientWidth = 452
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object LabeledEdit1: TLabeledEdit
    Left = 2
    Top = 24
    Width = 145
    Height = 21
    EditLabel.Width = 96
    EditLabel.Height = 13
    EditLabel.Caption = #1048#1084#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
    Text = 'sysdba'
  end
  object LabeledEdit2: TLabeledEdit
    Left = 148
    Top = 24
    Width = 145
    Height = 21
    EditLabel.Width = 38
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1072#1088#1086#1083#1100
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
    Text = 'masterkey'
  end
  object LabeledEdit3: TLabeledEdit
    Left = 294
    Top = 24
    Width = 157
    Height = 21
    EditLabel.Width = 37
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1077#1088#1074#1077#1088
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
  end
  object LabeledEdit4: TLabeledEdit
    Left = 2
    Top = 66
    Width = 449
    Height = 21
    EditLabel.Width = 343
    EditLabel.Height = 13
    Width = 449
    Height = 21
    EditLabel.Caption = #1055#1091#1090#1100' ('#1083#1086#1082#1072#1083#1100#1085#1099#1081' '#1086#1090#1085#1086#1089#1080#1090#1077#1083#1100#1085#1086' '#1089#1077#1088#1074#1077#1088#1072') '#1080' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093    EditLabel.Caption = #1055#1091#1090#1100' ('#1083#1086#1082#1072#1083#1100#1085#1099#1081' '#1086#1090#1085#1086#1089#1080#1090#1077#1083#1100#1085#1086' '#1089#1077#1088#1074#1077#1088#1072') '#1080' '#1080#1084#1103' '#1092#1072#1081#1083#1072' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
  end
  object RadioGroup1: TRadioGroup
    Left = 2
    Top = 96
    Width = 449
    Height = 57
    Caption = ' '#1060#1086#1090#1086#1075#1088#1072#1092#1080#1080' '
    ItemIndex = 0
    Items.Strings = (
      #1048#1084#1087#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1074' '#1041#1044
      #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100' '#1074' '#1087#1072#1087#1082#1091)
    TabOrder = 8
  end
  object Edit1: TEdit
    Left = 144
    Top = 128
    Width = 300
    Height = 21
    TabOrder = 9
  end
  object chbExportLog: TCheckBox
    Left = 8
    Top = 168
    Width = 209
    Height = 17
    Caption = #1069#1082#1089#1087#1086#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1080#1089#1090#1086#1088#1080#1102' ('#1089#1086#1073#1099#1090#1080#1103')'
    TabOrder = 10
  end
  object chbExcelVisible: TCheckBox
    Left = 8
    Top = 200
    Width = 185
    Height = 17
    Caption = #1044#1077#1083#1072#1090#1100' '#1086#1082#1085#1086' MS Excel '#1074#1080#1076#1080#1084#1099#1084
    TabOrder = 6
  end
  object btDBCreate: TButton
    Left = 2
    Top = 264
    Width = 121
    Height = 25
    Caption = #1057#1086#1079#1076#1072#1090#1100' '#1087#1091#1089#1090#1091#1102' '#1041#1044
    TabOrder = 5
    OnClick = btDBCreateClick
  end
  object btExcelExport: TButton
    Left = 138
    Top = 264
    Width = 153
    Height = 25
    Caption = #1069#1082#1089#1087#1086#1088#1090' '#1080#1079' '#1041#1044' '#1074' MS Excel'
    TabOrder = 7
    OnClick = btExcelExportClick
  end
  object btExcelImport: TButton
    Left = 298
    Top = 264
    Width = 153
    Height = 25
    Caption = #1048#1084#1087#1086#1088#1090' '#1080#1079' MS Excel '#1074' '#1041#1044
    TabOrder = 4
    OnClick = btExcelImportClick
  end
  object IBDatabase1: TIBDatabase
    LoginPrompt = False
    Left = 48
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = IBDatabase1
    Params.Strings = (
      'read_committed'
      'rec_version'
      'nowait')
    Left = 48
    Top = 32
  end
  object IBSQL1: TIBSQL
    Database = IBDatabase1
    Transaction = IBTransaction1
    Left = 48
    Top = 64
  end
  object IBDataSet1: TIBDataSet
    Database = IBDatabase1
    Transaction = IBTransaction1
    ForcedRefresh = True
    ParamCheck = False
    GeneratorField.Field = 'nn'
    GeneratorField.Generator = 'GEN_UNITS'
    Left = 88
    Top = 64
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'gdb'
    Filter = #1060#1072#1081#1083#1099' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093' (*.gdb)|*.gdb'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 408
    Top = 272
  end
  object SaveDialog2: TSaveDialog
    DefaultExt = 'xls'
    Filter = #1060#1072#1081#1083#1099' MS Excel (*.xls)|*.xls'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = #1048#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1101#1089#1087#1086#1088#1090#1080#1088#1086#1074#1072#1085#1085#1099#1093' '#1076#1072#1085#1085#1099#1093
    Left = 200
    Top = 264
  end
  object SaveDialog3: TSaveDialog
    DefaultExt = 'txt'
    Filter = #1058#1077#1082#1089#1090#1086#1074#1086#1081' '#1092#1072#1081#1083' (*.txt)|*.txt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Title = #1048#1084#1103' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1080#1089#1090#1086#1088#1080#1080' ('#1089#1086#1073#1099#1090#1080#1081')'
    Left = 208
    Top = 160
  end
  object OpenDialog1: TOpenDialog
    Filter = #1060#1072#1081#1083#1099' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093' (*.gdb)|*.gdb'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Title = #1042#1099#1073#1086#1088' '#1092#1072#1081#1083#1072' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093
    Left = 376
    Top = 64
  end
  object OpenDialog2: TOpenDialog
    Filter = #1060#1072#1081#1083#1099' MS Excel (*.xls; *.xlsx )|*.xls; *.xlsx'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Title = #1042#1099#1073#1086#1088' '#1092#1072#1081#1083#1072' MS Excel '#1076#1083#1103' '#1080#1084#1087#1086#1088#1090#1072
    Left = 344
    Top = 256
  end
end