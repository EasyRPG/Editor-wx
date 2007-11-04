#ifndef SCENE_H_
#define SCENE_H_
typedef struct menucomand
{
	int des1;
	int des2;
	int selected_moster;
} MC;
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
std:: vector <Sprite> Vtext_Sprite;
std:: vector <int> V_Sprite;//appuntadores a sprites
Sprite text;
char stringBuffer[255];
int falla;
bool disposing;
public: 
bool visible;
void dispose();
void init(int SizeX,int SizeY,int PosX,int PosY);
void draw(SDL_Surface* Screen);
void add_text(char * ctext, int x, int y);
void add_sprite(Sprite * the_sprite, int x, int y);
};

class Window_Select   {
protected:
Sistem System;
Sprite tapiz;
Sprite cursor;
Font fuente;
Menu_Easy menu;
std:: vector <Sprite> Vtext_Sprite;
int pos_X,pos_Y;
int Init_text_X;
int Size_X,Size_Y,Size_of_Block;
int Comand_X,Comand_Y;
std:: vector <std::string> * My_vector;
std:: vector <Sprite> My_Sprite;
bool disposing;
Sprite text;

public: 
bool visible;
bool on_use;
void updatekey(); 
int getindexX();
int getindexY();
void restarmenu();
bool desition();
void dispose();
void init(Audio * theaudio, bool * run,int ComandX,int ComandY,int SizeX,int SizeY,int PosX,int PosY);
void draw(SDL_Surface* Screen);
void add_text(char * ctext, int x, int y);
void set_posx_text(int x);
void setComands(std:: vector <std::string> * str_Vec);
};


class Window_Player_Select   {
protected:
Sistem System;
Sprite tapiz;
Sprite cursor;
Font fuente;
Menu_Easy menu;
std:: vector <Sprite> Vtext_Sprite;
int pos_X,pos_Y;
int Size_X,Size_Y,Size_of_Block;
int Comand_X,Comand_Y;
std:: vector <int> V_Sprite;//appuntadores a sprites
int Cur_pos_X,Cur_pos_Y;
int Moves_cursorY;
bool disposing;
Sprite text;

public: 
bool visible;
bool visible_window;
void updatekey(); 
int getindexX();
int getindexY();
void restarmenu();
bool desition();
void dispose();
void init_curXY(int x,int y); 
void init(Audio * theaudio, bool * run,int ComandX,int ComandY,int SizeX,int SizeY,int PosX,int PosY,int curX,int curY);
void draw(SDL_Surface* Screen);
void add_text(char * ctext, int x, int y);
void add_sprite(Sprite * the_sprite, int x, int y);
void set_curY(int y);
};



class Scene {
protected:
   unsigned char * NScene;
   bool * running;
   Audio * myaudio;
   Player_Team * myteam;
   int retardo;
public: 
  virtual void update(SDL_Surface* Screen);
  virtual void updatekey(); 
  virtual void dispose(); 

};

class Map_Scene: public Scene {
private:
 int SCREEN_SIZE_X, SCREEN_SIZE_Y;
  
 Chara * player;
 Chara npc;
 Faceset alexface;
 Sprite red;
 Font fuente;
 bool moving;
 int to_move;
 stMap Map;
  char stringBuffer[255];
public: 
   void init(Audio * audio,int SCREEN_X, int SCREEN_Y,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey(); 
   void slow_move(); 
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
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void init_party();
   void updatekey();
   void dispose();      
};
class Batle_Scene: public Scene {
private:  
   bool * the_run;
   int state;
   int Nmenu_used;
   int turnosp;
   int player_in_turn;
   int moster_in_turn;   
   Sprite title;
   Window_Base Window_text;
   Window_Player_Select window;
   Window_Select menu; 
   Window_Select menu_os; 
   Window_Select moster_select; 
   std:: vector <std::string> str_Vector;
   std:: vector <std::string> str_Vector2;
   std:: vector <MC> Comands;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey();
   void atack(SDL_Surface* Screen,int nperso,int enemy);
   void update_window_stats();
   void update_window_mosterselect();
   void action_mosterselect();
   void windowtext_showdamange(bool type,int atak,int ataked,int damange);
   void Give_turn();
   void win();
   void lose();
   void atacked(int enemy);
   void dispose();      
};
class Main_Menu_Scene: public Scene {
private:  
   Window_Player_Select players;
   Window_Base gold;
   Window_Select menu;
   Window_Select menu_exit;  
   std:: vector <std::string> str_Vector;
   std:: vector <std::string> str_Vector_2;
   void action();
   void action2();
   void action3();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
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
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};
class Item_use_scene: public Scene {
private:  
   Window_Player_Select players;
   Window_Base itemwin;
   Window_Base itemwin2;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
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
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
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
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};
class Euip_Menu_Scene: public Scene {
private:  
  bool * therun;
   Window_Base descripcion;
   Window_Base stats;
   Window_Select Armas;
   Window_Select menu; 
   std:: vector <std::string> str_Vector;
    std:: vector <std::string> str_Vector2;
   void action();
public: 
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey();
   void update_1_menu();
   void update_2_menu();
   void action2();
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
   void init(Audio * myaudio,  bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey();  
   void dispose();     
};
class GO_Scene: public Scene {
private:  
   Sprite title;
   void action();
public: 
   void init(Audio * theaudio, bool * run,unsigned char * TheScene,Player_Team * TheTeam);
   void update(SDL_Surface* Screen); 
   void updatekey();
   void dispose();       
};

#endif 
