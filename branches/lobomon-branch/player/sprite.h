/*sprite.h, EasyRPG player sprite class declaration file.
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

#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
protected:
    SDL_Surface     *actual_image;
    int             columns;
    int             rows;
    bool not_clean;
public:
    bool visible;
    int frame;
    int x_pos, y_pos;
    void set_x(int actual_x_pos)
    {
        x_pos = actual_x_pos;
    }
    void set_y(int actual_y_pos)
    {
        y_pos = y_pos;
    }
    void set_image(const char*string);
    void setcols(int icols)
    {
        columns = icols;
    }
    void setrows(int irows)
    {
        rows = irows;
    }
    void add_x(int c)
    {
        x_pos+=c;
    }
    void add_y(int c)
    {
        y_pos+=c;
    }
    void set_surface(SDL_Surface *imag);
    int get_x()
    {
        return x_pos;
    }
    int get_y()
    {
        return y_pos;
    }
    int get_weight()
    {
        return actual_image -> w / columns;
    }
    int get_height()
    {
        return actual_image->h/rows;
    }
    int get_cols()
    {
        return columns;
    }
    int get_rows()
    {
        return rows;
    }
    void draw(SDL_Surface *screen);
    void dispose();
    int colision(Sprite My_sprite);
};

class Character: public Sprite
{
private:
    int animation[4][4];//up right down left XP

public:
    int     dir;
    void    init_chara();
    void    frame_origin();
    void    frame_update();
    void    draw_c(SDL_Surface *screen);
};

class Faceset: public Sprite
{

public:
    void drawf (SDL_Surface *screen);
    void init_faceset(int x_pos,int y_pos,int theframe);
};

class Sprite_system: public Sprite
{
    private:
        SDL_Surface     *CubeDraw (SDL_Surface *screen,int sizeX,int sizeY);

    public:
        void init_video_system();
        void draw (SDL_Surface *screen,int i_frame,int x_pos,int y_pos);
        SDL_Surface     *Exdraw (int sizeX,int sizeY);
        SDL_Surface     *ex_draw_t (int sizeX,int sizeY,int tipe);
        SDL_Surface     *Cube_select(int type,int sizeX,int sizeY);
};
class Animation: public Sprite
{
private:
    int max_frame;
    short delay;
public:
    bool end_anim;
    void reset();
    void init_anim(int the_columns,int the_rows);
    void frame_update();
    void draw(SDL_Surface *screen);
};

#endif
