/* player.h, EasyRPG player Player class declaration file.
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

#ifndef PLAYER_H_
#define PLAYER_H_

struct view
{
    int     x_pos;
    int     y_pos;
};

class Player
{
    protected:
        Character   my_charset;
        Faceset     my_face;
        int         hp;
        int         max_hp;
        int         mp;
        int         max_mp;
        int         heal;
        int         attack;
        int         defense;
        int         speed;
        int         spirit;
        int         level;
        int         exp;
        int         max_exp;
        const char  *name;
        const char  *My_title_scene;
        Item        weapon;
        Item        shield;
        Item        armor;
        Item        helmet;
        Item        accessory;
        Uint8       weapon_type;//256 tipos nada mas
        Uint8       shield_type;
        Uint8       armor_type;
        Uint8       helmet_type;
        Uint8       accessory_type;

    public:



        // battler Battler;
        std:: vector <Skill> my_skills;

        Item        *get_weapon();
        Item        *get_shield();
        Item        *get_armor();
        Item        *get_helmet();
        Item        *get_accessory();
        void        set_weapon(Item the_weapon);
        void        set_shield(Item the_shield);
        void        set_armor(Item the_armor);
        void        set_helmet(Item the_helmet);
        void        set_accessory(Item the_accessory);
        Animation   *get_weapon_anim();
        Uint8       *get_weapon_type();
        Uint8       *get_shield_type();
        Uint8       *get_armor_type();
        Uint8       *get_helmet_type();
        Uint8       *get_accessory_type();

        void        set_weapon_type(Uint8 the_weapon_type);
        void        set_shield_type(Uint8 the_shield_type);
        void        set_armor_type(Uint8 the_armor_type);
        void        set_helmet_type(Uint8 the_helmet_type);
        void        set_accessory_type(Uint8 the_accessory_type);

        void        set_hp(int the_hp);
        void        set_max_hp(int the_max_hp);
        void        set_mp(int the_mp);
        void        set_max_mp(int the_max_mp);

        void        set_heal(int the_heal);
        void        set_attack(int the_attack);
        void        set_defense(int the_defense);
        void        set_speed(int the_speed);
        void        set_spirit(int the_spirit);
        void        set_level(int the_level);
        void        set_exp(int the_exp);
        void        set_max_exp(int the_max_exp);
        void        set_name(const char *name);
        void        set_job(const char *name);
        void        set_chara(Character thecharset);
        void        set_faceset(Faceset the_faceset);

        int         *get_hp();
        int         *get_max_hp();
        int         *get_mp();
        int         *get_max_mp();
        int         *get_heal();
        int         *get_attack();
        int         *get_defense();
        int         *get_speed();
        int         *get_spirit();
        int         *get_level();
        int         *get_exp();
        int         *get_max_exp();


        Faceset     *get_faceset();
        Character   *get_chara();
        const char  *get_name();
        const char  *get_job();
        void        add_skill(Skill My_skill);
        int         get_skill_size();
        const char  *get_skill_name(int num);
        int         *get_skill_mp_price(int num);
        int         *get_skill_damage(int num);
        int         *get_skill_level_req(int num);
        Animation   *get_skill_get_anim(int num);


};
class Player_team
{
        std::vector <Player>players;
        std::vector <Item>  items;
        int gold;

    public:
        std::vector <Enemy> enemies;
        void        clear_enemy();
        void        add_enemy(Enemy player);

        view        my_view;
        int         select;
        int         get_size();
        void        clear_team();
        void        clear_objects();
        void        add_player(Player My_player);
        void        set_gold(int the_gold);
        int         *get_gold();

        Character   *get_chara(int num);
        Faceset     *get_faceset(int num);
        const char  *get_name(int num);
        const char  *get_job(int num);

        int         *get_mp(int num);
        int         *get_max_mp(int num);
        int         *get_hp(int num);
        int         *get_max_hp(int num);

        int         *get_heal(int num);
        int         *get_attack(int num);
        int         *get_defense(int num);
        int         *get_speed(int num);
        int         *get_spirit(int num);
        int         *get_level(int num);
        int         *get_exp(int num);
        int         *get_max_exp(int num);

        void        erase_item(int num);
        Item        get_item(int num);
        int         get_num_items();
        void        add_item(Item My_item);
        int         *get_items_number(int num);
        Uint8       *get_type(int num);
        const char  *get_item_name(int num);
        Animation   *get_item_anim(int num);

        int         get_skill_size(int num);
        const char  *get_skill_name(int player_num,int num);
        int         *get_skill_mp_price(int player_num,int num);
        int         *get_skill_damage(int player_num,int num);
        int         *get_skill_level_req(int player_num,int num);
        Animation   *get_skill_get_anim(int player_num,int num);


        Animation   *get_weapon_anim(int num);

        Item        *get_weapon(int num);
        Item        *get_shield(int num);
        Item        *get_armor(int num);
        Item        *get_helmet(int num);
        Item        *get_accessory(int num);

        void        set_weapon(int player_num,Item the_weapon);
        void        set_shield(int player_num,Item the_shield);
        void        set_armor(int player_num,Item the_armor);
        void        set_helmet(int player_num,Item the_helmet);
        void        set_accessory(int player_num,Item the_accessory);

        Uint8       *get_weapon_type(int player_num);
        Uint8       *get_shield_type(int player_num);
        Uint8       *get_armor_type(int player_num);
        Uint8       *get_helmet_type(int player_num);
        Uint8       *get_accessory_type(int player_num);
        void        set_weapon_type(int player_num, Uint8 the_weapon_type);
        void        set_shield_type(int player_num, Uint8 the_shield_type);
        void        set_armor_type(int player_num, Uint8 the_armor_type);
        void        set_helmet_type(int player_num, Uint8 the_helmet_type);
        void        set_accessory_type(int player_num, Uint8 the_accessory_type);
};

#endif
