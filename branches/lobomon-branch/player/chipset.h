/*chipset.h, types and prototypes for the map tileset management.
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

#ifndef CHIPSET_H
#define CHIPSET_H

// *****************************************************************************
//=============================================================================
    #include <stdlib.h>
    #include <stdio.h>
    #include <string>
    #include "SDL.h"
    #include "tools.h"
//=============================================================================
// *****************************************************************************

    //===Chipset structure===================================================
    struct stChipset
    {
        // --- Fields declaration ----------------------------------------------

        // The chipset structure holds the graphic tileset of a chipset, as well
        // as their properties and the methods for correctly displaying them.
        SDL_Surface *My_surface;      // Chipset's base surface!
        SDL_Surface *chipset_surface;   // Chipset's precalculated surface

        // --- Methods declaration ---------------------------------------------
        bool generate_from_surface(SDL_Surface *My_surface);
        bool generate_from_file(std::string file_name);
        void Release();
        void dispose();
        void render_tile(SDL_Surface *My_destiny, int x_pos, int y_pos, Uint16 Tile, int frame);
        void render_water_tile(SDL_Surface *My_destiny, int x_pos, int y_pos, int frame, int Border, int Water, int Combination);
        void RenderDepthTile(SDL_Surface *My_destiny, int x_pos, int y_pos, int frame, int Depth, int DepthCombination);
        void render_terrain_tile(SDL_Surface *My_destiny, int x_pos, int y_pos, int Terrain, int Combination);
    };

#endif
