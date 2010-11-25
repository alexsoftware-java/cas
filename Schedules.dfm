object fSchedules: TfSchedules
  Left = 166
  Top = 46
  Width = 848
  Height = 776
  Caption = #1043#1088#1072#1092#1080#1082#1080
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
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 840
    Height = 40
    AutoSize = True
    ButtonHeight = 36
    ButtonWidth = 67
    Caption = 'ToolBar1'
    Images = fMain.ImageList1
    ShowCaptions = True
    TabOrder = 0
    object tbAdd: TToolButton
      Left = 0
      Top = 2
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      ImageIndex = 0
      OnClick = tbAddClick
    end
    object tbAddFolder: TToolButton
      Left = 67
      Top = 2
      Caption = #1044#1086#1073'. '#1087#1072#1087#1082#1091
      ImageIndex = 0
      OnClick = tbAddFolderClick
    end
    object tbAddCopy: TToolButton
      Left = 134
      Top = 2
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077#1084
      Caption = #1044#1086#1073'. '#1082#1086#1087#1080#1088'.'
      ImageIndex = 1
      OnClick = tbAddCopyClick
    end
    object tbChange: TToolButton
      Left = 201
      Top = 2
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      ImageIndex = 2
      OnClick = tbChangeClick
    end
    object tbDelete: TToolButton
      Left = 268
      Top = 2
      Caption = #1059#1076#1072#1083#1080#1090#1100
      ImageIndex = 3
      OnClick = tbDeleteClick
    end
    object ToolButton1: TToolButton
      Left = 335
      Top = 2
      Width = 8
      ImageIndex = 3
      Style = tbsSeparator
    end
    object tbSave: TToolButton
      Left = 343
      Top = 2
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Enabled = False
      ImageIndex = 4
      OnClick = tbSaveClick
    end
    object tbUndo: TToolButton
      Left = 410
      Top = 2
      Hint = #1054#1090#1084#1077#1085#1080#1090#1100' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Enabled = False
      ImageIndex = 5
      OnClick = tbUndoClick
    end
  end
  object TreeView1: TTreeView
    Left = 0
    Top = 40
    Width = 209
    Height = 702
    Align = alLeft
    DragMode = dmAutomatic
    HideSelection = False
    Images = ImageList1
    Indent = 19
    MultiSelect = True
    MultiSelectStyle = [msControlSelect, msShiftSelect]
    StateImages = fMain.ImageList
    TabOrder = 1
    OnChange = TreeView1Change
    OnChanging = TreeView1Changing
    OnDblClick = tbChangeClick
    OnDragDrop = TreeView1DragDrop
    OnDragOver = TreeView1DragOver
    OnEditing = TreeView1Editing
    OnExpanding = TreeView1Expanding
  end
  object GroupBox1: TGroupBox
    Left = 209
    Top = 40
    Width = 631
    Height = 702
    Align = alClient
    TabOrder = 2
    object Label1: TLabel
      Left = 275
      Top = 576
      Width = 80
      Height = 13
      Caption = #1056#1072#1073#1086#1095#1077#1077'  '#1074#1088#1077#1084#1103
    end
    object Label2: TLabel
      Left = 448
      Top = 576
      Width = 54
      Height = 13
      Caption = #1055#1077#1088#1077#1088#1099#1074#1099
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 72
      Width = 617
      Height = 497
      TabOrder = 0
      object StringGrid1: TStringGrid
        Left = 8
        Top = 50
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 0
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid2: TStringGrid
        Left = 160
        Top = 50
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 1
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid3: TStringGrid
        Left = 312
        Top = 50
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 2
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid4: TStringGrid
        Left = 464
        Top = 50
        Width = 145
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 3
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid5: TStringGrid
        Left = 8
        Top = 194
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 4
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid6: TStringGrid
        Left = 160
        Top = 194
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 5
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid7: TStringGrid
        Left = 312
        Top = 194
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 6
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid8: TStringGrid
        Left = 464
        Top = 194
        Width = 145
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 7
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid9: TStringGrid
        Left = 8
        Top = 339
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 8
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid10: TStringGrid
        Left = 160
        Top = 339
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 9
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid11: TStringGrid
        Left = 312
        Top = 339
        Width = 153
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 10
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object StringGrid12: TStringGrid
        Left = 464
        Top = 339
        Width = 145
        Height = 145
        BorderStyle = bsNone
        ColCount = 7
        DefaultColWidth = 20
        DefaultRowHeight = 16
        FixedCols = 0
        RowCount = 8
        FixedRows = 0
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -8
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Options = []
        ParentFont = False
        TabOrder = 11
        OnDrawCell = sgMonthCalendarDrawCell
        OnEnter = sgMonthCalendarEnter
        OnExit = sgMonthCalendarExit
        OnSelectCell = sgMonthCalendarSelectCell
      end
      object btYearBack: TButton
        Left = 16
        Top = 16
        Width = 97
        Height = 25
        Caption = #1053#1072' '#1075#1086#1076' '#1085#1072#1079#1072#1076
        TabOrder = 12
        OnClick = btNavigateCalendarClick
      end
      object btMonthBack: TButton
        Left = 120
        Top = 16
        Width = 97
        Height = 25
        Caption = #1053#1072' '#1084#1077#1089#1103#1094' '#1085#1072#1079#1072#1076
        TabOrder = 13
        OnClick = btNavigateCalendarClick
      end
      object btMonthForward: TButton
        Left = 408
        Top = 16
        Width = 97
        Height = 25
        Caption = #1053#1072' '#1084#1077#1089#1103#1094' '#1074#1087#1077#1088#1105#1076
        TabOrder = 14
        OnClick = btNavigateCalendarClick
      end
      object btYearForward: TButton
        Left = 512
        Top = 16
        Width = 97
        Height = 25
        Caption = #1053#1072' '#1075#1086#1076' '#1074#1087#1077#1088#1105#1076
        TabOrder = 15
        OnClick = btNavigateCalendarClick
      end
    end
    object gbDayType: TGroupBox
      Left = 16
      Top = 584
      Width = 129
      Height = 105
      Caption = ' '#1058#1080#1087' '#1076#1085#1103' '
      TabOrder = 1
      object Shape1: TShape
        Left = 8
        Top = 26
        Width = 25
        Height = 17
        Shape = stSquare
      end
      object Shape2: TShape
        Left = 8
        Top = 50
        Width = 25
        Height = 17
        Brush.Color = 8421631
        Shape = stSquare
      end
      object Shape3: TShape
        Left = 8
        Top = 74
        Width = 25
        Height = 17
        Brush.Color = clSkyBlue
        Shape = stSquare
      end
      object rbDayType1: TRadioButton
        Left = 40
        Top = 26
        Width = 80
        Height = 17
        Caption = #1088#1072#1073#1086#1095#1080#1081
        TabOrder = 0
        OnClick = rbDayTypeClick
      end
      object rbDayType2: TRadioButton
        Left = 40
        Top = 50
        Width = 80
        Height = 17
        Caption = #1074#1099#1093#1086#1076#1085#1086#1081
        TabOrder = 1
        OnClick = rbDayTypeClick
      end
      object rbDayType3: TRadioButton
        Left = 40
        Top = 74
        Width = 80
        Height = 17
        Caption = #1087#1088#1072#1079#1076#1085#1080#1082
        TabOrder = 2
        OnClick = rbDayTypeClick
      end
    end
    object vleWorkTime: TValueListEditor
      Left = 256
      Top = 592
      Width = 121
      Height = 97
      KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
      TabOrder = 2
      TitleCaptions.Strings = (
        #1089'  ('#1095#1095':'#1084#1084')'
        #1087#1086'  ('#1095#1095':'#1084#1084')')
      OnExit = ValueListEditorExit
      OnGetEditMask = ValueListEditorGetEditMask
      OnValidate = ValueListEditorValidate
      ColWidths = (
        56
        59)
    end
    object vleBreaks: TValueListEditor
      Left = 415
      Top = 592
      Width = 121
      Height = 97
      KeyOptions = [keyEdit, keyAdd, keyDelete, keyUnique]
      TabOrder = 3
      TitleCaptions.Strings = (
        #1089'  ('#1095#1095':'#1084#1084')'
        #1087#1086'  ('#1095#1095':'#1084#1084')')
      OnExit = ValueListEditorExit
      OnGetEditMask = ValueListEditorGetEditMask
      OnValidate = ValueListEditorValidate
      ColWidths = (
        56
        59)
    end
    object Button2: TButton
      Left = 40
      Top = 43
      Width = 217
      Height = 25
      Caption = #1057#1082#1086#1087#1080#1088#1086#1074#1072#1090#1100' '#1088#1072#1073#1086#1095#1077#1077' '#1074#1088#1077#1084#1103' '#1080' '#1087#1077#1088#1077#1088#1099#1074#1099
      TabOrder = 4
      OnClick = Button2Click
    end
    object Button1: TButton
      Left = 40
      Top = 16
      Width = 217
      Height = 25
      Caption = #1057#1076#1077#1083#1072#1090#1100' '#1074#1089#1077' '#1057#1041' '#1080' '#1042#1057' '#1074#1099#1093#1086#1076#1085#1099#1084#1080
      TabOrder = 5
      OnClick = Button1Click
    end
    object RadioGroup1: TRadioGroup
      Left = 294
      Top = 12
      Width = 185
      Height = 53
      ItemIndex = 0
      Items.Strings = (
        #1076#1083#1103' '#1090#1077#1082#1091#1097#1077#1075#1086' '#1084#1077#1089#1103#1094#1072
        #1076#1083#1103' '#1074#1089#1077#1093' '#1074#1080#1076#1080#1084#1099#1093' '#1084#1077#1089#1103#1094#1077#1074)
      TabOrder = 6
    end
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 496
    Top = 8
  end
  object IBSQL1: TIBSQL
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    Left = 536
    Top = 8
  end
  object ImageList1: TImageList
    Left = 584
    Top = 8
    Bitmap = {
      494C010103000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000BFBF
      BF007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000003F
      3F00007F7F00007F7F00007F7F00007F7F00007F7F00007F7F00007F7F007F7F
      7F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000007F
      7F003F3F3F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F00007F7F007F7F
      7F00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000808080008080
      8000808080008080800080808000808080008080800080808000808080008080
      800080808000808080008080800000000000BFBFBF007F7F7F007F7F7F00007F
      7F007F7F7F00BFBFFF0000000000000000000000000000000000007F7F003F3F
      3F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000808080008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000808080008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF00C0C0C00000FFFF0080808000000000007F7F7F000000000000000000007F
      7F007F7F7F00000000007F7FFF00000000000000000000000000007F7F000000
      000000000000000000000000000000000000000000000000000080808000C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF008080800080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008080800000FFFF00C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF00C0C0C00080808000000000007F7F7F007F7F7F0000000000007F
      7F007F7F7F0000000000000000003F3F3F007F7F7F0000000000007F7F007F7F
      7F00000000000000000000000000000000000000000080808000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF00C0C0C0008080800080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF00C0C0C00000FFFF0080808000000000007F7F7F007F7F7F0000000000007F
      7F007F7F7F0000000000000000007F7F7F000000000000000000007F7F000000
      7F000000FF007F7FFF0000000000000000000000000080808000FFFFFF00C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C000808080008080800080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008080800000FFFF00C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF00C0C0C00080808000000000007F7F7F007F7F7F0000000000007F
      7F007F7F7F000000000000000000BFBFBF000000000000000000007F7F000000
      7F00BFBFFF00BFBFFF00000000000000000080808000C0C0C000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF0080808000C0C0C00080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF00C0C0C00000FFFF0080808000000000007F7F7F007F7F7F0000000000007F
      7F00007F7F00007F7F00007F7F00007F7F00007F7F00007F7F0000BFBF000000
      7F003F3FFF0000000000000000000000000080808000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C0C0C0008080
      8000C0C0C000C0C0C00080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008080800000FFFF00C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF00C0C0C00080808000000000007F7F7F007F7F7F0000000000BFBF
      BF0000007F003F3F7F007F7F7F007F7F7F003F3F3F007F7F7F007F7F7F003F3F
      FF000000FF007F7FFF0000000000000000008080800080808000808080008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000C0C0C00000FFFF0080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF00C0C0C00000FFFF0080808000000000007F7F7F007F7F7F00000000003F3F
      FF000000FF007F7FFF0000000000000000007F7F7F0000000000BFBFFF00BFBF
      FF000000FF007F7FFF0000000000000000000000000080808000C0C0C000C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF00C0C0C00080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0080808000000000007F7F7F007F7F7F0000000000BFBF
      FF000000FF007F7FFF00000000007F7F7F003F3F3F00BFBFBF00BFBFFF000000
      FF000000FF00BFBFFF0000000000000000000000000080808000C0C0C00000FF
      FF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0C000C0C0
      C000C0C0C000C0C0C00000000000000000007F7F7F007F7F7F00000000000000
      00000000000000000000000000007F7F7F007F7F7F00BFBFBF00000000000000
      0000000000000000000000000000000000000000000080808000C0C0C000C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C000C0C0C00080808000808080008080
      8000808080008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000008080800080808000C0C0
      C00000FFFF00C0C0C00000FFFF00C0C0C0008080800000000000000000000000
      0000000000000000000000000000000000007F7F7F007F7F7F007F7FBF007F7F
      BF007F7FBF007F7FBF007F7FBF00BFBFDF007F7F7F007F7FBF007F7FBF007F7F
      BF007F7FBF007F7FBF00BFBFDF0000000000000000000000000080808000C0C0
      C000C0C0C000FFFFFF00C0C0C000FFFFFF008080800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080008080
      8000808080008080800080808000808080000000000000000000000000000000
      0000000000000000000000000000000000007F7F7F003F3F3F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F003F3F3F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F00000000000000000000000000000000008080
      8000808080008080800080808000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000BFBFBF007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FFFFE01FFFFF0000FFFFE00FFFFF0000
      FFFFE00FFFFF0000800103C0C0030000800105C0C00100008001264E80010000
      800126C280010000800126C20001000080012006000100008001200200010000
      8001234280010000800122028001000080033E3E80030000807F0000C07F0000
      C0FF0000E0FF0000FFFF0000FFFF000000000000000000000000000000000000
      000000000000}
  end
end