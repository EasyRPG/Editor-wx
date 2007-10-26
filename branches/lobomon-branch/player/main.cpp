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
    #include <SDL/SDL_image.h>
    #include <SDL/SDL_mixer.h>

    #include "tools.h"
    #include "map.h"
    #include "bitmap.h"
    #include "sprite.h"
    #include "key.h"
    #include "font.h"
    #include "audio.h"
    #include <vector>
    #include <string>  
    #include "player.h"
    #include "enemy.h"     
    #include "scene.h"
    #define SCREEN_SIZE_X  320
    #define SCREEN_SIZE_Y  240
    
    bool running = true;
    unsigned char TheScene=0;
    Mix_Music *musica;
    SDL_Surface * Screen;
    unsigned long nextTicks = 0, fps = 0, frames = 0;
    char stringBuffer[255];
    unsigned char speed=4,timer=0;
    unsigned long FRECUENCIA=18;
    Scene * actual;
    Map_Scene mapas;
    Title_Scene titulo;
    GO_Scene fin;
    Save_Load_Menu_Scene        Menu_Save_Load;
    Euip_Menu_Scene             Menu_Euip;
    Main_Menu_Scene             Menu_Main;
    Objects_Menu_Scene          Menu_Objects;
    Stats_Menu_Scene            Menu_Stats;
    Skills_Menu_Scene           Menu_Skills;
    Batle_Scene                 batalla;
int fps_sincronizar (void)
{
	static int t;
	static int tmp;
	static int tl = 0;
    static int fps=0;
    static unsigned long nextTicks=0;
     char stringBuffer[255];
    fps++;
	t = SDL_GetTicks ();//t tiempo trascurrido tl tiempo anterior
    if(SDL_GetTicks() > nextTicks)//cada que pase un segudo
    {nextTicks = SDL_GetTicks() + 1000;
     sprintf(stringBuffer, "Map test - FPS %lu ", fps);//imprime el numero de frames
     SDL_WM_SetCaption (stringBuffer, NULL);
     if(fps<59)
     FRECUENCIA--;
     if(fps>59)
     FRECUENCIA++;
     fps=0;
    } 
    if (t - tl >= FRECUENCIA)// si se tarda mas que la frecuencia
	{ 
		tmp = (t - tl) / FRECUENCIA;
		tl += tmp * FRECUENCIA;//incremente tiempo  pasado
		return tmp;// retorna temp para que refresque mas la movimientos
	}
	else// si se tarda menos
	{
		SDL_Delay (FRECUENCIA - (t - tl));//retardalo la frecuencia menos el tiempo actual
		tl += FRECUENCIA;//incremente tiempo  pasado
		return 1;
	}
}
 void CambioScene(Audio myaudio, Scene  ** apuntador) //si no haces esto, te cartgas la memoria donde lo estas ejecutando
 {   unsigned static char LastScene=0; 
      if(TheScene!=LastScene)
     {  //si alguie encuntra una mejor forma de hacerlo que avise -_- 
      (**apuntador).dispose();
      if(TheScene==0)
        { 
         titulo.init(& myaudio,& running,& TheScene);
         *apuntador=(& titulo);
         LastScene=0;
         }
      if(TheScene==1)
        { 
         mapas.init(&myaudio,320,240,& TheScene);
        *apuntador=& mapas;
         LastScene=1;
         }
       if(TheScene==2)
        { 
         batalla.init(& myaudio,& running,& TheScene);
        *apuntador=& batalla;
         LastScene=2;
         } 
       if(TheScene==3)
        { 
        fin.init(& myaudio,& running,& TheScene);
        *apuntador=& fin;
         LastScene=3;
         }   
        if(TheScene==4)
        { 
        Menu_Main.init(& myaudio,& running,& TheScene);
        *apuntador=& Menu_Main;
         LastScene=4;
         }
        if(TheScene==5)
        { 
        Menu_Objects.init(& myaudio,& running,& TheScene);
        *apuntador=& Menu_Objects;
         LastScene=5;
         }
        if(TheScene==6)
        { 
        Menu_Skills.init(& myaudio,& running,& TheScene);
        *apuntador=& Menu_Skills;
         LastScene=6;
         }       
         if(TheScene==7)
        { 
        Menu_Euip.init(& myaudio,& running,& TheScene);
        *apuntador=& Menu_Euip;
         LastScene=7;
         }
        if(TheScene==8)
        { 
        Menu_Stats.init(& myaudio,& running,& TheScene);
        *apuntador=& Menu_Stats;
         LastScene=8;
         }  

        if(TheScene==9)
        { 
        Menu_Save_Load.init(& myaudio,& running,& TheScene);
        *apuntador=& Menu_Save_Load;
         LastScene=9;
         }                  
      }
 }
 
 
           
 int main(int argc, char** argv)
    {   Title_Scene titulo;
        Audio myaudio;
        
       

        int repxciclo,i,j;
	    // ===[ INITIALIZATION ]================================================
        // Start SDL
        if (SDL_Init (SDL_INIT_VIDEO) < 0) exit(1);
        atexit (SDL_Quit);

        const SDL_VideoInfo * videoInfo = SDL_GetVideoInfo();
        unsigned long flags = 0;

        if (videoInfo->hw_available) flags |= SDL_HWSURFACE;
        else                         flags |= SDL_SWSURFACE;
        if (videoInfo->blit_hw)      flags |= SDL_HWACCEL;
//flags |= SDL_FULLSCREEN;
        // Start screen (set to 320x240)
        Screen = SDL_SetVideoMode (SCREEN_SIZE_X  , SCREEN_SIZE_Y, 16, flags );
        if (Screen == NULL) exit(2);
        SDL_WM_SetCaption ("Proyecto 1", NULL);

        // ===[ ENTRY POINT ]===================================================

        SDL_Event event;
         titulo.init(& myaudio,& running,& TheScene);
        actual= & titulo;

        while (running)
        {   
            timer++;
            // Check for events
            while (SDL_PollEvent (&event));
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
	repxciclo = fps_sincronizar ();
    SDL_FillRect(Screen, NULL, 0x0);// Clear screen    
    for (i = 0; i < repxciclo; i ++)//estradas a lectrura de teclado
	{

         actual->updatekey( );
	}
           
    actual->update(Screen);
    CambioScene( myaudio, & actual);
    SDL_Flip(Screen); // Flip

    }        
    SDL_Quit();
    return true;
 }
