
#include <SDL/SDL.h>
#include "../tools/SDL_rotozoom.h"
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#define pi2 6.28318
#include "sprite.h"

#define TRUE 1
#define FALSE 0


void Sistem::init_Sistem()//esto es asi porque no se me ocurre aun algo mejor
{
	     cols=20;
	     rows=10;
}
void Sistem::draw (SDL_Surface * screen,int iframe,int posx,int posy)
{
	int w = getw();
	int h = geth();

	SDL_Rect fuente = {(iframe%cols)* w,(iframe/cols) * h, w, h};
	SDL_Rect rect = {posx,posy, 0, 0};
	SDL_BlitSurface (img, & fuente,	screen, &rect);
}

SDL_Surface * Sistem::CubeDraw (SDL_Surface * screen,int sizeX,int sizeY)
{   int w = getw();
	int h = geth();
    int i;
    int cubesX=((sizeX-2*w)/w+1);
    int cubesY=((sizeY-1*h)/h);
    draw (screen,4,0, 0);//primera parte del cuadrado
    for(i=0;i<cubesX;i++)
    draw (screen,5,w*(i+1), 0);//primera parte del cuadrado
    for(i=0;i<cubesY;i++)
    draw (screen,24,0,h*(i+1));
    draw (screen,7,(sizeX-w), 0);//segunda parte del cuadrado
    for(i=0;i<cubesY;i++)
    draw (screen,27,(sizeX-w), h*(i+1));
    draw (screen,64,0, (sizeY-h));//segunda parte del cuadrado
    for(i=0;i<cubesX;i++)
    draw (screen,65,w*(i+1), (sizeY-h));//primera parte del cuadrado
    draw (screen,67,(sizeX-w), (sizeY-h));//segunda parte del cuadrado

	return (screen);
}
SDL_Surface * Sistem::Exdraw (int sizeX,int sizeY)
{   SDL_Surface * Eximg;
    SDL_Surface * Eximg2;
    double zoomX =((double)sizeX/32);
    double zoomY = (((double)sizeY)/32);
        Eximg =SDL_CreateRGBSurface(SDL_SWSURFACE,32, 32, 16,0, 0,0, 0);// IMG_Load ("../System/system2.PNG");
	SDL_Rect fuente = {0 , 0,32,32};
	SDL_Rect rect = {0,0, 0, 0};
	SDL_BlitSurface (img, &fuente,	Eximg, &rect);
    Eximg2=zoomSurface(Eximg, zoomX,zoomY,0);
    SDL_FreeSurface(Eximg);
	return (CubeDraw ( Eximg2, sizeX, sizeY));
}
SDL_Surface * Sistem::Cube_select(int type,int sizeX,int sizeY)
{
    SDL_Surface * screen;
    screen = SDL_CreateRGBSurface(SDL_SWSURFACE, sizeX, sizeY, 16,0, 0,0, 0x000000ff);
    int w = getw();
	int h = geth();
    int i,j;
    int cubesX=((sizeX-2*w)/w+1);
    int cubesY=((sizeY-1*h)/h);

 	  for(j=1;j<cubesX+1;j++)
	    for(i=1;i<cubesY+1;i++)
	     draw (screen,(25+(4*type)),w*(j), h*(i));//cuadro
   draw (screen,(4+(4*type)),0, 0);//esquina izq arriva
    for(i=0;i<cubesX;i++)
    draw (screen,(5+(4*type)),w*(i+1), 0);//recta horisontal arriva
    for(i=0;i<cubesY;i++)
    draw (screen,(24+(4*type)),0,h*(i+1));//recta vertical izq
    draw (screen,(7+(4*type)),(sizeX-w), 0);//esquina derecha arriva
    for(i=0;i<cubesY;i++)
    draw (screen,(27+(4*type)),(sizeX-w), h*(i+1));//recta vertical derecha
    draw (screen,(64+(4*type)),0, (sizeY-h));//esquina izquierda abajo
    for(i=0;i<cubesX;i++)
    draw (screen,(65+(4*type)),w*(i+1), (sizeY-h));//recta horisontal abajo
    draw (screen,(67+(4*type)),(sizeX-w), (sizeY-h));//esquina derecha abajo

	return (screen);
}
SDL_Surface * Sistem::ExdrawT (int sizeX,int sizeY,int tipe)
{   SDL_Surface * Eximg;
    SDL_Surface * Eximg2;
    double zoomX =((double)sizeX/32);
    double zoomY = (((double)sizeY)/32);
    Eximg =SDL_CreateRGBSurface(SDL_SWSURFACE,32, 32, 16,0, 0,0, 0);// IMG_Load ("../System/system2.PNG");
	SDL_Rect fuente = {(32*tipe) , 0,32,32};
	SDL_Rect rect = {0,0, 0, 0};
	SDL_BlitSurface (img, &fuente,	Eximg, &rect);
    Eximg2=zoomSurface (Eximg, zoomX,zoomY,0);
    SDL_FreeSurface(Eximg);
	return (Eximg2);
}
void Faceset::init_Faceset(int posx,int posy,int theframe)//esto es asi porque no se me ocurre aun algo mejor
{
         x = posx;
	     y = posy;
	     frame = theframe;

         cols=4;//redefinir
	     rows=4;//redefinir
    	int w = 48;
    	int h = 48;
       SDL_Surface * Eximg;
       Eximg = SDL_CreateRGBSurface(SDL_SWSURFACE,w, h, 16,0, 0,0, 0);
	SDL_Rect fuente = {(frame%cols)* w,(frame/cols) * h, w, h};
	SDL_Rect rect = {0,0, 0, 0};
	SDL_BlitSurface (img, & fuente,	Eximg, &rect);
dispose();
set_surface(Eximg);

}

