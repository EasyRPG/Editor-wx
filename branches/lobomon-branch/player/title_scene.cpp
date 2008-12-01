/*My_title_scene.cpp, EasyRPG player title scene file.
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
#include <iostream>

///almost clean

void Title_scene::init(Audio *the_audio, bool *run, Uint8 *the_scene, Player_team *the_team)
{
    My_team     = the_team;
    My_audio    = the_audio;

    (*My_audio).music_load("Music/title.mid");
    title.x_pos = 0;
    title.y_pos = 0;
    title.set_image("Title/title.png");
    My_menu.init( My_audio, run, 0, 2, 96, 67, 115, 115);
    string_vector.push_back("New");
    string_vector.push_back("Load");
    string_vector.push_back("Exit");
    My_menu.set_commands(&string_vector);
    running = run;
    new_scene = the_scene;
    delay = 0;
    
}

void Title_scene::update(SDL_Surface*screen)
{
    if (delay == 0)
    {
        title.draw(screen);
        My_menu.draw(screen);
    }
    delay++;
    //if(delay == 5)
    // {
    My_menu.draw(screen);
    //  delay = 1;
    // }

}

void Title_scene::action()
{
    static bool used = false;

    if (used == false)
    {
        used = true;
        if (My_menu.get_index_y() == 2)
            *running = false;
        if (My_menu.get_index_y() == 0)
        {
            init_party();
            *new_scene = 1;
        }
    }
}
void Title_scene::init_party()
{
    //since file stills unreadable, we simulate it
    Player alex;
    alex.set_name("Alex");
    Character alex_chara;
    alex_chara.init_chara();
    alex_chara.set_image("CharSet/charset.png");
    alex.set_chara(alex_chara);

    Faceset alex_face;
    alex_face.set_image("FaceSet/faceset.png");
    alex_face.init_faceset(0, 0, 0);

    alex.set_faceset(alex_face);
    alex.set_name("Alex");
    alex.set_job("Soldier");
    alex.set_hp(48);
    alex.set_max_hp(48);
    alex.set_mp(38);
    alex.set_max_mp(38);
    alex.set_heal(0);
    alex.set_attack(27);
    alex.set_defense(21);
    alex.set_speed(18);
    alex.set_spirit(23);
    alex.set_level(1);
    alex.set_exp(0);
    alex.set_max_exp(33);

    //no skills for Alex?
    Skill poison;
    poison.set_name("Poison");
    poison.set_damage(6);
    poison.set_level_req(1);
    poison.set_mp_price(10);
    alex.add_skill(poison);
    Skill paralysis;
    paralysis.set_name("Paralysis");
    paralysis.set_damage(5);
    paralysis.set_level_req(1);
    paralysis.set_mp_price(5);
    alex.add_skill(paralysis);

    Item sword;
    sword.set_name("Iron sword");
    sword.set_items_number(1);
    sword.set_type(4);
    sword.id = 15;

/*    Animation My_anim; // disabled (fdelapena)
    My_anim.set_image("Battle/sword.png");
    My_anim.init_anim(5, 2);


    sword.set_anim(My_anim);*/


    alex.set_weapon(sword);
    Item shield;
    shield.set_name("Wood shield");
    shield.set_items_number(1);
    shield.set_type(5);
    shield.id = 16;
    Item armor;
    armor.set_name("Leather armor");
    armor.set_items_number(1);
    armor.set_type(6);
    armor.id = 17;

    Item helm;
    helm.set_name("Leather helmet");
    helm.set_items_number(1);
    helm.set_type(7);
    helm.id = 18;

    Item talisman;
    talisman.set_name("Talisman");
    talisman.set_items_number(1);
    talisman.set_type(8);
    talisman.id = 19;


    alex.set_shield(shield);
    alex.set_armor(armor);
    alex.set_helmet(helm);
    alex.set_accessory(talisman);

    alex.set_weapon_type(4);
    alex.set_shield_type(5);
    alex.set_armor_type(6);
    alex.set_helmet_type(7);
    alex.set_accessory_type(8);
    Item null_item;
    null_item.set_name(" ");
    null_item.set_items_number(0);
    null_item.set_type(0);
    null_item.id = 0;

    Item null_weapon_item;
    null_weapon_item.set_name(" ");
    null_weapon_item.set_items_number(0);
    null_weapon_item.set_type(0);
    null_weapon_item.id = 0;


