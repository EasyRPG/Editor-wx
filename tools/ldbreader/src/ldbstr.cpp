#include "LDB.h"
void Magicblock::clear()
{
 Level=0;//=0x01,
 Spell_ID=0;//=0x02
}
void stcHero::clear()
{
strName="";//=0x01,
strClass="";//=0x02,
strGraphicfile="";//=0x03,
intGraphicindex=0;//=0x04,
intTransparent=0;//=0x05,
intStartlevel=0;//=0x07,
intMaxlevel=0;//=0x08,
intCrithit=0;//=0x09,
intHitchance=0;//=0x0A,
strFacegraphic="";//=0x0F,
intFaceindex=0;//=0x10,
blDualwield=0;//=0x15,
blFixedequipment=0;//=0x16,
blAI=0;//=0x17,
blHighdefense=0;//=0x18,
//Statisticscurves=0x1F,arraglode16bitescon5datos
vc_sh_Hp.clear();
vc_sh_Mp.clear();
vc_sh_Attack.clear();
vc_sh_Defense.clear();
vc_sh_Mind.clear();
vc_sh_Agility.clear();

intEXPBaseline=0;//=0x29,
intEXPAdditional=0;//=0x2A,
intEXPCorrection=0;//=0x2B,
intprofesion=0;//0x39--2003
Animatedbattle=0;//0x3E--2003
//Startequip=0x33,arraglode16bitescon5datos
  sh_Weapon=0;//
  sh_Shield=0;//
  sh_Armor=0;//
  sh_Head=0;//
  sh_Accessory=0;//


skills.clear();//Skills=0x3F,
blRenameMagic=0;//=0x42,
strMagicname="";//=0x43,
intCondlength=0;//=0x47,
//arraydeunbyte
vc_ch_Condeffects.clear();
intAttriblength=0;//=0x49,
//array de un byte
vc_ch_Attribeffects.clear();
//Combat Comand // =0x50 //4 byte one byte dimension array of 6 
}

void stcSound_effect::clear(){
Name_of_Sound_effect="";
 Volume=100; 
 Tempo=100; 
 Balance=50;
}

void stcSkill::clear()
{
strName="";//0x01,
strDescription="";//0x02,
strtext="";//0x03,
strtextline="";//0x04,
intFailure=0;//0x07,
intSpelltype=0;//0x08,
intMpconType=0;//0x09    //2003
intConsumtion=0;//0x0A  //2003
intCost=0;//0x0B,
intRange=0;//0x0C,
intSwitch=0;//0x0D,
intBattleanimation=0;//0x0E,
blFieldusage=0;//0x12,
blCombatusage=0;//0x13,
blChangeofstatus=0;//0x14 //-2003
intStrengtheffect=0;//0x15,
intMindeffect=0;//0x16,
intVariance=0;//0x17,
intBasevalue=0;//0x18,
intSuccessrate=0;//0x19,
blAffectHP=0;//0x1F,
blAffectMP=0;//0x20,
blAffectAttack=0;//0x21,
blAffectDefense=0;//0x22,
blAffectMind=0;//0x23,
blAffectAgility=0;//0x24,
blAbsorbdamage=0;//0x25,
blIgnoredefense=0;//0x26,
intConditionslength=0;//0x29,
vc_ch_Condeffects.clear();//0x2A,
intAttributeslength=0;//0x2B,
vc_ch_Attribeffects.clear(); //0x2C,

blAffectresistance=0;//0x2D       
intwhenusinganimation=0; //0x31 --2003
//CBA data  //0x32
}

