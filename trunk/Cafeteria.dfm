object fCafeteria: TfCafeteria
  Left = 292
  Top = 170
  Width = 692
  Height = 306
  Caption = #1040#1056#1052' <'#1057#1090#1086#1083#1086#1074#1072#1103'>'
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
  PixelsPerInch = 96
  TextHeight = 14
  object imgPhoto: TImage
    Left = 0
    Top = 0
    Width = 208
    Height = 270
    Align = alLeft
    Center = True
    Proportional = True
    Stretch = True
  end
  object lbStructure: TLabel
    Left = 233
    Top = 3
    Width = 119
    Height = 27
    Caption = 'lbStructure'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object lbLName: TLabel
    Left = 233
    Top = 59
    Width = 96
    Height = 27
    Caption = 'lbLName'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object lbFName: TLabel
    Left = 233
    Top = 94
    Width = 98
    Height = 27
    Caption = 'lbFName'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object lbMName: TLabel
    Left = 233
    Top = 128
    Width = 102
    Height = 27
    Caption = 'lbMName'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object lbPassText1: TLabel
    Left = 284
    Top = 197
    Width = 115
    Height = 24
    Caption = 'lbPassText1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object lbPassText2: TLabel
    Left = 284
    Top = 232
    Width = 115
    Height = 24
    Caption = 'lbPassText2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object shpCircle: TShape
    Left = 233
    Top = 190
    Width = 44
    Height = 35
    Shape = stCircle
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = fMain.IBDatabase1
    Params.Strings = (
      'nowait'
      'read_committed'
      'rec_version')
    Left = 416
    Top = 8
  end
  object IBSQL1: TIBSQL
    Database = fMain.IBDatabase1
    Transaction = IBTransaction1
    Left = 416
    Top = 48
  end
  object Timer1: TTimer
    Interval = 200
    OnTimer = Timer1Timer
    Left = 368
    Top = 128
  end
end