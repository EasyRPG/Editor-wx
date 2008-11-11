/*tools.cpp, miscellaneous shared routines.
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

//=========================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "tools.h"
//=========================================================================

Uint64 read_compressed_integer(FILE *file_stream)
{
    Uint64  value = 0;
    Uint8   temporal = 0;

    // int i = 0;
    do
    {
        value <<=7;

        // Get byte's value
        fread(&temporal, sizeof(char), 1, file_stream);

        // Check if it's a BER integer
        value |= temporal&0x7F;

    }
    while (temporal&0x80);

    return value;
}

std::string read_string(FILE *file_stream)
{
    Uint8 length;
    char    *characters;
    std::string  My_string;

    // Read string lenght's
    fread(&length, sizeof(char), 1, file_stream);
    if (length == 0) return std::string("");

    // Allocate string buffer
    characters = new char[length+1];
    memset(characters, 0, length+1);
    fread(characters, sizeof(char), length, file_stream);

    // Get string and free characters buffer
    My_string = std::string(characters);
    delete characters;

    return My_string;
}

std::string read_string(FILE *file_stream, Uint8 length)
{
    char        *characters;
    std::string My_string;

    // Allocate string buffer
    characters = new char[length+1];
    memset(characters, 0, length+1);
    fread(characters, sizeof(char), length, file_stream);

    // Get string and free characters buffer
    My_string = std::string(characters);
    delete characters;

    return My_string;
}

void set_transparency(SDL_Surface *ima)
{
    /*rm2k uses palette index 0 for transparent color instead of colorkey */
    SDL_Color colorkey = ima->format->palette->colors[0];
    SDL_Color *color;
    int maxColors = ima->format->palette->ncolors;
    for (int i = 1; i < maxColors; i ++)
    {
        /*Workaround to set transparency only in index 0 */
        color=& ima->format->palette->colors[i];
        if (colorkey.r == color->r && \
                colorkey.g == color->g && \
                colorkey.b == color->b)
        {
            if (color->b > 255 - 8)
                color->b -=8;
            else
                color->b +=8;
        }
    } /*Thanks to Hugo Ruscitti (www.losersjuegos.com.ar) for this fix */
}

SDL_Surface *create_surface(int Width, int Height)
{
    SDL_Surface *dummySurface = NULL;
    SDL_Surface *realSurface = NULL;
    SDL_Color color;
    Uint32 colorKey;

    dummySurface = SDL_CreateRGBSurface(SDL_SRCCOLORKEY, Width, Height, 8, 0, 0, 0, 0);
    if (!dummySurface) return NULL;

    set_transparency(dummySurface);

    realSurface  = SDL_DisplayFormat(dummySurface);
    if ( !realSurface ) return NULL;

    color = dummySurface->format->palette->colors[0];
    colorKey = SDL_MapRGB(realSurface->format, color.r, color.g, color.b);
    SDL_SetColorKey(realSurface, SDL_SRCCOLORKEY, colorKey);

    SDL_FreeSurface(dummySurface);

    if ( !realSurface ) return NULL;
    SDL_FillRect(realSurface, NULL, 0);

    return realSurface;

}

SDL_Surface *load_surface(std::string file_name)
{
    SDL_Surface *dummySurface = NULL;
    SDL_Surface *realSurface = NULL;
    SDL_Color color;
    Uint32 colorKey;

    dummySurface = IMG_Load(file_name.c_str());
    if (!dummySurface) return NULL;

    set_transparency(dummySurface);

    realSurface  = SDL_DisplayFormat(dummySurface);
    if ( !realSurface ) return NULL;

    color = dummySurface->format->palette->colors[0];
    colorKey = SDL_MapRGB(realSurface->format, color.r, color.g, color.b);
    SDL_SetColorKey(realSurface, SDL_SRCCOLORKEY, colorKey);

    SDL_FreeSurface(dummySurface);

    return realSurface;
}

void draw_surface(SDL_Surface *My_destiny, int dX, int dY, SDL_Surface *surface_source, int sX, int sY, int sW, int sH)
{
    if (sW == -1) sW = surface_source->w;
    if (sH == -1) sH = surface_source->h;

    SDL_Rect source_rect;
    source_rect.x = sX;
    source_rect.y = sY;
    source_rect.w = sW;
    source_rect.h = sH;

    SDL_Rect destiny_rect;
    destiny_rect.x = dX;
    destiny_rect.y = dY;
    destiny_rect.w = sW;
    destiny_rect.h = sH;

    SDL_BlitSurface(surface_source, &source_rect, My_destiny, &destiny_rect);
}

SDL_Surface *GrabFromSurface(SDL_Surface *surface_source, int sX, int sY, int sW, int sH)
{
    SDL_Surface *Return = create_surface(16, 16);
    draw_surface(Return, 0, 0, surface_source, sX, sY, sW, sH);

    return Return;
}
