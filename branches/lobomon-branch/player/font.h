/*font.h, EasyRPG player font class declaration file.
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

#ifndef FONT_H_
#define FONT_H_

class Font
{
    protected:
        int         size;
        int         red_color,  green_color,  blue_color,  fU; // fU = unused
        const char  *font_name;

    public:
        void        init_font();
        SDL_Surface *draw_text(char*string);
        SDL_Surface *draw_text(char*string,int red_color, int blue_color,int green_color, int u);
        SDL_Surface *draw_text(const char*string);
        void        draw_temp_text(SDL_Surface*screen,char*string, int x_pos, int y_pos);
        void        quit();

};

#endif
