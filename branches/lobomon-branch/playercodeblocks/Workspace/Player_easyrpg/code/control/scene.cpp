#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "../sprites/sprite.h"
#include "../tools/key.h"
#include "../tools/font.h"
#include "../tools/audio.h"
#include "../sprites/map.h"
#include <vector>
#include <string>
#include "../atributes/skill.h"
#include "../atributes/item.h"
#include "../atributes/Enemy.h"
#include "../atributes/Player.h"
#include "../tools/math-sll.h"
#include "../atributes/CActor.h"
#include "scene.h"
#define Size_of_font 16

/*Scene::~Scene()
{
}
Scene::Scene()
{
}*/

void Menu_Easy::init(Audio * theaudio, bool * run,int X,int Y) {
     myaudio=theaudio;
     desided=false;
     maxindexY=Y;
     maxindexX=X;
     delay=0;
     running=  run;
     }
bool Menu_Easy::desition(){
     return (desided);
     }

void Menu_Easy::restarmenu(){
     desided=false;
     delay=0;
     indexY=0;
     indexX=0;
   //  (*myaudio).freesound();
    }

int Menu_Easy::getindexY(){
    return (indexY);
    }

int Menu_Easy::getindexX(){
    return (indexX);
    }

void Menu_Easy::updatekey() {
  static unsigned char * keyData;
  static unsigned char Last_key;

  delay++;

  if (desided==false)
    if(delay==4)
        {
         keyData = SDL_GetKeyState(NULL);
        if ( keyData[SDLK_ESCAPE] )* running = false;

        if ( keyData[SDLK_LEFT]  ) {
        indexX--;
       // (*myaudio).soundload("../Sound/Cursor1.wav");
        }
        if ( keyData[SDLK_RIGHT] ) {indexX++;
       // (*myaudio).soundload("../Sound/Cursor1.wav");
        }
        if ( keyData[SDLK_UP]    ) {
             indexY--;
       // (*myaudio).soundload("../Sound/Cursor1.wav");
        }
        if ( keyData[SDLK_DOWN]  ) {
             indexY++;
       // (*myaudio).soundload("../Sound/Cursor1.wav");
        }


        if (( keyData[LMK_Z]  )&&(Last_key!=LMK_Z)) {
         //  (*myaudio).soundload("../Sound/Decision2.wav");
           Last_key=LMK_Z;
            desided= true;

           }
        if ((!keyData[LMK_Z])&&(Last_key==LMK_Z)){

               Last_key=0;
             }
        if (indexX<0)
        indexX=maxindexX;
        if (indexX>maxindexX)
        indexX=0;
        if (indexY<0)
        indexY=maxindexY;
        if (indexY>maxindexY)
        indexY=0;
        delay=0;
    }
 }

