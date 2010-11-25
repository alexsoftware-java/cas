object fReport: TfReport
  Left = 334
  Top = 359
  Width = 383
  Height = 124
  Caption = #1048#1076#1105#1090' '#1092#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1077' '#1086#1090#1095#1105#1090#1072'. '#1046#1076#1080#1090#1077'...'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Position = poScreenCenter
  Visible = True
  TextHeight = 13
  object Animate1: TAnimate
    Left = 51
    Top = 16
    Width = 272
    Height = 60
    Active = True
    CommonAVI = aviCopyFile
    StopFrame = 1
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 8
  end
  object IBQuery2: TIBQuery
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    Left = 40
    Top = 32
  end
  object IBQuery1: TIBQuery
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    Left = 8
    Top = 32
  end
  object prReport1: TprReport
    ShowProgress = True
    Values = <>
    Variables = <>
    OnDestroyPreview = prReport1DestroyPreview
    Left = 336
    Top = 32
  end
end