/*key.cpp, keyboard routines.
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

///Comentario de NeLo -> queda pendiente mirar alguno que estaba como antes de tocarlo, dejar para lo ultimo
#include "SDL.h"
bool key_pressed_and_released(Uint8 key)
{
    Uint8 *key_data;
    key_data = SDL_GetKeyState(NULL);
    if ( key_data[key] )
    {
        return(true);
    }
    else
    {
        return(false);
    }
}
