/*font.cpp, font routines.
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
#include "SDL_ttf.h"
#include "font.h"

void Font::init_font()//esto es asi porque no se me ocurre aun algo mejor
{
    font_name="../Fonts/BASKVILL.TTF";
    size = 14;
    red_color = 255;
    green_color = 255;
    blue_color = 255;
    fU = 0; //unused
    TTF_Init();
}

SDL_Surface*Font::draw_text(char*string)
{
    TTF_Font *font = TTF_OpenFont(font_name, size);
    SDL_Color foreground_color={ red_color, green_color, blue_color, fU};
    SDL_Surface *text_surface = TTF_RenderText_Blended(font, string,foreground_color);
    TTF_CloseFont(font);
    return(text_surface);
}

void Font::draw_temp_text(SDL_Surface*screen,char*string, int x_pos, int y_pos)
{
    TTF_Font        *font = TTF_OpenFont(font_name, size);
    SDL_Color       foreground_color={ red_color, green_color, blue_color, fU };
    SDL_Surface     *text_surface = TTF_RenderText_Blended(font, string,foreground_color);
    SDL_Rect        textLocation={ x_pos, y_pos, 0, 0 };
    SDL_BlitSurface(text_surface, NULL, screen, &textLocation);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);

}
SDL_Surface*Font::draw_text(const char*string)
{
    TTF_Font*font = TTF_OpenFont(font_name, size);
    SDL_Color foreground_color={ red_color, green_color, blue_color, fU };
    SDL_Surface*text_surface = TTF_RenderText_Blended(font, string,foreground_color);
    TTF_CloseFont(font);
    return(text_surface);

}
SDL_Surface*Font::draw_text(char*string,int red_color, int b,int green_color, int u)
{
    TTF_Font*font = TTF_OpenFont(font_name, size);
    SDL_Color foreground_color={ red_color, green_color, b, u };
    SDL_Surface*text_surface = TTF_RenderText_Blended(font, string,foreground_color);
    TTF_CloseFont(font);
    return(text_surface);
}
void Font::quit()//esto es asi porque no se me ocurre aun algo mejor
{
    TTF_Quit();
}
