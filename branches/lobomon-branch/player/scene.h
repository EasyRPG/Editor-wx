/*scene.h, EasyRPG player scene class declaration file.
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

#ifndef SCENE_H_
#define SCENE_H_

struct menu_command
{
    int     des1;
    int     des2;
    int     selected_monster;
};


class Easyrpg_menu
{
    protected:

        int     index_x,index_y;
        int     max_index_y,max_index_x;
        Audio   *My_audio;
        bool    *running;
        bool    decided;
        int     delay;
        int     repeat;
    public:

        bool    decision();
        int     get_index_y();
        int     get_index_x();
        void    update_key();
        void    restart_menu();
        void    init(Audio *the_audio, bool *run,int x_pos,int y_pos);
};
class Window_base
{
    protected:

        Sprite_system   My_sprite_system;
        Sprite          My_texture;
        Font            my_font;
        int             x_pos;
        int             y_pos;
        int             x_size;
        int             y_size;

        std:: vector <Sprite>   sprite_text;
        std:: vector <int>      v_sprite;   //  pointers to sprites
        Sprite                  text;
        char string_buffer[255];

        int text_dispose;

        bool disposing;

    public:

        bool visible;

        void init(int the_x_size,int the_y_size,int the_x_pos,int the_y_pos);

        void draw(SDL_Surface *screen);
        void add_text(const char *ctext, int the_x_pos, int the_y_pos);
        void add_sprite(Sprite *the_sprite, int the_x_pos, int the_y_pos);

        void dispose();
};

class Window_select
{
    protected:

        Sprite_system   My_sprite_system;
        Sprite          My_texture;
        Sprite          cursor;
        Font            my_font;
        Easyrpg_menu    My_menu;
        int             init_x_text;
        Sprite          text;

        int             x_pos,y_pos;
        int             x_size;
        int             y_size;
        int             block_size;
        int             x_command;
        int             y_command;

        std:: vector <std::string>  *My_vector;
        std:: vector <Sprite>       My_sprite;
        std:: vector <Sprite>       sprite_text;


        bool disposing;

    public:

        bool    visible;
        bool    on_use;
        bool    decision();

        void    init(Audio *the_audio, bool *run,int the_x_command,int the_y_command,int the_x_size,int the_y_size,int the_x_pos,int the_y_pos);

        int     get_index_x();
        int     get_index_y();
        void    set_x_pos_text(int x_pos);

        void    update_key();
        void    restart_menu();
        void    draw(SDL_Surface*screen);
        void    add_text(const char *ctext, int the_x_pos, int the_y_pos);
        void    set_commands(std::vector <std::string> *the_string_vector);

        void    dispose();
};


class Window_player_select
{
protected:

    Sprite_system   My_sprite_system;
    Sprite          My_texture;
    Sprite          cursor;
    Font            my_font;
    Easyrpg_menu    My_menu;
    Sprite          text;
    std:: vector <Sprite> sprite_text;

    int x_pos;
    int y_pos;
    int x_size;
    int y_size;
    int block_size;
    int x_command;
    int y_command;
    std:: vector <int> v_sprite;    //  Pointers to sprites
    int cursor_x;
    int cursor_y;
    int cursor_y_move;

    bool disposing;


public:

    bool    visible;
    bool    visible_window;
    void    update_key();
    bool    decision();

    void    init(Audio *the_audio, bool *run,int the_x_command,int the_y_command,int the_x_size,int the_y_size,int the_x_pos,int the_y_pos,int the_x_cursor,int the_y_cursor);

    int     get_index_x();
    int     get_index_y();
    void    restart_menu();
    void    init_xy_cur(int the_x_pos,int the_y_pos);
    void    set_y_cursor(int the_y_pos);

    void    draw(SDL_Surface*screen);
    void    add_text(const char *ctext, int the_x_pos, int the_y_pos);
    void    add_sprite(Sprite *the_sprite, int the_x_pos, int the_y_pos);

    void    dispose();
};

class Scene
{
protected:
    Uint8       *new_scene;
    bool        *running;
    Audio       *My_audio;
    Player_team *My_team;
    int delay;
public:

    virtual void    update(SDL_Surface*){} ;
    virtual void    update_key(){} ;
    virtual void    dispose(){} ;

};

class Map_scene: public Scene
{
private:

    int        screen_size_x, screen_size_y;
    Actor      My_actor;
    Character  *My_player;
    Character  npc;
    Faceset    alex_face;
    Sprite     my_net;
    Font       my_font;
    bool       moving;
    int        to_move;
    map        my_map;
    char string_buffer[255];

public:

    void    init(Audio *audio,int screen_X, int screen_Y,Uint8 *the_scene,Player_team *the_team);

    void    update(SDL_Surface*screen);
    void    scroll();
    void    update_key();
    void    slow_move();
    void    npc_map();

    void    dispose();
};
class Title_scene: public Scene
{
private:

    void action();

    Sprite                      title;
    Window_select               My_menu;
    std:: vector <std::string>  string_vector;

public:

    void init(Audio *My_audio,  bool *run,Uint8 *the_scene,Player_team *the_team);

    void update(SDL_Surface*screen);
    void init_party();
    void update_key();

    void dispose();

};

class Battle_scene: public Scene
{
private:
    bool            *the_run;
    int             state;
    int             new_menu_used;
    int             player_turns;
    int             player_in_turn;
    int             monster_in_turn;
    Sprite          title;
    Window_base     Window_text;
    Window_player_select    Window;
    Window_select   My_menu;
    Window_select   menu_os;
    Window_select   monster_select;
    std::vector <std::string> string_vector;
    std::vector <std::string> string_vector2;
    std::vector <menu_command> menu_commands;

    void action();


public:

    void    init(Audio *My_audio,  bool *run,Uint8 *the_scene,Player_team *the_team);

    void    update(SDL_Surface*screen);
    void    update_key();
    void    update_window_stats();
    void    update_window_monster_select();
    void    give_turn();

    void    attack(SDL_Surface*screen,int new_chara,int enemy);
    void    attacked(int enemy);
    void    action_monster_select();

    void    window_text_show_damage(bool type,int attack,int attacked,int damage);

    void    win();
    void    lose();

    void dispose();
};
class Main_menu_scene: public Scene
{
private:
    Window_player_select    players;
    Window_base             gold;
    Window_select           My_menu;
    Window_select           menu_exit;
    std:: vector <std::string> string_vector;
    std:: vector <std::string> string_vector_2;
    void                    action();
    void                    action2();
    void                    action3();
public:
    void init(Audio *My_audio,  bool *run,Uint8 *the_scene,Player_team *the_team);
    void update(SDL_Surface*screen);
    void update_key();
    void dispose();
};
class Inventory_scene: public Scene
{
    private:

        Window_base My_description;
        Window_select My_menu;
        std:: vector <std::string> string_vector;

        void action();

    public:

        void init(Audio *My_audio,  bool *run,Uint8 *the_scene,Player_team *the_team);

        void update(SDL_Surface*screen);
        void update_key();

        void dispose();
};
class Item_use_scene: public Scene
{

    private:

        Window_player_select players;
        Window_base item_win;
        Window_base item_win2;
        void action();

    public:

        void init(Audio *My_audio,  bool *run, Uint8 *the_scene,Player_team *the_team);

        void update(SDL_Surface*screen);
        void update_key();

        void dispose();
};

class Save_load_scene: public Scene
{
    private:
        Window_base My_description;
        Window_base My_save_pos_1;
        Window_base My_save_pos_2;
        Window_base My_save_pos_3;

    public:
        void init(Audio *My_audio, bool *run, Uint8 *the_scene, Player_team *the_team);
        void update(SDL_Surface *screen);
        void update_key();
        void dispose();
};

class Status_scene: public Scene
{
    private:

        Window_base Status;
        Window_base Status_vit;
        Window_base Profession;
        Window_base my_weapons;

    public:

        void init(Audio *My_audio, bool *run, Uint8 *the_scene, Player_team *the_team);
        void update(SDL_Surface*screen);
        void update_key();

        void dispose();
};

class Equipment_scene: public Scene
{
    private:

        bool *the_run;
        Window_base My_description;
        Window_base stats;
        Window_select my_weapons;
        Window_select My_menu;
        std:: vector <std::string> string_vector;
        std:: vector <std::string> string_vector2;
        void action();

    public:

        void init(Audio *My_audio,  bool *run,Uint8 *the_scene,Player_team *the_team);
        void update(SDL_Surface*screen);
        void update_key();
        void update_1_menu();
        void update_2_menu();
        void action2();
        void dispose();
};

class Skills_menu_scene: public Scene
{
    private:

        Window_base My_description;
        Window_base My_description2;
        Window_select My_menu;
        std:: vector <std::string> string_vector;
        void action();
    public:

        void init(Audio *My_audio,  bool *run,Uint8 *the_scene,Player_team *the_team);
        void update(SDL_Surface*screen);
        void update_key();
        void dispose();
};
class Game_over_scene: public Scene
{
    private:

        Sprite title;
        void action();

    public:

        void init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team);

        void update(SDL_Surface*screen);
        void update_key();

        void dispose();
};

#endif
