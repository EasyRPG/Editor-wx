/*sprite.cpp, sprite routines.
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

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_rotozoom.h"
#include "SDL_image.h"
#include "sprite.h"

#define pi2 6.28318
#define TRUE 1
#define FALSE 0

void Sprite_system::init_video_system()
{
    columns     = 20;
    rows        = 10;
}
void Sprite_system::draw (SDL_Surface *screen,int i_frame,int x_pos,int y_pos)
{
    int weight  = get_weight();
    int height  = get_height();

    SDL_Rect my_sprite_font = {(i_frame % columns)*weight, (i_frame / columns) *height, weight, height};
    SDL_Rect My_rect={x_pos, y_pos, 0, 0};
    SDL_BlitSurface (actual_image, &my_sprite_font, screen, &My_rect);
}

SDL_Surface *Sprite_system::cube_draw (SDL_Surface *screen,int the_x_size,int the_y_size)
{
    int         weight  = get_weight();
    int         height       = get_height();
    int         i;
    int         x_cubes = ((the_x_size - 2 * weight) / weight + 1);
    int the_y_cubes = ((the_y_size - 1 * height) / height);

    draw (screen,4,0, 0);//first square part
    for (i = 0; i < x_cubes; i++)
    {
        draw (screen, 5, weight * (i + 1), 0);  //  first square part
    }
    for (i = 0; i < the_y_cubes; i++)
    {
        draw (screen, 24, 0, height * (i + 1));
    }
    draw (screen, 7, (the_x_size - weight), 0); //  second square part
    for (i = 0; i < the_y_cubes; i++)
    {
        draw (screen, 27, (the_x_size - weight), height * (i + 1));
    }
    draw (screen, 64, 0, (the_y_size - height));     //  second square part
    for (i = 0;i<x_cubes;i++)
    {
        draw (screen,65,weight*(i+1), (the_y_size-height));      //  first square part
    }
    draw (screen,67,(the_x_size-weight), (the_y_size-height));   //  second square part

    return (screen);
}
SDL_Surface *Sprite_system::ex_draw (int the_x_size,int the_y_size)
{
    SDL_Surface     *ex_image;
    SDL_Surface     *Eximg2;
    double x_zoom=((double)the_x_size/32);
    double y_zoom=(((double)the_y_size)/32);
    ex_image = SDL_CreateRGBSurface(SDL_SWSURFACE,32, 32, 16,0, 0,0, 0);// IMG_Load ("System/system2.PNG");
    SDL_Rect my_sprite_font={0 , 0,32,32};
    SDL_Rect My_rect={0,0, 0, 0};
    SDL_BlitSurface (actual_image, &my_sprite_font,	ex_image, &My_rect);
    Eximg2 = zoomSurface (ex_image, x_zoom,y_zoom,0);
    SDL_FreeSurface(ex_image);
    return (cube_draw ( Eximg2, the_x_size, the_y_size));
}
SDL_Surface *Sprite_system::cube_select(int type, int the_x_size, int the_y_size)
{
    SDL_Surface     *screen;
    screen          = SDL_CreateRGBSurface(SDL_SWSURFACE, the_x_size, the_y_size, 16, 0, 0, 0, 0x000000ff);
    int             weight      = get_weight();
    int             height           = get_height();
    int             i;
    int             j;
    int             x_cubes     =((the_x_size - 2 * weight) / weight + 1);
    int             the_y_cubes =((the_y_size - 1 * height) / height);

    for (j = 1;j<x_cubes+1;j++)
        for (i = 1;i<the_y_cubes+1;i++)
            draw (screen,(25+(4*type)),weight*(j), height*(i));//cuadro
    draw (screen,(4+(4*type)),0, 0);//esquina izq arriva
    for (i = 0;i<x_cubes;i++)
        draw (screen,(5+(4*type)),weight*(i+1), 0);//recta horisontal arriva
    for (i = 0;i<the_y_cubes;i++)
        draw (screen,(24+(4*type)),0,height*(i+1));//recta vertical izq
    draw (screen,(7+(4*type)),(the_x_size-weight), 0);//esquina derecha arriva
    for (i = 0;i<the_y_cubes;i++)
        draw (screen,(27+(4*type)),(the_x_size-weight), height*(i+1));//recta vertical derecha
    draw (screen,(64+(4*type)),0, (the_y_size-height));//esquina izquierda abajo
    for (i = 0;i<x_cubes;i++)
        draw (screen,(65+(4*type)),weight*(i+1), (the_y_size-height));//recta horisontal abajo
    draw (screen,(67+(4*type)),(the_x_size-weight), (the_y_size-height));//esquina derecha abajo

    return (screen);
}
SDL_Surface *Sprite_system::ex_draw_t (int the_x_size,int the_y_size,int tipe)
{
    SDL_Surface *ex_image;
    SDL_Surface *Eximg2;
    double x_zoom=((double)the_x_size/32);
    double y_zoom=(((double)the_y_size)/32);
    ex_image = SDL_CreateRGBSurface(SDL_SWSURFACE,32, 32, 16,0, 0,0, 0);// IMG_Load ("System/system2.PNG");
    SDL_Rect My_font_rect={(32*tipe) , 0,32,32};
    SDL_Rect My_rect={0,0, 0, 0};
    SDL_BlitSurface (actual_image, &My_font_rect, ex_image, &My_rect);
    Eximg2 = zoomSurface (ex_image, x_zoom,y_zoom,0);
    SDL_FreeSurface(ex_image);
    return (Eximg2);
}
void Faceset::init_faceset(int x_pos,int y_pos,int the_frame)//esto es asi porque no se me ocurre aun algo mejor
{
    x_pos = x_pos;
    y_pos = y_pos;
    frame = the_frame;

    columns = 4;//redefinir
    rows = 4;//redefinir
    int weight = 48;
    int height = 48;
    SDL_Surface *ex_image;
    ex_image = SDL_CreateRGBSurface(SDL_SWSURFACE,weight, height, 16,0, 0,0, 0);
    SDL_Rect my_sprite_font={(frame%columns)*weight,(frame/columns) *height, weight, height};
    SDL_Rect My_rect={0,0, 0, 0};
    SDL_BlitSurface (actual_image, & my_sprite_font, ex_image, &My_rect);
    dispose();
    set_surface(ex_image);

}

void Faceset::drawf (SDL_Surface *screen)
{
    int weight = get_weight();
    int height = get_height();

    SDL_Rect my_sprite_font={ (frame % columns) * weight, (frame / columns) * height, weight, height};
    SDL_Rect My_rect={x_pos, y_pos, 0, 0};
    SDL_BlitSurface (actual_image, &my_sprite_font,	screen, &My_rect);
}
void Character::init_chara()
{
    x_pos           = 12;
    y_pos           = 12;
    frame           = 2;
    actor_direction             = 0;
    columns         = 3;
    rows            = 4;
    animation[0][0] = 1;//this is the 4-columns rpg maker reason
    animation[0][1] = 0;
    animation[0][2] = 1;
    animation[0][3] = 2;
    animation[1][0] = 4;
    animation[1][1] = 3;
    animation[1][2] = 4;
    animation[1][3] = 5;
    animation[2][0] = 7;
    animation[2][1] = 6;
    animation[2][2] = 7;
    animation[2][3] = 8;
    animation[3][0] = 10;
    animation[3][1] = 9;
    animation[3][2] = 10;
    animation[3][3] = 11;
}
void Character::frame_update()
{
    static long delay = 0;
    delay++;
    if (delay == 10)
    {
        frame = (frame + 1) % 4;
        delay = 0;
    }
}

void Character::frame_origin()
{
    if (frame != 0)
    {
        frame = 0;
    }
}

void Character::draw_c(SDL_Surface *screen)
{
    int         real_frame;
    int         weight  = 24;//get_weight();
    int         height       = 32;//get_height();
    real_frame = animation [actor_direction][frame];
    SDL_Rect    my_sprite_font  = {(real_frame%columns)*weight,(real_frame/columns) *height, weight, height};   //  ojo aqui, sintaxis desconocida
    SDL_Rect    My_rect         ={x_pos, y_pos, 0, 0}; //  lo mismo
    SDL_BlitSurface (actual_image, &my_sprite_font, screen, &My_rect);
}

void Animation::init_anim(int the_columns,int the_rows)
{
    x_pos           = 0;
    y_pos           = 0;
    frame       = 0;
    columns     = the_columns;
    rows        = the_rows;
    max_frame   = 10;
    end_anim    = false;
    delay       = 0;
}

void Animation::frame_update()
{
    delay++;
    if (delay == 10)
    {
        if (frame < max_frame)
        {
            frame++;
        }
        else
        {
            end_anim = true;
        }
        delay = 0;
    }
}

void Animation::reset()
{
    delay       = 0;
    frame       = 0;
    end_anim    = false;
}

void Animation::draw (SDL_Surface *screen)
{
    int weight  = get_weight();
    int height  = get_height();
    frame_update();
    if (!end_anim)
    {
        SDL_Rect my_sprite_font =
        {
            (frame%columns)*weight,(frame/columns) *height, weight, height
        };
        SDL_Rect My_rect =
        {
            x_pos, y_pos, 0, 0
        };
        SDL_BlitSurface (actual_image, & my_sprite_font,	screen, &My_rect);
    }
}

/*
void battler::init_Batler()//esto es asi porque no se me ocurre aun algo mejor
{	    int i,j
         x_pos = 50;
	     y_pos = 50;
	     frame = 2;
	     actor_direction = 0;
	     columns = 4;
	     rows = 6;
       for(i = 0;i<columns;i++)
	     for(j = 0;j<rows;j++)
         animation[i][j]=i+j%4;//por esto en rpgmake xp hay 4 colmunas


}
void battler::frame_update()
{static long delay = 0;
        delay++;
        if(delay == 10)
        {if(frame == 3)
        endanimation = true;
        frame=(frame +1)%4;
        delay = 0;
        }
}
int battler::Get_center_X()
{return(x_pos+get_weight()/2)
}
int battler::Get_center_Y()
{return(y_pos+get_height()/2)
}

bool battler::Move_to_XY(int moves, int posX,int posY)//movimiento de vector
{
     int MyX = Get_center_X();
     int MyY = Get_center_Y();

    if((MyY == posX)&& (MyX == posY))
      return (true);
     if(MyX!=posX)
    { x_pos = moves+x_pos;
     if(MyY!=posY)
     y_pos=((posY-MyY)/(posX-MyX))*moves+y_pos;}
     else
     {y_pos = y_pos+moves;}
   return (false);
}
bool battler::Move_to(battler Bt,int moves)//movimiento de vector
{
     int YourX = Bt.Get_center_X();
     int YourY = Bt.Get_center_Y();
   return ( Move_to_XY(moves,YourX,YourY) );
}

void battler::draw (SDL_Surface *screen)
{    int real_frame;
	int weight = get_weight();
	int height = get_height();
	real_frame = animation [actor_direction][frame];
	SDL_Rect my_sprite_font={(real_frame%columns)*weight,(real_frame/columns) *height, weight, height};
	SDL_Rect My_rect={x_pos, y_pos, 0, 0};
	SDL_BlitSurface (actual_image, & my_sprite_font,	screen, &My_rect);
}
*/

