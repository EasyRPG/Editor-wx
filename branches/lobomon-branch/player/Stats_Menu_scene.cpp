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

void Stats_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
    Status.init(230,80,90,0); 
    Status_vit.init(230,80,90,80); 
    Profesion.init(230,80,90,160); 
    Aramas.init(90,240,0,0); 
   running=  run;   
   NScene=TheScene;
}

void Stats_Menu_Scene::update(SDL_Surface* Screen)
{ 
   Status.draw(Screen); 
  Status_vit.draw(Screen); 
  Profesion.draw(Screen);  
   Aramas.draw(Screen);          
}

void Stats_Menu_Scene::updatekey() {
 if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=4; }
     }
void Stats_Menu_Scene::dispose() {
   Status.dispose(); 
   Status_vit.dispose(); 
   Profesion.dispose();  
   Aramas.dispose();         
     }
