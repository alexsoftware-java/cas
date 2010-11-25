object fInputLine: TfInputLine
  Left = 302
  Top = 323
  BorderStyle = bsDialog
  ClientHeight = 71
  ClientWidth = 472
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 150
    Top = 40
    Width = 75
    Height = 25
    Caption = 'OK'
    Enabled = False
    ModalResult = 1
    TabOrder = 1
  end
  object Button2: TButton
    Left = 246
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object LabeledEdit1: TLabeledEdit
    Left = 56
    Top = 8
    Width = 409
    Height = 21
    EditLabel.Width = 50
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 0
    OnChange = LabeledEdit1Change
    OnKeyDown = LabeledEdit1KeyDown
  end
end