void Sprite::set_image(const char *string)
{
    visible = true;
    not_clean = true;
    actual_image = IMG_Load (string);
}
void Sprite::set_surface(SDL_Surface *image)
{
    visible = true;
    not_clean = true;
    actual_image = image;
}
void Sprite::dispose()
{
    if (not_clean)
    {
        SDL_FreeSurface(actual_image);
        not_clean = false;
    }
}
void Sprite::draw (SDL_Surface *screen)
{
    if (visible)
    {
        SDL_Rect My_rect={x_pos, y_pos, 0, 0};
        SDL_BlitSurface (actual_image, NULL,	screen, &My_rect);
    }
}

int Sprite::colision(Sprite My_sprite)
{
    int sprite1_weight, sprite1_height, w2, h2, x1, y1, x2, y2;

    sprite1_weight      = get_weight();			// ancho del sprite1
    sprite1_height      = get_height();			// altura del sprite1
    w2                  = My_sprite.get_weight();		// ancho del sprite2
    h2                  = My_sprite.get_height();		// alto del sprite2
    x1                  = get_x();			// pos. x_pos del sprite1
    y1                  = get_y();			// pos. y_pos del sprite1
    x2                  = My_sprite.get_x();		// pos. x_pos del sprite2
    y2                  = My_sprite.get_y();		// pos. y_pos del sprite2

    if (((x1 + sprite1_weight) > x2) && ((y1 + sprite1_height) > y2) && ((x2 + w2) > x1) && ((y2 + h2) > y1))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
