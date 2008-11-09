/*player.cpp, player routines.
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

Item*Player::get_weapon()
{
    return (&weapon);
}
Item*Player::get_shield()
{
    return (&shield);
}
Item*Player::get_armor()
{
    return (&armor);
}
Item*Player::get_helmet()
{
    return (&helmet);
}
Item*Player::get_accessory()
{
    return (&accessory);
}


void Player::set_weapon(Item the_weapon)
{
    weapon = the_weapon;
}
void Player::set_shield(Item the_shield)
{
    shield = the_shield;
}

void Player::set_armor(Item the_armor)
{
    armor = the_armor;
}

void Player::set_helmet(Item the_helmet)
{
    helmet = the_helmet;
}
void Player::set_accessory(Item the_accessory)
{
    accessory = the_accessory;
}

Uint8*Player::get_weapon_type()
{
    return (&weapon_type);
}
Uint8*Player::get_shield_type()
{
    return (&shield_type);
}
Uint8*Player::get_armor_type()
{
    return (&armor_type);
}
Uint8*Player::get_helmet_type()
{
    return (&helmet_type);
}
Uint8*Player::get_accessory_type()
{
    return (&accessory_type);
}

void Player::set_weapon_type(Uint8 the_weapon_type)
{
    weapon_type = the_weapon_type;
}
void Player::set_shield_type(Uint8 the_shield_type)
{
    shield_type = the_shield_type;
}
void Player::set_armor_type(Uint8 the_armor_type)
{
    armor_type = the_armor_type;
}
void Player::set_helmet_type(Uint8 the_helmet_type)
{
    helmet_type = the_helmet_type;
}
void Player::set_accessory_type(Uint8 the_accessory_type)
{
    accessory_type = the_accessory_type;
}
void Player::set_hp(int the_hp)
{
    hp = the_hp;
}
void Player::set_max_hp(int the_max_hp)
{
    max_hp = the_max_hp;
}
void Player::set_mp(int the_mp)
{
    mp = the_mp;
}
void Player::set_max_mp(int the_max_mp)
{
    max_mp = the_max_mp;
}

int *Player::get_hp()
{
    return (&hp);
}
int *Player::get_max_hp()
{
    return (&max_hp);
}
int*Player::get_mp()
{
    return (&mp);
}
int*Player::get_max_mp()
{
    return (&max_mp);
}

void Player::set_heal(int the_heal)
{
    heal = the_heal;
}
void Player::set_attack(int the_attack)
{
    attack = the_attack;
}
void Player::set_defense(int the_defense)
{
    defense = the_defense;
}
void Player::set_speed(int the_speed)
{
    speed = the_speed;
}
void Player::set_spirit(int the_spirit)
{
    spirit = the_spirit;
}
void Player::set_level(int the_level)
{
    level = the_level;
}
void Player::set_exp(int the_exp)
{
    exp = the_exp;
}
void Player::set_max_exp(int the_max_exp)
{
    max_exp = the_max_exp;
}

int *Player::get_heal()
{
    return (&heal);
}
int *Player::get_attack()
{
    return (&attack);
}
int*Player::get_defense()
{
    return (&defense);
}
int*Player::get_speed()
{
    return (&speed);
}

int *Player::get_spirit()
{
    return (&spirit);
}
int *Player::get_level()
{
    return (&level);
}
int*Player::get_exp()
{
    return (&exp);
}
int*Player::get_max_exp()
{
    return (&max_exp);
}


void Player::set_job(const char *name)
{
    My_title_scene = name;
}
const char *Player::get_job()
{
    return(My_title_scene);
}
void Player::set_name(const char *name)
{
    name = name;
}
const char *Player::get_name()
{
    return(name);
}
void Player::set_faceset(Faceset the_faceset)
{
    my_face = the_faceset;
}
Faceset *Player::get_faceset()
{
    return(& my_face);
}
void Player::set_chara(Character thecharset)
{
    my_charset = thecharset;
}
Character *Player::get_chara()
{
    return (& my_charset);
}
void Player::add_skill(Skill Myskill)
{
    my_skills.push_back(Myskill);
}

const char *Player::get_skill_name(int num)
{
    return (((my_skills.at(num))).get_name());
}
int *Player::get_skill_mp_price(int num)
{
    return (((my_skills.at(num))).get_mp_price());
}
int *Player::get_skill_damage(int num)
{
    return (((my_skills.at(num))).get_damage());
}
int *Player::get_skill_level_req(int num)
{
    return (((my_skills.at(num))).get_level_req());
}

Animation *Player::get_weapon_anim()
{
    return (weapon.get_anim());
}

Animation *Player::get_skill_get_anim(int num)
{
    return (((my_skills.at(num))).get_anim());
}
int Player::get_skill_size()
{
    return (my_skills.size());
}

void Player_team::clear_team()
{
    players.clear();
}
void Player_team::clear_objects()
{
    items.clear();
}
void Player_team::clear_enemy()
{
    enemies.clear();
}
void Player_team::add_enemy(Enemy player)
{
    enemies.push_back(player);
}

void Player_team::add_player(Player My_player)
{
    players.push_back(My_player);
}
Item Player_team::get_item(int num)
{
    return (items.at(num));
}
void Player_team::add_item(Item Myitem)
{
    Uint32 i;
    int the_id;
    the_id = Myitem.id;
    for (i = 0;i<items.size();i++)
    {
        if (the_id==(items.at(i)).id)
            break;
    }

    if (i<items.size())//lo encontro
    {
        *((items.at(i)).get_items_number())=*((items.at(i)).get_items_number())+*Myitem.get_items_number();
    }
    else
    {
        items.push_back(Myitem);
    }
}



int Player_team::get_size()
{
    return (players.size());
}
Character *Player_team::get_chara(int num)
{
    return (((players.at(num))).get_chara());
}
Faceset *Player_team::get_faceset(int num)
{
    return (((players.at(num))).get_faceset());
}
const char *Player_team::get_name(int num)
{
    return (((players.at(num))).get_name());
}
const char *Player_team::get_job(int num)
{
    return (((players.at(num))).get_job());
}
int *Player_team::get_hp(int num)
{
    return (((players.at(num))).get_hp());
}
int *Player_team::get_max_hp(int num)
{
    return (((players.at(num))).get_max_hp());
}
int*Player_team::get_mp(int num)
{
    return (((players.at(num))).get_mp());
}
int*Player_team::get_max_mp(int num)
{
    return (((players.at(num))).get_max_mp());
}

int *Player_team::get_heal(int num)
{
    return (((players.at(num))).get_heal());
}
int *Player_team::get_attack(int num)
{
    return (((players.at(num))).get_attack());
}
int*Player_team::get_defense(int num)
{
    return (((players.at(num))).get_defense());
}
int*Player_team::get_speed(int num)
{
    return (((players.at(num))).get_speed());
}

int *Player_team::get_spirit(int num)
{
    return (((players.at(num))).get_spirit());
}
int *Player_team::get_level(int num)
{
    return (((players.at(num))).get_level());
}
int*Player_team::get_exp(int num)
{
    return (((players.at(num))).get_exp());
}
int*Player_team::get_max_exp(int num)
{
    return (((players.at(num))).get_max_exp());
}

int Player_team::get_num_items()
{
    return (items.size());
}
void Player_team::erase_item(int the_item)
{
    std::vector<Item>::iterator the_iterator;
    the_iterator = items.begin();
    int i;
    for (i = 0;i<the_item;i++)
    {
        the_iterator++;
    }
    items.erase(the_iterator);
}
int*Player_team::get_items_number(int num)
{
    return (((items.at(num))).get_items_number());
}
Uint8 *Player_team::get_type(int num)
{
    return (((items.at(num))).get_type());
}
const char *Player_team::get_item_name(int num)
{
    return (((items.at(num))).get_name());
}
Animation *Player_team::get_item_anim(int num)
{
    return (((items.at(num))).get_anim());
}
void Player_team::set_gold(int the_gold)
{
    gold = the_gold;
}
int*Player_team::get_gold()
{
    return (&gold);
}
int Player_team::get_skill_size(int num)
{
    return (((players.at(num))).get_skill_size());
}
const char *Player_team::get_skill_name(int player_num,int num)
{
    return (((players.at(player_num))).get_skill_name(num));
}
int *Player_team::get_skill_mp_price(int player_num,int num)
{
    return (((players.at(player_num))).get_skill_mp_price(num));
}
int *Player_team::get_skill_damage(int player_num,int num)
{
    return (((players.at(player_num))).get_skill_damage(num));
}
int *Player_team::get_skill_level_req(int player_num,int num)
{
    return (((players.at(player_num))).get_skill_level_req(num));
}

Animation *Player_team::get_skill_get_anim(int player_num,int num)
{
    return (((players.at(player_num))).get_skill_get_anim(num));
}
Animation *Player_team::get_weapon_anim(int player_num)
{
    return (((players.at(player_num))).get_weapon_anim());
}





Item*Player_team::get_weapon(int player_num)
{
    return ((players.at(player_num)).get_weapon());
}
Item*Player_team::get_shield(int player_num)
{
    return ((players.at(player_num)).get_shield());
}
Item*Player_team::get_armor(int player_num)
{
    return ((players.at(player_num)).get_armor());
}
Item*Player_team::get_helmet(int player_num)
{
    return ((players.at(player_num)).get_helmet());
}
Item*Player_team::get_accessory(int player_num)
{
    return ((players.at(player_num)).get_accessory());
}


void Player_team::set_weapon(int player_num, Item the_weapon)
{
    (players.at(player_num)).set_weapon(the_weapon);
}
void Player_team::set_shield(int player_num, Item the_shield)
{
    (players.at(player_num)).set_shield(the_shield);
}
void Player_team::set_armor(int player_num, Item the_armor)
{
    (players.at(player_num)).set_armor(the_armor);
}
void Player_team::set_helmet(int player_num, Item the_helmet)
{
    (players.at(player_num)).set_helmet(the_helmet);
}
void Player_team::set_accessory(int player_num,Item the_accessory)
{
    (players.at(player_num)).set_accessory(the_accessory);
}


Uint8*Player_team::get_weapon_type(int player_num)
{
    return ( (players.at(player_num)).get_weapon_type());
}
Uint8*Player_team::get_shield_type(int player_num)
{
    return ( (players.at(player_num)).get_shield_type());
}
Uint8*Player_team::get_armor_type(int player_num)
{
    return ( (players.at(player_num)).get_armor_type());
}
Uint8*Player_team::get_helmet_type(int player_num)
{
    return ( (players.at(player_num)).get_helmet_type());
}
Uint8*Player_team::get_accessory_type(int player_num)
{
    return ( (players.at(player_num)).get_accessory_type());
}

void Player_team::set_weapon_type(int player_num, Uint8 the_weapon_type)
{
    (players.at(player_num)).set_weapon_type(the_weapon_type);
}
void Player_team::set_shield_type(int player_num, Uint8 the_shield_type)
{
    (players.at(player_num)).set_shield_type(the_shield_type);
}
void Player_team::set_armor_type(int player_num, Uint8 the_armor_type)
{
    (players.at(player_num)).set_armor_type(the_armor_type);
}
void Player_team::set_helmet_type(int player_num, Uint8 the_helmet_type)
{
    (players.at(player_num)).set_helmet_type(the_helmet_type);
}
void Player_team::set_accessory_type(int player_num, Uint8 the_accessory_type)
{
    (players.at(player_num)).set_accessory_type(the_accessory_type);
}
