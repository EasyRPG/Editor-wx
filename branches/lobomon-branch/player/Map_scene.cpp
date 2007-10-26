#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "tools.h"
#include "map.h"
#include "bitmap.h"
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "scene.h"
//void Map_Scene::init(Audio myaudio, int argc, char** argv)
void Map_Scene::init(Audio * audio,int SCREEN_X, int SCREEN_Y,unsigned char * TheScene)
{       myaudio=audio;
        SCREEN_SIZE_X= SCREEN_X;
        SCREEN_SIZE_Y= SCREEN_Y;
        alexface.init_Faceset(5,180,0);
        alexface.setimg("../Faceset/Protagonist1.png");   
        player.init_Chara();
        npc.init_Chara();
        npc.setx(120);
	    npc.sety(120);
	    view.x = 0;
        view.y = 0;
        player.setimg("../chara/protagonist1.PNG"); 
        npc.setimg("../chara/Monster1.PNG"); 
       // ===[ LOADING MAP DATA ]==============================================

       // if (argc!=2)//no cargaremos nada del argumento
        Map.Load("Map0001.lmu");
       // else
     //	Map.Load(argv[1]);
       // Map.ShowInformation();
        Map.Chipset.GenerateFromFile("../chipset/Basis.png");
        (* myaudio).musicload("../Music/Town.mid");
        NScene=TheScene;
}
void Map_Scene::update(SDL_Surface* Screen)
{      
          Map.Render(Screen, 0, view.x, view.y); //dibuja mapa capa 1 con repecto a la vista
          Map.Render(Screen, 1, view.x, view.y);//dibuja mapa capa 2 con repecto a la vista
          player.draw(Screen);   
          npc.addx(-view.x);
          npc.addy(-view.y);
          npc.draw(Screen); 
          npc.addx(+view.x);
          npc.addy(+view.y);
          mapnpc();
}


 void Map_Scene::updatekey() {
   unsigned char * keyData;
     		  keyData = SDL_GetKeyState(NULL);
            if ( keyData[SDLK_ESCAPE] ) running = false;

            if ( keyData[SDLK_LEFT]  ){if (player.dir!=3) player.dir=3; 
                 if((player.x > 0)&&
            ((player.x >(SCREEN_SIZE_X/2))||(view.x<=0)))     
				player.x-=2;
			else              
			     if (view.x>0)	
                     view.x-=2;
             player.frameupdate();}
            if ( keyData[SDLK_RIGHT] ){if (player.dir!=1) player.dir=1; 
            if((player.x < (SCREEN_SIZE_X-24))&&
            ((player.x <(SCREEN_SIZE_X/2))||(view.x>=((SCREEN_SIZE_X/2)-Map.MapWidth))))     
				player.x+=2;
			else              
				if (view.x<( (SCREEN_SIZE_X/2) -Map.MapWidth))	
                                    view.x+=2;
            player.frameupdate();}
            if ( keyData[SDLK_UP]    ) {if (player.dir!=0) player.dir=0; 
            if((player.y > 0)&&
            ((player.y >(SCREEN_SIZE_Y/2))||(view.y<=0)))     
				player.y-=2;
			else             
				if (view.y>0)	
                   view.y-=2;
            player.frameupdate();}
            if ( keyData[SDLK_DOWN]  ) {if (player.dir!=2) player.dir=2;
            if((player.y < (SCREEN_SIZE_Y-32))&&
            ((player.y <(SCREEN_SIZE_Y/2))||(view.y>=((SCREEN_SIZE_Y/2)-Map.MapHeight))))     
				player.y+=2;
			else            
				if (view.y<( (SCREEN_SIZE_Y/2) -Map.MapHeight))
                                    view.y+=2;
            player.frameupdate();}
           if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cursor1.wav");* NScene=4; }
            
 }

void Map_Scene::mapnpc()
{  
         static unsigned char * keyData;
     		  keyData = SDL_GetKeyState(NULL);
       if ((Key_press_and_realsed(LMK_Z )) &&(npc.colision(player)))
        { //(*myaudio).soundload("../Sound/Monster2.wav");
// System.Exdraw(Screen,1, 0, 170,320,70);
 //        alexface.drawf(Screen);
 //        fuente.drawText(Screen,"Hola we, que haces?",60,180,255,255,255);
* NScene=2; 
      
        }
}
void Map_Scene::dispose() {
player.dispose();
npc.dispose();
Map.Chipset.dispose();
alexface.dispose();
(*myaudio).stopmusic();
}