void Faceset::drawf (SDL_Surface * screen)
{
	int w = getw();
	int h = geth();

	SDL_Rect fuente = {(frame%cols)* w,(frame/cols) * h, w, h};
	SDL_Rect rect = {x,y, 0, 0};
	SDL_BlitSurface (img, & fuente,	screen, &rect);
}
void Chara::init_Chara()//esto es asi porque no se me ocurre aun algo mejor
{
         x = 12;
	     y = 12;
	     frame = 2;
	     dir = 0;
	     cols=3;
	     rows=4;
         animation[0][0] = 1;//por esto en rpgmake xp hay 4 colmunas
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
void Chara::frameupdate()
{static long delay=0;
        delay++;
        if(delay==10)
        {
        frame= (frame +1)%4;
        delay=0;
        }
}
void Chara::frame_ori()
{
        if(frame!=0)
        frame= 0;
}

void Chara::drawc (SDL_Surface * screen)
{    int realframe;
	int w = 24;//getw();
	int h =32;//geth();
	realframe=animation [dir][frame];
	SDL_Rect fuente = {(realframe%cols)* w,(realframe/cols) * h, w, h};
	SDL_Rect rect = {x, y, 0, 0};
	SDL_BlitSurface (img, & fuente,	screen, &rect);
}

void Animacion::init_Anim(int the_cols,int the_rows)//esto es asi porque no se me ocurre aun algo mejor
{
         x = 0;
	     y = 0;
	     frame = 0;
	     cols=the_cols;
	     rows=the_rows;
         maxframe=10;
         endanim=false;
         delay=0;
}
void Animacion::frameupdate()
{
        delay++;
        if(delay==10)
        {
        if(frame<maxframe)
        {frame++;
        }
        else
        {endanim=true;}
        delay=0;
        }
}
void Animacion::reset()
{
       delay=0;
       frame=0;
       endanim=false;
}
void Animacion::draw (SDL_Surface * screen)
{
	int w = getw();
	int h = geth();
	 frameupdate();
	if(!endanim)
   {
    SDL_Rect fuente = {(frame%cols)* w,(frame/cols) * h, w, h};
	SDL_Rect rect = {x, y, 0, 0};
	SDL_BlitSurface (img, & fuente,	screen, &rect);
    }
}
/*
void Batler::init_Batler()//esto es asi porque no se me ocurre aun algo mejor
{	    int i,j
         x = 50;
	     y = 50;
	     frame = 2;
	     dir = 0;
	     cols=4;
	     rows=6;
       for(i=0;i<cols;i++)
	     for(j=0;j<rows;j++)
         animation[i][j] = i+j%4;//por esto en rpgmake xp hay 4 colmunas


}
void Batler::frameupdate()
{static long delay=0;
        delay++;
        if(delay==10)
        {if(frame==3)
        endanimation=true;
        frame= (frame +1)%4;
        delay=0;
        }
}
int Batler::Get_center_X()
{return(x+getw()/2)
}
int Batler::Get_center_Y()
{return(y+geth()/2)
}

bool Batler::Move_to_XY(int moves, int posX,int posY)//movimiento de vector
{
     int MyX=Get_center_X();
     int MyY=Get_center_Y();

    if((MyY==posX)&& (MyX==posY))
      return (true);
     if(MyX!=posX)
    { x=moves+x;
     if(MyY!=posY)
     y=((posY-MyY)/(posX-MyX))*moves+y;}
     else
     {y=y+moves;}
   return (false);
}
bool Batler::Move_to(Batler Bt,int moves)//movimiento de vector
{
     int YourX=Bt.Get_center_X();
     int YourY=Bt.Get_center_Y();
   return ( Move_to_XY(moves,YourX,YourY) );
}

void Batler::draw (SDL_Surface * screen)
{    int realframe;
	int w = getw();
	int h = geth();
	realframe=animation [dir][frame];
	SDL_Rect fuente = {(realframe%cols)* w,(realframe/cols) * h, w, h};
	SDL_Rect rect = {x, y, 0, 0};
	SDL_BlitSurface (img, & fuente,	screen, &rect);
}
*/

void Sprite::setimg(const char* string)
     { visible=true;
     not_clean =true;
     img = IMG_Load (string);
     }
void Sprite::set_surface(SDL_Surface * imag)
 {    visible=true;
     not_clean =true;
     img=imag;
 }
void Sprite::dispose()
{
       if(not_clean)
      { SDL_FreeSurface(img);
      not_clean =false;}
}
void Sprite::draw (SDL_Surface * screen)
{   if(visible)
{	SDL_Rect rect = {x, y, 0, 0};
	SDL_BlitSurface (img, NULL,	screen, &rect);}
}

int Sprite::colision(Sprite sp) {
int w1,h1,w2,h2,x1,y1,x2,y2;

	w1=getw();			// ancho del sprite1
	h1=geth();			// altura del sprite1
	w2=sp.getw();		// ancho del sprite2
	h2=sp.geth();		// alto del sprite2
	x1=getx();			// pos. X del sprite1
	y1=gety();			// pos. Y del sprite1
	x2=sp.getx();		// pos. X del sprite2
	y2=sp.gety();		// pos. Y del sprite2

	if (((x1+w1)>x2)&&((y1+h1)>y2)&&((x2+w2)>x1)&&((y2+h2)>y1)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
