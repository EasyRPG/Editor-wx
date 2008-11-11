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

///a quedado perfessto

void Game_over_scene::init(Audio *the_audio, bool *run, Uint8 *the_scene, Player_team *the_team)
{
    My_team     = the_team;
    My_team->clear_team();
    My_team->clear_objects();
    My_audio    = the_audio;
    (*My_audio).music_load("../Music/2003sorrow.mid");
    title.x_pos     = 0;
    title.y_pos     = 0;
    title.set_image("../GameOver/gameover.png");
    running     = run;
    new_scene   = the_scene;
}

void Game_over_scene::update(SDL_Surface *screen)
{
    title.draw(screen);
}

void Game_over_scene::action()
{
    *new_scene = 0;
}

void Game_over_scene::update_key()
{

    Uint8 *key_data;
    static int delay = 0;
    delay++;
    if (delay == 40)
    {
        key_data = SDL_GetKeyState(NULL);
        if ( key_data[SDLK_ESCAPE] )
        {
            *running = false;
        }

        if ( key_data[KEY_Z]  )
        {
            action();
        }
        delay = 0;
    }
}
void Game_over_scene::dispose()
{
    title.dispose();
}
