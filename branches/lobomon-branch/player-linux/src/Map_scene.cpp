#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "tools.h"
#include "map.h"
#include <vector>
#include <string>
#include "skill.h"
#include "item.h"
#include "Enemy.h"
#include "Player.h"
#include "scene.h"
//void Map_Scene::init(Audio myaudio, int argc, char** argv)

/*Map_Scene::~Map_Scene()
{
}
Map_Scene::Map_Scene()
{
}*/
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

        npc.setx(120);
	npc.sety(120);
     //  red.setimg("../title/malla.png"); 
      //  red.x=0;
      //  red.y=0;
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
{      SDL_FillRect(Screen, NULL, 0x0);// Clear screen  inutil   
          Map.Render(Screen, 0, (*myteam).view.x, (*myteam).view.y); //dibuja mapa capa 1 con repecto a la vista
        Map.Render(Screen, 1, (*myteam).view.x, (*myteam).view.y);//dibuja mapa capa 2 con repecto a la vista
      (*player).drawc(Screen);   
          npc.addx(-(*myteam).view.x);
          npc.addy(-(*myteam).view.y);
          npc.drawc(Screen); 
         npc.addx(+(*myteam).view.x);
          npc.addy(+(*myteam).view.y);
       
mapnpc();
     
       //ver los datos del mapa
/*     
  red.draw(Screen);
    sprintf(stringBuffer, " %d ", Map.MapWidth);
          fuente.draw_temp_Text(Screen,stringBuffer, 10, 10);
          sprintf(stringBuffer, " %d ", Map.MapHeight);
          fuente.draw_temp_Text(Screen,stringBuffer, 10, 28);
          
          sprintf(stringBuffer, " X %d ", ((*player).x+4));//comenzamos en -4
          fuente.draw_temp_Text(Screen,stringBuffer, 25, 10);
          sprintf(stringBuffer, " Y %d ", ((*player).y+4));
          fuente.draw_temp_Text(Screen,stringBuffer, 25, 28);
          
          sprintf(stringBuffer, " map X %d ",  (*myteam).view.x);//comenzamos en -4
          fuente.draw_temp_Text(Screen,stringBuffer, 25, 40);
          sprintf(stringBuffer, " map Y %d ",  (*myteam).view.y);
          fuente.draw_temp_Text(Screen,stringBuffer, 25, 58);          
   //   */    
         
}
 void Map_Scene::updatekey() {

 unsigned char * keyData;
     		  keyData = SDL_GetKeyState(NULL);
            if ( keyData[SDLK_ESCAPE] ) running = false;

            
            if ( keyData[SDLK_LEFT]  ){
            if(!moving){to_move=4;moving=true;}
               if ((*player).dir!=3) (*player).dir=3; 
                (*player).frameupdate();
            }
            else//4
            {
            if ( keyData[SDLK_RIGHT] ){
            if(!moving){to_move=1;moving=true;}
               if ((*player).dir!=1) (*player).dir=1; 
               (*player).frameupdate();}
            else//3
            {
            if ( keyData[SDLK_UP]    ) {
            if(!moving){to_move=2;moving=true;}
               if ((*player).dir!=0) (*player).dir=0; 
               (*player).frameupdate();}
            else//2
            {
            if ( keyData[SDLK_DOWN]  ) {
            if(!moving){to_move=3;moving=true;}
               if ((*player).dir!=2) (*player).dir=2;
               (*player).frameupdate();
            }
            else
            {(*player).frame_ori();
             
            }
            }
            }
            }
               
           if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cursor1.wav");* NScene=4; }
           slow_move(); 

}
 void Map_Scene::slow_move() 
 {
     static int moves =0;
   if(moving==true)
   {
     if (to_move==1)//derecha
      {  if (moves<8)
        {

   if(((*player).x < (SCREEN_SIZE_X-20))&&//160
            (((*player).x <((SCREEN_SIZE_X/2-4)))||((*myteam).view.x>=((Map.MapWidth*16)-(SCREEN_SIZE_X) ))))     
				(*player).x+=2;
			else              
			  if ((*myteam).view.x<((Map.MapWidth*16)-(SCREEN_SIZE_X) ))
                     (*myteam).view.x+=2;
         moves++;
           }else
           {moves=0;
           moving=false;
           }
       }
     if (to_move==4)//izquierda
      {  if (moves<8)
        {
        if(((*player).x > (-4))&&
            (((*player).x >(SCREEN_SIZE_X/2-4))||((*myteam).view.x<=0)))     
				(*player).x-=2;
			else              
			     if ((*myteam).view.x>0)	
                     (*myteam).view.x-=2;
         moves++;
           }else
           {moves=0;
           moving=false;
           }
       }
     if (to_move==2)//arriva
      {  if (moves<8)
        {
           if(((*player).y > (-4))&&
            (((*player).y >(SCREEN_SIZE_Y/2-28))||((*myteam).view.y<=0)))     
				(*player).y-=2;
			else             
				if ((*myteam).view.y>0)	
                   (*myteam).view.y-=2;
         moves++;
           }else
           {moves=0;
           moving=false;
           }
       }
      if (to_move==3)//abajo
      {  if (moves<8)
        {
            if(((*player).y < (SCREEN_SIZE_Y-36))&&
            (((*player).y <(SCREEN_SIZE_Y/2-28))||((*myteam).view.y>=((Map.MapHeight*16)-(SCREEN_SIZE_Y)))))     
				(*player).y+=2;
			else            
				if ((*myteam).view.y<( (Map.MapHeight*16)-(SCREEN_SIZE_Y) ))
                                    (*myteam).view.y+=2;
         moves++;
           }else
           {moves=0;
           moving=false;
           }
       }
      
   }
  }
