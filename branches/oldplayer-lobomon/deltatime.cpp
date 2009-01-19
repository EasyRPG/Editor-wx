/*deltatime.cpp, deltatime routines.
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

#include <stdio.h>
#include "SDL.h"
#include "deltatime.h"

Delta_time::Delta_time(int p_ideal_fps)
{
    // calls the set function
    set_ideal_fps(p_ideal_fps);
}
void Delta_time::set_ideal_fps(int p_ideal_fps)
{
// Change FPS settings and calculates ideal time.
    ideal_fps       = p_ideal_fps;
    ideal_time      = 1 / float(ideal_fps);
    clear();
}
void Delta_time::clear()
{
    time_previous   = SDL_GetTicks();
    time_current    = SDL_GetTicks();
    for (int i = 15; i>=0; i--)
    {
        delta_time_array[i] = ideal_time;
    }
}
void Delta_time::update()
{
    // Calculate interval between frames
    time_previous   = time_current;
    time_current    = SDL_GetTicks();
    // Calculate delta interval
    delta_time_array[delta_current_vector] = (float(((time_current - time_previous) * ideal_fps) * 0.001));

    ++delta_current_vector &=0xF;     //++ y_pos nunca mayor a 15
    // Calculate average time
    delta_time      = 0.0f;
    for (int i = 0; i<15; i++)
    {
        delta_time  += delta_time_array[i];
    }
        delta_time  *=  0.0625f;//  It's the same as delta_time /=16, but faster.
                                //  to p_ideal_fps = 60 and 16-clicks interval
                                //  delta_time is aprox. 1 delta_time = 1.0f;


}
