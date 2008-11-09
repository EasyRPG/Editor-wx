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
                // (*My_audio).sound_load("../Sound/Cursor1.wav");
            }
            if ( key_data[SDLK_RIGHT] )
            {
                index_x++;
                // (*My_audio).sound_load("../Sound/Cursor1.wav");
            }
            if (key_data[SDLK_UP])
            {
                index_y--;
                // (*My_audio).sound_load("../Sound/Cursor1.wav");
            }
            if (key_data[SDLK_DOWN])
            {
                index_y++;
                // (*My_audio).sound_load("../Sound/Cursor1.wav");
            }


            if ((key_data[KEY_Z]) && (last_key != KEY_Z))
            {
                //  (*My_audio).sound_load("../Sound/Decision2.wav");
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

void Window_Base::init(int the_x_size,int the_y_size,int x_pos,int y_pos)
{
    My_sprite_system.init_video_system();
    My_sprite_system.set_image("../System/system.png");
    My_texture.set_surface(My_sprite_system.Exdraw(the_x_size,the_y_size));
    My_texture.x_pos = x_pos;
    My_texture.y_pos = y_pos;
    my_font.init_font();
    pos_X = x_pos;
    pos_Y = y_pos;
    x_size = the_x_size;
    Size_Y = the_y_size;
    disposing = false;
    visible = true;
}
void Window_Base::dispose()
{
    disposing = true;
    My_sprite_system.dispose();
    My_texture.dispose();
    text.dispose();
    int i,tp;
    tp=(v_sprite).size();
    for (i = 0; i < tp; i ++)
        (v_sprite).pop_back();
    tp=(sprite_text).size();
    for (i = 0; i < tp; i ++)
        (sprite_text).pop_back();
}
void Window_Base::add_text(const char *ctext, int x_pos, int y_pos)
{
    text.x_pos = pos_X+x_pos;
    text.y_pos = pos_Y+y_pos;
    text.set_surface(my_font.draw_text(ctext));
    sprite_text.push_back(text);
}
void Window_Base::add_sprite(Sprite *the_sprite, int x_pos, int y_pos)
{
    (*the_sprite).x_pos = pos_X+x_pos;
    (*the_sprite).y_pos = pos_Y+y_pos;
    v_sprite.push_back((int)the_sprite);
}
void Window_Base::draw(SDL_Surface*screen)
{
    if (visible)
        if (  !disposing  )
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
                the_sprite=(Sprite *)((v_sprite).at(i));
                (*the_sprite).draw(screen);
            }
        }
}
void Window_Select::init(Audio *the_audio, bool *run,int the_x_command,int the_y_command, int the_x_size, int the_y_size, int the_x_pos, int the_y_pos)
{
    menu.init(the_audio, run, x_command, y_command);
    My_sprite_system.init_video_system();
    My_sprite_system.setimg("../System/system.png");
    My_texture.set_surface(System.Exdraw(the_x_size,the_y_size));
    My_texture.x    =the_x_pos;
    My_texture.y    =the_y_pos;
    my_font.init_font();
    x_pos           =the_x_pos;
    y_pos           =the_y_pos;
    x_size          =the_x_size;
    y_size          =the_y_size;
    x_command       =the_x_command;
    y_command       =the_y_command;
    visible         =true;
    block_size      =((x_size - 10) / (x_command + 1)) - 5 * x_command;
    cursor.set_surface(My_sprite_system.Cube_select(1,block_size,16));
    cursor.x        =the_x_pos+5;
    cursor.y        =the_y_pos+5;
    disposing       = false;
    init_x_text     = 10;
    on_use          = true;

}

