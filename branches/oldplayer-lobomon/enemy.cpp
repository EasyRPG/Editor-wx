/*enemy.cpp, enemy routines.
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

void Enemy::set_hp(int the_hp)
{
	hp = the_hp;
}

void Enemy::set_max_hp(int the_max_hp)
{
	max_hp = the_max_hp;
}

void Enemy::set_mp(int the_mp)
{
	mp = the_mp;
}

void Enemy::set_max_mp(int the_max_mp)
{
	max_mp = the_max_mp;
}

int *Enemy::get_hp()
{
	return (&hp);
}

int *Enemy::get_max_hp()
{
	return (&max_hp);
}

int*Enemy::get_mp()
{
	return (&mp);
}

int*Enemy::get_max_mp()
{
	return (&max_mp);
}

void Enemy::set_heal(int the_heal)
{
	heal = the_heal;
}

void Enemy::set_attack(int the_attack)
{
	attack = the_attack;
}

void Enemy::set_defense(int the_defense)
{
	defense = the_defense;
}

void Enemy::set_speed(int the_speed)
{
	speed = the_speed;
}

void Enemy::set_spirit(int the_spirit)
{
	spirit = the_spirit;
}

void Enemy::set_level(int the_level)
{
	level = the_level;
}

void Enemy::set_exp(int the_exp)
{
	exp = the_exp;
}

int *Enemy::get_heal()
{
	return (&heal);
}

int *Enemy::get_attack()
{
	return (&attack);
}

int*Enemy::get_defense()
{
	return (&defense);
}

int*Enemy::get_speed()
{
	return (&speed);
}

int *Enemy::get_spirit()
{
	return (&spirit);
}

int *Enemy::get_level()
{
	return (&level);
}

int*Enemy::get_exp()
{
	return (&exp);
}

void Enemy::set_name(const char *name)
{
	name = name;
}

const char *Enemy::get_name()
{
	return(name);
}

void Enemy::add_skill(Skill My_skill)
{
	my_skills.push_back(My_skill);
}

const char *Enemy::get_skill_name(int num)
{
	return (((my_skills.at(num))).get_name());
}

int *Enemy::get_skill_mp_price(int num)
{
	return (((my_skills.at(num))).get_mp_price());
}
int *Enemy::get_skill_damage(int num)
{
	return (((my_skills.at(num))).get_damage());
}
int *Enemy::get_skill_level_req(int num)
{
	return (((my_skills.at(num))).get_level_req());
}

Animation *Enemy::get_skill_get_anim(int num)
{
	return (((my_skills.at(num))).get_anim());
}
int Enemy::get_skill_size()
{
	return (my_skills.size());
}
