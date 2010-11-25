object fUnitProperties: TfUnitProperties
  Left = 297
  Top = 17
  Width = 873
  Height = 731
  Caption = #1057#1087#1080#1089#1086#1095#1085#1099#1081' '#1089#1086#1089#1090#1072#1074' '#1086#1088#1075#1072#1085#1080#1079#1072#1094#1080#1080'  --  '#1055#1088#1086#1089#1084#1086#1090#1088
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Arial'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = True
  Position = poDesktopCenter
  Visible = True
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnMouseWheel = FormMouseWheel
  PixelsPerInch = 96
  TextHeight = 14
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 857
    Height = 41
    AutoSize = True
    ButtonHeight = 37
    ButtonWidth = 72
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
    object tbAddCopy: TToolButton
      Left = 72
      Top = 2
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1086#1087#1080#1088#1086#1074#1072#1085#1080#1077#1084
      Caption = #1044#1086#1073'. '#1082#1086#1087#1080#1088'.'
      ImageIndex = 1
      OnClick = tbAddCopyClick
    end
    object tbChange: TToolButton
      Left = 144
      Top = 2
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      ImageIndex = 2
      OnClick = tbChangeClick
    end
    object tbDelete: TToolButton
      Left = 216
      Top = 2
      Caption = #1059#1076#1072#1083#1080#1090#1100
      ImageIndex = 3
      OnClick = tbDeleteClick
    end
    object ToolButton1: TToolButton
      Left = 288
      Top = 2
      Width = 8
      ImageIndex = 3
      Style = tbsSeparator
    end
    object tbSave: TToolButton
      Left = 296
      Top = 2
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Enabled = False
      ImageIndex = 4
      OnClick = tbSaveOrUndoClick
    end
    object tbUndo: TToolButton
      Left = 368
      Top = 2
      Hint = #1054#1090#1084#1077#1085#1080#1090#1100' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
      Enabled = False
      ImageIndex = 5
      OnClick = tbSaveOrUndoClick
    end
    object ToolButton2: TToolButton
      Left = 440
      Top = 2
      Width = 8
      Caption = 'ToolButton2'
      ImageIndex = 8
      Style = tbsSeparator
    end
    object tbPrior: TToolButton
      Left = 448
      Top = 2
      Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1080#1081
      ImageIndex = 6
      OnClick = tbPriorClick
    end
    object tbNext: TToolButton
      Left = 520
      Top = 2
      Caption = #1057#1083#1077#1076#1091#1102#1097#1080#1081
      ImageIndex = 7
      OnClick = tbNextClick
    end
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 41
    Width = 857
    Height = 654
    ActivePage = pc1_tsCard
    Align = alClient
    HotTrack = True
    MultiLine = True
    TabIndex = 1
    TabOrder = 1
    TabPosition = tpLeft
    object pc1_tsGrid: TTabSheet
      Caption = #1058#1072#1073#1083#1080#1094#1072
      object DBGrid1: TDBGrid
        Left = 0
        Top = 0
        Width = 830
        Height = 646
        Align = alClient
        DataSource = DataSource1
        Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgRowSelect, dgAlwaysShowSelection, dgConfirmDelete, dgCancelOnExit]
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Arial'
        TitleFont.Style = []
        OnDblClick = DBGrid1DblClick
        OnTitleClick = DBGrid1TitleClick
        Columns = <
          item
            Expanded = False
            FieldName = 'NN'
            Title.Alignment = taCenter
            Title.Caption = #1053#1086#1084#1077#1088' '#1074' '#1041#1044
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
            FieldName = 'CARD'
            Title.Alignment = taCenter
            Title.Caption = #1053#1086#1084#1077#1088' '#1082#1072#1088#1090#1086#1095#1082#1080
            Width = 134
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
            FieldName = 'ENABLED_TEXT'
            Title.Alignment = taCenter
            Title.Caption = #1040#1082#1090#1080#1074#1085#1072
            Width = 55
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
          end>
      end
    end
    object pc1_tsCard: TTabSheet
      Caption = #1050#1072#1088#1090#1086#1095#1082#1072
      ImageIndex = 1
      object NamePanel: TPanel
        Left = 0
        Top = 0
        Width = 830
        Height = 61
        Align = alTop
        TabOrder = 0
        object LabeledEdit1: TLabeledEdit
          Left = 3
          Top = 20
          Width = 277
          Height = 27
          EditLabel.Width = 46
          EditLabel.Height = 14
          EditLabel.Caption = #1060#1072#1084#1080#1083#1080#1103
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -17
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 0
        end
        object LabeledEdit2: TLabeledEdit
          Left = 279
          Top = 20
          Width = 277
          Height = 27
          EditLabel.Width = 23
          EditLabel.Height = 14
          EditLabel.Caption = #1048#1084#1103
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -17
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 1
        end
        object LabeledEdit3: TLabeledEdit
          Left = 555
          Top = 20
          Width = 276
          Height = 27
          EditLabel.Width = 51
          EditLabel.Height = 14
          EditLabel.Caption = #1054#1090#1095#1077#1089#1090#1074#1086
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -17
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 2
        end
      end
      object okCancelPanel: TPanel
        Left = 0
        Top = 602
        Width = 830
        Height = 44
        Align = alBottom
        TabOrder = 1
        Visible = False
        object btOK: TButton
          Left = 326
          Top = 9
          Width = 81
          Height = 27
          Caption = 'OK'
          ModalResult = 1
          TabOrder = 0
          OnClick = btOKClick
        end
        object btCancel: TButton
          Left = 430
          Top = 9
          Width = 80
          Height = 27
          Cancel = True
          Caption = #1054#1090#1084#1077#1085#1072
          ModalResult = 2
          TabOrder = 1
          OnClick = btCancelClick
        end
      end
      object PageControl2: TPageControl
        Left = 0
        Top = 61
        Width = 830
        Height = 541
        ActivePage = PageControl2_ts1
        Align = alClient
        TabIndex = 0
        TabOrder = 2
        object PageControl2_ts1: TTabSheet
          Caption = #1051#1080#1095#1085#1099#1077' '#1076#1072#1085#1085#1099#1077
          object Label2: TLabel
            Left = 4
            Top = 336
            Width = 86
            Height = 22
            AutoSize = False
            Caption = #1044#1077#1085#1100' '#1088#1086#1078#1076#1077#1085#1080#1103
            Layout = tlCenter
          end
          object Label1: TLabel
            Left = 244
            Top = 10
            Width = 111
            Height = 14
            Caption = #1057#1090#1088#1091#1082#1090#1091#1088#1085#1072#1103' '#1077#1076#1080#1085#1080#1094#1072
          end
          object GroupBox2: TGroupBox
            Left = 526
            Top = 9
            Width = 294
            Height = 242
            Caption = ' '#1055#1072#1089#1087#1086#1088#1090' '
            TabOrder = 0
            object LabeledEdit21: TLabeledEdit
              Left = 9
              Top = 34
              Width = 276
              Height = 22
              EditLabel.Width = 75
              EditLabel.Height = 14
              EditLabel.Caption = #1057#1077#1088#1080#1103' '#1080' '#1085#1086#1084#1077#1088
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit22: TLabeledEdit
              Left = 9
              Top = 78
              Width = 276
              Height = 22
              EditLabel.Width = 57
              EditLabel.Height = 14
              EditLabel.Caption = #1050#1077#1084' '#1074#1099#1076#1072#1085
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit23: TLabeledEdit
              Left = 9
              Top = 121
              Width = 276
              Height = 22
              EditLabel.Width = 65
              EditLabel.Height = 14
              EditLabel.Caption = #1050#1086#1075#1076#1072' '#1074#1099#1076#1072#1085
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
            end
            object LabeledEdit24: TLabeledEdit
              Left = 9
              Top = 164
              Width = 276
              Height = 22
              EditLabel.Width = 44
              EditLabel.Height = 14
              EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
              Visible = False
            end
            object LabeledEdit25: TLabeledEdit
              Left = 9
              Top = 207
              Width = 276
              Height = 22
              EditLabel.Width = 153
              EditLabel.Height = 14
              EditLabel.Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
          end
          object GroupBox3: TGroupBox
            Left = 526
            Top = 258
            Width = 294
            Height = 243
            Caption = ' '#1040#1074#1090#1086#1084#1086#1073#1080#1083#1100' '
            TabOrder = 1
            object LabeledEdit31: TLabeledEdit
              Left = 9
              Top = 34
              Width = 276
              Height = 22
              EditLabel.Width = 31
              EditLabel.Height = 14
              EditLabel.Caption = #1052#1072#1088#1082#1072
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit32: TLabeledEdit
              Left = 9
              Top = 78
              Width = 276
              Height = 22
              EditLabel.Width = 76
              EditLabel.Height = 14
              EditLabel.Caption = #1053#1086#1084#1077#1088#1085#1086#1081' '#1079#1085#1072#1082
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit33: TLabeledEdit
              Left = 9
              Top = 121
              Width = 276
              Height = 22
              EditLabel.Width = 124
              EditLabel.Height = 14
              EditLabel.Caption = #1047#1072#1085#1080#1084#1072#1077#1084#1072#1103' '#1076#1086#1083#1078#1085#1086#1089#1090#1100
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
              Visible = False
            end
            object LabeledEdit34: TLabeledEdit
              Left = 9
              Top = 164
              Width = 276
              Height = 22
              EditLabel.Width = 44
              EditLabel.Height = 14
              EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
              Visible = False
            end
            object LabeledEdit35: TLabeledEdit
              Left = 9
              Top = 207
              Width = 276
              Height = 22
              EditLabel.Width = 153
              EditLabel.Height = 14
              EditLabel.Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1072#1103' '#1080#1085#1092#1086#1088#1084#1072#1094#1080#1103
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
          end
          object DateTimePicker2: TDateTimePicker
            Left = 102
            Top = 335
            Width = 139
            Height = 21
            CalAlignment = dtaLeft
            Date = 40179
            Time = 40179
            DateFormat = dfLong
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 2
          end
          object LabeledEdit11: TLabeledEdit
            Left = 3
            Top = 379
            Width = 277
            Height = 22
            EditLabel.Width = 87
            EditLabel.Height = 14
            EditLabel.Caption = #1044#1086#1084#1072#1096#1085#1080#1081' '#1072#1076#1088#1077#1089
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 3
          end
          object LabeledEdit12: TLabeledEdit
            Left = 3
            Top = 422
            Width = 277
            Height = 22
            EditLabel.Width = 44
            EditLabel.Height = 14
            EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 4
          end
          object LabeledEdit13: TLabeledEdit
            Left = 3
            Top = 465
            Width = 277
            Height = 22
            EditLabel.Width = 175
            EditLabel.Height = 14
            EditLabel.Caption = #1055#1086#1083#1080#1089' '#1084#1077#1076#1080#1094#1080#1085#1089#1082#1086#1075#1086' '#1089#1090#1088#1072#1093#1086#1074#1072#1085#1080#1103
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 5
          end
          object btPersonalRecord: TButton
            Left = 280
            Top = 69
            Width = 199
            Height = 27
            Caption = #1051#1080#1095#1085#1072#1103' '#1082#1072#1088#1090#1086#1095#1082#1072
            ModalResult = 1
            TabOrder = 6
            Visible = False
          end
          object btEventsList: TButton
            Left = 280
            Top = 103
            Width = 199
            Height = 27
            Caption = #1048#1089#1090#1086#1088#1080#1103' '#1089#1086#1073#1099#1090#1080#1081
            ModalResult = 1
            TabOrder = 7
            OnClick = btEventsListClick
          end
          object btSetResidenceToday: TButton
            Left = 280
            Top = 172
            Width = 199
            Height = 27
            Caption = #1055#1086#1089#1090#1072#1074#1080#1090#1100' '#1087#1086#1089#1077#1097#1077#1085#1080#1077' '#1079#1072' '#1089#1077#1075#1086#1076#1085#1103
            ModalResult = 1
            TabOrder = 8
            OnClick = btSetResidenceTodayClick
          end
          object Button7: TButton
            Left = 280
            Top = 207
            Width = 199
            Height = 27
            Caption = #1059#1089#1087#1077#1074#1072#1077#1084#1086#1089#1090#1100
            Enabled = False
            ModalResult = 1
            TabOrder = 9
            Visible = False
          end
          object btResidenceMonth: TButton
            Left = 280
            Top = 138
            Width = 199
            Height = 27
            Caption = #1055#1086#1089#1077#1097#1072#1077#1084#1086#1089#1090#1100' '#1074' '#1090#1077#1082#1091#1097#1077#1084' '#1084#1077#1089#1103#1094#1077
            ModalResult = 1
            TabOrder = 10
            Visible = False
          end
          object ComboBox1: TComboBox
            Left = 244
            Top = 26
            Width = 272
            Height = 22
            AutoComplete = False
            Style = csDropDownList
            ItemHeight = 14
            TabOrder = 11
          end
          object gbPhoto: TGroupBox
            Left = 0
            Top = 8
            Width = 241
            Height = 320
            Caption = ' '#1060#1086#1090#1086#1075#1088#1072#1092#1080#1103' '
            TabOrder = 12
            object Image1: TImage
              Left = 2
              Top = 16
              Width = 237
              Height = 302
              Align = alClient
              Center = True
              Proportional = True
            end
            object btLoadPhoto: TButton
              Left = 9
              Top = 297
              Width = 60
              Height = 18
              Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
              TabOrder = 0
              OnClick = btLoadPhotoClick
            end
            object btDeletePhoto: TButton
              Left = 177
              Top = 297
              Width = 60
              Height = 18
              Caption = #1059#1076#1072#1083#1080#1090#1100
              TabOrder = 1
              OnClick = btDeletePhotoClick
            end
            object btSavePhoto: TButton
              Left = 105
              Top = 297
              Width = 60
              Height = 18
              Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
              TabOrder = 2
              OnClick = btSavePhotoClick
            end
          end
          object GroupBox4: TGroupBox
            Left = 296
            Top = 396
            Width = 217
            Height = 105
            Caption = ' '#1054#1090#1087#1088#1072#1074#1082#1072' SMS '#1087#1088#1080' '#1074#1093#1086#1076#1077' '#1080' '#1074#1099#1093#1086#1076#1077' '
            TabOrder = 13
            object chbSMSEnabled: TCheckBox
              Left = 16
              Top = 24
              Width = 73
              Height = 17
              Caption = #1042#1082#1083#1102#1095#1080#1090#1100
              TabOrder = 0
            end
            object LabeledEdit7: TLabeledEdit
              Left = 16
              Top = 64
              Width = 137
              Height = 22
              EditLabel.Width = 119
              EditLabel.Height = 14
              EditLabel.Caption = #1058#1077#1083#1077#1092#1086#1085' '#1076#1083#1103' '#1086#1090#1087#1088#1072#1074#1082#1080' '
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
              Text = '+7'
            end
          end
          object Button2: TButton
            Left = 280
            Top = 239
            Width = 199
            Height = 27
            Caption = #1052#1077#1076#1080#1094#1080#1085#1089#1082#1080#1077' '#1076#1072#1085#1085#1099#1077
            Enabled = False
            ModalResult = 1
            TabOrder = 14
            Visible = False
          end
        end
        object PageControl2_ts2: TTabSheet
          Caption = #1056#1072#1073#1086#1090#1072' '#1089' '#1089#1080#1089#1090#1077#1084#1086#1081
          Enabled = False
          ImageIndex = 1
          object Label3: TLabel
            Left = 333
            Top = 88
            Width = 67
            Height = 14
            Caption = #1058#1080#1087' '#1082#1072#1088#1090#1086#1095#1082#1080
          end
          object GroupBox1: TGroupBox
            Left = 4
            Top = 9
            Width = 284
            Height = 328
            Caption = ' '#1055#1088#1072#1074#1072' '#1087#1088#1080' '#1088#1072#1073#1086#1090#1077' '#1089' '#1089#1080#1089#1090#1077#1084#1086#1081' '
            PopupMenu = RightsScheme_PopupMenu
            TabOrder = 0
            object CheckListBox1: TCheckListBox
              Left = 2
              Top = 16
              Width = 280
              Height = 261
              Align = alTop
              ItemHeight = 14
              Items.Strings = (
                #1040#1056#1052' <'#1050#1055#1055'>'
                #1057#1087#1080#1089#1086#1082' '#1075#1088#1091#1087#1087':  '#1055#1088#1086#1089#1084#1086#1090#1088
                #1057#1087#1080#1089#1086#1082' '#1075#1088#1091#1087#1087':  '#1048#1079#1084#1077#1085#1077#1085#1080#1077
                #1057#1087#1080#1089#1086#1082' '#1075#1088#1091#1087#1087':  '#1044#1086#1073#1072#1074#1083#1077#1085#1080#1077
                #1057#1087#1080#1089#1086#1082' '#1075#1088#1091#1087#1087':  '#1059#1076#1072#1083#1077#1085#1080#1077
                #1057#1087#1080#1089#1086#1095#1085#1099#1081' '#1089#1086#1089#1090#1072#1074' '#1075#1088#1091#1087#1087':  '#1055#1088#1086#1089#1084#1086#1090#1088
                #1057#1087#1080#1089#1086#1095#1085#1099#1081' '#1089#1086#1089#1090#1072#1074' '#1075#1088#1091#1087#1087':  '#1048#1079#1084#1077#1085#1077#1085#1080#1077
                #1057#1087#1080#1089#1086#1095#1085#1099#1081' '#1089#1086#1089#1090#1072#1074' '#1075#1088#1091#1087#1087':  '#1044#1086#1073#1072#1074#1083#1077#1085#1080#1077
                #1057#1087#1080#1089#1086#1095#1085#1099#1081' '#1089#1086#1089#1090#1072#1074' '#1075#1088#1091#1087#1087':  '#1059#1076#1072#1083#1077#1085#1080#1077
                #1054#1090#1095#1105#1090#1099' '#1087#1086' '#1087#1086#1089#1077#1097#1072#1077#1084#1086#1089#1090#1080':  '#1055#1088#1086#1089#1084#1086#1090#1088
                #1054#1090#1095#1105#1090#1099' '#1087#1086' '#1087#1086#1089#1077#1097#1072#1077#1084#1086#1089#1090#1080':  '#1055#1077#1095#1072#1090#1100
                #1054#1090#1095#1105#1090#1099' '#1087#1086' '#1087#1086#1089#1077#1097#1072#1077#1084#1086#1089#1090#1080':  '#1048#1079#1084#1077#1085#1077#1085#1080#1077
                #1054#1090#1095#1105#1090' '#1086' '#1085#1072#1093#1086#1076#1103#1097#1080#1093#1089#1103' '#1085#1072' '#1090#1077#1088#1088#1080#1090#1086#1088#1080#1080
                #1054#1087#1077#1088#1072#1094#1080#1080' '#1089' '#1041#1044': '#1069#1082#1089#1087#1086#1088#1090' '#1074' MS Excel'
                #1054#1087#1077#1088#1072#1094#1080#1080' '#1089' '#1041#1044': '#1048#1084#1087#1086#1088#1090' '#1080#1079' MS Excel'
                #1055#1077#1095#1072#1090#1100' '#1082#1072#1088#1090#1086#1095#1077#1082
                #1042#1099#1082#1083#1102#1095#1077#1085#1080#1077' '#1082#1086#1084#1087#1100#1102#1090#1077#1088#1072
                #1040#1056#1052' <'#1057#1090#1086#1083#1086#1074#1072#1103'>')
              PopupMenu = RightsScheme_PopupMenu
              TabOrder = 0
            end
            object LabeledEdit5: TLabeledEdit
              Left = 2
              Top = 297
              Width = 279
              Height = 22
              EditLabel.Width = 207
              EditLabel.Height = 14
              EditLabel.Caption = #1055#1072#1088#1086#1083#1100' -- '#1076#1083#1103' '#1072#1074#1090#1086#1088#1080#1079#1072#1094#1080#1080' '#1073#1077#1079' '#1082#1072#1088#1090#1086#1095#1082#1080
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
          end
          object LabeledEdit4: TLabeledEdit
            Left = 331
            Top = 34
            Width = 242
            Height = 22
            EditLabel.Width = 48
            EditLabel.Height = 14
            EditLabel.Caption = #1050#1072#1088#1090#1086#1095#1082#1072
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
          object chbEnabled: TCheckBox
            Left = 331
            Top = 136
            Width = 130
            Height = 18
            Caption = #1044#1077#1081#1089#1090#1074#1080#1090#1077#1083#1100#1085#1072'   '#1044#1086
            Checked = True
            State = cbChecked
            TabOrder = 2
          end
          object DateTimePicker1: TDateTimePicker
            Left = 467
            Top = 134
            Width = 139
            Height = 21
            CalAlignment = dtaLeft
            Date = 38596
            Time = 38596
            DateFormat = dfLong
            DateMode = dmComboBox
            Kind = dtkDate
            ParseInput = False
            TabOrder = 3
          end
          object btGetCardNumber: TButton
            Left = 577
            Top = 34
            Width = 29
            Height = 23
            Caption = '...'
            TabOrder = 4
            OnClick = btGetCardNumberClick
          end
          object chbRenamePhoto: TCheckBox
            Left = 331
            Top = 60
            Width = 196
            Height = 19
            Caption = #1055#1077#1088#1077#1080#1084#1077#1085#1086#1074#1099#1074#1072#1090#1100' '#1092#1086#1090#1086#1075#1088#1072#1092#1080#1102
            Checked = True
            State = cbChecked
            TabOrder = 5
          end
          object chbMarkedForPrinting: TCheckBox
            Left = 331
            Top = 258
            Width = 144
            Height = 18
            Caption = #1055#1086#1084#1077#1095#1077#1085#1072' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080
            TabOrder = 6
          end
          object LabeledEdit6: TLabeledEdit
            Left = 331
            Top = 223
            Width = 242
            Height = 22
            EditLabel.Width = 100
            EditLabel.Height = 14
            EditLabel.Caption = #1064#1072#1073#1083#1086#1085' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 7
          end
          object btGetTemplateFilePath: TButton
            Left = 577
            Top = 223
            Width = 29
            Height = 23
            Caption = '...'
            TabOrder = 8
            OnClick = btGetTemplateFilePathClick
          end
          object ComboBox2: TComboBox
            Left = 331
            Top = 104
            Width = 275
            Height = 22
            Style = csDropDownList
            ItemHeight = 14
            TabOrder = 9
            Items.Strings = (
              #1054#1073#1099#1095#1085#1072#1103
              #1043#1086#1089#1090#1077#1074#1072#1103' '#1085#1077#1074#1099#1076#1072#1085#1085#1072#1103
              #1043#1086#1089#1090#1077#1074#1072#1103' '#1074#1099#1076#1072#1085#1085#1072#1103)
          end
          object GroupBox5: TGroupBox
            Left = 4
            Top = 344
            Width = 285
            Height = 105
            Caption = ' '#1047#1072#1082#1072#1079' '#1087#1088#1086#1087#1091#1089#1082#1086#1074' '#1095#1077#1088#1077#1079' Web-'#1080#1085#1090#1077#1088#1092#1077#1081#1089' '
            TabOrder = 10
            object LabeledEdit8: TLabeledEdit
              Left = 8
              Top = 35
              Width = 273
              Height = 22
              EditLabel.Width = 131
              EditLabel.Height = 14
              EditLabel.Caption = #1048#1084#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103' (login)'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit9: TLabeledEdit
              Left = 8
              Top = 75
              Width = 273
              Height = 22
              EditLabel.Width = 37
              EditLabel.Height = 14
              EditLabel.Caption = #1055#1072#1088#1086#1083#1100
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
          end
        end
        object PageControl2_ts3: TTabSheet
          Caption = #1055#1077#1095#1072#1090#1100' '#1082#1072#1088#1090#1086#1095#1082#1080
          ImageIndex = 2
          object Panel3: TPanel
            Left = 8
            Top = 10
            Width = 337
            Height = 201
            TabOrder = 0
            object PaintBox1: TPaintBox
              Left = 1
              Top = 1
              Width = 335
              Height = 199
              Align = alClient
              OnPaint = PaintBox1Paint
            end
          end
          object btPrepareCardForPrinting: TButton
            Left = 376
            Top = 56
            Width = 75
            Height = 25
            Caption = #1047#1072#1075#1088#1091#1079#1082#1072
            TabOrder = 1
            OnClick = btPrepareCardForPrintingClick
          end
          object btPrintCard: TButton
            Left = 376
            Top = 96
            Width = 75
            Height = 25
            Caption = #1055#1077#1095#1072#1090#1100
            TabOrder = 2
            OnClick = btPrintCardClick
          end
        end
      end
    end
  end
  object RightsScheme_PopupMenu: TPopupMenu
    Left = 696
    Top = 152
    object pmGuard: TMenuItem
      Caption = #1058#1080#1087#1080#1095#1085#1099#1077' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1076#1083#1103' '#1054#1093#1088#1072#1085#1085#1080#1082#1072
      OnClick = RightsScheme_PopupMenuClick
    end
    object pmStatistician: TMenuItem
      Caption = #1058#1080#1087#1080#1095#1085#1099#1077' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1076#1083#1103' '#1057#1090#1072#1090#1080#1089#1090#1080#1082#1072
      OnClick = RightsScheme_PopupMenuClick
    end
    object pmDirector: TMenuItem
      Caption = #1058#1080#1087#1080#1095#1085#1099#1077' '#1091#1089#1090#1072#1085#1086#1074#1082#1080' '#1076#1083#1103' '#1044#1080#1088#1077#1082#1090#1086#1088#1072
      OnClick = RightsScheme_PopupMenuClick
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Filter = #1060#1086#1090#1086#1075#1088#1072#1092#1080#1080' '#1074' '#1092#1086#1088#1084#1072#1090#1077' JPEG (*.jpg; *.jpeg)|*.jpg;*.jpeg'
    Title = #1042#1099#1073#1086#1088' '#1092#1086#1090#1086#1075#1088#1072#1092#1080#1080
    Left = 664
    Top = 232
  end
  object IBDataSet1: TIBDataSet
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    ForcedRefresh = True
    AfterDelete = IBDataSet1AfterDelete
    AfterEdit = IBDataSet1AfterChange
    AfterInsert = IBDataSet1AfterChange
    AfterOpen = IBDataSet1IsEmpyCheck
    AfterPost = IBDataSet1IsEmpyCheck
    DeleteSQL.Strings = (
      'DELETE FROM'
      '           Units'
      'WHERE'
      '     Units.nn = :nn;')
    InsertSQL.Strings = (
      'INSERT INTO'
      
        '  Units (nn, objects_lnk, card, card_type, enabled, expire, righ' +
        'ts, passwrd, template, marked_for_printing, web_login, web_passw' +
        'ord, fname, mname, lname, photo, sms_enabled, sms_phone, birthda' +
        'y, home_address, medical_policy, phone, father_fio, father_emplo' +
        'yment, father_post, father_phone, father_info, mother_fio, mothe' +
        'r_employment, mother_post, mother_phone, mother_info)'
      'VALUES'
      
        '  (:nn, :objects_lnk, :card, :card_type, :enabled, :expire, :rig' +
        'hts, :passwrd, :template, :marked_for_printing, :web_login, :web' +
        '_password, :fname, :mname, :lname, :photo, :sms_enabled, :sms_ph' +
        'one, :birthday, :home_address, :medical_policy, :phone, :father_' +
        'fio, :father_employment, :father_post, :father_phone, :father_in' +
        'fo, :mother_fio, :mother_employment, :mother_post, :mother_phone' +
        ', :mother_info);')
    RefreshSQL.Strings = (
      'SELECT'
      '      Units.*,'
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
      '      Units.*,'
      '      Aux_Yesno1.name AS enabled_text,'
      '      Aux_Yesno2.name AS marked_for_printing_text'
      'FROM'
      '    Units'
      'LEFT JOIN'
      '         Aux_yesno Aux_Yesno1 ON Units.enabled = Aux_yesno1.nn'
      'LEFT JOIN'
      
        '         Aux_yesno Aux_Yesno2 ON Units.marked_for_printing = Aux' +
        '_yesno2.nn'
      'ORDER BY'
      '    Units.structure_name, Units.lname, Units.fname, Units.mname;')
    ModifySQL.Strings = (
      'UPDATE'
      '      Units'
      'SET'
      '   Units.objects_lnk        = :objects_lnk,      '
      '   Units.card               = :card,             '
      '   Units.card_type          = :card_type,        '
      '   Units.enabled            = :enabled,          '
      '   Units.expire             = :expire,           '
      '   Units.rights             = :rights,           '
      '   Units.passwrd            = :passwrd,          '
      '   Units.template           = :template,         '
      '   Units.marked_for_printing= :marked_for_printing,'
      '   Units.web_login          = :web_login,        '
      '   Units.web_password       = :web_password,     '
      '   Units.fname              = :fname,            '
      '   Units.mname              = :mname,            '
      '   Units.lname              = :lname,            '
      '   Units.photo              = :photo,            '
      '   Units.sms_enabled        = :sms_enabled,      '
      '   Units.sms_phone          = :sms_phone,        '
      '   Units.birthday           = :birthday,         '
      '   Units.home_address       = :home_address,     '
      '   Units.medical_policy     = :medical_policy,   '
      '   Units.phone              = :phone,            '
      '   Units.father_fio         = :father_fio,       '
      '   Units.father_employment  = :father_employment,'
      '   Units.father_post        = :father_post,      '
      '   Units.father_phone       = :father_phone,     '
      '   Units.father_info        = :father_info,      '
      '   Units.mother_fio         = :mother_fio,       '
      '   Units.mother_employment  = :mother_employment,'
      '   Units.mother_post        = :mother_post,      '
      '   Units.mother_phone       = :mother_phone,     '
      '   Units.mother_info        = :mother_info       '
      'WHERE'
      '  Units.nn = :nn;')
    ParamCheck = False
    GeneratorField.Field = 'nn'
    GeneratorField.Generator = 'GEN_UNITS'
    Left = 648
    Top = 48
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 616
    Top = 48
  end
  object DataSource1: TDataSource
    DataSet = IBDataSet1
    Left = 680
    Top = 48
  end
  object OpenDialog1: TOpenDialog
    Filter = #1064#1072#1073#1083#1086#1085#1099' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080' (*.ini)|*.ini'
    Title = #1042#1099#1073#1086#1088' '#1096#1072#1073#1083#1086#1085#1072' '#1076#1083#1103' '#1087#1077#1095#1072#1090#1080' '#1082#1072#1088#1090#1086#1095#1082#1080
    Left = 576
    Top = 216
  end
  object PrintDialog1: TPrintDialog
    Copies = 1
    Options = [poWarning, poHelp, poDisablePrintToFile]
    Left = 488
    Top = 200
  end
end