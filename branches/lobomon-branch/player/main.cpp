/*main.cpp, EasyRPG player main file.
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

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_rotozoom.h"
#include "SDL_mixer.h"
#include "tools.h"
#include "map.h"
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "skill.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "actor.h"
#include "scene.h"
#include "timer.h"
#include "deltatime.h"
#include <iostream>

//Uint64 nextTicks = 0, fps = 0, frames = 0;
//char stringBuffer[255];

/* For convenience, we have to use (while we find another thing better) this conventions for make the
    development more readable and faster:
    -Data names in accurate english
    -Tabs instead of spaces.
    -ANSI compatible code.
    -Names_like_this.
    -Class names start with big letter, methods and variable names with small letters.
    -Doxygen compatible comments. ( http://www.stack.nl/~dimitri/doxygen/ )
    -Will add more (plus examples) later~
*/


//Variables

Uint8           speed = 4;
Uint8           timer = 0;
bool running    = true;
Uint8 the_scene = 0;
Mix_Music       *music;
SDL_Surface     *screen;
bool            wind;
Timer           update;
Timer           fps;


//  Gameplay scene instances
Title_scene             My_title_scene;
Save_load_scene         My_save_load_scene;     // Save_And_Load_Menu_Scene could be confusing and bothering
Scene                   *My_actual_scene;
Map_scene               My_map_scene;
Battle_scene            My_battle_scene;

//My_menu scene instances
Main_menu_scene         My_main_menu_scene;
Game_over_scene         My_gameover_scene;
Equipment_scene         My_equipment_scene;
Item_use_scene          My_items_use_scene;
Status_scene            My_status_scene;
Skills_menu_scene       My_skills_scene;
Inventory_scene         My_inventory_scene;
//  Misc instances
Player_team             My_team;
Delta_time              My_system_time(60);

int fps_synchronyze()
{
    static Uint32 frames    = 0 ;                     //  frames measurer
    int base_time, passed_time, ideal_frames, delay;    //  data related with time control
    frames++;
    if ((update.get_ticks() > 1020 ) || (frames == 60))
    {
        frames = 0;
        update.start();
        fps.start();
    }
    else
    {
        base_time =  (( 1020 - update.get_ticks()) / (60 - frames));
        passed_time = fps.get_ticks();

        if (passed_time < base_time)
        {
            SDL_Delay(base_time - passed_time);
            fps.start();
            return 1;
        }
        else
        {
            ideal_frames = update.get_ticks() / 17;//   frames that we had to be refreshed
            delay = ideal_frames - frames;
            fps.start();
            if (delay >= 1)   //  if there are more than one delay frame:
            {
                frames = frames+delay;
                //	System.update(); //to-delta updates
                return (1 + delay); //  it refreshes more input and output
            }
        }
    }
    return 1;
}


void change_scene(Audio My_audio, Scene **pointer) //si no haces esto, te cartgas la memoria donde lo estas ejecutando
{
    Uint8 last_scene = 0;
    if (the_scene != last_scene)
    {
        //  if someone finds a better way to do it please warn me -_-
        (**pointer).dispose();
        if (the_scene == 0)
        {
            My_title_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer = &My_title_scene;
            last_scene = 0;
        }
        if (the_scene == 1)
        {
            My_map_scene.init (&My_audio, 320, 240, &the_scene, &My_team);
            *pointer = &My_map_scene;
            last_scene = 1;
        }
        if (the_scene == 2)
        {
            My_battle_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer =& My_battle_scene;
            last_scene = 2;
        }
        if (the_scene == 3)
        {
            My_gameover_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer =& My_gameover_scene;
            last_scene = 3;
        }
        if (the_scene == 4)
        {
            My_main_menu_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer =& My_main_menu_scene;
            last_scene = 4;
        }
        if (the_scene == 5)
        {
            My_inventory_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer =& My_inventory_scene;
            last_scene = 5;
        }
        if (the_scene == 6)
        {
            My_skills_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer = &My_skills_scene;
            last_scene = 6;
        }
        if (the_scene == 7)
        {
            My_equipment_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer = &My_equipment_scene;
            last_scene = 7;
        }
        if (the_scene == 8)
        {
            My_status_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer = &My_status_scene;
            last_scene = 8;
        }

        if (the_scene == 9)
        {
            My_save_load_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer = &My_save_load_scene;
            last_scene = 9;
        }
        if (the_scene == 10)
        {
            My_items_use_scene.init(&My_audio, &running, &the_scene, &My_team);
            *pointer=&My_items_use_scene;
            last_scene = 10;
        }
    }
}

int main()
{
    Audio   My_audio;
    int     repeat_x_cicle;
    int     i;

    //============[ INITIALIZATION ]================

    // Start SDL
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
    {
        exit(1);
    }
    atexit (SDL_Quit);
    My_audio.init();
    const SDL_VideoInfo    *video_info = SDL_GetVideoInfo();
    Uint64 flags            = 0;

    if (video_info -> hw_available)
    {
        flags |= SDL_HWSURFACE;
    }
    else
    {
        flags |= SDL_SWSURFACE;
    }
    if (video_info -> blit_hw)
    {
        flags |= SDL_HWACCEL;
    }
    //flags |= SDL_FULLscreen;

    // Start screen (set to 320x240)
    screen = SDL_SetVideoMode (320, 240, 16, flags);
    if (screen == NULL)
    {
        exit(2);
    }
    SDL_WM_SetCaption ("Window title pending", NULL);

    //============[ ENTRY POINT ]====================

    SDL_Event   event;
    My_title_scene.init(&My_audio, &running, &the_scene, &My_team);
    My_actual_scene = &My_title_scene;
    update.start();
    fps.start();

    while (running)
    {
        timer++;

        // Check for events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if ( event.key.keysym.sym == SDLK_RETURN )
                {
                    if (wind)
                    {
                        screen = SDL_SetVideoMode( 320, 240, 16, SDL_SWSURFACE | SDL_RESIZABLE  );
                        wind = false;
                    }
                    else
                    {
                        screen = SDL_SetVideoMode( 320, 240, 16, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );
                        wind = true;
                    }
                    break;
                }
            default:
                break;
            }
        }
        repeat_x_cicle = fps_synchronyze ();

        // SDL_FillRect(screen, NULL, 0x0);// Nonsenseless Clear screen

        for (i = 0; i < repeat_x_cicle; i++)    //  Inputs to keyboard reading
        {
            My_system_time.update();    //  Updates to deltas
            My_actual_scene->update_key( );
        }

        My_actual_scene -> update(screen);
        change_scene(My_audio, &My_actual_scene);
        SDL_Flip(screen);   //  Flip
    }
    SDL_Quit();
    return 0;
}