void Window_Base::init(int SizeX,int SizeY,int PosX,int PosY)
{    System.init_Sistem();
     System.setimg("../System/system.png");
     tapiz.set_surface(System.Exdraw(SizeX,SizeY));
     tapiz.x=PosX;
	 tapiz.y=PosY;
	 fuente.init_Font();
     pos_X=PosX;
     pos_Y=PosY;
     Size_X=SizeX;
     Size_Y=SizeY;
     disposing=false;
     visible=true;
}
void Window_Base::dispose()
{    disposing=true;
     System.dispose();
     tapiz.dispose();
     text.dispose();
     int i,tp;
     tp=(V_Sprite).size();
     for (i = 0; i < tp; i ++)
     (V_Sprite).pop_back();
     tp=(Vtext_Sprite).size();
     for (i = 0; i < tp; i ++)
     (Vtext_Sprite).pop_back();
}
void Window_Base::add_text(const char * ctext, int x, int y)
{
 text.x=pos_X+x;
 text.y=pos_Y+y;
 text.set_surface(fuente.drawText(ctext));
 Vtext_Sprite.push_back(text);
}
void Window_Base::add_sprite(Sprite * the_sprite, int x, int y)
{
 (*the_sprite).x=pos_X+x;
 (*the_sprite).y=pos_Y+y;
 V_Sprite.push_back((int)the_sprite);
}
void Window_Base::draw(SDL_Surface* Screen)
{
if(visible)
if(  !disposing  )
{
tapiz.draw(Screen);
unsigned int i;
for (i = 0; i < (Vtext_Sprite).size(); i ++)
{
 ((Vtext_Sprite).at(i)).draw(Screen);
} Sprite * the_sprite;
for (i = 0; i < (V_Sprite).size(); i ++)
{ the_sprite=(Sprite *)((V_Sprite).at(i));
 (*the_sprite).draw(Screen);
}
}
}
void Window_Select::init(Audio * theaudio, bool * run,int ComandX,int ComandY,int SizeX,int SizeY,int PosX,int PosY)
{
     menu.init( theaudio,run,ComandX,ComandY);
     System.init_Sistem();
     System.setimg("../System/system.png");
     tapiz.set_surface(System.Exdraw(SizeX,SizeY));
     tapiz.x=PosX;
	 tapiz.y=PosY;
	 fuente.init_Font();
      pos_X=PosX;
      pos_Y=PosY;
      Size_X=SizeX;
      Size_Y=SizeY;
	  Comand_X=ComandX;
      Comand_Y=ComandY;
      visible=true;
Size_of_Block=((Size_X-10)/(ComandX+1))-5*ComandX;
cursor.set_surface(System.Cube_select(1,Size_of_Block,16));
cursor.x=PosX+5;
cursor.y=PosY+5;
disposing=false;
Init_text_X=10;
on_use=true;
 }

 void Window_Select::add_text(const char * ctext, int x, int y)
{
 text.x=pos_X+x;
 text.y=pos_Y+y;
 text.set_surface(fuente.drawText(ctext));
 Vtext_Sprite.push_back(text);
}
void Window_Select::dispose()
{    disposing=true;
     int i,tp;
     System.dispose();
     cursor.dispose();
     tapiz.dispose();
  //   text.dispose();

     tp=(* My_vector).size();
     for (i = 0; i < tp; i ++)
     (* My_vector).pop_back();

     tp=(My_Sprite).size();
     for (i = 0; i < tp; i ++)
     (My_Sprite).pop_back();
     tp=(Vtext_Sprite).size();
     for (i = 0; i < tp; i ++)
     (Vtext_Sprite).pop_back();

}
bool Window_Select::desition(){
     return (menu.desition());
     }

void Window_Select::restarmenu(){

 menu.restarmenu();
    }

int Window_Select::getindexY(){
    return (menu.getindexY());
    }

int Window_Select::getindexX(){
    return (menu.getindexX());
    }

void Window_Select::updatekey() {
if(visible)
if(on_use)
  menu.updatekey();
}

void Window_Select::set_posx_text(int x) {
   Init_text_X=x;
}


void Window_Select::setComands(vector <std::string> * str_Vec)
{
My_vector=str_Vec;
unsigned int i;
std::string strd;
for (i = 0; i < (*My_vector).size(); i ++)
{
strd = (*My_vector).at(i);
text.set_surface(fuente.drawText(strd.c_str()));
My_Sprite.push_back(text);
}

}

void Window_Select::draw(SDL_Surface* Screen)
 {
unsigned int i;
int j;
int offset=0;
if(!disposing)
if(visible)
{
tapiz.draw(Screen);
int Max_to_show= ((Size_Y-20)/Size_of_font);//los que caben
if(Max_to_show>Comand_Y){Max_to_show=Comand_Y;}

if(getindexY()>Max_to_show)
  { offset=getindexY()-Max_to_show;
     System.draw(Screen,25, (pos_X+ Size_X/2-8), (pos_Y+3));//flechas
     System.draw(Screen,26, (pos_X+ Size_X/2), (pos_Y+3));//flechas
  }
   else
   {offset=0;}

if((Comand_Y!=getindexY())&&(Max_to_show<Comand_Y))
 {    System.draw(Screen,45, (pos_X+ Size_X/2-8), (pos_Y+Size_Y-11));//flechas
     System.draw(Screen,46, (pos_X+ Size_X/2), (pos_Y+Size_Y-11));}//flechas

cursor.y=pos_Y+(getindexY()-offset)*Size_of_font+5;
cursor.x=pos_X+(getindexX())*Size_of_Block+10*getindexX()+5;
cursor.draw(Screen);
for (j = offset; j <= ((Max_to_show+offset+1)*(Comand_X+1)-1); j ++)  //comandos
{
    (My_Sprite.at(j)).x=pos_X+Init_text_X;
    if(Comand_X!=0)
    {
    (My_Sprite.at(j)).x= (My_Sprite.at(j)).x+((Size_of_Block+10)*((j)%(Comand_X+1)));
    (My_Sprite.at(j)).y=((pos_Y+5)+((j-offset)/(Comand_X+1))*Size_of_font);}
    else
    (My_Sprite.at(j)).y=((pos_Y+5)+((j-offset)*Size_of_font));
    (My_Sprite.at(j)).draw(Screen);
}

for (i = 0; i < (Vtext_Sprite).size(); i ++) //textoadiconal
{
 ((Vtext_Sprite).at(i)).draw(Screen);
}


}

}


