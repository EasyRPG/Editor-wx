/*skill.cpp, skill routines.
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

///a quedado perfessto
//Actions separated in methods to make easily call each action

void Skill::set_name(const char *name)
{
    actual_name = name;
}
const char *Skill::get_name()
{
    return(actual_name);
}
void Skill::set_anim(Animation the_anim)
{
    actual_anim = the_anim;
}
Animation *Skill::get_anim()
{
    return (&actual_anim);
}

void Skill::set_mp_price(int the_mp_price)
{
    mp_price = the_mp_price; //it would be too longer if we put actual_mana_points_price
}
int *Skill::get_mp_price()
{
    return (&mp_price); // idem
}
void Skill::set_damage(int the_damage)
{
    actual_damage = the_damage;
}
int *Skill::get_damage()
{
    return (&actual_damage);
}
void Skill::set_level_req(int the_level_req)
{
    level_required = the_level_req;
}
int*Skill::get_level_req()
{
    return (&level_required);
}


