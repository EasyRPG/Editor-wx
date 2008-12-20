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
#include "skill.h"
#include "item.h"
#include "Enemy.h"#include "Player.h"



Item* Player::get_Weapon()
{
   return (&Weapon);
}
Item* Player::get_Shield()
{
   return (&Shield);
}
Item* Player::get_Armor()
{
   return (&Armor);
}
Item* Player::get_Helmet()
{
   return (&Helmet);
}
Item* Player::get_Accessory()
{
   return (&Accessory);
}


void Player::set_Weapon(Item The_Weapon)
{
   Weapon=The_Weapon;
}
void Player::set_Shield(Item The_Shield)
{
   Shield=The_Shield;
}

void Player::set_Armor(Item The_Armor)
{
   Armor=The_Armor;
}

void Player::set_Helmet(Item The_Helmet)
{
   Helmet=The_Helmet;
}
void Player::set_Accessory(Item The_Accessory)
{
   Accessory=The_Accessory;
}

unsigned char* Player::get_Weapon_type()
{
   return (&Weapon_type);
}
unsigned char* Player::get_Shield_type()
{
   return (&Shield_type);
}
unsigned char* Player::get_Armor_type()
{
   return (&Armor_type);
}
unsigned char* Player::get_Helmet_type()
{
   return (&Helmet_type);
}
unsigned char* Player::get_Accessory_type()
{
   return (&Accessory_type);
}

void Player::set_Weapon_type(unsigned char The_Weapon_type)
{
   Weapon_type=The_Weapon_type;
}
void Player::set_Shield_type(unsigned char The_Shield_type)
{
   Shield_type=The_Shield_type;
}
void Player::set_Armor_type(unsigned char The_Armor_type)
{
   Armor_type=The_Armor_type;
}
void Player::set_Helmet_type(unsigned char The_Helmet_type)
{
   Helmet_type=The_Helmet_type;
}
void Player::set_Accessory_type(unsigned char The_Accessory_type)
{
   Accessory_type=The_Accessory_type;
}
void Player::set_HP(int The_HP)
{
   HP=The_HP;
}
void Player::set_MaxHP(int The_MaxHP)
{
   MaxHP=The_MaxHP;
}
void Player::set_MP(int The_MP)
{
   MP=The_MP;
}
void Player::set_MaxMP(int The_MaxMP)
{
   MaxMP=The_MaxMP;
}

int * Player::get_HP()
{
  return (&HP);
}
int * Player::get_MaxHP()
{
  return (&MaxHP);
}
int* Player::get_MP()
{
   return (&MP);
}
int* Player::get_MaxMP()
{
   return (&MaxMP);
}

void Player::set_Heal(int The_Heal)
{
   Heal=The_Heal;
}
void Player::set_Attack(int The_Attack)
{
   Attack=The_Attack;
}
void Player::set_Defense(int The_Defense)
{
   Defense=The_Defense;
}
void Player::set_Speed(int The_Speed)
{
   Speed=The_Speed;
}
void Player::set_Spirit(int The_Spirit)
{
   Spirit=The_Spirit;
}
void Player::set_Level(int The_Level)
{
   Level=The_Level;
}
void Player::set_Exp(int The_Exp)
{
   Exp=The_Exp;
}
void Player::set_MaxExp(int The_MaxExp)
{
   MaxExp=The_MaxExp;
}

int * Player::get_Heal()
{
  return (&Heal);
}
int * Player::get_Attack()
{
  return (&Attack);
}
int* Player::get_Defense()
{
   return (&Defense);
}
int* Player::get_Speed()
{
   return (&Speed);
}

int * Player::get_Spirit()
{
  return (&Spirit);
}
int * Player::get_Level()
{
  return (&Level);
}
int* Player::get_Exp()
{
   return (&Exp);
}
int* Player::get_MaxExp()
{
   return (&MaxExp);
}


