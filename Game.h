//---------------------------------------------------------------------------

#ifndef GameH
#define GameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "iv2game.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <MPlayer.hpp>
#include <gl\gl.h>
#include <gl\glu.h>
#include <Graphics.hpp>
#include <mmsystem.hpp>

//---------------------------------------------------------------------------
HDC   ghDC;
GLuint	base;
GLvoid BuildFont(int height)
{
     HFONT	font;
     HFONT	oldfont;
     base = glGenLists(256);
     font = CreateFont(	height,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,
                       ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
                       ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,
                       "Times New Roman Cyr");
     oldfont = (HFONT)SelectObject(ghDC, font);
     wglUseFontBitmaps(ghDC, 32, 256-32, base);
     SelectObject(ghDC, oldfont);
     DeleteObject(font);
}

GLvoid KillFont(GLvoid)
{
     glDeleteLists(base, 256);
}

GLvoid glPrint(const char *fmt, ...)
{
     char text[256];
     va_list ap;
     if (fmt == NULL)
      	return;
     va_start(ap, fmt);
        vsprintf(text, fmt, ap);
     va_end(ap);
    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}
typedef enum MousePosition {
    mpNewGame,
    mpSelectUser,
    mpResults,
    mpHelp,
    mpAbout,
    mpExit,
    mpOptions,
    mpNone
}MousePosition;
typedef enum MenuStatus {
    msNewGame,
    msSelectUser,
    msResults,
    msHelp,
    msAbout,
    msExit,
    msOptions,
    msNone
}MenuStatus;
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabeledEdit *Password;
        TBitBtn *BitBtn1;
        TComboBox *Users;
        TLabel *Label1;
        TTimer *Timer1;
        TMediaPlayer *MediaPlayer1;
        TTimer *Timer2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
private:	// User declarations
        void __fastcall SetupTextures();   //Загпрузка текстур
        void __fastcall SetPixelFormatDescriptor();   //Установка парметров для системы
         void __fastcall SetupLighting(); //Установка освещения
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall IdleLoop(TObject*, bool&);
        void __fastcall RenderGLScene();
        void __fastcall DrawObjects();
        Iv2Game Game;
        Graphics::TBitmap* bitmap;
        GLfloat  w, h;
        GLsizei size;
        GLuint texture[7],background,bon[7][10],twocolor[7][7];
        HDC hdc;
        HGLRC hrc;
        int PixelFormat;
        int Herz,W, H;
        MousePosition mPos;
        MenuStatus mStatus;
        bool Play, sound,music;
        GLuint startoflist;
        HGLRC ghRC;
        int numbermusic;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
