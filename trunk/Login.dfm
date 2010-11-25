object fLogin: TfLogin
  Left = 355
  Top = 151
  ActiveControl = Edit1
  BorderStyle = bsDialog
  ClientHeight = 251
  ClientWidth = 324
  Color = clTeal
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 96
    Top = 8
    Width = 131
    Height = 24
    Caption = ' '#1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100': '
    Color = clAqua
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label2: TLabel
    Left = 123
    Top = 192
    Width = 77
    Height = 24
    Caption = ' '#1055#1072#1088#1086#1083#1100': '
    Color = clAqua
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object ListBox1: TListBox
    Left = 7
    Top = 40
    Width = 310
    Height = 137
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 0
    OnDblClick = ListBox1DblClick
    OnKeyDown = ListBox1KeyDown
  end
  object Edit1: TEdit
    Left = 7
    Top = 224
    Width = 310
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
    OnKeyDown = Edit1KeyDown
  end
  object ControlCRTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = ControlCRTimerTimer
    Left = 16
    Top = 184
  end
end