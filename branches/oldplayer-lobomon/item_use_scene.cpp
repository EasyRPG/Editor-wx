/*item_use_scene.cpp, item use scene routines.
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

void Item_use_scene::init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team)
{
    int i;
    My_team = the_team;
    My_audio = the_audio;
    players.init(the_audio, run,0,(My_team->get_size()-1),184,240,136,0,124,48);
    players.init_xy_cur(55,5); //ya eran muchos comandos
    players.visible = true;
    item_win.init(136,30,0,0);
    item_win2.init(136,30,0,30);

    char string_buffer[255];
    i = My_team->select;
    item_win.add_text((My_team->get_item_name(i)) ,5,5);
    sprintf(string_buffer, "Own objects %d", (*My_team->get_items_number(i)));
    item_win2.add_text(string_buffer,5,5);
    running =  run;
    new_scene = the_scene;

    int space = 60;

    for (i = 0;i<My_team->get_size();i++)
    {
        players.add_sprite((My_team->get_faceset(i)),5,5+(i*space));
        players.add_text((My_team->get_name(i)),55,2+(i*space));

        sprintf(string_buffer, "Level %d ", (*My_team->get_level(i)));
        players.add_text(string_buffer,55,20+(i*space));
        players.add_text("Normal",55,37+(i*space));
        sprintf(string_buffer, "HP %d / %d", (*My_team->get_hp(i)), (*My_team->get_max_hp(i)));
        players.add_text(string_buffer,110,20+(i*space));
        sprintf(string_buffer, "MP %d / %d", (*My_team->get_mp(i)), (*My_team->get_max_mp(i)));
        players.add_text(string_buffer,110,37+(i*space));
    }

    delay = 0;
}

void Item_use_scene::update(SDL_Surface*screen)
{
    if (delay == 0)
    {
        SDL_FillRect(screen, NULL, 0x0);// Clear screen
        item_win.draw(screen);
        players.draw(screen);
        item_win2.draw(screen);
    }

    delay++;

    if (delay == 5)
    {
        item_win.draw(screen);
        players.draw(screen);
        item_win2.draw(screen);
        delay = 1;
    }
}

void Item_use_scene::action()
{
    int     i;
    char    string_buffer[255];
    i=My_team->select;
    (*My_team->get_items_number(i))=(*My_team->get_items_number(i))-1;

    if ((*My_team->get_items_number(i)) !=0)
    {
        item_win2.dispose();
        item_win2.init(136,30,0,30);
        sprintf(string_buffer, "Own objects %d", (*My_team->get_items_number(i)));
        item_win2.add_text(string_buffer,5,5);
        players.restart_menu();
    }
    else
    {
        My_team->erase_item(i);
        *new_scene = 5;
    }


}

void Item_use_scene::update_key()
{
    if (players.visible)
    {
        players.update_key();

        if (players.decision())
        {
            action();
        }
    }

    if (key_pressed_and_released(KEY_X ))//retorna alos objetos
    {
        (*My_audio).sound_load("Sound/cancel.wav");
        *new_scene = 5;
    }
}

void Item_use_scene::dispose()
{
    players.dispose();
    item_win.dispose();
    item_win2.dispose();
}