void Window_Player_Select::init(Audio * theaudio, bool * run,int ComandX,int ComandY,int SizeX,int SizeY,int PosX,int PosY,int curX,int curY)
{
     menu.init( theaudio,run,ComandX,ComandY);
     System.init_Sistem();
     System.setimg("../System/system.png");
     tapiz.set_surface(System.Exdraw(SizeX,SizeY));
     tapiz.x=PosX;
	 tapiz.y=PosY;
	 fuente.init_Font();
     Size_of_Block=((Size_X-10)/(ComandX+1))-5*ComandX;
      cursor.set_surface(System.Cube_select(1,curX,curY));
      Moves_cursorY=curY+12;
      cursor.x=PosX+5;
      cursor.y=PosY+5;
      disposing=false;
      pos_X=PosX;
      pos_Y=PosY;
      Size_X=SizeX;
      Size_Y=SizeY;
	  Comand_X=ComandX;
      Comand_Y=ComandY;
      Cur_pos_X=5;
      Cur_pos_Y=5;
      visible=false;//del cursor
      visible_window=true;//de la ventana
 }
void Window_Player_Select::init_curXY(int x,int y) {
      Cur_pos_X=x;
      Cur_pos_Y=y;
}

void Window_Player_Select::set_curY(int y) {
      Cur_pos_Y=y;
}
 void Window_Player_Select::add_text(const char * ctext, int x, int y)
{
 text.x=pos_X+x;
 text.y=pos_Y+y;
 text.set_surface(fuente.drawText(ctext));
 Vtext_Sprite.push_back(text);

}
void Window_Player_Select::dispose()
{    disposing=true;
     int i,tp;
     System.dispose();
     cursor.dispose();
     tapiz.dispose();
     tp=(V_Sprite).size();
     for (i = 0; i < tp; i ++)
     (V_Sprite).pop_back();
     tp=(Vtext_Sprite).size();
     for (i = 0; i < tp; i ++)
     (Vtext_Sprite).pop_back();
     restarmenu();
}
bool Window_Player_Select::desition(){
     return (menu.desition());
     }

void Window_Player_Select::restarmenu(){

 menu.restarmenu();
    }

int Window_Player_Select::getindexY(){
    return (menu.getindexY());
    }

int Window_Player_Select::getindexX(){
    return (menu.getindexX());
    }

void Window_Player_Select::updatekey() {
if(visible)
  menu.updatekey();
}

void Window_Player_Select::add_sprite(Sprite * the_sprite, int x, int y)
{
 (*the_sprite).x=pos_X+x;
 (*the_sprite).y=pos_Y+y;
 V_Sprite.push_back((int)the_sprite);
}

void Window_Player_Select::draw(SDL_Surface* Screen)
 {
unsigned int i;
int offset=0;
if(visible_window)
if(!disposing)

{
tapiz.draw(Screen);

int Max_to_show= ((Size_Y-20)/Size_of_font);//los que caben
if(Max_to_show>Comand_Y){Max_to_show=Comand_Y;}

if(getindexY()>Max_to_show)
  { offset=getindexY()-Max_to_show;
     System.draw(Screen,25, (pos_X+ Size_X/2-8), (pos_Y+3));//flechas
     System.draw(Screen,26, (pos_X+ Size_X/2), (pos_Y+3));//flechas
  }
else
   {offset=0;}


if((Comand_Y!=getindexY())&&(Max_to_show<Comand_Y))
 {    System.draw(Screen,45, (pos_X+ Size_X/2-8), (pos_Y+Size_Y-11));//flechas
     System.draw(Screen,46, (pos_X+ Size_X/2), (pos_Y+Size_Y-11));}//flechas

if(visible)
{
cursor.y=pos_Y+(getindexY()-offset)*Moves_cursorY+Cur_pos_Y;
cursor.x=pos_X+(getindexX())*Size_of_Block+10*getindexX()+Cur_pos_X;
cursor.draw(Screen);
}

for (i = 0; i < (Vtext_Sprite).size(); i ++)  //texto adicional
{
 ((Vtext_Sprite).at(i)).draw(Screen);
}

Sprite * the_sprite;//dibujo de imagenes
for (i = 0; i < (V_Sprite).size(); i ++)
{ the_sprite=(Sprite *)((V_Sprite).at(i));
 (*the_sprite).draw(Screen);
}

}

}
