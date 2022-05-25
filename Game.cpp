//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Game.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    Application->OnIdle = IdleLoop;
    size = 100.0f;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::IdleLoop(TObject*, bool& done)
{
    done = false;
    RenderGLScene();
    SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RenderGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glCallList(startoflist);
    if(!Play)
    {
        glCallList(startoflist+1);
        if(mStatus==msNone)
        {
            glColor3f(0,0,1);
            switch(mPos){
              case mpExit:
                glBegin(GL_QUADS);
                glVertex3f(-30,-22,-1);
                glVertex3f(-30,-29,-1);
                glVertex3f( 30,-29,-1);
                glVertex3f( 30,-22,-1);
                glEnd();
                break;
              case mpOptions:
                glBegin(GL_QUADS);
                glVertex3f(-30,-15,-1);
                glVertex3f(-30,-22,-1);
                glVertex3f( 30,-22,-1);
                glVertex3f( 30,-15,-1);
                glEnd();
                break;
              case mpAbout:
                glBegin(GL_QUADS);
                glVertex3f(-30,-8,-1);
                glVertex3f(-30,-15,-1);
                glVertex3f( 30,-15,-1);
                glVertex3f( 30,-8,-1);
                glEnd();
                break;
              case mpHelp:
                glBegin(GL_QUADS);
                glVertex3f(-30,-1,-1);
                glVertex3f(-30,-8,-1);
                glVertex3f( 30,-8,-1);
                glVertex3f( 30,-1,-1);
                glEnd();
                break;
              case mpResults:
                glBegin(GL_QUADS);
                glVertex3f(-30,6,-1);
                glVertex3f(-30,-1,-1);
                glVertex3f( 30,-1,-1);
                glVertex3f( 30,6,-1);
                glEnd();
                break;
              case mpSelectUser:
                glBegin(GL_QUADS);
                glVertex3f(-30,13,-1);
                glVertex3f(-30,6,-1);
                glVertex3f( 30,6,-1);
                glVertex3f( 30,13,-1);
                glEnd();
                break;
              case mpNewGame:
                glBegin(GL_QUADS);
                glVertex3f(-30,20,-1);
                glVertex3f(-30,13,-1);
                glVertex3f( 30,13,-1);
                glVertex3f( 30,20,-1);
                glEnd();
                break;
            }
            glCallList(startoflist+2);
        }
        if(mStatus==msNewGame)
        {
            glColor3f(0,0,1);
            switch(mPos){
              case mpExit:
                glBegin(GL_QUADS);
                glVertex3f(-30,-22,-1);
                glVertex3f(-30,-29,-1);
                glVertex3f( 30,-29,-1);
                glVertex3f( 30,-22,-1);
                glEnd();
                break;
              case mpResults:
                glBegin(GL_QUADS);
                glVertex3f(-30,6,-1);
                glVertex3f(-30,-1,-1);
                glVertex3f( 30,-1,-1);
                glVertex3f( 30,6,-1);
                glEnd();
                break;
              case mpSelectUser:
                glBegin(GL_QUADS);
                glVertex3f(-30,13,-1);
                glVertex3f(-30,6,-1);
                glVertex3f( 30,6,-1);
                glVertex3f( 30,13,-1);
                glEnd();
                break;
              case mpNewGame:
                glBegin(GL_QUADS);
                glVertex3f(-30,20,-1);
                glVertex3f(-30,13,-1);
                glVertex3f( 30,13,-1);
                glVertex3f( 30,20,-1);
                glEnd();
                break;
            }
            glCallList(startoflist+3);
        }

        if(mStatus==msResults)
        {
            glColor3f(0,0,1);
            switch(mPos){
              case mpExit:
                glBegin(GL_QUADS);
                glVertex3f(-30,-22,-1);
                glVertex3f(-30,-29,-1);
                glVertex3f( 30,-29,-1);
                glVertex3f( 30,-22,-1);
                glEnd();
                break;
            }
            glCallList(startoflist+5);
            Game.Paint(true,false);
        }
        if(mStatus==msHelp)
        {
            glColor3f(0,0,1);
            switch(mPos){
              case mpExit:
                glBegin(GL_QUADS);
                glVertex3f(-30,-22,-1);
                glVertex3f(-30,-29,-1);
                glVertex3f( 30,-29,-1);
                glVertex3f( 30,-22,-1);
                glEnd();
                break;
            }
            glCallList(startoflist+6);
            //KillFont();
            BuildFont(-21);
            glRasterPos2f(-28,20);
            glNormal3f(0,0,1);
            glPrint("Соберите линию из трех");
            glRasterPos2f(-28,15);
            glPrint("шаров одного цвета из");
            glRasterPos2f(-28,10);
            glPrint("предложенных пяти шаров");
            glRasterPos2f(-28,5);
            glPrint("в правом верхнем углу.");
            glRasterPos2f(-28,0);
            glPrint("Побеждает тот, кто набирает");
            glRasterPos2f(-28,-5);
            glPrint("большее количество очков.");
            //KillFont();
            BuildFont(48);
        }
        if(mStatus==msAbout)
        {
            glColor3f(0,0,1);
            switch(mPos){
              case mpExit:
                glBegin(GL_QUADS);
                glVertex3f(-30,-22,-1);
                glVertex3f(-30,-29,-1);
                glVertex3f( 30,-29,-1);
                glVertex3f( 30,-22,-1);
                glEnd();
                break;
            }
            glCallList(startoflist+7);
            BuildFont(-21);
            glRasterPos2f(-28,20);
            glNormal3f(0,0,1);
            glPrint("PolyLines");
            glRasterPos2f(-28,15);
            glPrint("Логическая игра");
            glRasterPos2f(-28,10);
            glPrint("Версия 1.1");
            glRasterPos2f(-28,5);
            glPrint("Дата создания: 24 мая 2008г.");
            glRasterPos2f(-28,0);
            glPrint("Адрес в интернете: ivx2.narod.ru");
            glRasterPos2f(-28,-5);
            glPrint("Данная программа не является");
            glRasterPos2f(-28,-10);
            glPrint("коммерческим продуктом.");
            glRasterPos2f(-28,-15);
            glPrint("Авторы программы:");
            glRasterPos2f(-28,-20);
            glPrint("Иванов И. С. Александров А. С.");
            BuildFont(48);
        }
        if(mStatus==msOptions)
        {
            glColor3f(0,0,1);
            switch(mPos){
              case mpExit:
                glBegin(GL_QUADS);
                glVertex3f(-30,-22,-1);
                glVertex3f(-30,-29,-1);
                glVertex3f( 30,-29,-1);
                glVertex3f( 30,-22,-1);
                glEnd();
                break;
              case mpSelectUser:
                glBegin(GL_QUADS);
                glVertex3f(-30,13,-1);
                glVertex3f(-30,6,-1);
                glVertex3f( 30,6,-1);
                glVertex3f( 30,13,-1);
                glEnd();
                break;
              case mpNewGame:
                glBegin(GL_QUADS);
                glVertex3f(-30,20,-1);
                glVertex3f(-30,13,-1);
                glVertex3f( 30,13,-1);
                glVertex3f( 30,20,-1);
                glEnd();
                break;
            }
            glCallList(startoflist+8);
            if(sound){
              glColor3f(0,1,0);
              glRasterPos2f(-29,15);          glPrint("Вкл");
            }else{
              glColor3f(1,0,0);
              glRasterPos2f(-29,15);          glPrint("Выкл");
            }
            if(music){
               glColor3f(0,1,0);
               glRasterPos2f(-29,8);           glPrint("Вкл");
            }else{
               glColor3f(1,0,0);
               glRasterPos2f(-29,8);           glPrint("Выкл");

            }
        }
    }else{
      glCallList(startoflist+9);
      glColor3f(0,0,1);
      switch(mPos){
        case mpExit:
          glBegin(GL_QUADS);
          glVertex3f(30,-35,-1);
          glVertex3f(30,-42,-1);
          glVertex3f(70,-42,-1);
          glVertex3f(70,-35,-1);
          glEnd();
          break;
        case mpNewGame:
          glBegin(GL_QUADS);
          glVertex3f(30,-25,-1);
          glVertex3f(30,-32,-1);
          glVertex3f(70,-32,-1);
          glVertex3f(70,-25,-1);
          glEnd();
          break;
      }
      glColor3f(0,0,0);
      glRasterPos2f(32,-40);
      glPrint("Возврат");
      glRasterPos2f(32,-30);
      glPrint("%s",(Timer1->Enabled)?("Игра"):("Пауза"));
      glRasterPos2f(32,-10);
      glPrint("%d/90",Game.GetUserWins());
      glRasterPos2f(32,-5);
      glPrint("Рейтинг:");
      glRasterPos2f(32,5);
      glPrint("%ld",Game.GetUserScoreAll()+Game.GetUserScoreLevel());
      glRasterPos2f(32,10);
      glPrint("Очки:");
      if(Game.SelectBall>-1)
      {
        glBegin(GL_QUADS);
        glNormal3f(0,0,1);
          glColor3f(1,0,0);  glVertex3f(36+Game.SelectBall*6,30,-2);
          glColor3f(0,1,0);  glVertex3f(36+Game.SelectBall*6,40,-2);
          glColor3f(0,1,1);  glVertex3f(30+Game.SelectBall*6,40,-2);
          glColor3f(0,0,1);  glVertex3f(30+Game.SelectBall*6,30,-2);
        glEnd();
      }
      glColor3f(0,0,0);
      Game.Paint(false,true);
    }
    glPopMatrix();

    SwapBuffers(hdc);

}
//---------------------------------------------------------------------------

