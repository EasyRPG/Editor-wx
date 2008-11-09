/* item.cpp, item routines.
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
#include "item.h"
///perfesssto ^_^

void Item::set_items_number(int the_items_number)
{
    items_number = the_items_number;
}
int*Item::get_items_number()
{
    return (&items_number);
}
void Item::set_name(const char *the_name)
{
    actual_name = the_name;
}
const char *Item::get_name()
{
    return(actual_name);
}

void Item::set_type(Uint8 the_type)//consultar a delapipol
{
    actual_type = the_type;
}
Uint8 *Item::get_type()
{
    return (&actual_type);
}
void Item::set_anim(Animation the_anim)
{
    anim = the_anim;
}
Animation *Item::get_anim()
{
    return (&anim);
}

