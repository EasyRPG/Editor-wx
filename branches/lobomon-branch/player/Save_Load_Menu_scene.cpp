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

void Save_Load_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
  
   descripcion.init(320,30,0,0);
   Save_pos_1.init(320,70,0,30);
   Save_pos_2.init(320,70,0,100);
   Save_pos_3.init(320,70,0,170);
   running=  run;   
   NScene=TheScene;
}

void Save_Load_Menu_Scene::update(SDL_Surface* Screen)
{  int i,j;
   Save_pos_1.draw(Screen);
   Save_pos_2.draw(Screen);
   Save_pos_3.draw(Screen);
   descripcion.draw(Screen);          
}

void Save_Load_Menu_Scene::updatekey() {
  if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=4; }
     }
void Save_Load_Menu_Scene::dispose() {
   Save_pos_1.dispose();
   Save_pos_2.dispose();
   Save_pos_3.dispose();
   descripcion.dispose(); 
}