void Window_Select::add_text(const char *ctext, int the_x_pos, int the_y_pos)
{
    text.x_pos      = the_x_pos+x_pos;
    text.y_pos      = the_y_pos+y_pos;
    text.set_surface(my_font.draw_text(ctext));
    sprite_text.push_back(text);
}
void Window_Select::dispose()
{
    disposing       = true;
    int i,aux_size;
    My_sprite_system.dispose();
    cursor.dispose();
    My_texture.dispose();
    //   text.dispose();

    tp=(*My_vector).size();
    for (i = 0; i < tp; i ++)
        (*My_vector).pop_back();

    tp=(My_Sprite).size();
    for (i = 0; i < tp; i ++)
        (My_Sprite).pop_back();
    tp=(sprite_text).size();
    for (i = 0; i < tp; i ++)
        (sprite_text).pop_back();

}
bool Window_Select::decision()
{
    return (My_menu.decision());
}

void Window_Select::restart_menu()
{

    My_menu.restart_menu();
}

int Window_Select::get_index_y()
{
    return (My_menu.get_index_y());
}

int Window_Select::get_index_x()
{
    return (My_menu.get_index_x());
}

void Window_Select::update_key()
{
    if (visible)
        if (on_use)
            My_menu.update_key();
}

void Window_Select::set_x_pos_text(int x_pos)
{
    Init_text_X = x_pos;
}


void Window_Select::set_commands(vector <std::string> *str_Vec)
{
    My_vector = str_Vec;
    Uint32 i;
    std::string strd;
    for (i = 0; i < (*My_vector).size(); i ++)
    {
        strd=(*My_vector).at(i);
        text.set_surface(my_font.draw_text(strd.c_str()));
        My_Sprite.push_back(text);
    }

}

void Window_Select::draw(SDL_Surface*screen)
{
    Uint32 i;
    int j;
    int offset = 0;
    if (!disposing)
        if (visible)
        {
            My_texture.draw(screen);
            int Max_to_show=((Size_Y-20)/font_size);//los que caben
            if (Max_to_show>y_command)
            {
                Max_to_show = y_command;
            }

            if (get_index_y()>Max_to_show)
            {
                offset = get_index_y()-Max_to_show;
                My_sprite_system.draw(screen,25, (pos_X+ x_size/2-8), (pos_Y+3));//flechas
                My_sprite_system.draw(screen,26, (pos_X+ x_size/2), (pos_Y+3));//flechas
            }
            else
            {
                offset = 0;
            }

            if ((y_command!=get_index_y())&&(Max_to_show<y_command))
            {
                My_sprite_system.draw(screen,45, (pos_X+ x_size/2-8), (pos_Y+Size_Y-11));//flechas
                My_sprite_system.draw(screen,46, (pos_X+ x_size/2), (pos_Y+Size_Y-11));
            }//flechas

            cursor.y_pos = pos_Y+(get_index_y()-offset)*font_size+5;
            cursor.x_pos = pos_X+(get_index_x())*block_size+10*get_index_x()+5;
            cursor.draw(screen);
            for (j = offset; j <=((Max_to_show+offset+1)*(x_command+1)-1); j ++)  //comandos
            {
                (My_Sprite.at(j)).x_pos = pos_X+Init_text_X;
                if (x_command!=0)
                {
                    (My_Sprite.at(j)).x_pos=(My_Sprite.at(j)).x_pos+((block_size+10)*((j)%(x_command+1)));
                    (My_Sprite.at(j)).y_pos=((pos_Y+5)+((j-offset)/(x_command+1))*font_size);
                }
                else
                    (My_Sprite.at(j)).y_pos=((pos_Y+5)+((j-offset)*font_size));
                (My_Sprite.at(j)).draw(screen);
            }

            for (i = 0; i < (sprite_text).size(); i ++) //textoadiconal
            {
                ((sprite_text).at(i)).draw(screen);
            }


        }

}


