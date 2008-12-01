/*scene.cpp, scene routines.
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
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "map.h"
#include "skill.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "math-sll.h"
#include "actor.h"
#include "scene.h"
#define font_size 16
#include <iostream>

void Easyrpg_menu::init(Audio *the_audio, bool *run, int x_pos,int y_pos)
{

    My_audio    = the_audio;
    decided     = false;
    max_index_y = y_pos;
    max_index_x = x_pos;
    repeat      = false;
    running     = run;
}
bool Easyrpg_menu::decision()
{
    return (decided);
}

void Easyrpg_menu::restart_menu()
{
    decided     = false;
    delay       = 0;
    index_y     = 0;
    index_x     = 0;
    //  (*My_audio).freesound();
}

int Easyrpg_menu::get_index_y()
{
    return (index_y);
}

int Easyrpg_menu::get_index_x()
{
    return (index_x);
}

void Easyrpg_menu::update_key()
{
    static Uint8 *key_data;
    static Uint8 last_key;

    if (decided == false)
    {

        {
            key_data = SDL_GetKeyState(NULL);

            if ( key_data[SDLK_ESCAPE] ) *running = false;

            if ( key_data[SDLK_LEFT]  )
            {
                index_x--;
                // (*My_audio).sound_load("Sound/Cursor1.wav");
            }
            if ( key_data[SDLK_RIGHT] )
            {
                index_x++;
                // (*My_audio).sound_load("Sound/Cursor1.wav");
            }
            if (key_data[SDLK_UP])
            {
                index_y--;
                // (*My_audio).sound_load("Sound/Cursor1.wav");
            }
            if (key_data[SDLK_DOWN])
            {
                index_y++;
                // (*My_audio).sound_load("Sound/Cursor1.wav");
            }


            if ((key_data[KEY_Z]) && (last_key != KEY_Z))
            {
               //   (*My_audio).sound_load("Sound/Decision2.wav");
                last_key = KEY_Z;
                decided = true;

            }
            if (index_x < 0)
            {
                index_x = max_index_x;
            }
            if (index_x > max_index_x)
            {
                index_x = 0;
            }
            if (index_y < 0)
            {
                index_y = max_index_y;
            }
            if (index_y > max_index_y)
            {
                index_y = 0;
            }
        }
    }
}

void Window_base::init(int the_x_size,int the_y_size,int the_x_pos,int the_y_pos)
{
    visible     = true;

    My_sprite_system.init_video_system();
    My_sprite_system.set_image("System/system.png");
    My_texture.set_surface(My_sprite_system.ex_draw(the_x_size,the_y_size));
    my_font.init_font();

    x_pos               = the_x_pos;
    y_pos               = the_y_pos;
    x_size              = the_x_size;
    y_size              = the_y_size;
    My_texture.x_pos    = x_pos;
    My_texture.y_pos    = y_pos;

    disposing   = false;
}
void Window_base::dispose()
{
    My_sprite_system.dispose();
    My_texture.dispose();
    text.dispose();
    int i;
    int dispose;
    text_dispose=(v_sprite).size();
    for (i = 0; i < text_dispose; i ++)
    {
        (v_sprite).pop_back();
    }
    text_dispose = (sprite_text).size();
    for (i = 0; i < text_dispose; i ++)
    {
        (sprite_text).pop_back();
        disposing = true;
    }
}

void Window_base::add_text(const char *ctext, int the_x_pos, int the_y_pos)
{
    text.x_pos = the_x_pos+x_pos;
    text.y_pos = the_y_pos+y_pos;
    text.set_surface(my_font.draw_text(ctext));
    sprite_text.push_back(text);
}

void Window_base::add_sprite(Sprite *the_sprite, int the_x_pos, int the_y_pos)
{
    the_sprite->x_pos = the_x_pos+x_pos;
    the_sprite->y_pos = the_y_pos+y_pos;
    v_sprite.push_back((int)the_sprite);
}

void Window_base::draw(SDL_Surface *screen)
{
    if (visible)
        if (!disposing)
        {
            My_texture.draw(screen);
            Uint32 i;
            for (i = 0; i < (sprite_text).size(); i ++)
            {
                ((sprite_text).at(i)).draw(screen);
            }
            Sprite *the_sprite;
            for (i = 0; i < (v_sprite).size(); i ++)
            {
                the_sprite = (Sprite *)(v_sprite.at(i));    //  S.O.S
                the_sprite->draw(screen);
            }
        }
}
void Window_select::init(Audio *the_audio, bool *run,int the_x_command,int the_y_command, int the_x_size, int the_y_size, int the_x_pos, int the_y_pos)
{
    My_menu.init(the_audio, run, x_command, y_command);
    My_sprite_system.init_video_system();
    My_sprite_system.set_image("System/system.png");
    My_texture.set_surface(My_sprite_system.ex_draw(the_x_size,the_y_size));
    My_texture.x_pos    = the_x_pos;
    My_texture.y_pos    = the_y_pos;
    my_font.init_font();
    x_pos               = the_x_pos;
    y_pos               = the_y_pos;
    x_size              = the_x_size;
    y_size              = the_y_size;
    x_command           = the_x_command;
    y_command           = the_y_command;
    visible             = true;
    block_size          = ((x_size - 10) / (x_command + 1)) - 5 * x_command;
    cursor.set_surface(My_sprite_system.cube_select(1,block_size,16));
    cursor.x_pos        = the_x_pos+5;
    cursor.y_pos        = the_y_pos+5;
    disposing           = false;
    init_x_text         = 10;
    on_use              = true;

}

void Window_select::add_text(const char *ctext, int the_x_pos, int the_y_pos)
{
    text.x_pos      = the_x_pos+x_pos;
    text.y_pos      = the_y_pos+y_pos;
    text.set_surface(my_font.draw_text(ctext));
    sprite_text.push_back(text);
}
void Window_select::dispose()
{
    int     i;
    int     text_dispose;
    My_sprite_system.dispose();
    cursor.dispose();
    My_texture.dispose();

    text_dispose=My_vector->size();
    for (i = 0; i < text_dispose; i ++)
        My_vector->pop_back();

    text_dispose=My_sprite.size();
    for (i = 0; i < text_dispose; i ++)
    {
        My_sprite.pop_back();
    }
    text_dispose=(sprite_text).size();
    for (i = 0; i < text_dispose; i ++)
        (sprite_text).pop_back();
    disposing       = true;

}
bool Window_select::decision()
{
    return (My_menu.decision());
}

void Window_select::restart_menu()
{

    My_menu.restart_menu();
}

int Window_select::get_index_y()
{
    return (My_menu.get_index_y());
}

int Window_select::get_index_x()
{
    return (My_menu.get_index_x());
}

void Window_select::update_key()
{
    if (visible)
        if (on_use)
            My_menu.update_key();
}

void Window_select::set_x_pos_text(int x_pos)
{
    init_x_text = x_pos;
}


void Window_select::set_commands(std::vector <std::string> *the_string_vector)
{
    My_vector = the_string_vector;
    Uint32 i;
    std::string strd;
    for (i = 0; i < My_vector->size(); i ++)
    {
        strd = My_vector->at(i);
        text.set_surface(my_font.draw_text(strd.c_str()));
        My_sprite.push_back(text);
    }
    

}

void Window_select::draw(SDL_Surface*screen)
{
    Uint32 i;
    int j;
    int offset = 0;
    if (!disposing)
        if (visible)
        {
            My_texture.draw(screen);
            int Max_to_show=((y_size - 20) / font_size);    // los que caben <<- translate
            if (Max_to_show>y_command)
            {
                Max_to_show = y_command;
            }

            if (get_index_y()>Max_to_show)
            {
                offset = get_index_y()-Max_to_show;
                My_sprite_system.draw(screen, 25, (x_pos + x_size / 2 - 8), (y_pos + 3));   //  arrows
                My_sprite_system.draw(screen, 26, (x_pos + x_size / 2), (y_pos + 3));       //  arrows
            }
            else
            {
                offset = 0;
            }

            if ((y_command != get_index_y()) && (Max_to_show < y_command))
            {
                My_sprite_system.draw(screen, 45, (x_pos + x_size / 2 - 8), (y_pos + y_size - 11));//   arrows
                My_sprite_system.draw(screen, 46, (x_pos + x_size / 2), (y_pos + y_size - 11));
            }//flechas

            cursor.y_pos = y_pos + (get_index_y() - offset) * font_size + 5;
            cursor.x_pos = x_pos + (get_index_x()) * block_size + 10 * get_index_x() + 5;
            cursor.draw(screen);
            for (j = offset; j <= ((Max_to_show + offset + 1) * (x_command + 1) - 1); j ++)  //    commands
            {
                (My_sprite.at(j)).x_pos = x_pos + init_x_text;
                if (x_command != 0)
                {
                    (My_sprite.at(j)).x_pos = (My_sprite.at(j)).x_pos+((block_size+10)*((j)%(x_command+1)));
                    (My_sprite.at(j)).y_pos = ((y_pos + 5) + ((j - offset) / (x_command + 1)) * font_size);
                }
                else
                {
                    (My_sprite.at(j)).y_pos = ((y_pos + 5) + ((j - offset) * font_size));
                }
                (My_sprite.at(j)).draw(screen);
            }

            for (i = 0; i < (sprite_text).size(); i++) //additional text
            {
                ((sprite_text).at(i)).draw(screen);
            }


        }

}


void Window_player_select::init(Audio *the_audio, bool *run,int the_x_command,int the_y_command,int the_x_size,int the_y_size,int the_x_pos,int the_y_pos,int the_cursor_x,int the_cursor_y)
{
    My_menu.init(the_audio, run, the_x_command, the_y_command);
    My_sprite_system.init_video_system();
    My_sprite_system.set_image("System/system.png");
    My_texture.set_surface(My_sprite_system.ex_draw(the_x_size,the_y_size));
    My_texture.x_pos    = the_x_pos;
    My_texture.y_pos    = the_y_pos;
    my_font.init_font();
    block_size          =((x_size - 10) / (the_x_command + 1)) - 5 * the_x_command;
    cursor.set_surface(My_sprite_system.cube_select(1, the_cursor_x, the_cursor_y));
    cursor_y_move       = the_cursor_y+12;
    cursor.x_pos        = the_x_pos+5;
    cursor.y_pos        = the_y_pos+5;
    disposing           = false;
    x_pos               = the_x_pos;
    y_pos               = the_y_pos;
    x_size              = the_x_size;
    y_size              = the_y_size;
    x_command           = the_x_command;
    y_command           = the_y_command;
    cursor_x            = 5;
    cursor_y            = 5;
    visible             = false;    //  from cursor
    visible_window      = true;     //  from window
}
void Window_player_select::init_xy_cur(int the_x_pos,int the_y_pos)
{
    cursor_x = the_x_pos;
    cursor_y = the_y_pos;
}

void Window_player_select::set_y_cursor(int the_y_pos)
{
    cursor_y = y_pos;
}
void Window_player_select::add_text(const char *ctext, int the_x_pos, int the_y_pos)
{
    text.x_pos = x_pos + the_x_pos;
    text.y_pos = y_pos + the_y_pos;
    text.set_surface(my_font.draw_text(ctext));
    sprite_text.push_back(text);

}
void Window_player_select::dispose()
{
    disposing       = true;
    int             i;
    int             text_dispose;

    My_sprite_system.dispose();
    cursor.dispose();
    My_texture.dispose();
    text_dispose    = (v_sprite).size();
    for (i = 0; i < text_dispose; i ++)
    {
        (v_sprite).pop_back();
    }
    text_dispose    = (sprite_text).size();
    for (i = 0; i < text_dispose; i ++)
    {
        (sprite_text).pop_back();
    }
    restart_menu();
}
bool Window_player_select::decision()
{
    return (My_menu.decision());
}

void Window_player_select::restart_menu()
{

    My_menu.restart_menu();
}

int Window_player_select::get_index_y()
{
    return (My_menu.get_index_y());
}

int Window_player_select::get_index_x()
{
    return (My_menu.get_index_x());
}

void Window_player_select::update_key()
{
    if (visible)
        My_menu.update_key();
}

void Window_player_select::add_sprite(Sprite *the_sprite, int the_x_pos, int the_y_pos)
{
    the_sprite->x_pos = x_pos + the_x_pos;
    the_sprite->y_pos = y_pos + the_y_pos;
    v_sprite.push_back((int)the_sprite);
}

void Window_player_select::draw(SDL_Surface*screen)
{
    Uint32      i;
    int         offset = 0;
    if (visible_window)
    {
        if (!disposing)

        {
            My_texture.draw(screen);

            int Max_to_show = ((y_size - 20) / font_size);//los que caben
            if (Max_to_show > y_command)
            {
                Max_to_show = y_command;
            }

            if (get_index_y() > Max_to_show)
            {
                offset = get_index_y()-Max_to_show;
                My_sprite_system.draw(screen, 25, (x_pos + x_size / 2 - 8), (y_pos + 3));  //arrows
                My_sprite_system.draw(screen, 26, (x_pos + x_size / 2), (y_pos + 3));    //arrows
            }
            else
            {
                offset = 0;
            }


            if ((y_command != get_index_y()) && (Max_to_show < y_command))
            {
                My_sprite_system.draw(screen, 45, (x_pos + x_size / 2 - 8), (y_pos+y_size - 11));   //arrows
                My_sprite_system.draw(screen, 46, (x_pos + x_size / 2), (y_pos + y_size - 11));
            }//flechas

            if (visible)
            {
                cursor.y_pos = x_pos+ (get_index_y() - offset) * cursor_y_move + cursor_y;
                cursor.x_pos = y_pos+ (get_index_x()) * block_size + 10 * get_index_x() + cursor_y;
                cursor.draw(screen);
            }

            for (i = 0; i < (sprite_text).size(); i ++)  //texto adicional
            {
                ((sprite_text).at(i)).draw(screen);
            }

            Sprite *the_sprite;//dibujo de imagenes
            for (i = 0; i < (v_sprite).size(); i ++)
            {
                the_sprite = (Sprite*)((v_sprite).at(i));
                the_sprite->draw(screen);
            }

        }

    }
}
