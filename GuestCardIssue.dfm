object fGuestCardIssue: TfGuestCardIssue
  Left = 217
  Top = 113
  Caption = #1054#1092#1086#1088#1084#1083#1077#1085#1080#1077' '#1075#1086#1089#1090#1077#1074#1086#1075#1086' '#1087#1088#1086#1087#1091#1089#1082#1072
  ClientHeight = 511
  ClientWidth = 913
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  Position = poDefault
  Visible = True
  OnActivate = FormResize
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 297
    Height = 476
    Align = alLeft
    Caption = ' '#1040#1088#1093#1080#1074' '#1087#1086#1089#1077#1090#1080#1090#1077#1083#1077#1081' '
    TabOrder = 0
    object ImageArch: TImage
      Left = 2
      Top = 254
      Width = 293
      Height = 220
      Align = alBottom
      Center = True
      Proportional = True
    end
    object DBGrid1: TDBGrid
      Left = 2
      Top = 15
      Width = 293
      Height = 225
      Align = alTop
      DataSource = DataSourceGuests
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      PopupMenu = DBGrid1PopupMenu
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnCellClick = DBGrid1CellClick
      OnTitleClick = DBGrid1TitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'lname'
          Title.Alignment = taCenter
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Width = 44
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'fname'
          Title.Caption = #1048#1084#1103
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'mname'
          Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'organization_name'
          Title.Alignment = taCenter
          Title.Caption = #1050#1091#1076#1072
          Width = 49
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'visit_from'
          Title.Alignment = taCenter
          Title.Caption = #1054#1090#1082#1091#1076#1072
          Width = 51
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'visit_reason'
          Title.Alignment = taCenter
          Title.Caption = #1055#1088#1080#1095#1080#1085#1072
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'visit_date'
          Title.Alignment = taCenter
          Title.Caption = #1044#1072#1090#1072
          Visible = True
        end>
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 476
    Width = 913
    Height = 35
    Align = alBottom
    TabOrder = 1
    object ButtonOk: TButton
      Left = 368
      Top = 6
      Width = 105
      Height = 25
      Caption = #1042#1099#1076#1072#1090#1100
      Enabled = False
      TabOrder = 0
      OnClick = ButtonOkClick
    end
    object ButtonCancel: TButton
      Left = 494
      Top = 6
      Width = 107
      Height = 25
      Caption = #1054#1090#1084#1077#1085#1072
      TabOrder = 1
      OnClick = ButtonCancelClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 649
    Top = 0
    Width = 264
    Height = 476
    Align = alRight
    Caption = ' '#1047#1072#1103#1074#1082#1080' '#1085#1072' '#1074#1088#1077#1084#1077#1085#1085#1099#1077' '#1087#1088#1086#1087#1091#1089#1082#1072' '
    TabOrder = 2
    object DBGrid2: TDBGrid
      Left = 2
      Top = 15
      Width = 260
      Height = 459
      Align = alClient
      DataSource = DataSourceGuestsReq
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'lname'
          Title.Alignment = taCenter
          Title.Caption = #1060#1072#1084#1080#1083#1080#1103
          Width = 47
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'fname'
          Title.Caption = #1048#1084#1103
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'mname'
          Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'organization_name'
          Title.Alignment = taCenter
          Title.Caption = #1050#1091#1076#1072
          Width = 49
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'visit_from'
          Title.Alignment = taCenter
          Title.Caption = #1054#1090#1082#1091#1076#1072
          Width = 51
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'visit_reason'
          Title.Alignment = taCenter
          Title.Caption = #1055#1088#1080#1095#1080#1085#1072
          Width = 61
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'visit_date'
          Title.Alignment = taCenter
          Title.Caption = #1044#1072#1090#1072
          Visible = True
        end>
    end
  end
  object GroupBox3: TGroupBox
    Left = 304
    Top = 0
    Width = 345
    Height = 473
    Caption = #1054#1092#1086#1088#1084#1083#1077#1085#1080#1077
    TabOrder = 3
    object ImageMain: TImage
      Left = 2
      Top = 224
      Width = 335
      Height = 177
      Center = True
      Proportional = True
    end
    object ButtonScan: TButton
      Left = 120
      Top = 408
      Width = 121
      Height = 25
      Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1080#1079' '#1092#1072#1081#1083#1072
      TabOrder = 4
      OnClick = ButtonScanClick
    end
    object EditFrom: TLabeledEdit
      Left = 2
      Top = 130
      Width = 336
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1090#1082#1091#1076#1072
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      OnChange = ComboBox1Change
    end
    object ComboBox1: TComboBox
      Left = 2
      Top = 88
      Width = 337
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = ComboBox1Change
    end
    object ButtonArch: TButton
      Left = 22
      Top = 408
      Width = 75
      Height = 25
      Caption = '>>'
      TabOrder = 3
      OnClick = ButtonArchClick
    end
    object ButtonQuery: TButton
      Left = 262
      Top = 408
      Width = 75
      Height = 25
      Caption = '<<'
      TabOrder = 5
      OnClick = ButtonQueryClick
    end
    object ComboBox2: TComboBox
      Left = 8
      Top = 440
      Width = 329
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
      OnChange = ComboBox1Change
    end
    object ComboBoxReas: TComboBox
      Left = 2
      Top = 168
      Width = 337
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      OnChange = ComboBox1Change
    end
    object StaticText1: TStaticText
      Left = 2
      Top = 152
      Width = 107
      Height = 17
      Caption = #1055#1088#1080#1095#1080#1085#1072' '#1087#1086#1089#1077#1097#1077#1085#1080#1103
      TabOrder = 6
    end
    object StaticText2: TStaticText
      Left = 2
      Top = 64
      Width = 182
      Height = 17
      Caption = #1042' '#1082#1072#1082#1091#1102' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1086#1085#1085#1091#1102' '#1077#1076#1080#1085#1080#1094#1091
      TabOrder = 8
    end
    object ComboBox1a: TComboBox
      Left = 32
      Top = 88
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 9
      Visible = False
    end
    object ComboBox2a: TComboBox
      Left = 88
      Top = 440
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 10
      Visible = False
    end
    object EditMN: TLabeledEdit
      Left = 227
      Top = 28
      Width = 110
      Height = 27
      EditLabel.Width = 47
      EditLabel.Height = 13
      EditLabel.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 11
      OnChange = ComboBox1Change
      OnKeyPress = EditMNKeyPress
    end
    object EditFN: TLabeledEdit
      Left = 115
      Top = 28
      Width = 110
      Height = 27
      EditLabel.Width = 22
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 12
      OnChange = ComboBox1Change
      OnKeyPress = EditFNKeyPress
    end
    object EditLN: TLabeledEdit
      Left = 3
      Top = 28
      Width = 110
      Height = 27
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -17
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 13
      OnChange = EditLNChange
      OnKeyPress = EditLNKeyPress
    end
    object DateTimePicker1: TDateTimePicker
      Left = 2
      Top = 200
      Width = 337
      Height = 21
      CalAlignment = dtaLeft
      Date = 38796.6899104398
      Time = 38796.6899104398
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 14
      OnChange = ComboBox1Change
    end
  end
  object GuestTransaction: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 192
    Top = 224
  end
  object Q1: TIBQuery
    Database = fMain.IBDatabase1
    Transaction = GuestTransaction
    Left = 232
    Top = 224
  end
  object Guests: TIBDataSet
    Database = fMain.IBDatabase1
    Transaction = GuestTransaction
    InsertSQL.Strings = (
        'INSERT INTO GUESTS(NN,FNAME,MNAME,LNAME,STRUCTURES_LNK,visit_fro' +
        'm,visit_reason,DOCUMENT_photo) VALUES (:NN,:FNAME,:MNAME,:LNAME,' +
        ':STRUCTURES_LNK,:visit_from,:visit_reason,:DOCUMENT_photo)')
    RefreshSQL.Strings = (
      'SELECT * FROM GUESTS WHERE NN=:NN')
    SelectSQL.Strings = (
      'SELECT * FROM GUESTS'
      'ORDER BY LNAME')
    GeneratorField.Field = 'NN'
    GeneratorField.Generator = 'GEN_GUESTS'
    Left = 192
    Top = 256
  end
  object DataSourceGuests: TDataSource
    DataSet = Guests
    Left = 232
    Top = 256
  end
  object GuestsReq: TIBDataSet
    Database = fMain.IBDatabase1
    Transaction = GuestTransaction
    RefreshSQL.Strings = (
      'SELECT * FROM GUESTS_REQUEST WHERE NN=:NN')
    SelectSQL.Strings = (
      'SELECT * FROM GUESTS_REQUEST'
      'WHERE FINISHED=0'
      'ORDER BY LNAME')
    Left = 192
    Top = 288
  end
  object DataSourceGuestsReq: TDataSource
    DataSet = GuestsReq
    Left = 232
    Top = 336
  end
  object OpenJPGDialog: TOpenPictureDialog
    DefaultExt = 'jpg'
    Filter = 'JPEG Image File (*.jpg)|*.jpg|JPEG Image File (*.jpeg)|*.jpeg'
    Left = 112
    Top = 304
  end
  object Units: TIBDataSet
    Database = fMain.IBDatabase1
    Transaction = GuestTransaction
    RefreshSQL.Strings = (
      'SELECT * FROM UNITS WHERE NN=:NN')
    ModifySQL.Strings = (
      
        'UPDATE UNITS SET PHOTO=:PHOTO,CARD_TYPE=:CARD_TYPE,EXPIRE=:EXPIR' +
        'E  WHERE NN=:NN')
    Left = 192
    Top = 320
  end
  object DBGrid1PopupMenu: TPopupMenu
    Left = 184
    Top = 144
    object N1: TMenuItem
      Caption = #1060#1080#1083#1100#1090#1088
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1054#1090#1084#1077#1085#1072' '#1092#1080#1083#1100#1090#1088#1072
      OnClick = N2Click
    end
  end
end