object fAbout: TfAbout
  Left = 238
  Top = 166
  ActiveControl = OKButton
  BorderStyle = bsNone
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 243
  ClientWidth = 721
  Color = clTeal
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = True
  Position = poMainFormCenter
  Visible = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object AboutMemo: TMemo
    Left = 8
    Top = 8
    Width = 705
    Height = 180
    TabStop = False
    BorderStyle = bsNone
    Color = clYellow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Lucida Console'
    Font.Style = [fsBold]
    Lines.Strings = (
      ''
      #1057#1080#1089#1090#1077#1084#1072' '#1050#1086#1085#1090#1088#1086#1083#1103' '#1044#1086#1089#1090#1091#1087#1072' - '#1064#1082#1086#1083#1072
      ''
      'Copyright (C) 2003-2010, '#1040#1083#1077#1082#1089#1072#1085#1076#1088' '#1044'. '#1063#1072#1075#1072#1076#1072#1077#1074
      #1042#1089#1077' '#1087#1088#1072#1074#1072' '#1079#1072#1097#1080#1097#1077#1085#1099'.'
      #1057#1074#1080#1076#1077#1090#1077#1083#1100#1089#1090#1074#1086' '#1086#1073' '#1086#1092#1080#1094#1080#1072#1083#1100#1085#1086#1081' '#1088#1077#1075#1080#1089#1090#1088#1072#1094#1080#1080' '#1087#1088#1086#1075#1088#1072#1084#1084#1099' '#1076#1083#1103' '#1069#1042#1052' '#8220'CAS'#8221' '#8470' 2005613275'
      ''
      '  '#1055#1088#1086#1089#1080#1084' '#1042#1072#1089' '#1089#1086#1086#1073#1097#1072#1090#1100' '#1086' '#1083#1102#1073#1099#1093' '#1086#1073#1085#1072#1088#1091#1078#1077#1085#1085#1099#1093' '#1086#1096#1080#1073#1082#1072#1093'.'
      #1058#1072#1082#1078#1077' '#1085#1072#1084' '#1080#1085#1090#1077#1088#1077#1089#1085#1099' '#1042#1072#1096#1080' '#1080#1076#1077#1080' '#1080' '#1089#1086#1074#1077#1090#1099' '#1087#1086' '#1091#1083#1091#1095#1096#1077#1085#1080#1102' '#1087#1088#1086#1076#1091#1082#1090#1072'.'
      ''
      ' '#1058#1077#1083#1077#1092#1086#1085': +7 (916) 656-35-90'
      ' E-Mail : cas@adc.su'
      ' '#1057#1072#1081#1090'   : www.adc.su/cas')
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
    WordWrap = False
  end
  object OKButton: TButton
    Left = 24
    Top = 204
    Width = 673
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = OKButtonClick
  end
end