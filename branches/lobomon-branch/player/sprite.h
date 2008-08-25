/* sprite.h, EasyRPG player sprite class declaration file.
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

class Sprite {
protected:
            SDL_Surface * img;
          	int cols,rows;
          	bool not_clean;
public:
     bool visible;
    int frame;
    int x,y;   
    void setx(int posx) {x=posx;}
	void sety(int posy) {y=posy;}
	void setimg(const char* string);
    void setcols(int icols) {cols=icols;}
	void setrows(int irows) {rows=irows;}
	void addx(int c) {x+=c;}
	void addy(int c) {y+=c;}
	void set_surface(SDL_Surface * imag);
	int getx() {return x;}
	int gety() {return y;}
	int getw() {return img->w/cols;}
	int geth() {return img->h/rows;}
	int getcols() {return cols;}
	int getrows() {return rows;}
	void draw(SDL_Surface *screen);
	void dispose();
	int colision(Sprite sp);
};

class Chara: public Sprite {
private:
  int animation[4][4];//up right down left XP 
  
public:
    int dir;  
    void init_Chara();   
    void frame_ori();  
    void frameupdate();
   	void drawc(SDL_Surface *screen);
};

class Faceset: public Sprite {

public:
    void drawf (SDL_Surface * screen);
    void init_Faceset(int posx,int posy,int theframe);     
};

class Sistem: public Sprite {
private:
   SDL_Surface *CubeDraw (SDL_Surface * screen,int sizeX,int sizeY);
public:
    void init_Sistem();  
    void draw (SDL_Surface * screen,int iframe,int posx,int posy);
    SDL_Surface * Exdraw (int sizeX,int sizeY);
    SDL_Surface * ExdrawT (int sizeX,int sizeY,int tipe);
    SDL_Surface * Cube_select(int type,int sizeX,int sizeY);
};
class Animacion: public Sprite {
private:
  int maxframe;
  short delay;
public:
    bool endanim; 
    void reset();
    void init_Anim(int the_cols,int the_rows);  
    void frameupdate();
   	void draw(SDL_Surface *screen);
};

#endif
