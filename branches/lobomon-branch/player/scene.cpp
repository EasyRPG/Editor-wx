#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "map.h"
#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"
#include "scene.h"
#define Size_of_font 16
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
     (*myaudio).freesound();
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
        (*myaudio).soundload("../Sound/Cursor1.wav");
        }
        if ( keyData[SDLK_RIGHT] ) {indexX++;
        (*myaudio).soundload("../Sound/Cursor1.wav");
        }
        if ( keyData[SDLK_UP]    ) {
             indexY--;
        (*myaudio).soundload("../Sound/Cursor1.wav");
        }
        if ( keyData[SDLK_DOWN]  ) {
             indexY++;
        (*myaudio).soundload("../Sound/Cursor1.wav");
        }		


        if (( keyData[LMK_Z]  )&&(Last_key!=LMK_Z)) {
           (*myaudio).soundload("../Sound/Decision2.wav"); 
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
}
void Window_Base::dispose()
{System.dispose();
tapiz.dispose();
}
 void Window_Base::draw(SDL_Surface* Screen)
 { tapiz.draw(Screen);
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
     SDL_Surface * ms;
int i;     

Size_of_Block=((Size_X-10)/(ComandX+1))-5*ComandX;
int amask = 0x000000ff;
ms = SDL_CreateRGBSurface(SDL_SWSURFACE, (Size_of_Block), 16, 16,0, 0,0, amask);
 
      for (i = 0; i < (Size_of_Block/8); i ++)
                   System.draw(ms,10, ((8*i)+5),0);//20
      for (i = 0; i < (Size_of_Block/8); i ++)
                   System.draw(ms,69, ((8*i)+5),8);
       System.draw(ms,8, 0,0);
       System.draw(ms,11, (Size_of_Block-8),0);
       System.draw(ms,68, 0,8);
       System.draw(ms,71,(Size_of_Block-8) , 8);
cursor.set_surface(ms);
cursor.x=PosX+5;
cursor.y=PosY+5;
 }
void Window_Select::dispose()
{int i;
System.dispose();
cursor.dispose();
tapiz.dispose();

//for (i = 0; i < (*My_vector).size(); i ++)  
//(My_Sprite.at(i)).dispose();
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
  menu.updatekey();   
}


void Window_Select::setComands(vector <std::string> * str_Vec)
{My_vector=str_Vec;
int i;
std::string strd;  
for (i = 0; i < (*My_vector).size(); i ++)  
{ 
strd = (*My_vector).at(i);       
text.set_surface(fuente.drawText(strd.c_str()));
My_Sprite.push_back(text);
}
   
}

void Window_Select::draw(SDL_Surface* Screen)
 {int i,offset=0;

if(visible)
{  
tapiz.draw(Screen);
cursor.draw(Screen);
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

for (i = offset; i <= ((Max_to_show+offset+1)*(Comand_X+1)-1); i ++)  
{
    (My_Sprite.at(i)).x=pos_X+10;
    if(Comand_X!=0)
    {
    (My_Sprite.at(i)).x= (My_Sprite.at(i)).x+((Size_of_Block+10)*((i)%(Comand_X+1)));
    (My_Sprite.at(i)).y=((pos_Y+5)+((i-offset)/(Comand_X+1))*Size_of_font);}
    else
    (My_Sprite.at(i)).y=((pos_Y+5)+((i-offset)*Size_of_font));
    (My_Sprite.at(i)).draw(Screen);
}

}

}
