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

void Objects_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
   menu.init( theaudio, run, 1,2, 320, 210, 0, 30);
   descripcion.init(320,30,0,0);
   str_Vector.push_back("Posion ");
   str_Vector.push_back("Ether ");
   str_Vector.push_back("Revive");
   str_Vector.push_back("Posion ");
   str_Vector.push_back("Ether ");
   str_Vector.push_back("Revive");
   menu.setComands(& str_Vector);
   running=  run;   
   NScene=TheScene;
}

void Objects_Menu_Scene::update(SDL_Surface* Screen)
{   int i,j;
   menu.draw(Screen);
   descripcion.draw(Screen);          
}

void Objects_Menu_Scene::action()
{ 
  /* if(menu.getindexY()==2)
  * running =false;
   if(menu.getindexY()==0)
    * NScene=1;     */        
}

void Objects_Menu_Scene::updatekey() {
menu.updatekey();
     if(menu.desition())
     action();

 if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=4; }
     }
void Objects_Menu_Scene::dispose() {
   menu.dispose();
   descripcion.dispose();  
}