void stcItem::clear()
{
std::string Name="";//0x01,
std::string Description="";//0x02,
Type=0;//0x03,
Cost=0;//0x05,
Uses=0;//0x06,
Attack=0;//0x0B,
Defense=0;//0x0C,
Mind=0;//0x0D,
Speed=0;//0x0E,
Equip=0;//0x0F,
MPcost=0;//0x10,
Chancetohit=0;//0x11,
Criticalhit=0;//0x12,
Battleanimation=0;//0x14,
Preemptiveattack=0;//0x15,
Doubleattack=0;//0x16,
Attackallenemies=0;//0x17,
Ignoreevasion=0;//0x18,
Preventcriticalhits=0;//0x19,
Raiseevasion=0;//0x1A,
MPusecutinhalf=0;//0x1B,
Noterraindamage=0;//0x1C,
Is_equip=0;//0x1D//2003
Healsparty=0;//0x1F,
HPrecovery=0;//0x20,
HPrecoveryvalue=0;//0x21,
MPrecovery=0;//0x22,
MPrecoveryvalue=0;//0x23,
Useonfieldonly=0;//0x25,
Onlyondeadheros=0;//0x26,
MaxHPmodify=0;//0x29,
MaxMPmodify=0;//0x2A,
Attackmodify=0;//0x2B,
Defensemodify=0;//0x2C,
Mindmodify=0;//0x2D,
Speedmodify=0;//0x2E,
Usagemessage=0;//0x33,
Efectiveastool=0;//0x35//2003
Switchtoturnon=0;//0x37,
Useonfield=0;//0x39,
Useinbattle=0;//0x3A,
Heroeslength=0;//0x3D,
vc_ch_Heroescanuse.clear();
Conditionslength=0;//0x3F,
vc_ch_Condeffects.clear();
Attributeslength=0;//0x41,
vc_ch_Attribeffects.clear();
Chancetochange=0;//0x43
Whenuseanimation=0;//0x45
ItemtoSkill=0;//0x47
EquitoVoc=0;//0x48
}
void stcEnemy_Action::clear()
{  		
  intAction=0;//=0x01,	
  intAction_data=0;//	=0x02,
  intSkill_ID=0;//=0x03,	
  intMonster_ID=0;//=0x04,	
  intCondition=0;//	=0x05,
  intLower_limit=0;//=0x06,	
  intUpper_limit=0;//	=0x07,
  intPriority=0;//=0x0D
}

void stcEnemy::clear()
{
   strName="";	// = 0x01,
   strGraphicfile="";	//= 0x02,
  intHuealteration=0;	//= 0x03,
  intMaxHP=0;	//= 0x04,
  intMaxMP=0;	//= 0x05,
  intAttack=0;	//= 0x06,
  intDefense=0;	//= 0x07,
  intMind=0;	//= 0x08,
  intSpeed=0;	//= 0x09,
  blTranslucentgraphic=0;	//= 0x0A,
  intExperience=0;	//= 0x0B,
  intGold=0;	//= 0x0C,
  intSpoilsitemID=0;	//= 0x0D,
  intSpoilschance=0;	//= 0x0E,
  blCanusecriticalhits=0;	//= 0x15,
  intCriticalhitchance=0;	//= 0x16,
  blUsuallymiss=0;	//= 0x1A,
  blAirborne=0;	//= 0x1C,
  intConditionslength=0;	//= 0x1F,
 vc_ch_Condeffects.clear(); //= 0x20, arreglo de un byte //una dimencion
  inyAttributeslength=0;//= 0x21,
  vc_ch_Attribeffects.clear();//= 0x22, arreglo de un byte //una dimencion
  //Actionslist= 0x2A
}

void stcEnemy_group_data::clear()
{ 		
	int	Enemy_ID=0;//=0x01,
	int	X_position=0;//=0x02,
	int	Y_position=0;//=0x03
}
void stcEnemy_group_condition::clear()
{ 		
    Condition_flags=0;//=0x01,
    Switch_A=0;//=0x02,
    Turn_number_A=0;//=0x06,
	Lower_limit=0;//=0x0B,
	Upper_limit=0;//=0x0C,
}

void stcEnemy_group_event_page::clear()
{ 		
    conditions.clear();//	Page_conditions=0x02,
	Event_length=0;//=0x0B,
//	Event=0x0C// como en eventos
}

void stcEnemy_group::clear()
{
 strName="";// =0x01,
 Enemy_data.clear();//data=0x02,
 intTerrainlength=0;		//=0x04,
 vc_ch_Terraindata.clear();		//=0x05,
 vecPartyMonsterevent.clear();
}
void stcTerrain::clear()
{
strName="";	//=0x01,
intDamageontravel=0;	//=0x02,
intEncounterate=0;	//=0x03,
strBattlebackground="";	//=0x04,
blSkiffmaypass=0;	//=0x05,
blBoatmaypass=0;	//=0x06,
blAirshipmaypass=0;	//=0x07,
blAirshipmayland=0;	//=0x09,
intHeroopacity=0;	//=0x0B
}

void stcAttribute::clear()
{ 
strName="";//=0x01,
intType=0;//=0x02,
intA_damage=0;//=0x0B,
intB_damage=0;//=0x0C,
intC_damage=0;//=0x0F,
intD_damage=0;//e=0x0F,
intE_damage=0;//=0x0F
}

