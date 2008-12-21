#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "../sprites/sprite.h"
#include "../tools/key.h"
#include "../tools/font.h"
#include "../tools/audio.h"
#include "../sprites/map.h"
#include <vector>
#include <string>
#include "../atributes/skill.h"
#include "../atributes/item.h"
#include "../atributes/Enemy.h"
#include "../atributes/Player.h"
#include "../tools/math-sll.h"
#include "../atributes/CActor.h"
#include "scene.h"

void Map_Scene::init(Audio * audio,int SCREEN_X, int SCREEN_Y,unsigned char * TheScene,Player_Team * TheTeam)
{
       myteam=TheTeam;
        myaudio=audio;
        SCREEN_SIZE_X= SCREEN_X;
        SCREEN_SIZE_Y= SCREEN_Y;
      player=((*myteam).get_chara(0));
        npc.init_Chara();
       (*myteam).view.x = 0;
        (*myteam).view.y = 0;
        npc.setimg("../chara/Monster1.png");
Actor.init_Chara();
Actor.setimg("../chara/protagonist1.PNG");
Actor.setposXY(12,12);

        npc.setx(120);
	npc.sety(120);
        red.setimg("../title/malla.png");
        red.x=0;
        red.y=0;
       // ===[ LOADING MAP DATA ]==============================================
          Map.Load("../Map0001.lmu");
        Map.Chipset.GenerateFromFile("../ChipSet/Basis.png");
        (* myaudio).musicload("../Music/Town.mid");
        NScene=TheScene;
        moving=false;
        to_move=0;
        fuente.init_Font();
}
void Map_Scene::update(SDL_Surface* Screen)
{     // SDL_FillRect(Screen, NULL, 0x0);// Clear screen  inutil
Map.Render(Screen, 0, (*myteam).view.x, (*myteam).view.y); //dibuja mapa capa 1 con repecto a la vista
Map.Render(Screen, 1, (*myteam).view.x, (*myteam).view.y);//dibuja mapa capa 2 con repecto a la vista
Actor.drawc(Screen);
npc.addx(-(*myteam).view.x);
npc.addy(-(*myteam).view.y);
npc.drawc(Screen);
npc.addx(+(*myteam).view.x);
npc.addy(+(*myteam).view.y);

    // red.draw(Screen);
       //ver los datos del mapa

}


void Map_Scene::Scroll() {
//active the  scroll
(*myteam).view.x= Actor.Clamp((int) sll2dbl(Actor.realX)+ 8 - (SCREEN_SIZE_X>>1),0, (Map.MapWidth<<4)-SCREEN_SIZE_X);
          if(!Actor.outofarea)
          { Actor.x= (int)sll2dbl(Actor.realX)  -(*myteam).view.x;
          }else
           {Actor.x=(SCREEN_SIZE_X>>1)-8; }
(*myteam).view.y= Actor.Clamp((int) sll2dbl(Actor.realY) - (SCREEN_SIZE_Y>>1), 0, (Map.MapHeight<<4)-SCREEN_SIZE_Y);
          if(!Actor.outofarea)
          { Actor.y=(int)sll2dbl(Actor.realY)-(*myteam).view.y;
          }else
           {Actor.y=(SCREEN_SIZE_Y>>1); }
}
//minimo
 void Map_Scene::updatekey() {

Actor.MoveOnInput();
Scroll();

           if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cursor1.wav");* NScene=4; }
}


void Map_Scene::mapnpc()
{
         static unsigned char * keyData;
     		  keyData = SDL_GetKeyState(NULL);
       if ((Key_press_and_realsed(LMK_Z )) &&(npc.colision((*player))))
        {
       Enemy enemigo;
        enemigo.set_HP(20);
       enemigo.set_MaxHP(20);
       enemigo.set_MP(200);
       enemigo.set_MaxMP(200);
       enemigo.set_Attack(12);
       enemigo.set_Defense(50);
       enemigo.set_Speed(25);
       enemigo.set_Spirit(20);
       (enemigo.Batler).setimg("../Monster/Slime.png");
       (enemigo.Batler).setcols(1);
       (enemigo.Batler).setrows(1);
       (enemigo.Batler).x=140;
       (enemigo.Batler).y=100;
       enemigo.set_name("Limo");
        (*myteam).add_enemy(enemigo);
         enemigo.set_name("Murici");
       enemigo.set_HP(300);
       enemigo.set_MaxHP(30);
 (enemigo.Batler).setimg("../Monster/Bat.png");
      (enemigo.Batler).x=80;
(enemigo.Batler).y=100;
   (*myteam).add_enemy(enemigo);
enemigo.set_HP(35);
enemigo.set_MaxHP(35);
 enemigo.set_name("Ara�a");
 (enemigo.Batler).setimg("../Monster/Spider.png");
(enemigo.Batler).x=180;
(enemigo.Batler).y=100;
   (*myteam).add_enemy(enemigo);
  enemigo.set_HP(20);
       enemigo.set_MaxHP(20);
        enemigo.set_name("Avisp�n");
 (enemigo.Batler).setimg("../Monster/Bee.png");
(enemigo.Batler).x=140;
(enemigo.Batler).y=60;
   (*myteam).add_enemy(enemigo);
* NScene=2;

        }
}
void Map_Scene::dispose() {
     red.dispose();
//(*player).dispose();
npc.dispose();
Map.Chipset.dispose();
alexface.dispose();
(*myaudio).stopmusic();
}