void PLLevel::Paint()
{
       char str=Caption[0];
       int i,len;
       for(len=0; Caption[len]!=0; len++)
          ;
       if(len>8){
         for(i=0; Caption[i+1]!=0; i++)
           Caption[i]=Caption[i+1];
         Caption[i+0]=str;
         Caption[i+1]=0;
       }
       glPushMatrix();
       glColor3f(0,0,0);
       glRasterPos2f(32,25);
       glPrint("%s",Caption);
       glRasterPos2f(32,20);
       glPrint("%d - %d",Number/3+1,Number%3+1);
       if(ModeGame==2){
         glRasterPos2f(32,-20);
         glPrint("%d сек.",Time);
       }
       glTranslatef(-57,41.5,0);
       for(int y=0; y<15; y++)
        {
          for(int x=0; x<15; x++)
          {
            glTranslatef(6*x,0,0);
            if(Matrix[y][x].Data) {
               glColor3f(0.6,0.6,0.6);
            }else
               glColor3f(1,1,1);
            if(Matrix[y][x].Color) {
              glBindTexture(GL_TEXTURE_2D, Form1->texture[Matrix[y][x].Color-1]);
              if(Matrix[y][x].Bonus)
              glBindTexture(GL_TEXTURE_2D, Form1->bon[Matrix[y][x].Color-1][ Matrix[y][x].Bonus-1]);
              if(Matrix[y][x].Bonus==2)
              glBindTexture(GL_TEXTURE_2D, Form1->twocolor[Matrix[y][x].Color/10-1][ Matrix[y][x].Color%10-1]);

              glCallList(Form1->startoflist+10);
            }
            glTranslatef(-6*x,0,0);
        }
         glTranslatef(0,-6,0);

        }
        glTranslatef(24+10*6,40+7*6,0);
        for(int x=0; x<5; x++)
        {
            glTranslatef(6,0,0);
            if(Buffer[x].Color) {
              glBindTexture(GL_TEXTURE_2D, Form1->texture[Buffer[x].Color-1]);
              if(Buffer[x].Bonus)
              glBindTexture(GL_TEXTURE_2D, Form1->bon[Buffer[x].Color-1][Buffer[x].Bonus-1]);
              if(Buffer[x].Bonus==2)
              glBindTexture(GL_TEXTURE_2D, Form1->twocolor[Buffer[x].Color/10-1][Buffer[x].Color%10-1]);
              glCallList(Form1->startoflist+10);
            }
            glCallList(Form1->startoflist+10);
        }
        glPopMatrix();
        
}
void TResults::OnPrint(int Left,int Top,int Width, int Height)
{
        AnsiString str;
        BuildFont(-21);
        for(int i=0; i<10; i++) {
              str.sprintf("%s %d\\%d\\%d %ld",Data[i].Name,Data[i].Date.Day,
                      Data[i].Date.Month,Data[i].Date.Year,Data[i].Score);
              glRasterPos2f(-28,20-4*i);
              glPrint(str.c_str());
        }
        BuildFont(48);
           
         
}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    char *Names[256];
    int Count;
    numbermusic=0;
    hdc = GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc = wglCreateContext(hdc);
    if(hrc == NULL)
    	ShowMessage(":-)~ hrc == NULL");
    if(wglMakeCurrent(hdc, hrc) == false)
    	ShowMessage("Could not MakeCurrent");
    w = 800;
    h = 600;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if(Game.Launch())
    {
        ghDC = GetDC(Handle);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Game.GetUsers(Names,&Count);
        AnsiString str;
        for(int i=0; i<Count; i++)
        {
          str=AnsiString(Names[i]);
          Users->Items->Add(str);
        }
        SetupLighting();
        SetupTextures();
        BuildFont(48);
        startoflist = glGenLists(11);
        DrawObjects();
        mPos=mpNone;
        mStatus=msNone;
        Play=false;
        sound=true;
        music=true;
        FILE *media=fopen("polylines.cfg","r");
        if(media){
          sound=fgetc(media);
          music=fgetc(media);
        }
        fclose(media);
        if(music){
          MediaPlayer1->FileName="music0.mid";
          MediaPlayer1->Open();
          MediaPlayer1->Play();
          MediaPlayer1->Tag=1;
        }
        
    }else{
        ShowMessage("Ошибка при загрузке");
        exit(0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        DEVMODE DM;
        DM.dmSize = sizeof(DEVMODE);
        DM.dmBitsPerPel = 32; // глубина цвета, бит на пиксель
        DM.dmPelsWidth = W; // разрешение по горизонтали
        DM.dmPelsHeight = H; // разрешение по вертикали
        DM.dmFields = DM_BITSPERPEL + DM_PELSWIDTH + DM_PELSHEIGHT + DM_DISPLAYFREQUENCY;
        DM.dmDisplayFrequency = Herz; // частота обновления экрана
        ChangeDisplaySettings(&DM, 0); 
        Game.Exit();
        FILE *media=fopen("polylines.cfg","w");
        fputc(sound,media);
        fputc(music,media);
        fclose(media);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetupTextures()
{
    GLubyte bits[256][256][4],bits1[64][64][4];
    AnsiString string;
    bitmap = new Graphics::TBitmap;
    bitmap->LoadFromFile("images//bg.bmp");
    for(int i = 0; i < 256; i++)
    {
    	 for(int j = 0; j < 256; j++)
         {
            bits[255-j][i][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[i][j]);
            bits[255-j][i][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[i][j]);
            bits[255-j][i][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[i][j]);
            bits[255-j][i][3]= (GLbyte)255;
        }
     }
     //glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
     glGenTextures(1, &background);
     glBindTexture(GL_TEXTURE_2D, background);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
     glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);    // Set The Texture Generation Mode For T To Sphere Mapping (NEW)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
    glEnable(GL_TEXTURE_2D);
     for(int k=0; k<=6; k++)
    {
     string.sprintf("images//ball%d.bmp",k);
     bitmap->LoadFromFile(string);
     for(int i = 0; i < 64; i++)
     {
    	for(int j = 0; j < 64; j++)
        {
            bits1[i][j][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][3]= (GLbyte)255;
        }
     }
     glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
     glGenTextures(1, &texture[k]);
     glBindTexture(GL_TEXTURE_2D, texture[k]);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits1);
     glEnable(GL_TEXTURE_2D);

    }
    for(int p=0; p<10; p++)
    {
     for(int k=0; k<=6; k++)
    {
    if(p==1) p++;
     string.sprintf("images//bonus%d%d.bmp",p+1,k);
     bitmap->LoadFromFile(string);
     for(int i = 0; i < 64; i++)
     {
    	for(int j = 0; j < 64; j++)
        {
            bits1[i][j][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][3]= (GLbyte)255;
        }
     }
     glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
     glGenTextures(1, &bon[k][p]);
     glBindTexture(GL_TEXTURE_2D, bon[k][p]);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits1);

    }
    }
    for(int p=0; p<7; p++)
    {
     for(int k=0; k<7; k++)
    {
     if(p==k) continue;
     string.sprintf("images//ball%d.bmp",p);
     bitmap->LoadFromFile(string);
     for(int i = 0; i < 64; i++)
     {
    	for(int j = 0; j < 32; j++)
        {
            bits1[i][j][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j][3]= (GLbyte)255;
        }
     }
     string.sprintf("images//ball%d.bmp",k);
     bitmap->LoadFromFile(string);
     for(int i = 0; i < 64; i++)
     {
    	for(int j = 0; j < 32; j++)
        {
            bits1[i][j+32][0]= (GLbyte)GetRValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j+32][1]= (GLbyte)GetGValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j+32][2]= (GLbyte)GetBValue(bitmap->Canvas->Pixels[i][j]);
            bits1[i][j+32][3]= (GLbyte)255;
        }
     }
     glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
     glGenTextures(1, &twocolor[k][p]);
     glBindTexture(GL_TEXTURE_2D, twocolor[k][p]);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits1);
     
    }
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,
    };
    PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SetupLighting()
{
    GLfloat MaterialAmbient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat MaterialDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat MaterialSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat MaterialShininess[] = {50.0};
    GLfloat AmbientLightPosition[] = {0.5, 1.0, 1.0, 0.0};
    GLfloat LightAmbient[] = {0.5, 0.5, 0.5, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
    glLightfv(GL_LIGHT0, GL_POSITION, AmbientLightPosition);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
}


void __fastcall TForm1::FormResize(TObject *Sender)
{
    GLfloat nRange = 45.0;

    w = 800;
    h = 600;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION );

    glLoadIdentity();

    if (w <= h)
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else
	glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
    RenderGLScene();
   
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        if(!Play){
        if(mStatus==msNone){
           if(X>=200 && X<=599 && Y>=442 && Y<=488)
           Close();
           else if(X>=200 && X<=599 && Y>=396 && Y<=442)
           mStatus=msOptions;
           else if(X>=200 && X<=599 && Y>=350 && Y<396)
           mStatus=msAbout;
           else if(X>=200 && X<=599 && Y>=304 && Y<350)
           mStatus=msHelp;
           else if(X>=200 && X<=599 && Y>=166 && Y<212)
           {
           if(!Panel1->Visible)  mStatus=msNewGame;
           }
           else if(X>=200 && X<=599 && Y>=212 && Y<258)
           Panel1->Visible=true;
           else if(X>=200 && X<=599 && Y>=258 && Y<304)
           mStatus=msResults;
           else
           mStatus=msNone;
        } else if(mStatus==msNewGame){
           if(X>=200 && X<=599 && Y>=442 && Y<=488)
           mStatus=msNone;
           else if(X>=200 && X<=599 && Y>=166 && Y<212)
           {    Game.SetupLevel(Game.UserNumberLevels[0],0);Play=true; }
           else if(X>=200 && X<=599 && Y>=212 && Y<258)
           {    Game.SetupLevel(Game.UserNumberLevels[1],1);Play=true; }
           else if(X>=200 && X<=599 && Y>=258 && Y<304)
           {
           Game.SetupLevel(Game.UserNumberLevels[2],2); Timer1->Enabled=true;Play=true; }
           else                                                 mStatus=msNewGame;
        } else if(mStatus==msResults){
           if(X>=200 && X<=599 && Y>=442 && Y<=488)             mStatus=msNone;
           else                                                 mStatus=msResults;
        }else if(mStatus==msHelp){
           if(X>=200 && X<=599 && Y>=442 && Y<=488)             mStatus=msNone;
           else                                                 mStatus=msHelp;
        }else if(mStatus==msOptions){
           if(X>=200 && X<=599 && Y>=442 && Y<=488){
           mStatus=msNone;
           Timer2->Enabled=false;
           numbermusic=0;
           if(music){
              MediaPlayer1->FileName="music0.mid";
              MediaPlayer1->Open();
              MediaPlayer1->Play();
              MediaPlayer1->Tag=1;
           }else{
              if(MediaPlayer1->Tag){
                MediaPlayer1->Stop();
                MediaPlayer1->Tag=0;
              }
           }
           Timer2->Enabled=true;
           }
           else if(X>=200 && X<=599 && Y>=166 && Y<212)         sound=!sound;
           else if(X>=200 && X<=599 && Y>=212 && Y<258)         music=!music;
           else                                                 mStatus=msOptions;

        }else if(mStatus==msAbout){
           if(X>=200 && X<=599 && Y>=442 && Y<=488)             mStatus=msNone;
           else                                                 mStatus=msAbout;
        }
        }else{
           if(X>=600 && X<=800 && Y>=57 && Y<=96)               Game.SelectBall=(X-600)/39;
           else if(X>=600  && Y>=470 && Y<526)                  {Timer1->Enabled=!Timer1->Enabled;}
           else if(X>=600  && Y>=526 && Y<582)
           {
              Play=false;
              Game.BreakGame();
           }
           if(X>=0 && X<=599)                                   {  Game.SelectColomn=X/39;  Game.PlayGame();  }

        }
        if(sound)
          sndPlaySound("выбор.wav", SND_SYNC);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
       if(!Play) {
           if(X>=200 && X<=599 && Y>=442 && Y<488)                  mPos=mpExit;
           else if(X>=200 && X<=599 && Y>=396 && Y<442)             mPos=mpOptions;
           else if(X>=200 && X<=599 && Y>=350 && Y<396)             mPos=mpAbout;
           else if(X>=200 && X<=599 && Y>=304 && Y<350)             mPos=mpHelp;
           else if(X>=200 && X<=599 && Y>=166 && Y<212)             mPos=mpNewGame;
           else if(X>=200 && X<=599 && Y>=212 && Y<258)             mPos=mpSelectUser;
           else if(X>=200 && X<=599 && Y>=258 && Y<304)             mPos=mpResults;
           else                                                     mPos=mpNone;
       }else{
          if(X>=600  && Y>=470 && Y<526)                            mPos=mpNewGame;
          else if(X>=600  && Y>=526 && Y<582)                       mPos=mpExit;
          else                                                      mPos=mpNone;
       }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawObjects()
{
    glNewList(startoflist, GL_COMPILE);
      glPushMatrix();
      glBindTexture(GL_TEXTURE_2D, background);            // This Will Select The BG Maps...
      glTranslatef(0.0f, 0.0f, -24.0f);
      glBegin(GL_QUADS);
      glNormal3f( 0.0f, 0.0f, 1.0f);
      glColor3f(1,1,1);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-70.0, -50.0,  0.0);
      glTexCoord2f(1.0f, 0.0f); glVertex3f( 70.0, -50.0,  0.0);
      glTexCoord2f(1.0f, 1.0f); glVertex3f( 70.0,  50.0,  0.0);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-70.0,  50.0,  0.0);
      glEnd();
      glPopMatrix();
    glEndList();
    glNewList(startoflist+1, GL_COMPILE);
        glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glColor3f(0.8,0.8,0.8); glVertex3f(-30,-30,-2);
        glColor3f(0.5,0.5,0.5); glVertex3f(+30,-30,-2);
        glColor3f(0.8,0.8,0.8); glVertex3f(+30,+30,-2);
        glColor3f(1.0,1.0,1.0); glVertex3f(-30,+30,-2);
        glEnd();
        
     glEndList();
     glNewList(startoflist+2, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("PolyLines 1.1");
         glColor3f(0,0,0);
         glRasterPos2f(-26,15);          glPrint("Играть");
         glRasterPos2f(-26,8);           glPrint("Пользователь");
         glRasterPos2f(-26,1);           glPrint("Рекорды");
         glRasterPos2f(-26,-6);          glPrint("Помощь");
         glRasterPos2f(-26,-13);         glPrint("О программе");
         glRasterPos2f(-26,-20);         glPrint("Опции");
         glRasterPos2f(-26,-27);         glPrint("Выход");
     glEndList();
     glNewList(startoflist+3, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("Играть");
         glColor3f(0,0,0);
         glRasterPos2f(-26,15);          glPrint("Путешествие");
         glRasterPos2f(-26,8);           glPrint("Головоломка");
         glRasterPos2f(-26,1);           glPrint("На время");
         glRasterPos2f(-26,-27);         glPrint("Возврат");
     glEndList();
     glNewList(startoflist+4, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("Пользователь");
         glColor3f(0,0,0);
         glRasterPos2f(-26,15);          glPrint("Новый");
         glRasterPos2f(-26,-27);         glPrint("Возврат");
     glEndList();
     glNewList(startoflist+5, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("Рекорды");
         glColor3f(0,0,0);
         glRasterPos2f(-26,-27);         glPrint("Возврат");
     glEndList();
     glNewList(startoflist+6, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("Помощь");
         glColor3f(0,0,0);
         glRasterPos2f(-26,-27);         glPrint("Возврат");
     glEndList();
     glNewList(startoflist+7, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("О программе");
         glColor3f(0,0,0);
         glRasterPos2f(-26,-27);         glPrint("Возврат");
     glEndList();
     glNewList(startoflist+8, GL_COMPILE);
         glColor3f(1,0,0);
         glRasterPos2f(-26,25);
         glPrint("Опции");
         glColor3f(0,0,0);
         glRasterPos2f(-10,15);          glPrint("Звук");
         glRasterPos2f(-10,8);           glPrint("Музыка");
         glRasterPos2f(-26,-27);         glPrint("Возврат");
     glEndList();
     glNewList(startoflist+9, GL_COMPILE);
        glBegin(GL_QUADS);
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glColor3f(0.8,0.8,0.8); glVertex3f(30,-50,-2);
        glColor3f(0.5,0.5,0.5); glVertex3f(70,-50,-2);
        glColor3f(0.8,0.8,0.8); glVertex3f(70,+30,-2);
        glColor3f(1.0,1.0,1.0); glVertex3f(30,+30,-2);
        glEnd();
     glEndList();
     GLUquadricObj *BlueSphere = gluNewQuadric();
     glNewList(startoflist + 10, GL_COMPILE);
        glPushMatrix();
        gluQuadricTexture(BlueSphere, GL_TRUE);
        glRotatef(-80, 1.0, 0.0, 0.0);
        gluSphere(BlueSphere, 3, 15,15);
        glPopMatrix();
     glEndList();
}

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
        if(!Game.NewUser(Users->Text.c_str(),Password->Text.c_str()))
        {
          if(!Game.SelectUser(Users->Text.c_str(),Password->Text.c_str()))
            MessageBox(0,"Пароль неверный","System error",MB_ICONSTOP);
          else
            Panel1->Visible=false;
        }
        else
        {
          Users->Items->Add(Users->Text);
          if(!Game.SetupLevel(0,0))
            MessageBox(0,"Уровень не найден","Error",MB_ICONSTOP);
          else
            Panel1->Visible=false;
        }
      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        Game.NextTime();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
        HDC hDCScreen = GetDC(NULL);
        Herz = GetDeviceCaps(hDCScreen, VREFRESH);
        W=Screen->Width;
        H=Screen->Height;
        ReleaseDC(NULL, hDCScreen);
        DEVMODE DM;
        DM.dmSize = sizeof(DEVMODE);
        DM.dmBitsPerPel = 32; // глубина цвета, бит на пиксель
        DM.dmPelsWidth = 800; // разрешение по горизонтали
        DM.dmPelsHeight = 600; // разрешение по вертикали
        DM.dmFields = DM_BITSPERPEL + DM_PELSWIDTH + DM_PELSHEIGHT + DM_DISPLAYFREQUENCY;
        DM.dmDisplayFrequency = Herz; // частота обновления экрана
        ChangeDisplaySettings(&DM, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        AnsiString str;
        str.sprintf("music%d.mid",numbermusic);
        switch(numbermusic){
          case 0: Timer2->Interval=1*60000+28000; break;
          case 1: Timer2->Interval=3*60000+ 8000; break;
          case 2: Timer2->Interval=2*60000+48000; break;
        }
        if(music){
          MediaPlayer1->FileName=str;
          MediaPlayer1->Open();
          MediaPlayer1->Play();
        }
        numbermusic++;
        if(numbermusic>2)
          numbermusic=0;
}
//---------------------------------------------------------------------------

