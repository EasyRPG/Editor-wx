/* item.h, EasyRPG player item class declaration file.
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

///a quedado perfessto

#ifndef ITEM_H_
#define ITEM_H_

class Item
{
protected:
    const char  *actual_name;          //  item name
    int         items_number;   //  items quantity
    Animation   anim;           //  battle animation
    Uint8       actual_type;           //  weapon, healer, protecter, etc types
    int         shop_price;     //  item prices for shops

public:
    //  better we define on herency changes in items data
    int         id;
    void        set_items_number(int the_items_number);
    int         *get_items_number();
    void        set_name(const char *name);
    const char  *get_name();
    void        set_type(Uint8 the_type);
    Uint8       *get_type();
    void        set_anim(Animation the_anim);
    Animation   *get_anim();
};

#endif
