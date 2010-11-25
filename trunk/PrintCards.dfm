object fPrintCards: TfPrintCards
  Left = 243
  Top = 36
  Width = 913
  Height = 565
  ActiveControl = GroupBox1
  Caption = #1055#1077#1095#1072#1090#1100' '#1082#1072#1088#1090#1086#1095#1077#1082
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = True
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnMouseWheel = FormMouseWheel
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 880
    Height = 150
    Align = alTop
    TabOrder = 10
    object btPrint: TButton
      Left = 680
      Top = 62
      Width = 113
      Height = 25
      Caption = #1055#1077#1095#1072#1090#1100
      TabOrder = 0
      OnClick = PrintClick
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 10
      Width = 209
      Height = 129
      Caption = ' '#1053#1040' '#1063#1025#1052' '#1055#1045#1063#1040#1058#1040#1058#1068' '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object rbPhotoPrinter: TRadioButton
        Left = 8
        Top = 24
        Width = 113
        Height = 17
        Caption = #1060#1086#1090#1086'-'#1087#1088#1080#1085#1090#1077#1088' A4'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = rbPhotoPrinterClick
      end
      object lbePageTemplateFile: TLabeledEdit
        Left = 24
        Top = 64
        Width = 153
        Height = 21
        EditLabel.Width = 149
        EditLabel.Height = 13
        EditLabel.Caption = #1064#1072#1073#1083#1086#1085' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080' '#1089#1090#1088#1072#1085#1080#1094#1099
        LabelPosition = lpAbove
        LabelSpacing = 5
        TabOrder = 1
        Text = 'a.ini'
      end
      object rbCardPrinter: TRadioButton
        Left = 8
        Top = 96
        Width = 121
        Height = 17
        Caption = #1050#1072#1088#1090#1086#1095#1085#1099#1081' '#1087#1088#1080#1085#1090#1077#1088
        TabOrder = 2
        OnClick = rbCardPrinterClick
      end
    end
    object GroupBox3: TGroupBox
      Left = 224
      Top = 10
      Width = 217
      Height = 129
      Caption = ' '#1063#1058#1054' '#1048' '#1050#1040#1050' '#1055#1045#1063#1040#1058#1040#1058#1068' '
      Color = clBtnFace
      ParentColor = False
      TabOrder = 2
      object rbPrintFromDB: TRadioButton
        Left = 8
        Top = 24
        Width = 105
        Height = 17
        Caption = #1055#1077#1095#1072#1090#1100' '#1080#1079' '#1073#1072#1079#1099
        TabOrder = 0
      end
      object rbPrintPage: TRadioButton
        Left = 8
        Top = 43
        Width = 161
        Height = 17
        Caption = #1055#1077#1095#1072#1090#1100' '#1090#1077#1082#1091#1097#1077#1081' '#1089#1090#1088#1072#1085#1080#1094#1099
        Checked = True
        TabOrder = 1
        TabStop = True
      end
      object cbClearAfterPrinting: TCheckBox
        Left = 11
        Top = 69
        Width = 182
        Height = 17
        Caption = #1054#1095#1080#1097#1072#1090#1100' '#1089#1090#1088#1072#1085#1080#1094#1091' '#1087#1086#1089#1083#1077' '#1087#1077#1095#1072#1090#1080
        TabOrder = 2
      end
      object btSelectPicture: TButton
        Left = 11
        Top = 96
        Width = 182
        Height = 25
        Caption = #1042#1099#1073#1086#1088' '#1075#1086#1090#1086#1074#1086#1081' '#1082#1072#1088#1090#1080#1085#1082#1080
        TabOrder = 3
        OnClick = btSelectPictureClick
      end
    end
    object GroupBox4: TGroupBox
      Left = 448
      Top = 10
      Width = 217
      Height = 129
      Caption = ' '#1057#1050#1054#1051#1068#1050#1054' '#1055#1045#1063#1040#1058#1040#1058#1068' '
      Color = clBtnFace
      ParentColor = False
      TabOrder = 3
      object lbePagesNumber: TLabeledEdit
        Left = 8
        Top = 40
        Width = 160
        Height = 21
        EditLabel.Width = 178
        EditLabel.Height = 13
        EditLabel.Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1089#1090#1088#1072#1085#1080#1094' '#1089' '#1082#1072#1088#1090#1086#1095#1082#1072#1084#1080' '
        EditLabel.Layout = tlCenter
        LabelPosition = lpAbove
        LabelSpacing = 5
        TabOrder = 0
        Text = '1'
      end
      object UpDown1: TUpDown
        Left = 168
        Top = 40
        Width = 16
        Height = 21
        Associate = lbePagesNumber
        Min = 1
        Position = 1
        TabOrder = 1
        Wrap = False
      end
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 150
    Width = 880
    Height = 131
    Align = alTop
    DataSource = DataSource1
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 11
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'NN'
        Title.Alignment = taCenter
        Title.Caption = #1053#1086#1084#1077#1088
        Width = 57
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'LNAME'
        Title.Alignment = taCenter
        Title.Caption = #1060#1072#1084#1080#1083#1080#1103
        Width = 176
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'FNAME'
        Title.Alignment = taCenter
        Title.Caption = #1048#1084#1103
        Width = 118
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MNAME'
        Title.Alignment = taCenter
        Title.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
        Width = 178
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TEMPLATE'
        Title.Alignment = taCenter
        Title.Caption = #1064#1072#1073#1083#1086#1085
        Width = 87
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MARKED_FOR_PRINTING_TEXT'
        Title.Alignment = taCenter
        Title.Caption = #1055#1077#1095#1072#1090#1072#1090#1100
        Width = 67
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'ENABLED_TEXT'
        Title.Alignment = taCenter
        Title.Caption = #1040#1082#1090#1080#1074#1085#1072
        Width = 55
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'STRUCTURE_NAME'
        Title.Alignment = taCenter
        Title.Caption = #1057#1090#1088#1091#1082#1090#1091#1088#1085#1072#1103' '#1077#1076#1080#1085#1080#1094#1072
        Width = 143
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CARD'
        Title.Alignment = taCenter
        Title.Caption = #1053#1086#1084#1077#1088' '#1082#1072#1088#1090#1086#1095#1082#1080
        Width = 134
        Visible = True
      end>
  end
  object Panel1: TPanel
    Left = 8
    Top = 290
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 1'
    TabOrder = 0
    object PaintBox1: TPaintBox
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel2: TPanel
    Left = 360
    Top = 290
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 2'
    TabOrder = 1
    object PaintBox2: TPaintBox
      Tag = 1
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel3: TPanel
    Left = 8
    Top = 501
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 3'
    TabOrder = 2
    object PaintBox3: TPaintBox
      Tag = 2
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel4: TPanel
    Left = 360
    Top = 501
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 4'
    TabOrder = 3
    object PaintBox4: TPaintBox
      Tag = 3
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel5: TPanel
    Left = 8
    Top = 712
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 5'
    TabOrder = 4
    object PaintBox5: TPaintBox
      Tag = 4
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel6: TPanel
    Left = 360
    Top = 712
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 6'
    TabOrder = 5
    object PaintBox6: TPaintBox
      Tag = 5
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel7: TPanel
    Left = 8
    Top = 923
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 7'
    TabOrder = 6
    object PaintBox7: TPaintBox
      Tag = 6
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel8: TPanel
    Left = 360
    Top = 923
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 8'
    TabOrder = 7
    object PaintBox8: TPaintBox
      Tag = 7
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel9: TPanel
    Left = 8
    Top = 1134
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 9'
    TabOrder = 8
    object PaintBox9: TPaintBox
      Tag = 8
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object Panel10: TPanel
    Left = 360
    Top = 1134
    Width = 337
    Height = 201
    Caption = #1050#1072#1088#1090#1086#1095#1082#1072' '#8470' 10'
    TabOrder = 9
    object PaintBox10: TPaintBox
      Tag = 9
      Left = 1
      Top = 1
      Width = 335
      Height = 199
      Align = alClient
      OnClick = PaintBoxClick
      OnPaint = PaintBoxPaint
    end
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 384
    Top = 136
  end
  object IBDataSet1: TIBDataSet
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    ForcedRefresh = True
    RefreshSQL.Strings = (
      'SELECT'
      '      Units.nn,'
      '      Units.card,'
      '      Units.enabled,'
      '      Units.template,'
      '      Units.marked_for_printing,'
      '      Units.photo,'
      '      Units.structure_name,'
      '      Units.fname,'
      '      Units.mname,'
      '      Units.lname,'
      '      Units.home_address,'
      '      Units.phone,'
      '      Units.medical_policy,'
      '      Aux_Yesno1.name AS enabled_text,'
      '      Aux_Yesno2.name AS marked_for_printing_text'
      'FROM'
      '    Units'
      'LEFT JOIN'
      '         Aux_yesno Aux_Yesno1 ON Units.enabled = Aux_yesno1.nn'
      'LEFT JOIN'
      
        '         Aux_yesno Aux_Yesno2 ON Units.marked_for_printing = Aux' +
        '_yesno2.nn'
      'WHERE'
      '     Units.nn = :nn;')
    SelectSQL.Strings = (
      'SELECT'
      '      Units.nn,'
      '      Units.card,'
      '      Units.enabled,'
      '      Units.template,'
      '      Units.marked_for_printing,'
      '      Units.photo,'
      '      Units.structure_name,'
      '      Units.fname,'
      '      Units.mname,'
      '      Units.lname,'
      '      Units.home_address,'
      '      Units.phone,'
      '      Units.medical_policy,'
      '      Aux_Yesno1.name AS enabled_text,'
      '      Aux_Yesno2.name AS marked_for_printing_text'
      'FROM'
      '    Units'
      'LEFT JOIN'
      '         Aux_yesno Aux_Yesno1 ON Units.enabled = Aux_yesno1.nn'
      'LEFT JOIN'
        '         Aux_yesno Aux_Yesno2 ON Units.marked_for_printing = Aux_yesno2.nn'
      'ORDER BY'
        '        Units.structure_name, Units.fname, Units.lname, Units.marked_for_printing DESC;')
    ModifySQL.Strings = (
      'UPDATE'
      '      Units'
      'SET'
      '   Units.marked_for_printing=:marked_for_printing'
      'WHERE'
      '     Units.nn = :nn;')
    ParamCheck = False
    Left = 424
    Top = 136
  end
  object DataSource1: TDataSource
    DataSet = IBDataSet1
    Left = 456
    Top = 136
  end
  object PrintDialog1: TPrintDialog
    Copies = 1
    Options = [poWarning, poHelp, poDisablePrintToFile]
    Left = 424
    Top = 200
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Filter = #1050#1072#1088#1090#1080#1085#1082#1080' '#1074' '#1092#1086#1088#1084#1072#1090#1077' BMP (*.bmp)|*.bmp'
    Title = #1042#1099#1073#1086#1088' '#1075#1086#1090#1086#1074#1086#1081' '#1082#1072#1088#1090#1080#1085#1082#1080' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080
    Left = 368
    Top = 248
  end
end