void Player::set_job(const char * name)
{
   titulo=name;
}
const char * Player::get_job()
{
   return(titulo);
}
void Player::set_name(const char * name)
{
   nombre=name;
}
const char * Player::get_name()
{
   return(nombre);
}
void Player::set_faceset(Faceset theFaceset)
{
   Face=theFaceset;
}
Faceset * Player::get_faceset()
{
   return (& Face);
}
void Player::set_chara(Chara thecharset)
{
   charset=thecharset;
}
Chara * Player::get_chara()
{
   return (& charset);
}
void Player::add_skill(Skill Myskill)
{
      Skills.push_back(Myskill);
}

const char * Player::get_skill_name(int num)
{
   return (((Skills.at(num))).get_name());
}
int * Player::get_skill_mp_price(int num)
{
   return (((Skills.at(num))).get_mp_price());
}
int * Player::get_skill_damange(int num)
{
   return (((Skills.at(num))).get_damange());
}
int * Player::get_skill_level_req(int num)
{
   return (((Skills.at(num))).get_level_req());
}

Animacion * Player::get_Weapon_Anim()
{
   return (Weapon.get_anim());
}

Animacion * Player::get_skill_get_anim(int num)
{
   return (((Skills.at(num))).get_anim());
}
int Player::get_skill_size()
{
     return (Skills.size());
}

void Player_Team::clear_team()
{
      Players.clear();
}
void Player_Team::clear_obj()
{
      Items.clear();
}
void Player_Team::clear_enemy()
{
      Enemys.clear();
}
void Player_Team::add_enemy(Enemy Myplayer)
{
      Enemys.push_back(Myplayer);
}

void Player_Team::add_player(Player Myplayer)
{
      Players.push_back(Myplayer);
}
Item Player_Team::get_item(int num)
{
return (Items.at(num));
}
void Player_Team::add_item(Item Myitem)
{
unsigned int i;
int the_id;
the_id=Myitem.id;
     for (i=0;i<Items.size();i++)
    { if (the_id ==(Items.at(i)).id)
       break;
    }

    if (i<Items.size())//lo encontro
    {
    *((Items.at(i)).get_NOI())= *((Items.at(i)).get_NOI())+*Myitem.get_NOI();
    }
    else
      {Items.push_back(Myitem);}
}



int Player_Team::get_size()
{
     return (Players.size());
}
Chara * Player_Team::get_chara(int num)
{
     return (((Players.at(num))).get_chara());
}
Faceset * Player_Team::get_faceset(int num)
{
     return (((Players.at(num))).get_faceset());
}
const char * Player_Team::get_name(int num)
{
   return (((Players.at(num))).get_name());
}
const char * Player_Team::get_job(int num)
{
   return (((Players.at(num))).get_job());
}
int * Player_Team::get_HP(int num)
{
  return (((Players.at(num))).get_HP());
}
int * Player_Team::get_MaxHP(int num)
{
  return (((Players.at(num))).get_MaxHP());
}
int* Player_Team::get_MP(int num)
{
   return (((Players.at(num))).get_MP());
}
int* Player_Team::get_MaxMP(int num)
{
   return (((Players.at(num))).get_MaxMP());
}

int * Player_Team::get_Heal(int num)
{
  return (((Players.at(num))).get_Heal());
}
int * Player_Team::get_Attack(int num)
{
  return (((Players.at(num))).get_Attack());
}
int* Player_Team::get_Defense(int num)
{
  return (((Players.at(num))).get_Defense());
}
int* Player_Team::get_Speed(int num)
{
   return (((Players.at(num))).get_Speed());
}

int * Player_Team::get_Spirit(int num)
{
  return (((Players.at(num))).get_Spirit());
}
int * Player_Team::get_Level(int num)
{
  return (((Players.at(num))).get_Level());
}
int* Player_Team::get_Exp(int num)
{
  return (((Players.at(num))).get_Exp());
}
int* Player_Team::get_MaxExp(int num)
{
  return (((Players.at(num))).get_MaxExp());
}

