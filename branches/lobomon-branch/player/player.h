/* player.h, EasyRPG player Player class declaration file.
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

#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct view
{
	int x;
	int y;
} View;
class Player {
     
protected: 
      Chara charset;
      Faceset Face;
      int HP;
      int MaxHP;
      int MP;
      int MaxMP;
      int Heal;
      int Attack;
      int Defense;
      int Speed;
      int Spirit;
      int Level;
      int Exp;
      int MaxExp;
      const char * nombre;
      const char * titulo;    
      Item Weapon;
      Item Shield;
      Item Armor;
      Item Helmet;
      Item Accessory;
      unsigned char Weapon_type;//256 tipos nada mas
      unsigned char Shield_type;
      unsigned char Armor_type;
      unsigned char Helmet_type;
      unsigned char Accessory_type;

public: 

      
        
     // Batler Battler;
     std:: vector <Skill> Skills;

     Item* get_Weapon();
     Item* get_Shield();
     Item* get_Armor();
     Item* get_Helmet();
     Item* get_Accessory();
     void set_Weapon(Item The_Weapon);
     void set_Shield(Item The_Shield);
     void set_Armor(Item The_Armor);
     void set_Helmet(Item The_Helmet);
     void set_Accessory(Item The_Accessory);
     Animacion * get_Weapon_Anim();
     unsigned char* get_Weapon_type();
     unsigned char* get_Shield_type();
     unsigned char* get_Armor_type();
     unsigned char* get_Helmet_type();
     unsigned char* get_Accessory_type();

     void set_Weapon_type(unsigned char The_Weapon_type);
     void set_Shield_type(unsigned char The_Shield_type);
     void set_Armor_type(unsigned char The_Armor_type);
     void set_Helmet_type(unsigned char The_Helmet_type);    
     void set_Accessory_type(unsigned char The_Accessory_type);

     void set_HP(int The_HP);
     void set_MaxHP(int The_MaxHP);
     void set_MP(int The_MP);
     void set_MaxMP(int The_MaxMP);
     
     void set_Heal(int The_Heal);
     void set_Attack(int The_Attack);
     void set_Defense(int The_Defense);
     void set_Speed(int The_Speed);
     void set_Spirit(int The_Spirit);
     void set_Level(int The_Level);
     void set_Exp(int The_Exp);
     void set_MaxExp(int The_MaxExp);

     void set_name(const char * name);
     void set_job(const char * name);
     void set_chara(Chara thecharset);
     void set_faceset(Faceset theFaceset);
     
     int * get_HP();
     int * get_MaxHP();
     int * get_MP();
     int * get_MaxMP();
     int * get_Heal();
     int * get_Attack();
     int * get_Defense();
     int * get_Speed();
     int * get_Spirit();
     int * get_Level();
     int * get_Exp();
     int * get_MaxExp();

     
     Faceset * get_faceset();
     Chara   * get_chara();
     const char * get_name();
     const char * get_job();
     void add_skill(Skill Myskill);
     int get_skill_size();
     const char * get_skill_name(int num);
     int * get_skill_mp_price(int num);
     int * get_skill_damange(int num);
     int * get_skill_level_req(int num);
     Animacion * get_skill_get_anim(int num);    
     
         
};
class Player_Team {
std:: vector <Player> Players;
std:: vector <Item> Items;
int Gold;
public: 
std:: vector <Enemy> Enemys;
void clear_enemy();
void add_enemy(Enemy Myplayer);

View view;  
int select;
int get_size();
void clear_team();
void clear_obj();
void add_player(Player Myplayer);
void set_Gold(int The_Gold);
int* get_Gold();

Chara * get_chara(int num);
Faceset * get_faceset(int num);
const char * get_name(int num);
const char * get_job(int num);

int * get_MP(int num);
int * get_MaxMP(int num);
int * get_HP(int num);
int * get_MaxHP(int num);

int * get_Heal(int num);
int * get_Attack(int num);
int * get_Defense(int num);
int * get_Speed(int num);
int * get_Spirit(int num);
int * get_Level(int num);
int * get_Exp(int num);
int * get_MaxExp(int num);

void erase_item(int num);
Item get_item(int num);
int get_num_items();
void add_item(Item Myitem);
int* get_NOI(int num);
unsigned char * get_type(int num);
const char * get_item_name(int num);
Animacion * get_item_anim(int num);

int get_skill_size(int num); 
const char * get_skill_name(int nump,int num); 
int * get_skill_mp_price(int nump,int num); 
int * get_skill_damange(int nump,int num); 
int * get_skill_level_req(int nump,int num); 
Animacion * get_skill_get_anim(int nump,int num); 


Animacion * get_Weapon_Anim(int num);

Item* get_Weapon(int num);
Item* get_Shield(int num);
Item* get_Armor(int num);
Item* get_Helmet(int num);
Item* get_Accessory(int num);

void set_Weapon(int nump,Item The_Weapon);
void set_Shield(int nump,Item The_Shield);
void set_Armor(int nump,Item The_Armor);
void set_Helmet(int nump,Item The_Helmet);
void set_Accessory(int nump,Item The_Accessory);

unsigned char* get_Weapon_type(int nump);
unsigned char* get_Shield_type(int nump);
unsigned char* get_Armor_type(int nump);
unsigned char* get_Helmet_type(int nump);
unsigned char* get_Accessory_type(int nump);
void set_Weapon_type(int nump, unsigned char The_Weapon_type);
void set_Shield_type(int nump, unsigned char The_Shield_type);
void set_Armor_type(int nump, unsigned char The_Armor_type);
void set_Helmet_type(int nump, unsigned char The_Helmet_type);     
void set_Accessory_type(int nump, unsigned char The_Accessory_type);
};

#endif
