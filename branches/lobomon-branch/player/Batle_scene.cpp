#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "map.h"
#include <vector>
#include <string>
#include "player.h"
#include "enemy.h"
#include "scene.h"

void Batle_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene)
{    myaudio=theaudio;
    // myaudio.stopmusic();
     (*myaudio).musicload("../Music/Battle2.mid");
     title.x=0;
	 title.y=0;
     title.setimg("../Backdrop/Grass.png");
     window.init(320,80,0,160);
    // menu_os.init( theaudio, run, 0,4, 96, 80, 96, 160);
    // menu_os.visible=false;
     menu.init( theaudio, run, 0,4, 96, 80, 0, 160);
     str_Vector.push_back("Atacar ");
     str_Vector.push_back("Habilidades ");
     str_Vector.push_back("Objetos ");
     str_Vector.push_back("Defender ");
     str_Vector.push_back("Huir ");
     menu.setComands(& str_Vector);
     Myanim.setimg("../Battle/Sword1.png");
     Myanim.init_Anim();
     running=  run;   
     NScene=TheScene;
     state=0;
     set_stats();
}

void Batle_Scene::set_stats()
{
       jugador.HP=200;
       jugador.MaxHP=200;
       jugador.MP=200;
       jugador.MaxMP=200;
       jugador.Ataque=120;
       jugador.Defensa=50;
       jugador.Agilidad=25;
       jugador.Espiritu=20;
       
       enemigo.HP=200;
       enemigo.MaxHP=200;
       enemigo.MP=200;
       enemigo.MaxMP=200;
       enemigo.Ataque=120;
       enemigo.Defensa=50;
       enemigo.Agilidad=25;
       enemigo.Espiritu=20;
       (enemigo.Batler).setimg("../Monster/Slime.png");
       (enemigo.Batler).setcols(1);
       (enemigo.Batler).setrows(1);
(enemigo.Batler).x=140;
(enemigo.Batler).y=100;
}
void Batle_Scene::update(SDL_Surface* Screen)
{ 
    title.draw(Screen);
    window.draw(Screen);
   // menu_os.draw(Screen);
    menu.draw(Screen);
   (enemigo.Batler).draw(Screen); 
  if(state==1)
   atack(Screen);
  if(state==2)
   atacked();

}
void Batle_Scene::atack(SDL_Surface* Screen)
{ 
Myanim.x=(enemigo.Batler).x-(enemigo.Batler).getw();
Myanim.y=(enemigo.Batler).y-(enemigo.Batler).geth();
Myanim.draw(Screen);
if(Myanim.endanim)
{Myanim.reset();
                  state=2;}
}
void Batle_Scene::atacked()
{ static   int posxt =title.x;
  static   int posxe =(enemigo.Batler).x;
  static   int flag =0;
  static   int timer =0;
  static   int moves =0;
timer++;
if(timer==4)
{flag++;timer=0;}
if(flag%2)
 {
title.x=posxt+20;
(enemigo.Batler).x=posxe+20;
}
else
{flag=0;moves++;
title.x=posxt-20;
(enemigo.Batler).x=posxe-20;
}
if(moves==10)
{moves=0;
flag=0;
timer=0;
 title.x=posxt;
(enemigo.Batler).x=posxe;            
 state=0;
 menu.restarmenu();
 menu.visible=true;  
}
}
void Batle_Scene::action()
{ if(menu.visible)
  { if(menu.getindexY()==2)
  * running =false;
   if(menu.getindexY()==0)
    {state=1; 
     menu.visible=false;  
     }
     
    if(menu.getindexY()==3)
    {state=2; 
      jugador.Defensa+=10;
      menu.visible=false;
    }   
   if(menu.getindexY()==4)
    {state=1; 
    * NScene=1;
     }   
   }       
}

void Batle_Scene::updatekey() {
 menu.updatekey();
     if(menu.desition())
     action();
     }
void Batle_Scene::dispose() {
Myanim.dispose();
title.dispose();
window.dispose();
(enemigo.Batler).dispose();
(*myaudio).stopmusic();
menu.dispose();
}

