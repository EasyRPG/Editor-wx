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

void Euip_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
   menu.init( theaudio, run, 0,3, 190, 105, 130, 30);
   Armas.init( theaudio, run, 1,1, 320, 105, 0, 135);
   descripcion.init(320,30,0,0);
   stats.init(130,105,0,30);
   str_Vector.push_back("Espada ");
   str_Vector.push_back("Escudo ");
   str_Vector.push_back("Casco");
   str_Vector.push_back("Armadura");
   menu.setComands(& str_Vector);
   Armas.setComands(& str_Vector);
   running=  run;   
   NScene=TheScene;
}

void Euip_Menu_Scene::update(SDL_Surface* Screen)
{  
   menu.draw(Screen);
   Armas.draw(Screen);
   stats.draw(Screen);
   descripcion.draw(Screen);          
}

void Euip_Menu_Scene::action()
{ 
  /* if(menu.getindexY()==2)
  * running =false;
   if(menu.getindexY()==0)
    * NScene=1;     */        
}

void Euip_Menu_Scene::updatekey() {
menu.updatekey();
     if(menu.desition())
     action();
 if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=4; }
     }
void Euip_Menu_Scene::dispose() {
menu.dispose();
Armas.dispose();
descripcion.dispose();
stats.dispose();
}
