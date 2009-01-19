/*equip_menu_scene.cpp, equip My_menu scene routines.
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

void Equipment_scene::init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team)
{
    My_team         = the_team;
    My_audio        = the_audio;
    the_run         = run;

    My_menu.init(the_audio, run, 0, 4, 190, 105, 130, 30);
    my_weapons.init(the_audio, run, 1, 0, 320, 105, 0, 135);
    My_description.init(320,30,0,0);
    stats.init(130,105,0,30);
    int             i = My_team->select;
    int             space = 16;
    int             block_size = 150;
    char            string_buffer[255];

    string_vector.push_back(( (*(My_team->get_weapon(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_shield(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_armor(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_helmet(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_accessory(i))).get_name()));
    My_menu.set_x_pos_text(90);

    My_menu.add_text("Weapon",10,5);
    My_menu.add_text("Shield",10,5+(1*space));
    My_menu.add_text("Armor",10,5+(2*space));
    My_menu.add_text("Helmet",10,5+(3*space));
    My_menu.add_text("Other",10,5+(4*space));
    My_menu.set_commands(& string_vector);
    int j;
    int item_type=(*( (*(My_team->get_weapon(i))).get_type()));
    int item_tipe2;
    for (j = 0;j<My_team->get_num_items();j++)
    {
        item_tipe2=(*(My_team->get_type(j)));
        if (item_type == item_tipe2)
        {
            string_vector2.push_back( (const char *) (My_team->get_item_name(j)) );
            sprintf(string_buffer, "%d ", (*My_team->get_items_number(j)));
            my_weapons.add_text(string_buffer,block_size-10+((block_size+10)*((j)%(2))),5+((j/2)*space));
        }
    }

    while (string_vector2.size()<2)//para que no truene
        string_vector2.push_back( " " );
    my_weapons.set_commands(& string_vector2);
    my_weapons.on_use = false;
    space = 17;

    stats.add_text((My_team->get_name(i)),10,5);

    sprintf(string_buffer, "Strenght        %d ", (*My_team->get_attack(i)));
    stats.add_text(string_buffer,10,5+(1*space));
    sprintf(string_buffer, "Defense       %d ", (*My_team->get_defense(i)));
    stats.add_text(string_buffer,10,5+(2*space));
    sprintf(string_buffer, "Intelligence     %d ", (*My_team->get_spirit(i)));
    stats.add_text(string_buffer,10,5+(3*space));
    sprintf(string_buffer, "Agility      %d ", (*My_team->get_speed(i)));
    stats.add_text(string_buffer,10,5+(4*space));
    delay       = 0;
    running     = run;
    new_scene   = the_scene;

}

void Equipment_scene::update_1_menu()
{
    int i       =My_team->select;
    int space   = 16;
//   int block_size = 150;
    My_menu.dispose();
    My_menu.init(My_audio, the_run, 0,4, 190, 105, 130, 30);

    string_vector.push_back(( (*(My_team->get_weapon(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_shield(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_armor(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_helmet(i))).get_name()));
    string_vector.push_back(( (*(My_team->get_accessory(i))).get_name()));
    My_menu.set_x_pos_text(90);

    My_menu.add_text("Weapon",10,5);
    My_menu.add_text("Shield",10,5+(1*space));
    My_menu.add_text("Armor",10,5+(2*space));
    My_menu.add_text("Helmet",10,5+(3*space));
    My_menu.add_text("Other",10,5+(4*space));
    My_menu.set_commands(&string_vector);
}

void Equipment_scene::update_2_menu()
{
    int k = 0,i = My_menu.get_index_y();
    char string_buffer[255];
    int space = 16,block_size = 150;
    my_weapons.dispose();

    my_weapons.init( My_audio, the_run, 1,0, 320, 105, 0, 135);
    int j=My_team->select;
    Uint8 item_tipe2,item_type = 4;

    if (i == 0)
        item_type=(*(My_team->get_weapon_type(j)));
    if (i == 1)
        item_type=(*(My_team->get_shield_type(j)));
    if (i == 2)
        item_type=(*(My_team->get_armor_type(j)));
    if (i == 3)
        item_type=(*(My_team->get_helmet_type(j)));
    if (i == 4)
        item_type=(*(My_team->get_accessory_type(j)));

    for (j = 0;j<My_team->get_num_items();j++)
    {
        item_tipe2=(*(My_team->get_type(j)));
        if (item_type == item_tipe2)
        {
            string_vector2.push_back( (const char *) (My_team->get_item_name(j)) );
            sprintf(string_buffer, "%d ", (*My_team->get_items_number(j)));
            k = string_vector2.size()-1;
            my_weapons.add_text(string_buffer,block_size-10+((block_size+10)*((k)%(2))),5+((k/2)*space));
        }
    }
    while (string_vector2.size()<2)//para que no truene
        string_vector2.push_back( " " );
    my_weapons.set_commands(& string_vector2);
    my_weapons.on_use = false;
}

void Equipment_scene::update(SDL_Surface*screen)
{
    int static lastcusor = 0;
    delay++;
    if (delay == 6)
    {
        My_menu.draw(screen);

        if (lastcusor !=My_menu.get_index_y())
        {
            update_2_menu();
            lastcusor = My_menu.get_index_y();
        }
        my_weapons.draw(screen);

        stats.draw(screen);
        My_description.draw(screen);
        delay = 0;
    }
}

void Equipment_scene::action()
{
    my_weapons.on_use = true;

}


void Equipment_scene::action2()
{
    int i=My_team->select;
    std::string strd;
    const char *cadena;
    int k = 0,j;
    if (((*(My_team->get_weapon(i))).id)!=0)// si el objeto del heroe no es vacio
    {
        if (My_menu.get_index_y()==0)
            My_team->add_item((*(My_team->get_weapon(i))));
        if (My_menu.get_index_y()==1)
            My_team->add_item((*(My_team->get_shield(i))));
        if (My_menu.get_index_y()==2)
            My_team->add_item((*(My_team->get_armor(i))));
        if (My_menu.get_index_y()==3)
            My_team->add_item((*(My_team->get_helmet(i))));
        if (My_menu.get_index_y()==4)
            My_team->add_item((*(My_team->get_accessory(i))));

    }//agregalo a la lista de objetos
    k = my_weapons.get_index_x()+2*my_weapons.get_index_y();//k igal al indice elegido

    strd = string_vector2.at(k);

    for (j = 0;j<My_team->get_num_items();j++)
    {
        cadena=((My_team->get_item_name(j)));
        if (strd.compare(cadena)==0)//si son iguales
            break;//j es elindice real
    }//si no lo encuetra pones el nulo

    if (j==My_team->get_num_items())
    {
        Item null_item;
        null_item.set_name(" ");
        null_item.set_items_number(0);
        null_item.set_type(0);
        null_item.id = 0;
        if (My_menu.get_index_y()==0)
            My_team->set_weapon(i ,null_item);
        if (My_menu.get_index_y()==1)
            My_team->set_shield(i ,null_item);
        if (My_menu.get_index_y()==2)
            My_team->set_armor(i ,null_item);
        if (My_menu.get_index_y()==3)
            My_team->set_helmet(i ,null_item);
        if (My_menu.get_index_y()==4)
            My_team->set_accessory(i ,null_item);
    }
    else
    {
        if (My_menu.get_index_y()==0)
            My_team->set_weapon(i ,My_team->get_item(j)  );
        if (My_menu.get_index_y()==1)
            My_team->set_shield(i ,My_team->get_item(j)  );
        if (My_menu.get_index_y()==2)
            My_team->set_armor(i ,My_team->get_item(j)  );
        if (My_menu.get_index_y()==3)
            My_team->set_helmet(i ,My_team->get_item(j)  );
        if (My_menu.get_index_y()==4)
            My_team->set_accessory(i ,My_team->get_item(j)  );

        (*My_team->get_items_number(j))=(*My_team->get_items_number(j))-1;
        if ((*My_team->get_items_number(j))==0)
            My_team->erase_item(j);
    }

    my_weapons.restart_menu();
    My_menu.restart_menu();
    my_weapons.on_use = false;
    update_1_menu();
    update_2_menu();

}

void Equipment_scene::update_key()
{
    if (my_weapons.on_use)
    {
        my_weapons.update_key();
        if (my_weapons.decision())
            action2();
    }
    else
    {
        My_menu.update_key();
        if (My_menu.decision())
            action();
    }


    if (key_pressed_and_released(KEY_X ))
    {
        (*My_audio).sound_load("Sound/cancel.wav");
        *new_scene = 4;
    }
}
void Equipment_scene::dispose()
{
    My_menu.dispose();
    my_weapons.dispose();
    My_description.dispose();
    stats.dispose();
}
