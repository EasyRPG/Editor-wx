/* deltatime.h, EasyRPG player delta time class declaration file.
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

#ifndef DELTATIME_H
#define DELTATIME_H
///perfesto

class Delta_time
{
    public:
        // Methods
        Delta_time (int p_ideal_fps);
        void        set_ideal_fps(int p_ideal_fps);
        void        clear();
        void        update();
        // Attributes
        float       delta_time;

    private:
        long        ideal_fps;
        float       ideal_time;
        float       time_previous;
        float       time_current;

        float       delta_time_array[16];
        int         delta_current_vector;
};

#endif

