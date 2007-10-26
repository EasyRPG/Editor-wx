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

void Title_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
    // 
     (*myaudio).musicload("../Music/2003wingtoskies.mid");
     title.x=0;
	 title.y=0;
     title.setimg("../title/title2.png");
     menu.init( myaudio, run, 0,2, 96, 67, 115, 115);
     str_Vector.push_back("Nuevo ");
     str_Vector.push_back("Cargar ");
     str_Vector.push_back("Salir ");
     menu.setComands(& str_Vector);
     running=  run;   
     NScene=TheScene;
}

void Title_Scene::update(SDL_Surface* Screen)
{   int i,j;
    title.draw(Screen);
    menu.draw(Screen);
            
}

void Title_Scene::action()
{ 
   if(menu.getindexY()==2)
  * running =false;
   if(menu.getindexY()==0)
    * NScene=1;             
}

void Title_Scene::updatekey() {
 menu.updatekey();
     if(menu.desition())
     action();
}
void Title_Scene::dispose() {
title.dispose();
menu.dispose();
(*myaudio).stopmusic();
}