int Player_Team::get_num_items()
{
     return (Items.size());
}
void Player_Team::erase_item(int the_item)
{  vector<Item>::iterator the_iterator;
the_iterator=Items.begin();
int i;
for(i=0;i<the_item;i++)
{the_iterator++;
}
Items.erase( the_iterator);
}
int* Player_Team::get_NOI(int num)
{
  return (((Items.at(num))).get_NOI());
}
unsigned char * Player_Team::get_type(int num)
{
  return (((Items.at(num))).get_type());
}
const char * Player_Team::get_item_name(int num)
{
   return (((Items.at(num))).get_name());
}
Animacion * Player_Team::get_item_anim(int num)
{
   return (((Items.at(num))).get_anim());
}
void Player_Team::set_Gold(int The_Gold)
{
   Gold=The_Gold;
}
int* Player_Team::get_Gold()
{
   return (&Gold);
}
int Player_Team::get_skill_size(int num)
{
    return (((Players.at(num))).get_skill_size());
}
const char * Player_Team::get_skill_name(int nump,int num)
{
   return (((Players.at(nump))).get_skill_name(num));
}
int * Player_Team::get_skill_mp_price(int nump,int num)
{
    return (((Players.at(nump))).get_skill_mp_price(num));
}
int * Player_Team::get_skill_damange(int nump,int num)
{
   return (((Players.at(nump))).get_skill_damange(num));
}
int * Player_Team::get_skill_level_req(int nump,int num)
{
   return (((Players.at(nump))).get_skill_level_req(num));
}

Animacion * Player_Team::get_skill_get_anim(int nump,int num)
{
    return (((Players.at(nump))).get_skill_get_anim(num));
}
Animacion * Player_Team::get_Weapon_Anim(int nump)
{
    return (((Players.at(nump))).get_Weapon_Anim());
}





Item* Player_Team::get_Weapon(int nump)
{
   return ((Players.at(nump)).get_Weapon());
}
Item* Player_Team::get_Shield(int nump)
{
    return ((Players.at(nump)).get_Shield());
}
Item* Player_Team::get_Armor(int nump)
{
   return ((Players.at(nump)).get_Armor());
}
Item* Player_Team::get_Helmet(int nump)
{
    return ((Players.at(nump)).get_Helmet());
}
Item* Player_Team::get_Accessory(int nump)
{
   return ((Players.at(nump)).get_Accessory());
}


void Player_Team::set_Weapon(int nump,Item The_Weapon)
{
  (Players.at(nump)).set_Weapon(The_Weapon);
}
void Player_Team::set_Shield(int nump,Item The_Shield)
{
    (Players.at(nump)).set_Shield(The_Shield);
}
void Player_Team::set_Armor(int nump,Item The_Armor)
{
   (Players.at(nump)).set_Armor(The_Armor);
}
void Player_Team::set_Helmet(int nump,Item The_Helmet)
{
    (Players.at(nump)).set_Helmet(The_Helmet);
}
void Player_Team::set_Accessory(int nump,Item The_Accessory)
{
    (Players.at(nump)).set_Accessory(The_Accessory);
}


unsigned char* Player_Team::get_Weapon_type(int nump)
{
   return ( (Players.at(nump)).get_Weapon_type());
}
unsigned char* Player_Team::get_Shield_type(int nump)
{
   return ( (Players.at(nump)).get_Shield_type());
}
unsigned char* Player_Team::get_Armor_type(int nump)
{
   return ( (Players.at(nump)).get_Armor_type());
}
unsigned char* Player_Team::get_Helmet_type(int nump)
{
   return ( (Players.at(nump)).get_Helmet_type());
}
unsigned char* Player_Team::get_Accessory_type(int nump)
{
   return ( (Players.at(nump)).get_Accessory_type());
}

void Player_Team::set_Weapon_type(int nump, unsigned char The_Weapon_type)
{
    (Players.at(nump)).set_Weapon_type(The_Weapon_type);
}
void Player_Team::set_Shield_type(int nump, unsigned char The_Shield_type)
{
    (Players.at(nump)).set_Shield_type(The_Shield_type);
}
void Player_Team::set_Armor_type(int nump, unsigned char The_Armor_type)
{
    (Players.at(nump)).set_Armor_type(The_Armor_type);
}
void Player_Team::set_Helmet_type(int nump, unsigned char The_Helmet_type)
{
    (Players.at(nump)).set_Helmet_type(The_Helmet_type);
}
void Player_Team::set_Accessory_type(int nump, unsigned char The_Accessory_type)
{
    (Players.at(nump)).set_Accessory_type(The_Accessory_type);
}
