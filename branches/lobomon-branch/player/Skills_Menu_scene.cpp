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

void Skills_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
   menu.init( theaudio, run, 1,1, 320, 180, 0, 60);
   descripcion.init(320,30,0,0);
   descripcion2.init(320,30,0,30);
   str_Vector.push_back("Habilidad 1 ");
   str_Vector.push_back("Habilidad 2 ");
   str_Vector.push_back("Habilidad 3");
   str_Vector.push_back("Habilidad 4");
   menu.setComands(& str_Vector);
   running=  run;   
   NScene=TheScene;
}

void Skills_Menu_Scene::update(SDL_Surface* Screen)
{   int i,j;
   menu.draw(Screen);
   descripcion.draw(Screen); 
   descripcion2.draw(Screen);          
}

void Skills_Menu_Scene::action()
{ 
  /* if(menu.getindexY()==2)
  * running =false;
   if(menu.getindexY()==0)
    * NScene=1;     */        
}

void Skills_Menu_Scene::updatekey() {
menu.updatekey();
     if(menu.desition())
     action();
 if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=4; }
     }
void Skills_Menu_Scene::dispose() {
   menu.dispose();
   descripcion.dispose(); 
   descripcion2.dispose();   
     }
