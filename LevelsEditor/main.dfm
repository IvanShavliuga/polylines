object Form1: TForm1
  Left = 206
  Top = 134
  Width = 510
  Height = 446
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1091#1088#1086#1074#1085#1077#1081
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 176
    Top = 40
    Width = 225
    Height = 225
    OnMouseDown = Image1MouseDown
  end
  object Label1: TLabel
    Left = 8
    Top = 208
    Width = 66
    Height = 13
    Caption = #1056#1077#1078#1080#1084' '#1080#1075#1088#1099':'
  end
  object Image2: TImage
    Left = 176
    Top = 8
    Width = 225
    Height = 25
  end
  object CaptionLevel: TLabeledEdit
    Left = 8
    Top = 24
    Width = 161
    Height = 21
    EditLabel.Width = 91
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1091#1088#1086#1074#1085#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 0
    Text = #1058#1077#1089#1090
  end
  object WidthMatrix: TLabeledEdit
    Left = 8
    Top = 144
    Width = 161
    Height = 21
    EditLabel.Width = 69
    EditLabel.Height = 13
    EditLabel.Caption = #1064#1080#1088#1080#1085#1072' '#1087#1086#1083#1103':'
    Enabled = False
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 1
    Text = '15'
  end
  object HeightMatrix: TLabeledEdit
    Left = 8
    Top = 184
    Width = 161
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = #1042#1099#1089#1086#1090#1072' '#1087#1086#1083#1103':'
    Enabled = False
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
    Text = '15'
  end
  object GameName: TLabeledEdit
    Left = 8
    Top = 64
    Width = 161
    Height = 21
    EditLabel.Width = 81
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1080#1075#1088#1099':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
    Text = 'PolyLines 1.0'
  end
  object TabSet1: TTabSet
    Left = 176
    Top = 272
    Width = 225
    Height = 21
    DitherBackground = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Tabs.Strings = (
      #1062#1074#1077#1090#1072
      #1041#1086#1085#1091#1089#1099
      #1042#1099#1076#1077#1083#1077#1085#1080#1077)
    TabIndex = 0
    OnClick = TabSet1Click
  end
  object Button1: TButton
    Left = 8
    Top = 328
    Width = 75
    Height = 25
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100
    TabOrder = 5
    OnClick = Button1Click
  end
  object NumberLevel: TLabeledEdit
    Left = 8
    Top = 104
    Width = 161
    Height = 21
    EditLabel.Width = 75
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1086#1084#1077#1088' '#1091#1088#1086#1074#1085#1103':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 6
    Text = '0'
  end
  object MinScore: TLabeledEdit
    Left = 8
    Top = 264
    Width = 161
    Height = 21
    EditLabel.Width = 53
    EditLabel.Height = 13
    EditLabel.Caption = #1052#1080#1085'. '#1086#1095#1082#1080':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 7
    Text = '0'
  end
  object MaxScore: TLabeledEdit
    Left = 8
    Top = 304
    Width = 161
    Height = 21
    EditLabel.Width = 59
    EditLabel.Height = 13
    EditLabel.Caption = #1052#1072#1082#1089'. '#1086#1095#1082#1080':'
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 8
    Text = '300'
  end
  object ModeGame: TComboBox
    Left = 8
    Top = 224
    Width = 161
    Height = 21
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 9
    Text = #1055#1091#1090#1077#1096#1077#1089#1090#1074#1080#1077
    Items.Strings = (
      #1055#1091#1090#1077#1096#1077#1089#1090#1074#1080#1077
      #1043#1086#1083#1086#1074#1086#1083#1084#1082#1072
      #1053#1072' '#1074#1088#1077#1084#1103)
  end
  object Button2: TButton
    Left = 88
    Top = 328
    Width = 75
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 10
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 360
    Width = 75
    Height = 25
    Caption = #1040#1085#1072#1083#1080#1079
    TabOrder = 11
    OnClick = Button3Click
  end
  object MainMenu1: TMainMenu
    Left = 336
    Top = 272
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N3: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        ShortCut = 113
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        ShortCut = 114
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        ShortCut = 115
        OnClick = N5Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.level'
    Filter = #1060#1072#1081#1083#1099' '#1091#1088#1086#1074#1085#1077#1081'|*.level'
    Left = 304
    Top = 272
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '*.level'
    Filter = #1060#1072#1081#1083#1099' '#1091#1088#1086#1074#1085#1077#1081'|*.level'
    Left = 368
    Top = 272
  end
end
