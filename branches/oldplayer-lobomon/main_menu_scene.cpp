/*main_menu_scene.cpp, main My_menu scene routines.
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

void Main_menu_scene::init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team)
{
    int         i;
    My_team     = the_team;
    My_audio    = the_audio;
    My_menu.init( the_audio, run, 0, 5, 96, 125, 0, 0);
    players.init(the_audio, run, 0, (My_team->get_size()-1), 224, 240, 96, 0, 166, 48);
    players.init_xy_cur(55,5); //ya eran muchos comandos
    gold.init(96,40,0,200);
    menu_exit.init(the_audio, run, 0, 2, 96, 67, 112, 86);
    string_vector.push_back("Objects");
    string_vector.push_back("Skills");
    string_vector.push_back("Equipment");
    string_vector.push_back("States");
    string_vector.push_back("Save");
    string_vector.push_back("Exit game");
    My_menu.set_commands(&string_vector);
    string_vector_2.push_back("Go to title scene");
    string_vector_2.push_back("Exit");
    string_vector_2.push_back("Cancel");
    menu_exit.set_commands(& string_vector_2);
    menu_exit.visible   = false;
    running             = run;
    new_scene           = the_scene;

    gold.add_text("Gold",5,5);

    char string_buffer[255];
    sprintf(string_buffer, "$ %d", (*My_team->get_gold()));
    gold.add_text(string_buffer,5,20);
    int space   = 60;

    for (i = 0; i < My_team->get_size(); i++)
    {
        players.add_sprite((My_team->get_faceset(i)),5,5+(i*space));
        players.add_text((My_team->get_name(i)),55,2+(i*space));
        players.add_text((My_team->get_job(i)),150,2+(i*space));

        sprintf(string_buffer, "Level %d  Normal", (*My_team->get_level(i)));
        players.add_text(string_buffer, 55, 20 + (i*space));
        sprintf(string_buffer, "Exp %d / %d", (*My_team->get_exp(i)), (*My_team->get_max_exp(i)));
        players.add_text(string_buffer,55,37+(i*space));
        sprintf(string_buffer, "HP %d / %d", (*My_team->get_hp(i)), (*My_team->get_max_hp(i)));
        players.add_text(string_buffer,150,20+(i*space));
        sprintf(string_buffer, "MP %d / %d", (*My_team->get_mp(i)), (*My_team->get_max_mp(i)));
        players.add_text(string_buffer,150,37+(i*space));
    }
    delay   = 0;

}

void Main_menu_scene::update(SDL_Surface*screen)
{
    // static int delay = 0;
    if (delay == 0)
    {
        SDL_FillRect(screen, NULL, 0x0);// Clear screen
        gold.draw(screen);
        players.draw(screen);
        My_menu.draw(screen);
    }
    delay++;

    if (delay == 5)
    {
        players.draw(screen);
        My_menu.draw(screen);
        menu_exit.draw(screen);


        delay = 1;
    }
}

void Main_menu_scene::action()
{
    int i;
    for (i = 1; i < 4; i++)
        if (My_menu.get_index_y() == i)
        {
            players.visible = true;
        }
    if (My_menu.get_index_y() == 0)
        *new_scene = 5;
    if (My_menu.get_index_y()==4)
        *new_scene = 9;

    if (My_menu.get_index_y()==5)
        menu_exit.visible = true;
}
void Main_menu_scene::action2()
{
    if (menu_exit.get_index_y()==0)
        *new_scene = 0;
    if (menu_exit.get_index_y()==1)
        (*running)=false;
    if (menu_exit.get_index_y()==2)
    {
        menu_exit.visible = false;
        menu_exit.restart_menu();
        My_menu.restart_menu();
        delay = 0;
    }
}

void Main_menu_scene::action3()
{
    int i;
    My_team->select = players.get_index_y();
    for (i = 1;i<4;i++)
        if (My_menu.get_index_y()==i)
            *new_scene = 5+i;

}
void Main_menu_scene::update_key()
{
    if (players.visible)
    {
        players.update_key();
        if (players.decision())
            action3();
    }

    if (menu_exit.visible)
    {
        menu_exit.update_key();
        if (menu_exit.decision())
            action2();
    }
    else
    {
        My_menu.update_key();
        if (My_menu.decision())
        {
            action();
        }
    }
    if (key_pressed_and_released(KEY_X ))
    {
        (*My_audio).sound_load("Sound/cancel.wav");
        *new_scene = 1;
    }
}
void Main_menu_scene::dispose()
{
    My_menu.dispose();
    players.dispose();
    gold.dispose();
    menu_exit.dispose();
}
