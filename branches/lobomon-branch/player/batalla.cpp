#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "map.h"
#include "scene.h"

void Battle_Scene::init(Audio theaudio, bool * run,unsigned char * TheScene)
{
     indexX=0,indexY=1;
     myaudio=theaudio;
     theaudio.musicload("../Music/2003fightopening.mid");
     System.init_Sistem();
     System.setimg("../System/system.png");
     fuente.init_Font();
     title.x=0;
	 title.y=0;
     title.setimg("../Backdrop/grassyplain.png");
     running=  run;   
     NScene=TheScene;
}

 void Battle_Scene::status()
{Random random = new java.util.Random();

    heroMagic=400;
    heroSpeed=400;
    heropower=400;
    herodefense=200;
    
    enemymaxHp=800+Math.abs(random.nextInt())% 300+1;
     enemymaxMP=200;
     enemyHp=enemymaxHp; 
     enemyMP=enemymaxMP;
     enemyMagic=100;
     enemySpeed=100;
     enemypower=300+Math.abs(random.nextInt())% 300+1;
    enemydefense=50+Math.abs(random.nextInt())% 300+1;
}

void Battle_Scene::init2()///1
{
status();//inisialisa los estatus de batalla
///////////////////////////////////////////////incializa sprites	
battler=Battler();//inicializa sprites?
enemy=Enemy();

index=planeSprite("/puntero.png");
lm.append(index); 
 message=messagepaper(8,3);
 message.setPosition(0,getHeight()- message.getHeight());// dibujar sprite
 lm.append(message); 
index.setRefPixelPosition(10,getHeight()-message.getHeight());
enemy.setRefPixelPosition(getWidth(),enemy.getHeight());
battler.setRefPixelPosition(battler.getHeight()+10,getHeight()-message.getHeight());
lm.append(battler); 
lm.append(enemy); 	
lm.append(background); 
battler.setFrameSequence(waiturn);
enemy.setFrameSequence(ewaiturn);
///////////////////////////////////////////////termina sprites	
indexX=1;indexY=1;maxindexX=2;maxindexY=2;
}


bool Battle_Scene::  batlestate()////5
{
if(heroHp<=0)
{int  count;
	long start, end;                        //toma de tiempos de inicio y final
	int duration;   
     Graphics g = getGraphics();
		battler.setFrameSequence(die);
	count=battler.getFrameSequenceLength();
	while (count>0)
	{	start = System.currentTimeMillis(); 	    
	render(g);                          
			paint(g);
			end = System.currentTimeMillis();     // tiempo al finalizar
			duration = (int)(end - start);        // tiempo tardado
			if (duration < frameTime*2) {          //  control de FPS
				try {                      //si tardo menos de lo esperado
					Thread.sleep(frameTime - duration);//que duerma
				} catch (InterruptedException ie) {done=true;}}
	count--;	
	}	
	
*NScene=3;
}
//dinero
if(enemyHp<=0)
{dinero=dinero+enemypower/10;
long start, end;                        //toma de tiempos de inicio y final
	int duration,count;   
     Graphics g = getGraphics();
	enemy.setFrameSequence(edie);
	count=enemy.getFrameSequenceLength();
	while (count>0)
	{	start = System.currentTimeMillis(); 	    
	render(g);                          
			paint(g);
			end = System.currentTimeMillis();     // tiempo al finalizar
			duration = (int)(end - start);        // tiempo tardado
			if (duration < frameTime*2) {          //  control de FPS
				try {                      //si tardo menos de lo esperado
					Thread.sleep(frameTime - duration);//que duerma
				} catch (InterruptedException ie) {done=true;}}
	count--;	
	}	

endbatle();
return false;
	}return true;
	
}


