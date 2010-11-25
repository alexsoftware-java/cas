object fReportSelection: TfReportSelection
  Left = 282
  Top = 164
  Width = 487
  Height = 324
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #1054#1090#1095#1105#1090#1099' '#1087#1086' '#1087#1086#1089#1077#1097#1072#1077#1084#1086#1089#1090#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  Icon.Data = {
    0000010001004020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000010000000100000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000003333333333333333333333000000000
    000FFFFFFFFFFFFFFFFFFFF30000000000FFF8FFFFFFFFF88FFFFFF300000000
    006FFEFFFFFFFF118FFFFFF300000000000F88888888881188888FF300000000
    00FFFEFFFFFFFFF88FFFFFF300000000006F88888888881178888FF300000000
    000FFEFFFFFFFF118FFFFFF30000000000FF88888888881117888FF300000000
    006FFEFFFFFFFFF1118FFFF300000000000F88888888117811788FF300000000
    00FFFEFFFFFF1111118FFFF300000000006F88888338811118888FF300000000
    000FFEFFBB3FFFFFFFFFFFF30000000000FF8888BB88888888888FF300000000
    006FFEFFFFFFFFFF8888FFF300000000000F88888338888CCCC78FF300000000
    00FFFEFFBB3FFFFFCC8FFFF300000000006F8888BB388888CC788FF300000000
    000FFEFFBB3FFFFFCC8FFFF30000000000FF8888BB388888CC788FF300000000
    006FFEFFBB3FFFFCCC8FFFF300000000000F8888BB88888887788FF300000000
    00FFFEFFFFFFFFFFCC8FFFF300000000006FFFFFFFFFFFFFCCFFFFF300000000
    000FFFFFFFFFFFFFFFFFFFF30000000000FFFFFFFFFFFFFFFFFFFFF300000000
    000000000000000000000000000000000000000000000000000000000000FFFF
    FFFFFFFFFFFFF800000FF8000007F0000007E8000007E8000007F0000007E800
    0007E8000007F0000007E8000007E8000007F0000007E8000007E8000007F000
    0007E8000007E8000007F0000007E8000007E8000007F0000007E8000007E800
    0007F0000007E8000007E8000007F0000007F8000007F800000FFFFFFFFF}
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 249
    Height = 209
    Caption = ' '#1044#1040#1058#1040' '#1080' '#1042#1056#1045#1052#1071' '
    TabOrder = 1
    object MonthCalendar1: TMonthCalendar
      Left = 2
      Top = 15
      Width = 245
      Height = 154
      Date = 38966.7387357523
      ShowToday = False
      TabOrder = 0
    end
    object DateTimePicker1: TDateTimePicker
      Left = 32
      Top = 176
      Width = 186
      Height = 21
      CalAlignment = dtaLeft
      Date = 38149.3541666667
      Format = '  HH:mm'
      Time = 38149.3541666667
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 1
    end
  end
  object rgReportMode: TRadioGroup
    Left = 0
    Top = 211
    Width = 249
    Height = 73
    Caption = ' '#1056#1045#1046#1048#1052' '
    ItemIndex = 0
    Items.Strings = (
      #1055#1088#1086#1089#1084#1086#1090#1088' '#1086#1090#1095#1105#1090#1072
      #1053#1077#1084#1077#1076#1083#1077#1085#1085#1072#1103' '#1087#1077#1095#1072#1090#1100
      #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1096#1072#1073#1083#1086#1085#1072)
    TabOrder = 0
    OnClick = rgReportModeClick
  end
  object rgReportType: TRadioGroup
    Left = 254
    Top = 0
    Width = 211
    Height = 209
    Caption = ' '#1042#1048#1044' '
    Items.Strings = (
      #1044#1080#1072#1075#1088#1072#1084#1084#1072' '#1087#1086#1089#1077#1097#1072#1077#1084#1086#1089#1090#1080
      #1057#1087#1080#1089#1086#1082' '#1086#1090#1089#1091#1090#1089#1090#1074#1086#1074#1072#1074#1096#1080#1093
      #1057#1087#1080#1089#1086#1082' '#1087#1088#1080#1096#1077#1076#1096#1080#1093' '#1076#1086
      #1057#1087#1080#1089#1086#1082' '#1087#1088#1080#1096#1077#1076#1096#1080#1093' '#1087#1086#1089#1083#1077
      #1057#1087#1080#1089#1086#1082' '#1091#1096#1077#1076#1096#1080#1093' '#1087#1086#1089#1083#1077
      #1053#1072#1088#1091#1096#1080#1090#1077#1083#1080' '#1087#1088#1086#1087#1091#1089#1082#1085#1086#1075#1086' '#1088#1077#1078#1080#1084#1072)
    TabOrder = 2
  end
  object Button1: TButton
    Left = 256
    Top = 235
    Width = 209
    Height = 25
    TabOrder = 3
    OnClick = Button1Click
  end
end