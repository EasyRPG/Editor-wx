/*chipset.cpp, routines for the map tileset management.
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

//===My_chipset structure===================================================
bool stChipset::generate_from_surface(SDL_Surface *My_surface)
{
    // Set base surface, used for generating the tileset
    My_surface     = My_surface;
    chipset_surface  = create_surface(32*16, 45*16);

    int current_tile = 0;

    // Generate water A
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<47; i++, current_tile++)
        {
            render_water_tile(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, j, 0, 0, i);
        }
    }
    // Generate water B
    for (int j = 0; j<3; j++)
    {
        for (int i = 0; i<47; i++, current_tile++)
        {
            render_water_tile(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, j, 1, 0, i);
        }
    }
    // Generate water C
    for (int j = 0; j<3; j++)
        {
            for (int i = 0; i<47; i++, current_tile++)
            {
                render_water_tile(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, j, 0, 3, i);
            }
        }
    // Generate water depth tiles
    for (int i = 0; i<48; i++, current_tile++)
            {
                RenderDepthTile(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, i/16, 1, i%16);
            }
    for (int i = 0; i<48; i++, current_tile++)
        {
            RenderDepthTile(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, i/16, 3, i%16);
        }
    // Generate animated tiles
    for (int j = 0; j<3; j++)
        for (int i = 0; i<4; i++, current_tile++)
            draw_surface(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, My_surface, 48+j*16, 64+i*16, 16, 16);

    // Generate terrain tiles
    for (int j = 0; j<12; j++)
        for (int i = 0; i<50; i++, current_tile++)
            render_terrain_tile(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, j, i);

    // Generate common tiles
    for (int i = 0; i<288; i++, current_tile++)
        draw_surface(chipset_surface, (current_tile%32)*16, (current_tile/32)*16, My_surface, 192+((i%6)*16)+(i/96)*96, ((i/6)%16)*16, 16, 16);

    // Done
    return true;
};

bool stChipset::generate_from_file(std::string file_name)
{
    SDL_Surface *file_surface = load_surface(file_name);
    return generate_from_surface(file_surface);
}
void stChipset::dispose()
{
    SDL_FreeSurface(My_surface);
    SDL_FreeSurface(chipset_surface);
}

//=========================================================================
void stChipset::render_tile(SDL_Surface *My_destiny, int x_pos, int y_pos, Uint16 Tile, int frame)
{
    if (Tile >=0x2710)         // Upper layer tiles
    {
        Tile -=0x2710;
        Tile +=0x04FB;
        draw_surface(My_destiny, x_pos, y_pos, chipset_surface, ((Tile&0x1F)<<4), ((Tile>>5)<<4), 16, 16);
    }
    else if (Tile >=0x1388)  // Lower layer tiles
    {
        Tile -=0x1388;
        Tile +=0x046B;
        draw_surface(My_destiny, x_pos, y_pos, chipset_surface, ((Tile&0x1F)<<4), ((Tile>>5)<<4), 16, 16);
    }
    else if (Tile >=0x0FA0)  // Terrain tiles
    {
        Tile -=0x0FA0;
        Tile +=0x0213;
        draw_surface(My_destiny, x_pos, y_pos, chipset_surface, ((Tile&0x1F)<<4), ((Tile>>5)<<4), 16, 16);
    }
    else if (Tile >=0x0BB8)  // Animated tiles
    {
        frame %=4;
        Tile = 0x0207 + (((Tile-0x0BB8)/50)<<2) + frame;
        draw_surface(My_destiny, x_pos, y_pos, chipset_surface, ((Tile&0x1F)<<4), ((Tile>>5)<<4), 16, 16);
    }
    else                      // Water tiles
    {
        frame %=3;
        int WaterTile =  Tile%50;
        int WaterType=((Tile/50)/20);
        Tile = WaterType*141+WaterTile+(frame*47);

        draw_surface(My_destiny, x_pos, y_pos, chipset_surface, ((Tile&0x1F)<<4), ((Tile>>5)<<4), 16, 16);
    }
}

void stChipset::render_water_tile(SDL_Surface *My_destiny, int x_pos, int y_pos, int frame, int Border, int Water, int Combination)
{
    int SFrame       = frame*16, SBorder = Border*48;
    //int SFrameBorder = SFrame+SBorder;
    Combination &=0x3F;

    // Since this function isn't meant to be used in realtime, we can allow
    // use nasty code here. First off, draw the water tile, for the background.
    draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame, 64+(Water*16), 16, 16);

    // Now, get the combination from the tile and draw it using this stupidly
    // hard coded routine. I've found out that this was easier than just find
    // out a damn algorithm.
    if (Combination & 0x20)
    {
        // This is where it gets nasty :S
        if (Combination > 0x29)
        {
            // Multiple edge possibilities
            switch (Combination)
            {
            case 0x2A:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 0, 16, 8);
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 24, 16, 8);
                break;
            case 0x2B:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 0, 8, 16);
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 32, 8, 16);
                break;
            case 0x2C:
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 8, 16, 8);
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 16, 16, 8);
                break;
            case 0x2D:
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 0, 8, 16);
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 32, 8, 16);
                break;
            case 0x2E:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 0, 16, 16);
                break;
            }
        }
        else
        {
            // Wall + inner edges
            switch ((Combination>>1)&0x07)
            {
            case 0x00:
                if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 32, 16, 16);
                else                  draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 16, 16, 16);
                break;
            case 0x01:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 0, 8, 8);           // Corner
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 24, 8, 8);        // Left/Right frame
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 32, 8, 8);      // Top/Bottom frame

                if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 48+8, 8, 8);
                break;
            case 0x02:
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 0, 8, 8);       // Corner
                draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 24, 8, 8);    // Left/Right frame
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 32, 8, 8);          // Top/Bottom frame

                if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 48+8, 8, 8);
                break;
            case 0x03:
                draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 8, 8, 8);     // Corner
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 16, 8, 8);      // Left/Right frame
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 40, 8, 8);        // Top/Bottom frame

                if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 48, 8, 8);
                break;
            case 0x04:
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 8, 8, 8);         // Corner
                draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 16, 8, 8);          // Left/Right frame
                draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 40, 8, 8);    // Top/Bottom frame

                if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 48, 8, 8);
                break;
            }
        }
    }
    else if (Combination & 0x10)
    {
        // Wall + inner edge cases. They're also easier to find out the
        // values here too
        switch ((Combination>>2)&0x03)
        {
        case 0x00:
            // render left wall
            draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 16, 8, 16);

            // render top right corner and bottom right corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos,   My_surface, SFrame+SBorder+8, 48, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 48+8, 8, 8);
            break;
        case 0x01:
            // render top wall
            draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 32, 16, 8);

            // render bottom right corner and bottom left corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 48+8, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos, y_pos+8,   My_surface, SFrame+SBorder, 48+8, 8, 8);
            break;
        case 0x02:
            // Right wall
            draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 16, 8, 16);

            // render bottom left corner and top left corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 48+8, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos, y_pos,   My_surface, SFrame+SBorder, 48, 8, 8);
            break;
        case 0x03:
            // Bottom wall
            draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 32+8, 16, 8);

            // render top left corner and top right corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos,   My_surface, SFrame+SBorder, 48, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 48, 8, 8);
            break;
        }
    }
    else
    {
        // Single inner edge cases. They're easier to find out the values
        // this way.
        if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos, My_surface, SFrame+SBorder, 48, 8, 8);
        if (Combination&0x02) draw_surface(My_destiny, x_pos+8, y_pos, My_surface, SFrame+SBorder+8, 48, 8, 8);
        if (Combination&0x04) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+SBorder+8, 48+8, 8, 8);
        if (Combination&0x08) draw_surface(My_destiny, x_pos, y_pos+8, My_surface, SFrame+SBorder, 48+8, 8, 8);
    }
}

void stChipset::render_terrain_tile(SDL_Surface *My_destiny, int x_pos, int y_pos, int Terrain, int Combination)
{
    Terrain +=4;
    int XTerrain=((Terrain%2)*48)+(Terrain/8)*96, YTerrain=((Terrain/2)%4)*64;


    // Since this function isn't meant to be used in realtime, we can allow
    // use nasty code here. First off, draw the water tile, for the background.
    draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+16, YTerrain+32, 16, 16);

    // Now, get the combination from the tile and draw it using this stupidly
    // hard coded routine. I've found out that this was easier than just find
    // out a damn algorithm.
    if (Combination & 0x20)
    {
        // This is where it gets nasty :S
        if (Combination > 0x29)
        {
            // Multiple edge possibilities
            switch (Combination)
            {
            case 0x2A:
                draw_surface(My_destiny, x_pos, y_pos, My_surface,     XTerrain,    YTerrain+16, 8, 16);
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface,   XTerrain+40, YTerrain+16, 8, 16);
                break;
            case 0x2B:
                draw_surface(My_destiny, x_pos, y_pos, My_surface,     XTerrain,    YTerrain+16, 16, 8);
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface,   XTerrain,    YTerrain+56, 16, 8);
                break;
            case 0x2C:
                draw_surface(My_destiny, x_pos, y_pos, My_surface,     XTerrain,    YTerrain+48, 8, 16);
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface,   XTerrain+40, YTerrain+48, 8, 16);
                break;
            case 0x2D:
                draw_surface(My_destiny, x_pos, y_pos, My_surface,     XTerrain+32, YTerrain+16, 16, 8);
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface,   XTerrain+32, YTerrain+56, 16, 8);
                break;
            case 0x2E:
                draw_surface(My_destiny, x_pos, y_pos, My_surface,     XTerrain,    YTerrain+16, 8, 8);
                draw_surface(My_destiny, x_pos+8, y_pos, My_surface,   XTerrain+40, YTerrain+16, 8, 8);
                draw_surface(My_destiny, x_pos, y_pos+8, My_surface,   XTerrain,    YTerrain+56, 8, 8);
                draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, XTerrain+40, YTerrain+56, 8, 8);
                break;
            case 0x31:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain, YTerrain, 16, 16);
                break;
            }
        }
        else
        {
            // Wall + inner edges
            switch ((Combination>>1)&0x07)
            {
            case 0x00:
                if (Combination&0x01)
                {
                    draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+16, YTerrain+16, 16, 8);
                    draw_surface(My_destiny, x_pos, y_pos+8, My_surface, XTerrain+16, YTerrain+56, 16, 8);
                }
                else
                {
                    draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain, YTerrain+32, 8, 16);
                    draw_surface(My_destiny, x_pos+8, y_pos, My_surface, XTerrain+32, YTerrain+32, 8, 16);
                }
                break;
            case 0x01:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain, YTerrain+16, 16, 16);
                if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, XTerrain+40, YTerrain+8, 8, 8);
                break;
            case 0x02:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+32, YTerrain+16, 16, 16);
                if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos+8, My_surface, XTerrain+32, YTerrain+8, 8, 8);
                break;
            case 0x03:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+32, YTerrain+48, 16, 16);
                if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+32, YTerrain, 8, 8);
                break;
            case 0x04:
                draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain, YTerrain+48, 16, 16);
                if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos, My_surface, XTerrain+40, YTerrain, 8, 8);
                break;
            }
        }
    }
    else if (Combination & 0x10)
    {
        // Wall + inner edge cases. They're also easier to find out the
        // values here too
        switch ((Combination>>2)&0x03)
        {
        case 0x00:
            // render left wall
            draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain, YTerrain+32, 16, 16);

            // render top right corner and bottom right corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos,   My_surface, XTerrain+40, YTerrain, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, XTerrain+40, YTerrain+8, 8, 8);
            break;
        case 0x01:
            // render top wall
            draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+16, YTerrain+16, 16, 16);

            // render bottom right corner and bottom left corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, XTerrain+40, YTerrain+8, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos, y_pos+8,   My_surface, XTerrain+32, YTerrain+8, 8, 8);
            break;
        case 0x02:
            // Right wall
            draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+32, YTerrain+32, 16, 16);

            // render bottom left corner and top left corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos+8,   My_surface, XTerrain+32, YTerrain+8, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos, y_pos,     My_surface, XTerrain+32, YTerrain, 8, 8);
            break;
        case 0x03:
            // Bottom wall
            draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+16, YTerrain+48, 16, 16);

            // render top left corner and top right corner
            if (Combination&0x01) draw_surface(My_destiny, x_pos, y_pos,     My_surface, XTerrain+32, YTerrain, 8, 8);
            if (Combination&0x02) draw_surface(My_destiny, x_pos+8, y_pos,   My_surface, XTerrain+40, YTerrain, 8, 8);
            break;
        }
    }
    else
    {
        // Single inner edge cases. They're easier to find out the values
        // this way.
        if (Combination&0x01)
        {
             draw_surface(My_destiny, x_pos, y_pos, My_surface, XTerrain+32, YTerrain, 8, 8);
        }
        if (Combination&0x02) draw_surface(My_destiny, x_pos+8, y_pos,   My_surface, XTerrain+40, YTerrain, 8, 8);
        if (Combination&0x04) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, XTerrain+40, YTerrain+8, 8, 8);
        if (Combination&0x08) draw_surface(My_destiny, x_pos, y_pos+8,   My_surface, XTerrain+32, YTerrain+8, 8, 8);
    }
}

void stChipset::RenderDepthTile(SDL_Surface *My_destiny, int x_pos, int y_pos, int frame, int Depth, int DepthCombination)
{
    int SFrame = frame*16;

    // Now render the depth part
    if (DepthCombination&0x01) draw_surface(My_destiny, x_pos,   y_pos,   My_surface, SFrame,   64+(Depth*16),   8, 8);
    if (DepthCombination&0x02) draw_surface(My_destiny, x_pos+8, y_pos,   My_surface, SFrame+8, 64+(Depth*16),   8, 8);
    if (DepthCombination&0x04) draw_surface(My_destiny, x_pos+8, y_pos+8, My_surface, SFrame+8, 64+(Depth*16)+8, 8, 8);
    if (DepthCombination&0x08) draw_surface(My_destiny, x_pos,   y_pos+8, My_surface, SFrame,   64+(Depth*16)+8, 8, 8);
}

//=========================================================================