void Battle_Scene:: enemyaction()/////4
{
	int damange;
	enemy.setFrameSequence(eatack);
	long start, end;                        //toma de tiempos de inicio y final
	int duration,count;   
    Graphics g = getGraphics();
	count=enemy.getFrameSequenceLength();
	while (count>0)
	{	start = System.currentTimeMillis(); 	    
	render(g);                          
			paint(g);
			end = System.currentTimeMillis();     // tiempo al finalizar
			duration = (int)(end - start);        // tiempo tardado
			if (duration < frameTime*2) {          //  control de FPS
				try {                      //si tardo menos de lo esperado
					Thread.sleep(frameTime - duration);//que duerma
				} catch (InterruptedException ie) {done=true;}}
	count--;	
	}
		enemy.setFrameSequence(ewaiturn);
	damange=enemypower-herodefense;
	if (damange<0)
	damange=0;
	heroHp=heroHp-(damange);
	batlestate();
	
}

 void Battle_Scene:: cure (int tipe)/////5
{   int damange, count;
	damange=100*tipe;
	heroHp=heroHp+(damange);
	if(heroHp>heromaxHp)
	heroHp=heromaxHp;
	enemyaction();

}

 void Battle_Scene:: atack (int tipe)////3
{   int damange, count;
	long start, end;                        //toma de tiempos de inicio y final
	int duration;   
     Graphics g = getGraphics();
	battler.setFrameSequence(atack);
	count=battler.getFrameSequenceLength();
	while (count>0)
	{	start = System.currentTimeMillis(); 	    
	render(g);                          
			paint(g);
			end = System.currentTimeMillis();     // tiempo al finalizar
			duration = (int)(end - start);        // tiempo tardado
			if (duration < frameTime*2) {          //  control de FPS
				try {                      //si tardo menos de lo esperado
					Thread.sleep(frameTime - duration);//que duerma
				} catch (InterruptedException ie) {done=true;}}
	count--;	
	}
		battler.setFrameSequence(waiturn);
	damange=heropower-enemydefense;
	if (damange<0)
	damange=0;
	enemyHp=enemyHp-(damange*tipe);
	if (batlestate())
	enemyaction();

}


 void Menu_Easy::updatekey() {
  unsigned char * keyData;
  static int delay=0;  
  delay++;
  
  if (desided==false)
    if(delay==4)
        {
          keyData = SDL_GetKeyState(NULL);
            if ( keyData[SDLK_ESCAPE] ) running = false;
       
        if ( keyData[SDLK_LEFT]  ) {indexX--;}
        if ( keyData[SDLK_RIGHT] ) {indexX++;}
        if ( keyData[SDLK_UP]    ) {indexY--;myaudio.soundload("../Sound/Cursor1.wav");}
        if ( keyData[SDLK_DOWN]  ) {indexY++;myaudio.soundload("../Sound/Cursor1.wav");}		

        if ( keyData[LMK_Z]  ) {
        myaudio.soundload("../Sound/Decision2.wav"); 
         true;
           }
        if (indexX<0)
        indexX=maxindexX;
        if (indexX>maxindexX)
        indexX=0;
        if (indexY<0)
        indexY=maxindexY;
        if (indexY>maxindexY)
        indexY=0;
        delay=0;
    }    
 }
