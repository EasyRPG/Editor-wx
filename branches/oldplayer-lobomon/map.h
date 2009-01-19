/* map.h, main map routines.
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

#ifndef MAP_H
#define MAP_H

// *****************************************************************************
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "SDL.h"
#include "tools.h"
#include "chipset.h"
//=============================================================================
// *****************************************************************************

//===Map structure=======================================================
struct map
{
    // --- Fields declaration ----------------------------------------------
    short       map_width, map_height;      // These determine the size of the map

    short       chipset_id;                // This points to the id of the My_chipset
    stChipset   my_chipset;              // the map uses, and the structure
    // contains the tileset data of it

    Uint8       loop_type;       // These flags determines if the map has to
    // loop infinitely.

    bool        parallax_background;
    std::string background_name;

    bool        horizontal_pan;
    bool        horizontal_auto_pan;
    short       horizontal_pan_speed;

    bool        vertical_pan;
    bool        vertical_auto_pan;
    short       vertical_pan_speed;

    Uint16 *lower_layer;
    Uint16 *upper_layer;

    int saved_times;
    int events_number;

    // --- Methods declaration ---------------------------------------------
    bool load(std::string file_name);
    void get_next_chunk(FILE *stream);
    void ProcessChunk(FILE *stream, t_chunk *Chunk);
    void show_information();

    void render(SDL_Surface *My_destiny, int layer, int x_camera, int camera_y);
};

#endif
