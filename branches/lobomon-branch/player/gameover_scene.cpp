/* gameover_scene.cpp, gameover scene routines.
   Copyright (C) 2007 EasyRPG Project <http://easyrpg.sourceforge.net/>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "math-sll.h"
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "map.h"
#include "skill.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "actor.h"
#include "scene.h"

void GO_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene,Player_Team * TheTeam)
{    myteam=TheTeam;
   (*myteam).clear_team();
   (*myteam).clear_obj();
     myaudio=theaudio;
     (*myaudio).musicload("../Music/2003sorrow.mid");
     title.x=0;
	 title.y=0;
     title.setimg("../GameOver/gameover.png"); 
     running=  run;   
     NScene=TheScene;
}

void GO_Scene::update(SDL_Surface* Screen)
{  
  title.draw(Screen);
}

void GO_Scene::action()
{ 
    * NScene=0;             
}

 void GO_Scene::updatekey() {

  unsigned char * keyData;
  static int delay=0;  
  delay++;
    if(delay==40)
    {
          keyData = SDL_GetKeyState(NULL);
            if ( keyData[SDLK_ESCAPE] ) * running = false;

        if ( keyData[LMK_Z]  ) {
         action();	
           }
  delay=0;
    }    
 }
void GO_Scene::dispose() {
title.dispose();
}
