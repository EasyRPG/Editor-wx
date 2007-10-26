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

void Main_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
   menu.init( theaudio, run, 0,5, 96, 125, 0, 0);
   players.init(224,240,96,0);
   gold.init(96,40,0,200);
   menu_exit.init( theaudio, run, 0,2, 96, 67, 112, 86);
   str_Vector.push_back("Objetos ");
   str_Vector.push_back("Técnicas ");
   str_Vector.push_back("Equipamiento");
   str_Vector.push_back("Estados");
   str_Vector.push_back("Guardar");
   str_Vector.push_back("Fin partida");
   menu.setComands(& str_Vector);
   str_Vector_2.push_back("Ir a titulo");
   str_Vector_2.push_back("Salir");
   str_Vector_2.push_back("Cancelar");
   menu_exit.setComands(& str_Vector_2);
   menu_exit.visible=false; 
   running=  run;   
   NScene=TheScene;
}

void Main_Menu_Scene::update(SDL_Surface* Screen)
{   
   menu.draw(Screen);
   players.draw(Screen);
   gold.draw(Screen);
   menu_exit.draw(Screen);      
}

void Main_Menu_Scene::action()
{ int i;
     for(i=0;i<5;i++)
     if(menu.getindexY()==i)
    * NScene=i+5;  
if(menu.getindexY()==5)
   menu_exit.visible=true; 
}
void Main_Menu_Scene::action2()
{ 
if(menu_exit.getindexY()==0)
 * NScene=0;  
if(menu_exit.getindexY()==1)
(*running)=false;
if(menu_exit.getindexY()==2)
    { menu_exit.visible=false; 
    menu_exit.restarmenu();
    menu.restarmenu();
    }
}
void Main_Menu_Scene::updatekey() {
if(menu_exit.visible)
{
menu_exit.updatekey();
if(menu_exit.desition())
action2();
}else{
menu.updatekey();
if(menu.desition())
{action();}
}
 if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=1; }
     }
void Main_Menu_Scene::dispose() {
   menu.dispose();
   players.dispose();
   gold.dispose();
   menu_exit.dispose();       
}
