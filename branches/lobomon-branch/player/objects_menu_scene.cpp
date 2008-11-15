/*objects_menu_scene.cpp, objects My_menu scene routines.
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

void Inventory_scene::init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team)
{
    My_team     = the_team;
    My_audio    = the_audio;

    int k = ((My_team->get_num_items() - 1) / 2);// S.O.S.!!!
    My_menu.init(the_audio, run, 1, k, 320, 210, 0, 30);
    My_description.init(320,30,0,0);
    int i = 0, space = 16, block_size = 150;
    char string_buffer[255];
    for (i = 0; i < My_team->get_num_items(); i++)
    {
        string_vector.push_back( (const char *) (My_team->get_item_name(i)) );
        sprintf(string_buffer, "%d ", (*My_team->get_items_number(i)));
        My_menu.add_text(string_buffer, block_size - 10 + ((block_size + 10) * ((i) % (2))), 5 + ((i / 2) * space));
    }

    if (string_vector.size() % 2)   //to avoid game freezes
        {
        string_vector.push_back(" ");
    }

    while (string_vector.size()<2)//to avoid game freezes if there's nothing
    {
        string_vector.push_back(" ");
    }
    My_menu.set_commands(& string_vector);
    running     = run;
    new_scene   = the_scene;
    delay       = 0;
}

void Inventory_scene::update(SDL_Surface*screen)
{
    //en los menus no se necesitnatantos refrescos
    delay++;
    if (delay == 4)
    {
        My_menu.draw(screen);
        My_description.draw(screen);
        delay   = 0;
    }
}

void Inventory_scene::action()
{
    My_team->select = My_menu.get_index_y() * 2 + My_menu.get_index_x();
    if (My_team->select < My_team->get_num_items())
    {
        *new_scene = 10;
    }
    else
    {
        My_menu.restart_menu();
    }
}

void Inventory_scene::update_key()
{
    My_menu.update_key();
    if (My_menu.decision())
    {
        action();
    }
    if (key_pressed_and_released(KEY_X))
    {
        (*My_audio).sound_load("Sound/Cansel2.wav");
        *new_scene = 4;
    }
}
void Inventory_scene::dispose()
{
    My_menu.dispose();
    My_description.dispose();
}
