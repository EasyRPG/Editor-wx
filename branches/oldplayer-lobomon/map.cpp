/*map.cpp, main map routines.
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
#include "tools.h"
#include "map.h"
//=========================================================================

// --- Create list of chunks opcodes ---------------------------------------
enum map_chunks_enum //comentar a delapipol
{
    CHUNK_MAP_END_OF_BLOCK      = 0x00,
    CHUNK_MAP_CHIPSET           = 0x01,

    CHUNK_MAP_WIDTH             = 0x02,
    CHUNK_MAP_HEIGHT            = 0x03,

    CHUNK_MAP_TYPE_OF_LOOP      = 0x0B,
    CHUNK_MAP_PARALLAX_BACK     = 0x1F,
    CHUNK_MAP_BACKGROUND        = 0x20,

    CHUNK_MAP_HORIZONTAL_PAN    = 0x21,
    CHUNK_MAP_VERTICAL_PAN      = 0x22,

    CHUNK_MAP_HORIZONTAL_PAN_A  = 0x23,
    CHUNK_MAP_HORIZONTAL_PAN_SP = 0x24,

    CHUNK_MAP_VERTICAL_PAN_A    = 0x25,
    CHUNK_MAP_VERTICAL_PAN_SP   = 0x26,

    CHUNK_MAP_LOWER_LAYER       = 0x47,
    CHUNK_MAP_UPPER_LAYER       = 0x48,
    CHUNK_MAP_EVENTS_LAYER      = 0x51,

    CHUNK_MAP_TIMES_SAVED       = 0x5B
};

enum map_event_chunks
{
    CHUNK_EVENT_NAME            = 0x01,
    CHUNK_EVENT_X               = 0x02,
    CHUNK_EVENT_Y               = 0x03,
    CHUNK_EVENT_PAGES           = 0x05
};

// --- Map class -----------------------------------------------------------
bool map::load(std::string file_name)
{
    // Open map file to read
    FILE            *stream;
    stream          = fopen(file_name.c_str(), "rb");

    // Get header and check if it's a valid file
    std::string     My_header = read_string(stream);
    if (My_header != "LcfMapUnit")
    {
        printf("Reading error: File is not a valid RPG2000 map\n");
        fclose(stream);
        return false;
    }

    // Set default data of the map
    chipset_id = 1;
    map_width = 20;
    map_height = 15;
    loop_type = 0;
    parallax_background = false;
    std::string background_name = "None";
    horizontal_pan = false;
    horizontal_auto_pan = false;
    horizontal_pan_speed = 0;
    vertical_pan = false;
    vertical_auto_pan = false;
    vertical_pan_speed = 0;
    lower_layer     = NULL;
    upper_layer     = NULL;
    events_number   = 0;

    // Get data from map
    get_next_chunk(stream);

    // Close stream
    fclose(stream);

    // Done
    return true;
}

void map::get_next_chunk(FILE *stream)
{
    t_chunk     chunk_info;
    Uint8       null;

    // Loop while we haven't reached the end of the file
    while (!feof(stream))
    {
        chunk_info.id           = read_compressed_integer(stream);
        chunk_info.length       = read_compressed_integer(stream);

        switch (chunk_info.id)
        {
        case CHUNK_MAP_CHIPSET:
            chipset_id          = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_WIDTH:
            map_width           = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_HEIGHT:
            map_height          = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_TYPE_OF_LOOP:
            loop_type          = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_PARALLAX_BACK:
            parallax_background = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_BACKGROUND:
            background_name   = read_string(stream, chunk_info.length);
            break;

        case CHUNK_MAP_HORIZONTAL_PAN:
            horizontal_pan    = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_VERTICAL_PAN:
            vertical_pan      = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_HORIZONTAL_PAN_A:
            horizontal_auto_pan = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_HORIZONTAL_PAN_SP:
            horizontal_pan_speed = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_VERTICAL_PAN_A:
            vertical_auto_pan  = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_VERTICAL_PAN_SP:
            vertical_pan_speed = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_LOWER_LAYER:
            // Allocate lower map layer
            lower_layer = new Uint16[chunk_info.length>>1];
            fread(lower_layer, sizeof(char), chunk_info.length, stream);
            break;

        case CHUNK_MAP_UPPER_LAYER:
            // Allocate upper map layer
            upper_layer = new Uint16[chunk_info.length >> 1];
            fread(upper_layer, sizeof(char), chunk_info. length, stream);
            break;

//                case CHUNK_MAP_EVENTS_LAYER:
//                    break;

        case CHUNK_MAP_TIMES_SAVED:
            saved_times = read_compressed_integer(stream);
            break;

        case CHUNK_MAP_END_OF_BLOCK:
            return;

        default:
            // Skip chunk
            while (chunk_info.length--) fread(&null, sizeof(char), 1, stream);
            break;
        }
    }
}

//void map::ProcessChunk(FILE *stream, t_chunk *Chunk)
//{
//
//}

void map::show_information()
{
    printf("Map information\n"
           "===========================================================\n");
    printf("My_chipset : %i\n", chipset_id);
    printf("Size : %ix%i\n", map_width, map_height);
    printf("Type of Loop : %i\n", loop_type);
    printf("Use parallax background : %i\n", parallax_background);
    if (parallax_background)
    {
        printf(" -> Background file : %s\n", background_name.c_str());
        printf(" -> Horizontal pan : %i\n", horizontal_pan);
        if (horizontal_pan)
        {
            printf(" --> Horizontal auto pan : %i\n", horizontal_auto_pan);
            if (horizontal_auto_pan)
            {
                printf(" ---> Horizontal pan speed : %i\n", horizontal_pan_speed);
            }
        }
        printf(" -> Vertical pan : %i\n", vertical_pan);
        if (vertical_pan)
        {
            printf(" --> Vertical auto pan : %i\n", vertical_auto_pan);
            if (vertical_auto_pan)
                printf(" ---> Vertical pan speed : %i\n", vertical_pan_speed);
        }
    }

    if (lower_layer != NULL)
    {
        printf("\nLower layer map data :\n");
        for (int y_pos = 0; y_pos < map_height; y_pos++ )
        {
            for (int x_pos = 0; x_pos < map_width; x_pos++ )
            {
                printf("%04X, ", lower_layer[x_pos + y_pos * map_width]);
            }
            printf("\n");
        }
    }
    if (upper_layer != NULL)
    {
        printf("\nUpper layer map data :\n");
        for (int y_pos = 0; y_pos < map_height; y_pos++ )
        {
            for (int x_pos = 0; x_pos < map_width; x_pos++ )
            {
                printf("%04X, ", upper_layer[x_pos+y_pos*map_width]);
            }
            printf("\n");
        }
    }
    printf("Number of times saved : %i\n", saved_times);
}

void map::render(SDL_Surface *My_destiny, int layer, int x_camera, int camera_y)
{
    // Declarate the variables we're going to use...
    int x_pos, y_pos, x_start, x_end, y_start, y_end;
    //int Tile;
    Uint16 *tile_pointer;
    Uint64  step_per_y;
    int frame = SDL_GetTicks()>>7;
    //SDL_Rect destiny_rect;

    // Calculate boundaries
    x_start=(x_camera>>4) - 1;
    y_start=(camera_y>>4) - 1;
    x_end  =((x_camera + My_destiny->w)>>4) + 1;
    y_end  =((camera_y + My_destiny->h)>>4) + 1;

    // Clipping
    if ( x_start < 0        ) x_start = 0;
    if ( y_start < 0        ) y_start = 0;
    if ( x_end   > map_width ) x_end   = map_width;
    if ( y_end   > map_height) y_end   = map_height;

    switch (layer)
    {
    case 0:
        // Calculate initial pointer and step
        tile_pointer    = &lower_layer[x_start + y_start *map_width];
        step_per_y      = map_width - (x_end-x_start);

        // Run through the whole map
        for ( y_pos = y_start; y_pos < y_end; y_pos++, tile_pointer += step_per_y )
        {
            for ( x_pos = x_start; x_pos < x_end; x_pos++, tile_pointer++ )
            {
                my_chipset.render_tile(My_destiny, (x_pos << 4) - x_camera, (y_pos << 4) - camera_y, *tile_pointer, frame);
            }
        break;
        }
    case 1:
        // Calculate initial pointer and step
        tile_pointer    = &upper_layer[x_start + y_start *map_width];
        step_per_y      = map_width - (x_end-x_start);

        // Run through the whole map
        for ( y_pos = y_start; y_pos < y_end; y_pos++, tile_pointer += step_per_y )
            {
                for ( x_pos = x_start; x_pos < x_end; x_pos++, tile_pointer++ )
                {
                    my_chipset.render_tile(My_destiny, (x_pos << 4) - x_camera, (y_pos << 4) - camera_y, *tile_pointer, frame);
                }
        break;
            }
    }
}