/*    My_anim.set_image("Battle/null.png"); // disabled (fdelapena)
    My_anim.init_anim(5, 3);


    null_weapon_item.set_anim(My_anim);*/



    My_team->add_player(alex);

    Player brian;

    Character brian_chara;
    brian_chara.init_chara();
    brian_chara.set_image("CharSet/chara4.png");
    brian.set_chara(brian_chara);
    Faceset brian_face;
    brian_face.set_image("FaceSet/chara2.png");
    brian_face.init_faceset(0, 0, 8);

    brian.set_faceset(brian_face);
    brian.set_name("Brian");
    brian.set_job("Soldier");
    brian.set_hp(52);
    brian.set_max_hp(52);
    brian.set_mp(0);
    brian.set_max_mp(0);
    brian.set_heal(0);
    brian.set_attack(18);
    brian.set_defense(21);
    brian.set_speed(10);
    brian.set_spirit(24);
    brian.set_level(1);
    brian.set_exp(0);
    brian.set_max_exp(32);
    brian.set_weapon(null_weapon_item);
    brian.set_shield(null_item);
    brian.set_armor(null_item);
    brian.set_helmet(null_item);
    brian.set_accessory(null_item);
    My_team->add_player(brian);


    Player caro;

    Character caro_chara;
    caro_chara.init_chara();
    caro_chara.set_image("CharSet/charset.png");
    caro.set_chara(caro_chara);
    Faceset caro_face;
    caro_face.set_image("FaceSet/faceset.png");
    caro_face.init_faceset(0, 0, 5);

    caro.set_faceset(caro_face);
    caro.set_name("carola");
    caro.set_job("wizard");
    caro.set_hp(36);
    caro.set_max_hp(36);
    caro.set_mp(58);
    caro.set_max_mp(58);
    caro.set_heal(0);
    caro.set_attack(18);
    caro.set_defense(15);
    caro.set_speed(29);
    caro.set_spirit(22);
    caro.set_level(1);
    caro.set_exp(0);
    caro.set_max_exp(31);

    Item staff;
    staff.set_name("Wood staff");
    staff.set_items_number(1);
    staff.set_type(16);
    staff.id = 16;
/*    My_anim.set_image("Battle/staff.png"); // disabled (fdelapena)
    My_anim.init_anim(5, 2);


    staff.set_anim(My_anim); */
    caro.set_weapon(staff);




    caro.set_shield(null_item);
    caro.set_armor(null_item);
    caro.set_helmet(null_item);
    caro.set_accessory(null_item);
    My_team->add_player(caro);

    Player enrique;

    Character enrique_chara;
    enrique_chara.init_chara();
    enrique_chara.set_image("CharSet/charset.png");
    enrique.set_chara(enrique_chara);
    Faceset enrique_face;
    enrique_face.set_image("FaceSet/faceset.png");
    enrique_face.init_faceset(0, 0, 10);

    enrique.set_faceset(enrique_face);
    enrique.set_name("Enrique");
    enrique.set_job("Fighter");
    enrique.set_hp(59);
    enrique.set_max_hp(59);
    enrique.set_mp(0);
    enrique.set_max_mp(0);
    enrique.set_heal(0);
    enrique.set_attack(28);
    enrique.set_defense(22);
    enrique.set_speed(26);
    enrique.set_spirit(16);
    enrique.set_level(1);
    enrique.set_exp(0);
    enrique.set_max_exp(29);
    enrique.set_weapon(null_weapon_item);
    enrique.set_shield(null_item);
    enrique.set_armor(null_item);
    enrique.set_helmet(null_item);
    enrique.set_accessory(null_item);
    My_team->add_player(enrique);
    My_team->set_gold(100);

    Item potion;
    potion.set_name("Potion");
    potion.set_items_number(10);
    potion.set_type(0);
    potion.id = 1;
    Item ether;
    ether.set_name("Ether");
    ether.set_items_number(5);
    ether.set_type(0);
    ether.id = 2;

    Item sword2;
    sword2.set_name("Wood sword");
    sword2.set_items_number(1);
    sword2.set_type(4);
    sword2.id = 25;
    My_team->add_item(sword2);
    My_team->add_item(potion);
    My_team->add_item(ether);

}
void Title_scene::update_key()
{
    My_menu.update_key();
    if (My_menu.decision())
    {
        action();
    }
}
void Title_scene::dispose()
{
    title.dispose();
    My_menu.dispose();
    (*My_audio).stop_music();
}
