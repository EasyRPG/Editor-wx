/*enemy.h, EasyRPG player enemy class declaration file.
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

#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy {

private:
      int       hp;
      int       max_hp;
      int       mp;
      int       max_mp;
      int       heal;
      int       attack;
      int       defense;
      int       speed;
      int       spirit;
      int       level;
      int       exp;//esperiencia a dar
      int       gold_to;//oro a dar
      const char *name;

public:
      Sprite battler;


     std:: vector <Skill> my_skills;//skills del moustruo
     std:: vector <Item> my_equip;// items a dar

void    set_hp(int the_hp);
void    set_max_hp(int the_max_hp);
void    set_mp(int the_mp);
void    set_max_mp(int the_max_mp);
int     *get_hp();
int     *get_max_hp();
int     *get_mp();
int     *get_max_mp();
void    set_heal(int The_Heal);
void    set_attack(int The_Attack);
void    set_defense(int The_Defense);
void    set_speed(int The_Speed);
void    set_spirit(int The_Spirit);
void    set_level(int The_Level);
void    set_exp(int The_Exp);
int     *get_heal();
int     *get_attack();
int     *get_defense();
int     *get_speed();
int     *get_spirit();
int     *get_level();
int     *get_exp();
int     *get_max_exp();
void    set_name(const char *name);
const char  *get_name();
void        add_skill(Skill Myskill);
const char  *get_skill_name(int num);
int         *get_skill_mp_price(int num);
int         *get_skill_damage(int num);
int         *get_skill_level_req(int num);
Animation   *get_skill_get_anim(int num);
int         get_skill_size();

};

#endif
