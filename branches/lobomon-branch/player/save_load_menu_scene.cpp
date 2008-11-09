/*save_load_menu_scene.cpp, save load My_menu routines.
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

///a quedado perfessto
void Save_load_scene::init(Audio *the_audio, bool *run, Uint8 *the_scene, Player_team *the_team)
{
    My_team     = the_team;
    My_audio    = the_audio;

    description.init(320,30,0,0);
    description.add_text("¿Where do you want save game? ",10,5);
    Save_pos_1.init(320,70,0,30);
    Save_pos_2.init(320,70,0,100);
    Save_pos_3.init(320,70,0,170);
    running     = run;
    new_scene   = the_scene;
    delay       = 0;
}

void Save_load_scene::update(SDL_Surface*screen)
{
    delay++;
    if (delay == 6)
    {
        Save_pos_1.draw(screen);
        Save_pos_2.draw(screen);
        Save_pos_3.draw(screen);
        description.draw(screen);
        delay = 0;
    }
}

void Save_load_scene::update_key()
{
    if (key_pressed_and_released(KEY_X ))
    {
        (*My_audio).sound_load("../Sound/Cansel2.wav");
        *new_scene = 4;
    }
}
void Save_load_scene::dispose()
{
    Save_pos_1.dispose();
    Save_pos_2.dispose();
    Save_pos_3.dispose();
    description.dispose();
}
