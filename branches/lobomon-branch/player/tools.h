/*tools.h, miscellaneous shared routines.
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

#ifndef TOOLS_H
#define TOOLS_H

//=========================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "SDL.h"
//=========================================================================

// --- Chunk structure -----------------------------------------------------
struct t_chunk
{
    Uint8 id;

    union
    {
        Uint64 length;
        Uint64 events_number;
    };

    Uint64 bytes_read;
};

// --- Read functions ---------------------------------------------------------
Uint64 read_compressed_integer(FILE *file_stream);
std::string read_string(FILE *file_stream);
std::string read_string(FILE *file_stream, Uint8 length);

// --- My_surface Tools -------------------------------------------------------
struct Color
{
    Uint8 red_color, green_color, blue_color;
    // ------------------------------------------------------------------------
    Color()
    {
        red_color = green_color = blue_color = 0;
    }
    Color(int n_red, int n_green, int n_blue)
    {
        red_color       = n_red;
        green_color     = n_green;
        blue_color      = n_blue;
    }

    Uint64 get_color_from_format(SDL_PixelFormat *fmt)
    {
        return SDL_MapRGB(fmt, red_color, green_color, blue_color);
    }
};

void set_transparency(SDL_Surface *ima);
SDL_Surface     *create_surface(int Width, int Height);
SDL_Surface     *load_surface(std::string file_name);
SDL_Surface     *grab_from_surface(SDL_Surface *surface_source, int sX, int sY, int sW, int sH);
void draw_surface(SDL_Surface *My_destiny, int dX, int dY, SDL_Surface *surface_source, int sX = 0, int sY = 0, int sW=-1, int sH=-1);

#endif