void stcState::clear()
{  
strName="";//=0x01,
intLength=0;//=0x02,
intColor=0;//=0x03,
intPriority=0;//=0x04,
intLimitation=0;//=0x05,
intA_chance=0;//=0x0B,
intB_chance=0;//=0x0C,
intC_chance=0;//=0x0D,
intD_chance=0;//=0x0E,
intE_chance=0;//=0x0F,
intTurnsforhealing=0;//=0x15,
intHealperturn=0;//=0x16,
intHealonshock=0;//=0x17,
intTypeofincrease=0;//0x1E-2003
blHalveAttack=0;//=0x1F,
blHalveDefense=0;//=0x20,
blHalveMind=0;//=0x21,
blHalveAgility=0;//=0x22,
intHitratechange=0;//=0x23,
blAvoidatack=0;//0x24--2003
blmagicreflection=0;//0x25--2003
blItemequip=0;//0x26--2003
intAnime=0;//0x27--2003
blPrevent_skill_use=0;//=0x29,
intMinimum_skill_level=0;//=0x2A,
blPreventmagicuse=0;//=0x2B,
intMinimummindlevel=0;//=0x2C,
intmpdecreasetype=0;//0x2D-2003
inthpdecreasetype=0;//0x2E-2003
strAllyenterstate="";//=0x33,
strEnemyentersstate="";//=0x34,
strAlreadyinstate="";//=0x35,
strAffectedbystate="";//=0x36,
strStatusrecovered="";//=0x37,
intHPloss=0;//=0x3D,
intHPlossvalue=0;//=0x3E,
intHPmaploss=0;//=0x3F,
intHPmapsteps=0;//=0x40,
intMPloss=0;//=0x41,
intMPlossvalue=0;//=0x42,
intMPmaploss=0;//=0x43,
intMPmapsteps=0;//=0x44
}

void stcAnimationTiming::clear()
{	
		Frame=0;//=0x01,
		Sound_effect.clear();//=0x02,
		Flash_effect=0;//=0x03,
		Green_component=0;//=0x05,
		Blue_component=0;//=0x06,
		Flash_power=0;//=0x07
}

void stcAnimationCelldata::clear()
{	
		 Cell_source=0;//=0x02,
		 X_location=0;//=0x03,
		 Y_location=0;//=0x04,
		 Magnification=0;//=0x05,
		 Red_component=0;//=0x06,
		 Green_component=0;//=0x07,
		 Blue_component=0;//=0x08,
		 Chroma_component=0;//=0x09,
		 Alpha=0;//=0x0A,
}
void stcAnimationCell::clear()
{
	Cell_data.clear();
}

void stcAnimated_battle::clear()
{
 strName="";//=0x01,
 strAnimation_file="";//=0x02,
 vecAnimationTiming.clear();//Timing_data=0x06,
 intApply_to=0;//0x09,
  intY_coordinate_line=0;//=0x0A,
 //Framedata=0x0C
}
void stcChipSet::clear()
{
 strName="";//=0x01,
 strGraphic="";//=0x02,
 vc_sh_Lower_tile_terrain.clear();// Lower_tile_terrain=0x03,
 vc_ch_Lower_tile_passable.clear();// Lower_tile_passable=0x04,
 vc_ch_Upper_tile_passable.clear();// Upper_tile_passable=0x05,
 Water_animation=0;//=0x0B,
 Animation_speed=0;//=0x0C
}

void stcEvent::clear()
{   	
  std::string strName;//=0x01,
   intNameActivation_condition=0;//=0x0B,
   blNameActivate_on_switch=0;//=0x0C,
   intNameSwitch_ID=0;//=0x0D,
   intNameScript_length=0;//=0x15,

}

void stcFight_anim::clear()//array bidimencional
{   
 strName="";//=0x01, 
 strFilename="";//=0x02, 
 intPosition=0;//=0x03,  
 blExtended_expanded=0;//=0x04,  	
 intID_Expansion_animated_combat_ID=0;//=0x05
}
void stcProfetion::clear()//array bidimencional
{
     strName="";// =0x01,
      TwoWeapon=0;//=0x15,
      fixed_equipment=0;// =0x16,
      AI_forced_action=0;// =0x17,
      strong_defense=0;// =0x18,
 	 //Each_level =0x1F, 2 bytes integer array
 	  Experience_curve_basic_values=0;// =0x29,
      Experience_curve_increase_degree=0;// =0x2A,
 	  Experience_curve_correction_value=0;//=0x2B,
 	  Animated_battle=0;//	=0x3E,
 	 //Special_skills_level=0x3F, misma estructura que heroe
 	  Effectiveness_state_number=0;// =0x47,
 	 //Effectiveness_state_data =0x48,  //1 byte one dimention array
      Effectiveness_Attribute_number=0;// =0x49,
 	 //Effectiveness_Attribute_data =0x4A,/1 byte one dimention array
     //Combat_Command=0x50 4 bytes one dimention array
}
