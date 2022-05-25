//---------------------------------------------------------------------------

#ifndef mainformH
#define mainformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include "result.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N13;
        TListBox *ListBox1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TPanel *Panel1;
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
        TMenuItem *N10;
        TMenuItem *N11;
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N13Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
       TResults Recordes;
       __fastcall TForm1(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
