/*skills_menu_scene.cpp, skills My_menu scene routines.
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

void Skills_menu_scene::init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team)
{
    My_team = the_team;
    My_audio = the_audio;
    int j;
    j=(*My_team).select;

    int k=(((*My_team).get_skill_size(j)-1)/2);

    My_menu.init( the_audio, run, 1,k, 320, 180, 0, 60);
    description.init(320,30,0,0);
    description2.init(320,30,0,30);

    int i;
    int space = 16,block_size = 150;
    char string_buffer[255];
    sprintf(string_buffer, " NV  %d  Normal  Hp %d / %d Mp %d / %d  ", (*(*My_team).get_level(j)), (*(*My_team).get_hp(j)), (*(*My_team).get_max_hp(j)), (*(*My_team).get_mp(j)), (*(*My_team).get_max_mp(j)));
    description2.add_text(((*My_team).get_name(j)),10,5);
    description2.add_text(string_buffer,80,5);

    for (i = 0;i<(*My_team).get_skill_size(j);i++)
    {
        string_vector.push_back( (const char *) ((*My_team).get_skill_name(j,i)) );
        sprintf(string_buffer, "%d ", (*((*My_team).get_skill_mp_price(j,i))));
        My_menu.add_text(string_buffer,block_size-10+((block_size+10)*((i)%(2))),5+((i/2)*space));
    }
    if (string_vector.size()%2)    //  this is for avoid errors if it's null
    {
        string_vector.push_back( " " );
    }

    while (string_vector.size()<2) //  this is for avoid error if there's nothing
    {
        string_vector.push_back( " " );
    }
    My_menu.set_commands(& string_vector);
    running      =  run;
    new_scene    = the_scene;
    delay        = 0;
}

void Skills_menu_scene::update(SDL_Surface*screen)
{
    if (delay == 0)
    {
        My_menu.draw(screen);
        description.draw(screen);
        description2.draw(screen);
    }
    delay++;
    if (delay == 5)
    {
        My_menu.draw(screen);
        description.draw(screen);
        delay = 1;
    }
}

void Skills_menu_scene::action()
{
    /*if(My_menu.get_index_y()==2)
    *running = false;
     if(My_menu.get_index_y()==0)
      *new_scene = 1;     */
}

void Skills_menu_scene::update_key()
{
    My_menu.update_key();
    if (My_menu.decision())
    {
        action();
    }
    if (key_pressed_and_released(KEY_X ))
    {
        (*My_audio).sound_load("../Sound/Cansel2.wav");
        *new_scene = 4;
    }
}
void Skills_menu_scene::dispose()
{
    My_menu.dispose();
    description.dispose();
    description2.dispose();
}
