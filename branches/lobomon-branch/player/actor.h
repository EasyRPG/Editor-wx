/*  actor.h, EasyRPG actor class declaration file.
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

#ifndef ACTOR_H
#define ACTOR_H

#include "math-sll.h"

struct mot  //comentar a delapipol(que es mot?)
{
    sll distance;
    sll delta;
    Uint8 direction;
};


class Actor:public Character
{
    public:
        // Methods
        void move_on_input();

        int min(int value, int max);
        sll min_f(float value, float max);
        int clamp(int value, int min, int max);
        sll clamp_f(float value, float min, float max);
        void set_xy_position(int x_pos,int y_pos);
        Uint8  flags;
        Uint8 state;
        mot Motion;
        int grid_x;///aparte de la x_pos  y_pos y_pos  tenemos la poscion con referencia bloques.
        int GridY;
        sll realX;
        sll realY;
        bool outofarea;
};

#endif