public void lista(int tipe)
{objetlist=true;
if (tipe==1)
atkit=true;
else
atkit=false;

lista=messagepaper(6,6);
 if(battle)
 lista.setPosition(0,getHeight()- lista.getHeight());// dibujar sprite
 else
  lista.setPosition(getWidth()- lista.getWidth(),0);
 lm.insert(lista, 1);
lm.remove(index);
 lm.insert(index, 0);
 	
 if (tipe==2)
{Items[0]= new Item("pizza",1);
Items[1]= new Item("pizza2",1);
Items[2]= new Item("pizza3",1);
Items[3]= new Item("pizza4",1);
Items[4]= new Item("pizza5",1);
Items[5]= new Item("pizza6",1);
Items[6]= new Item("pizza7",1);
Items[7]= new Item("pizza8",1);}
else
{Items[0]= new Item("especial 1",1);
Items[1]= new Item("especial 2",1);
Items[2]= new Item("especial 3",1);
Items[3]= new Item("especial 4",1);
Items[4]= new Item("especial 5",1);
Items[5]= new Item("especial 6",1);
Items[6]= new Item("especial 7",1);
Items[7]= new Item("especial 8",1);}
rangelist=5;
maxindexY=rangelist;
menustring1=Items[0].name;
menustring2=Items[1].name;
menustring3=Items[2].name;
menustring4=Items[3].name;
menustring5=Items[4].name;
indexX=1;
  	indexY=1;
}
public void inputlist() {///2
		 int keyStates = getKeyStates();//estado precinado no precionado
       	if ((keyStates & LEFT_PRESSED) != 0) {indexX--;}
       	if ((keyStates & RIGHT_PRESSED) != 0) {indexX++;}
       	if ((keyStates & UP_PRESSED) != 0) {indexY--;}
       	if ((keyStates & DOWN_PRESSED) != 0) {	indexY++;}		
        if ( (keyStates & FIRE_PRESSED) != 0 ){
         objetlist=false;
         lm.remove(lista);	
        if (atkit)
      atack(indexY);
      else
      cure(indexY);
        }
       if (indexX<=0)
       indexX=maxindexX;
       if (indexX>maxindexX)
       indexX=1;
       if (indexY<=0)
       indexY=8;
       if (indexY>8)
       indexY=1;
       
       if (indexY>rangelist)///modificacion a los strins mostrados en el menu
      {menustring1=Items[indexY-rangelist].name;
       menustring2=Items[indexY-rangelist+1].name;
       menustring3=Items[indexY-rangelist+2].name;
       menustring4=Items[indexY-rangelist+3].name;
       menustring5=Items[indexY-rangelist+4].name;}
       else
       {menustring1=Items[0].name;
       menustring2=Items[1].name;
       menustring3=Items[2].name;
       menustring4=Items[3].name;
       menustring5=Items[4].name;
       }
       
       
}


public void action() {
			if((indexY==1)&&(indexX==1))
			{if (title){newgame();}
		  if(mainmenu) {lista(2);}
		  }		
			if((indexY==3)&&(indexX==1))	
{	if (title){	done = true; exit=true;
try {player.stop();
	} catch (Exception ex) {}
	}
	  if(mainmenu){Selecsave(1);}}
		
				if((indexY==2)&&(indexX==2)){			
if (battle){endbatle();}}
		if((indexY==1)&&(indexX==1)){			
if (battle){atack(1);}}

				if((indexY==2)&&(indexX==1)){			
                 if (battle){lista(1);}
                 	if (title){Selecsave(2);}
                  if(mainmenu){Status();}
                 }

	if((indexY==1)&&(indexX==2)){			
if (battle){lista(2);}}
	if((indexY==4)&&(indexX==1)){	
		done = true;exit=true; try {player.stop();
	} catch (Exception ex) {}}

		}
		public void inputlist() {
		 int keyStates = getKeyStates();//estado precinado no precionado
       	if ((keyStates & LEFT_PRESSED) != 0) {indexX--;}
       	if ((keyStates & RIGHT_PRESSED) != 0) {indexX++;}
       	if ((keyStates & UP_PRESSED) != 0) {indexY--;}
       	if ((keyStates & DOWN_PRESSED) != 0) {	indexY++;}		
        if ( (keyStates & FIRE_PRESSED) != 0 ){
         objetlist=false;
         lm.remove(lista);	
        if (atkit)
      atack(indexY);
      else
      cure(indexY);
        }
       if (indexX<=0)
       indexX=maxindexX;
       if (indexX>maxindexX)
       indexX=1;
       if (indexY<=0)
       indexY=8;
       if (indexY>8)
       indexY=1;
       
       if (indexY>rangelist)
      {menustring1=Items[indexY-rangelist].name;
       menustring2=Items[indexY-rangelist+1].name;
       menustring3=Items[indexY-rangelist+2].name;
       menustring4=Items[indexY-rangelist+3].name;
       menustring5=Items[indexY-rangelist+4].name;}
       else
       {menustring1=Items[0].name;
       menustring2=Items[1].name;
       menustring3=Items[2].name;
       menustring4=Items[3].name;
       menustring5=Items[4].name;
       }
       
       
}
