/* main.cpp, EasyRPG player main file.
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

    #include <stdlib.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include "tools.h"
    #include "map.h"

    int main(int argc, char** argv)
    {
        const char * usage = "Usage: lmu2bmp.exe map.lmu chipset.bmp output.bmp [ -i | -s ]";
        FILE *f;
        int iLayer = 1;
        int sLayer = 1;
        
        #ifdef WIN32
        // Redirect output to console
        freopen ("CON", "w", stdout);
        freopen ("CON", "w", stderr);
        #endif
        // Print title
        printf("\nEasyRPG lmu2bmp 1.0\n");
        printf("-------------------\n");
        
        // Check arguments
        if(argc != 4 && argc != 5)
        {
            printf("%s\n", usage);
            return 1;
        }
        f = fopen(argv[1], "rb");
        if(f == NULL)
        {
            printf("%s\n", usage);
            return 1;
        }
        fclose(f);
        f = fopen(argv[2], "rb");
        if(f == NULL)
        {
            printf("%s\n", usage);
            return 1;
        }
        fclose(f);
        if(argc == 5)
        {
            if(strcmp(argv[4], "-i") == 0)
                sLayer = 0;
            else if(strcmp(argv[4], "-s") == 0)
                iLayer = 0;
            else
            {
                printf("Invalid argument\n%s\n", usage);
                return 1;
            }
        }
        
        // Start SDL
        if (SDL_Init (SDL_INIT_VIDEO) < 0) exit(1);
        atexit (SDL_Quit);
        SDL_Surface *Screen = SDL_SetVideoMode(1, 1, 16, SDL_SWSURFACE);
        if (Screen == NULL) exit(2);

        // Load map data
        stMap Map;
        if(Map.Load(argv[1]) == false)
        {
            printf("%s\n", usage);
            return 1;
        }
        if(Map.Chipset.GenerateFromFile(argv[2]) == false)
        {
            printf("%s\n", usage);
            return 1;
        }

        // Create final surface with chipset palette
        SDL_Surface *bmpOutput = SDL_CreateRGBSurface(SDL_SWSURFACE, Map.MapWidth * 16, Map.MapHeight * 16, 8, 0, 0, 0, 0);
        SDL_Surface *bmpChipset = SDL_LoadBMP(argv[2]);
        bmpOutput->format->palette = bmpChipset->format->palette;
        
        // Render map
        if(iLayer)
            Map.Render(bmpOutput, 0, 0, 0);
        if(sLayer)
            Map.Render(bmpOutput, 1, 0, 0);

        // Save output bitmap
        if(SDL_SaveBMP(bmpOutput, argv[3]) == -1)
        {
            printf("%s\n", usage);
            return 1;
        }
        
        // Exit
        printf("Output saved in %s\n", argv[3]);
        return 0;
    }
