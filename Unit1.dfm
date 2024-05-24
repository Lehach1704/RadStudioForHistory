object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'WorkWithDB'
  ClientHeight = 439
  ClientWidth = 1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object InfoLabel: TLabel
    Left = 176
    Top = 272
    Width = 3
    Height = 15
  end
  object WayDB: TEdit
    Left = 8
    Top = 16
    Width = 1058
    Height = 23
    TabOrder = 0
  end
  object StructureDB: TVirtualStringTree
    Left = 8
    Top = 56
    Width = 1058
    Height = 201
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    TabOrder = 1
    OnAddToSelection = StructureDBAddToSelection
    OnGetText = StructureDBGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'Id'
        Width = 100
      end
      item
        MinWidth = 100
        Position = 1
        Text = 'URL'
        Width = 1000
      end>
  end
  object OpenDB: TButton
    Left = 8
    Top = 272
    Width = 153
    Height = 33
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093'...'
    TabOrder = 2
    OnClick = OpenDBClick
  end
  object DelRecDB: TButton
    Left = 8
    Top = 320
    Width = 153
    Height = 33
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100' '#1080#1079' '#1041#1044
    TabOrder = 3
    OnClick = DelRecDBClick
  end
  object ClearDB: TButton
    Left = 8
    Top = 368
    Width = 153
    Height = 33
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1090#1072#1073#1083#1080#1094#1091
    TabOrder = 4
    OnClick = ClearDBClick
  end
  object OpenDBDialog: TOpenDialog
    Left = 528
    Top = 384
  end
end
