/* objects_menu_scene.cpp, objects menu scene routines.
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

void Objects_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene,Player_Team * TheTeam)
{    myteam=TheTeam;
     myaudio=theaudio;
     
     int k =(((*myteam).get_num_items()-1)/2);
   menu.init( theaudio, run, 1,k, 320, 210, 0, 30);
   descripcion.init(320,30,0,0);
   int i=0,space=16,Size_of_Block=150;
   char stringBuffer[255];
   for(i=0;i<(*myteam).get_num_items();i++) 
  { 
  str_Vector.push_back( (const char *) ((*myteam).get_item_name(i)) );
   sprintf(stringBuffer, "%d ", (*(*myteam).get_NOI(i)));
   menu.add_text(stringBuffer,Size_of_Block-10+((Size_of_Block+10)*((i)%(2))),5+((i/2)*space));
  }

if(str_Vector.size()%2)//para que no truene si son nones
{ str_Vector.push_back( " " );
}

while(str_Vector.size()<2)//para que no truene si no hay nada
{ str_Vector.push_back( " " );
}
   menu.setComands(& str_Vector);
   running=  run;   
   NScene=TheScene;
   retardo=0;
}

void Objects_Menu_Scene::update(SDL_Surface* Screen)
{ //en los menus no se necesitnatantos refrescos
  retardo++;
   if(retardo==4)
   { 
   menu.draw(Screen);
   descripcion.draw(Screen);  
   retardo=0;
   }        
}

void Objects_Menu_Scene::action()
{ (*myteam).select=menu.getindexY()*2+menu.getindexX();
   if((*myteam).select <(*myteam).get_num_items())
   { * NScene=10; }else
   {menu.restarmenu();
   }           
}

void Objects_Menu_Scene::updatekey() {
menu.updatekey();
     if(menu.desition())
     action();

 if (Key_press_and_realsed(LMK_X ))
        {
        (*myaudio).soundload("../Sound/Cansel2.wav");
        * NScene=4; }
     }
void Objects_Menu_Scene::dispose() {
   menu.dispose();
   descripcion.dispose();  
}
