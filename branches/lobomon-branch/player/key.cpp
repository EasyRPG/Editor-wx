/* key.cpp, keyboard routines.
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

#include "SDL.h"
bool Key_press_and_realsed( unsigned char key )
{
  unsigned char * keyData;
  keyData = SDL_GetKeyState(NULL);
  static unsigned char Last_key;
        if (( keyData[key]  )&&(Last_key!=key)) {
           Last_key=key;
           return(true);
           }
        if ((!keyData[key])&&(Last_key==key)){
               Last_key=0; 
          } 
  return(false);
}
