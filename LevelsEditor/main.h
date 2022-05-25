//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Tabs.hpp>
#include <Dialogs.hpp>
#include "PolyLinesLevel.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TImage *Image1;
        TLabeledEdit *CaptionLevel;
        TLabeledEdit *WidthMatrix;
        TLabeledEdit *HeightMatrix;
        TLabeledEdit *GameName;
        TTabSet *TabSet1;
        TButton *Button1;
        TLabeledEdit *NumberLevel;
        TLabeledEdit *MinScore;
        TLabeledEdit *MaxScore;
        TComboBox *ModeGame;
        TLabel *Label1;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TImage *Image2;
        TButton *Button2;
        TButton *Button3;
        void __fastcall N5Click(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TabSet1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        PLLevel Level;
        int color;
        int bonus;
        bool select;
        void PaintIv2(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
