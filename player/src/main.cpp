/* main.cpp, EasyRPG player main file.
Copyright (C) 2007 EasyRPG Project <http://easyrpg.sourceforge.net/>.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.*/

#include <vector>
#include <string>
#include "tools/math-sll.h"
#include "tools/audio.h"
#include "tools/CDeltaTime.h"
#include "tools/control.h"
#include "tools/font.h"
#include "tools/key.h"
#include "tools/tools.h"
#include "tools/Timer.h"
#include "sprites/chipset.h"
#include "sprites/sprite.h"
#include "control/Batle_scene.h"
#include "control/GameOver_scene.h"
#include "control/Map_scene.h"
#include "control/scene.h"
#include "control/Title_scene.h"
#include "interface/Control/Equip_Menu_scene.h"
#include "interface/Control/Item_use_scene.h"
#include "interface/Control/Main_Menu_scene.h"
#include "interface/Control/Objects_Menu_scene.h"
#include "interface/Control/Save_Load_Menu_scene.h"
#include "interface/Control/Skills_Menu_scene.h"
#include "interface/Control/Stats_Menu_scene.h"
#include "readers/iniparser.h"
#include "readers/map.h"
#include "attributes/CActor.h"
#include "attributes/Enemy.h"
#include "attributes/item.h"
#include "attributes/Player.h"
#include "attributes/skill.h"

#define SCREEN_SIZE_X 320
#define SCREEN_SIZE_Y 240

bool running = true;
unsigned char TheScene = 0;
Mix_Music *musica;
SDL_Surface *Screen;
unsigned char speed = 4, timer = 0;
Scene *actual;
Map_Scene mapas;
Title_Scene titulo;
GO_Scene fin;
Save_Load_Menu_Scene Menu_Save_Load;
Equip_Menu_Scene Menu_Euip;
Main_Menu_Scene Menu_Main;
Objects_Menu_Scene Menu_Objects;
Stats_Menu_Scene Menu_Stats;
Skills_Menu_Scene Menu_Skills;
Item_use_scene Menu_item_use;
Batle_scene batalla;
Player_Team team;
CDeltaTime System(60);
bool Fullscreen;
Timer update;
Timer fps;

void CalculateFPS()
{
    static unsigned long nextTicks = 0, fps = 0, frames = 0;
    frames++;
    if ( SDL_GetTicks() > nextTicks )
    {
        fps = frames;
        frames = 0;
        nextTicks = SDL_GetTicks() + 1000;

        printf("Map test - FPS %lu /n \n", fps);
        //SDL_WM_SetCaption (stringBuffer, NULL);
    }
}

int fps_sincronizar()
{
    static unsigned int frames = 0;
    int tiempodesignado, tiempotrascurrido, framesideales, retraso;
    frames++;
    if ((update.get_ticks() > 1000 ) || (frames == 60))
    {
        frames = 0;
        update.start();
        fps.start();
    }
    else
    {
        tiempodesignado = (1000 - update.get_ticks()) / (60 - frames);
        tiempotrascurrido = fps.get_ticks();
        if (tiempotrascurrido < tiempodesignado)
        {
            SDL_Delay(tiempodesignado - tiempotrascurrido);
            fps.start();
            return 1;
        }
        else
        {
            framesideales = update.get_ticks() / 17;
            retraso = framesideales - frames;
            fps.start();
            if (retraso >= 1)
            {
                frames = frames + retraso;
                return (1 + retraso);
            }
        }
    }
    return 1;
}

void CambioScene(Audio *myaudio, Scene **apuntador)
{
    unsigned static char LastScene = 0;
    if (TheScene != LastScene)
    {
        (*apuntador)->dispose();
        if (TheScene == 0)
        {
            Control::set_delay_default();
            titulo.init(myaudio, &running, &TheScene, &team);
            *apuntador = &titulo;
            LastScene = 0;
        }
        if (TheScene == 1)
        {
            mapas.init(myaudio, 320, 240, &TheScene, &team);
            *apuntador = &mapas;
            LastScene=1;
        }
        if (TheScene==2)
        {
            Control::set_delay_default();
            batalla.init(myaudio, &running, &TheScene, &team);
            *apuntador = &batalla;
            LastScene = 2;
        }
        if (TheScene == 3)
        {
            Control::set_delay_default();
            fin.init(myaudio, &running, &TheScene, &team);
            *apuntador = &fin;
            LastScene = 3;
        }
        if (TheScene == 4)
        {
            Control::set_delay_default();
            Menu_Main.init(myaudio, &running, &TheScene, &team);
            *apuntador = &Menu_Main;
            LastScene = 4;
        }
        if (TheScene == 5)
        {
            Control::set_delay_default();
            Menu_Objects.init(myaudio, &running, &TheScene, &team);
            *apuntador = &Menu_Objects;
            LastScene = 5;
        }
        if (TheScene == 6)
        {
            Control::set_delay_default();
            Menu_Skills.init(myaudio, &running, &TheScene, &team);
            *apuntador = &Menu_Skills;
            LastScene = 6;
        }
        if (TheScene == 7)
        {
            Control::set_delay_default();
            Menu_Euip.init(myaudio, &running, &TheScene, &team);
            *apuntador= &Menu_Euip;
            LastScene = 7;
        }
        if (TheScene == 8)
        {
            Control::set_delay_default();
            Menu_Stats.init(myaudio, &running, &TheScene, &team);
            *apuntador = &Menu_Stats;
            LastScene = 8;
        }
        if (TheScene == 9)
        {
            Control::set_delay_default();
            Menu_Save_Load.init(myaudio, &running, &TheScene, &team);
            *apuntador = &Menu_Save_Load;
            LastScene = 9;
        }
        if (TheScene == 10)
        {
            Control::set_delay_default();
            Menu_item_use.init(myaudio, &running, &TheScene, &team);
            *apuntador = &Menu_item_use;
            LastScene = 10;
        }
    }
}

#ifdef PSP
extern "C"
#endif
int main(int argc, char *argv[])
{
    #ifdef PSP
    freopen("stdout", "w", stdout);
    freopen("stderr", "w", stderr);
    #endif
    Music myaudio;
    int repxciclo,i;
    dictionary *ini;
    // ===[ INITIALIZATION ]================================================
    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
    {
        exit(1);//mod
    }
    atexit (SDL_Quit);
    SDL_ShowCursor(SDL_DISABLE);
    myaudio.init();
    const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo();
    unsigned  long flags = 0;

    flags |= SDL_SWSURFACE;

    Screen = SDL_SetVideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16, flags);
    if (Screen == NULL)
    {
        exit(2);
    }

    ini = iniparser_new("RPG_RT.ini");
    SDL_WM_SetCaption (iniparser_getstring(ini, "RPG_RT:GameTitle", "Untitled"), NULL);
    iniparser_free(ini);

    Control::set_keys();

    // ===[ ENTRY POINT ]===================================================

//	SDL_Event event;
    titulo.init(&myaudio, &running, &TheScene, &team);

    actual = &titulo;
    update.start();
    fps.start();

    while (running)
    {
        timer++;
        // Check for events
       repxciclo = fps_sincronizar();
        for (i = 0; i < repxciclo; i++)
         {
            Control::update_keys();
            System.update(); //updates delta
            actual->updatekey();
         }
        actual->update(Screen);

        CambioScene(&myaudio, &actual);

        SDL_Flip(Screen); // Flip
        CalculateFPS();
        //SDL_Delay(100);

    }

    Control::cleanup();

    SDL_Quit();

    #ifdef PSP
    fclose(stdout);
    fclose(stderr);
    #endif

    return 0;
}
