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
#include "../control/scene.h"
/* Save_Load_Menu_Scene::~ Save_Load_Menu_Scene()
{
}
 Save_Load_Menu_Scene:: Save_Load_Menu_Scene()
{
}*/
void Save_Load_Menu_Scene::init(Audio * theaudio, bool * run,unsigned char * TheScene,Player_Team * TheTeam)
{    myteam=TheTeam;
     myaudio=theaudio;

   descripcion.init(320,30,0,0);
   descripcion.add_text("�D�nde deseas guardar la partida? ",10,5);
   Save_pos_1.init(320,70,0,30);
   Save_pos_2.init(320,70,0,100);
   Save_pos_3.init(320,70,0,170);
   running=  run;
   NScene=TheScene;
     retardo=0;
}

void Save_Load_Menu_Scene::update(SDL_Surface* Screen)
{
retardo++;
if(retardo==6)
{  Save_pos_1.draw(Screen);
   Save_pos_2.draw(Screen);
   Save_pos_3.draw(Screen);
   descripcion.draw(Screen);
   retardo=0;
}
}

void Save_Load_Menu_Scene::updatekey() {
  if (Key_press_and_realsed(LMK_X ))
        { (*myaudio).soundload("../Sound/Cansel2.wav");* NScene=4; }
     }
void Save_Load_Menu_Scene::dispose() {
   Save_pos_1.dispose();
   Save_pos_2.dispose();
   Save_pos_3.dispose();
   descripcion.dispose();
}