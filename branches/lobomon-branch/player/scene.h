#ifndef SCENE_H_
#define SCENE_H_
typedef struct view
{
	int x;
	int y;
} View;
class Menu_Easy {
protected: 
  int indexX,indexY;    
  int maxindexY,maxindexX;  
   Audio * myaudio;
   bool * running;
   bool desided;
   int delay;
public: 
   bool desition();
   int getindexY();
   int getindexX(); 
   void updatekey(); 
   void restarmenu();
   void init(Audio * theaudio, bool * run,int X,int Y);
};
class Window_Base  {
protected:
Sistem System;
Sprite tapiz;
Font fuente;
int pos_X,pos_Y;
int Size_X,Size_Y;
public: 
void dispose();
void init(int SizeX,int SizeY,int PosX,int PosY);
void draw(SDL_Surface* Screen);
};

class Window_Select   {
protected:
Sistem System;
Sprite tapiz;
Sprite cursor;
Font fuente;
Menu_Easy menu;
int pos_X,pos_Y;
int Size_X,Size_Y,Size_of_Block;
int Comand_X,Comand_Y;
std:: vector <std::string> * My_vector;
std:: vector <Sprite> My_Sprite;
Sprite text;

public: 
bool visible;
void updatekey(); 
int getindexX();
int getindexY();
void restarmenu();
bool desition();
void dispose();
void init(Audio * theaudio, bool * run,int ComandX,int ComandY,int SizeX,int SizeY,int PosX,int PosY);
void draw(SDL_Surface* Screen);
void setComands(std:: vector <std::string> * str_Vec);
};




class Scene {
protected:
   unsigned char * NScene;
   bool * running;
 //  Sistem System;
 //  Font fuente;
   Audio * myaudio;
public: 
  virtual void update(SDL_Surface* Screen);
  virtual void updatekey(); 
  virtual void dispose(); 

};

class Map_Scene: public Scene {
private:
 int SCREEN_SIZE_X, SCREEN_SIZE_Y;
 View view;    
 Chara player;
 Chara npc;
 Faceset alexface;
 stMap Map;
public: 
   void init(Audio * audio,int SCREEN_X, int SCREEN_Y,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void mapnpc();
   void dispose();
}; 
class Title_Scene: public Scene {
private:  
   Sprite title;
   Window_Select menu; 
   std:: vector <std::string> str_Vector;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();
   void dispose();      
};
class Batle_Scene: public Scene {
private:  
   int state;
   Sprite title;
   Player jugador;
   Enemy enemigo;
   Animacion Myanim;
   Window_Base window;
   Window_Select menu; 
   Window_Select menu_os; 
   std:: vector <std::string> str_Vector;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void set_stats();
   void updatekey();
   void atack(SDL_Surface* Screen); 
   void atacked();
   void dispose();      
};
class Main_Menu_Scene: public Scene {
private:  
   Window_Base players;
   Window_Base gold;
   Window_Select menu;
   Window_Select menu_exit;  
   std:: vector <std::string> str_Vector;
   std:: vector <std::string> str_Vector_2;
   void action();
   void action2();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey(); 
   void dispose();      
};
class Objects_Menu_Scene: public Scene {
private:  
   Window_Base descripcion;
   Window_Select menu; 
   std:: vector <std::string> str_Vector;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};

class Save_Load_Menu_Scene: public Scene {
private:  
   Window_Base descripcion;
   Window_Base Save_pos_1;
   Window_Base Save_pos_2;
   Window_Base Save_pos_3;
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};
class Stats_Menu_Scene: public Scene {
private:  
   Window_Base Status; 
   Window_Base Status_vit; 
   Window_Base Profesion; 
   Window_Base Aramas; 
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};
class Euip_Menu_Scene: public Scene {
private:  
   Window_Base descripcion;
   Window_Base stats;
   Window_Select Armas;
   Window_Select menu; 
   std:: vector <std::string> str_Vector;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();
   void dispose();       
};
class Skills_Menu_Scene: public Scene {
private:  
   Window_Base descripcion;
   Window_Base descripcion2;
   Window_Select menu; 
   std:: vector <std::string> str_Vector;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};
class GO_Scene: public Scene {
private:  
   Sprite title;
   void action();
public: 
   void init(Audio * theaudio, bool * run,unsigned char * TheScene);
   void update(SDL_Surface* Screen); 
   void updatekey();
   void dispose();       
};

#endif 