/*//atiguo basado en pixeles

 void Map_Scene::updatekey() {
   unsigned char * keyData;
     		  keyData = SDL_GetKeyState(NULL);
            if ( keyData[SDLK_ESCAPE] ) running = false;

            if ( keyData[SDLK_LEFT]  ){if ((*player).dir!=3) (*player).dir=3; 
                 if(((*player).x > 0)&&
            (((*player).x >(SCREEN_SIZE_X/2))||((*myteam).view.x<=0)))     
				(*player).x-=2;
			else              
			     if ((*myteam).view.x>0)	
                     (*myteam).view.x-=2;
             (*player).frameupdate();}
            if ( keyData[SDLK_RIGHT] ){if ((*player).dir!=1) (*player).dir=1; 
            if(((*player).x < (SCREEN_SIZE_X-24))&&
            (((*player).x <(SCREEN_SIZE_X/2))||((*myteam).view.x>=((SCREEN_SIZE_X/2)-Map.MapWidth))))     
				(*player).x+=2;
			else              
				if ((*myteam).view.x<( (SCREEN_SIZE_X/2) -Map.MapWidth))	
                                    (*myteam).view.x+=2;
            (*player).frameupdate();}
            if ( keyData[SDLK_UP]    ) {if ((*player).dir!=0) (*player).dir=0; 
            if(((*player).y > 0)&&
            (((*player).y >(SCREEN_SIZE_Y/2))||((*myteam).view.y<=0)))     
				(*player).y-=2;
			else             
				if ((*myteam).view.y>0)	
                   (*myteam).view.y-=2;
            (*player).frameupdate();}
            if ( keyData[SDLK_DOWN]  ) {if ((*player).dir!=2) (*player).dir=2;
            if(((*player).y < (SCREEN_SIZE_Y-32))&&
            (((*player).y <(SCREEN_SIZE_Y/2))||((*myteam).view.y>=((SCREEN_SIZE_Y/2)-Map.MapHeight))))     
				(*player).y+=2;
			else            
				if ((*myteam).view.y<( (SCREEN_SIZE_Y/2) -Map.MapHeight))
                                    (*myteam).view.y+=2;
            (*player).frameupdate();}
           if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cursor1.wav");* NScene=4; }
            
 }
*/

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
 enemigo.set_name("Araña");
 (enemigo.Batler).setimg("../Monster/Spider.png");
(enemigo.Batler).x=180;
(enemigo.Batler).y=100;
   (*myteam).add_enemy(enemigo);
  enemigo.set_HP(20);
       enemigo.set_MaxHP(20);
        enemigo.set_name("Avispón");
 (enemigo.Batler).setimg("../Monster/Bee.png");
(enemigo.Batler).x=140;
(enemigo.Batler).y=60;
   (*myteam).add_enemy(enemigo);    
* NScene=2; 
      
        }
}
void Map_Scene::dispose() {
//(*player).dispose();
npc.dispose();
Map.Chipset.dispose();
alexface.dispose();
(*myaudio).stopmusic();
}

