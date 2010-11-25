object fOrganizationInfo: TfOrganizationInfo
  Left = 252
  Top = 166
  Width = 563
  Height = 224
  Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  Position = poScreenCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  PixelsPerInch = 96
  TextHeight = 13
  object IBTransaction1: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 144
    Top = 8
  end
  object IBSQL1: TIBSQL
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    Left = 184
    Top = 8
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 555
    Height = 40
    AutoSize = True
    ButtonHeight = 36
    ButtonWidth = 60
    Caption = 'ToolBar1'
    Images = fMain.ImageList1
    ShowCaptions = True
    TabOrder = 5
    object tbSave: TToolButton
      Left = 0
      Top = 2
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Enabled = False
      ImageIndex = 4
      OnClick = tbSaveClick
    end
    object tbUndo: TToolButton
      Left = 60
      Top = 2
      Hint = #1054#1090#1084#1077#1085#1080#1090#1100' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Enabled = False
      ImageIndex = 5
      OnClick = tbUndoClick
    end
  end
  object LabeledEdit1: TLabeledEdit
    Left = 155
    Top = 56
    Width = 393
    Height = 21
    EditLabel.Width = 147
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1080' '
    LabelPosition = lpLeft
    LabelSpacing = 5
    TabOrder = 0
    OnChange = Change
  end
  object LabeledEdit2: TLabeledEdit
    Left = 155
    Top = 80
    Width = 393
    Height = 21
    EditLabel.Width = 103
    EditLabel.Height = 13
    EditLabel.Caption = #1060#1048#1054' '#1088#1091#1082#1086#1074#1086#1076#1080#1090#1077#1083#1103' '
    LabelPosition = lpLeft
    LabelSpacing = 5
    TabOrder = 1
    OnChange = Change
  end
  object LabeledEdit3: TLabeledEdit
    Left = 155
    Top = 104
    Width = 393
    Height = 21
    EditLabel.Width = 116
    EditLabel.Height = 13
    EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1080' '
    LabelPosition = lpLeft
    LabelSpacing = 5
    TabOrder = 2
    OnChange = Change
  end
  object LabeledEdit5: TLabeledEdit
    Left = 8
    Top = 160
    Width = 249
    Height = 21
    EditLabel.Width = 62
    EditLabel.Height = 13
    EditLabel.Caption = 'LabeledEdit5'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
    OnChange = Change
  end
  object Button1: TButton
    Left = 264
    Top = 160
    Width = 33
    Height = 21
    Caption = '...'
    TabOrder = 4
    OnClick = Button1Click
  end
end