void Window_Player_Select::init(Audio *the_audio, bool *run,int the_x_command,int the_y_command,int the_x_size,int the_y_size,int x_pos,int y_pos,int curX,int curY)
{
    My_menu.init( the_audio,run,the_x_command,the_y_command);
    My_sprite_system.init_Video_system();
    My_sprite_system.set_image("../My_sprite_system/system.png");
    My_texture.set_surface(My_sprite_system.Exdraw(the_x_size,the_y_size));
    My_texture.x_pos = x_pos;
    My_texture.y_pos = y_pos;
    my_font.init_font();
    block_size=((x_size-10)/(the_x_command+1))-5*the_x_command;
    cursor.set_surface(My_sprite_system.Cube_select(1,x_cursor,y_cursor));
    cursor_y_move = curY+12;
    cursor.x_pos = x_pos+5;
    cursor.y_pos = y_pos+5;
    disposing = false;
    pos_X = the_x_pos;
    pos_Y = the_y_pos;
    x_size = the_x_size;
    y_size = the_y_size;
    x_command = the_x_command;
    y_command = the_y_command;
    cur_pos_X = 5;
    cur_pos_Y = 5;
    visible = false;//del cursor
    visible_window = true;//de la ventana
}
void Window_Player_Select::init_xy_cur(int the_x_pos,int the_y_pos)
{
    cur_pos_X = the_x_pos;
    cur_pos_Y = the_y_pos;
}

void Window_Player_Select::cursor_y_set(int y_pos)
{
    cur_pos_Y = y_pos;
}
void Window_Player_Select::add_text(const char *ctext, int x_pos, int y_pos)
{
    text.x_pos = pos_X+x_pos;
    text.y_pos = pos_Y+y_pos;
    text.set_surface(my_font.draw_text(ctext));
    sprite_text.push_back(text);

}
void Window_Player_Select::dispose()
{
    disposing = true;
    int i, aux_size; //sos
    My_sprite_system.dispose();
    cursor.dispose();
    My_texture.dispose();
    aux_size=(v_sprite).size();
    for (i = 0; i < aux_size; i ++)
        (v_sprite).pop_back();
    aux_size=(sprite_text).size();
    for (i = 0; i < aux_size; i ++)
        (sprite_text).pop_back();
    restart_menu();
}
bool Window_Player_Select::decision()
{
    return (My_menu.decision());
}

void Window_Player_Select::restart_menu()
{

    My_menu.restart_menu();
}

int Window_Player_Select::get_index_y()
{
    return (My_menu.get_index_y());
}

int Window_Player_Select::get_index_x()
{
    return (My_menu.get_index_x());
}

void Window_Player_Select::update_key()
{
    if (visible)
        My_menu.update_key();
}

void Window_Player_Select::add_sprite(Sprite *the_sprite, int the_x_pos, int the_y_pos)
{
    (*the_sprite).x_pos = x_pos + the_x_pos;
    (*the_sprite).y_pos = y_pos + the_y_pos;
    v_sprite.push_back((int)the_sprite);
}

void Window_Player_Select::draw(SDL_Surface*screen)
{
    Uint32 i;
    int offset = 0;
    if (visible_window)
        if (!disposing)

        {
            My_texture.draw(screen);

            int Max_to_show=((y_size - 20) / font_size);//los que caben
            if (Max_to_show>y_command)
            {
                Max_to_show = y_command;
            }

            if (get_index_y()>Max_to_show)
            {
                offset = get_index_y()-Max_to_show;
                My_sprite_system.draw(screen,25, (x_pos + x_size / 2 - 8), (y_pos + 3));  //arrows
                My_sprite_system.draw(screen,26, (x_pos + x_size / 2), (y_pos + 3));    //arrows
            }
            else
            {
                offset = 0;
            }


            if ((y_command != get_index_y()) && (Max_to_show < y_command))
            {
                My_sprite_system.draw(screen, 45, (pos_X + x_size / 2 - 8), (y_pos+y_size - 11));   //arrows
                My_sprite_system.draw(screen, 46, (pos_X + x_size / 2), (y_pos + y_size - 11));
            }//flechas

            if (visible)
            {
                cursor.y_pos = pos_Y + (get_index_y() - offset) * cursor_y_move + cur_pos_Y;
                cursor.x_pos = pos_X + (get_index_x()) * block_size + 10 * get_index_x() + cur_pos_X;
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
                (*the_sprite).draw(screen);
            }

        }

}
